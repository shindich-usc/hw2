#include "mydatastore.h"
#include "util.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
    for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete *it;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.insert(p);
    // Update keywords map to include product in all of its keyword mappings
    std::set<std::string> pKeys = p->keywords();
    for (std::set<std::string>::iterator it = pKeys.begin(); it != pKeys.end(); ++it) {
        if (keywordMap_.find(*it) == keywordMap_.end()) {
            keywordMap_[*it] = {p};
        }
        else {
            keywordMap_[*it].insert(p);
        }
    }
}

void MyDataStore::addUser(User* u)
{
    users_.insert(u);
    std::deque<Product*> newCart;
    userCarts_[u] = newCart;
}

User* MyDataStore::findUser(std::string& uname)
{
    for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        if ((*it)->getName() == uname) {return *it;}
    }
    return nullptr;
} 

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    // Get sets corresponding to each keyword, then union / intersect depending on type
    std::set<Product*> searchSet = keywordMap_[terms[0]];
    if (terms.size() > 1) {
        for (size_t i = 1; i < terms.size(); i++) {
            if (type == 0) {
                searchSet = setIntersection(searchSet, keywordMap_[terms[i]]);
            }
            else {
                searchSet = setUnion(searchSet, keywordMap_[terms[i]]);
            }
        }
    }
    // Convert to vector for return
    std::vector<Product*> searchVector;
    for (std::set<Product*>::iterator it = searchSet.begin(); it != searchSet.end(); ++it) {
        searchVector.push_back(*it);
    }
    return searchVector;
}

void MyDataStore::addToCart(User* u, Product* p)
{
    userCarts_[u].push_back(p);
}

void MyDataStore::viewCart(User* u)
{
    std::deque<Product*> userCart = userCarts_[u];
    for (size_t i = 0; i < userCart.size(); i++) {
        cout << i + 1 << ": " << userCart[i]->getName() << endl;
    }
}

void MyDataStore::buyCart(User* u)
{
    for (size_t i = 0; i < userCarts_[u].size(); i++) {
        Product* frontItem = userCarts_[u].front();
        if ((frontItem->getQty() > 0) && (u->getBalance() >= frontItem->getPrice())) {
            userCarts_[u].pop_front();
            frontItem->subtractQty(1);
            u->deductAmount(frontItem->getPrice());
        }
        // If cannot buy item, remove and append to back of queue
        // After iteration is finished, the original order will be retained for remaining items
        else {
            userCarts_[u].pop_front();
            userCarts_[u].push_back(frontItem);
        }
    }
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}