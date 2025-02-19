#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <queue>
#include <map>
#include <string>
#include <set>
#include <vector>
#include "datastore.h"


class MyDataStore: public DataStore {
public:
    MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    User* findUser(std::string& uname);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void addToCart(User* u, Product* p);
    void viewCart(User* u);
    void buyCart(User* u);
    void dump(std::ostream& ofile);
private:
    std::map<std::string, std::set<Product*>> keywordMap_;
    std::set<Product*> products_;
    std::set<User*> users_;
    std::map<User*, std::deque<Product*>> userCarts_;
};
#endif
