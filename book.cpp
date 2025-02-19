#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

std::string Book::getISBN() const
{
    return isbn_;
}

std::string Book::getAuthor() const
{
    return author_;
}

std::set<std::string> Book::keywords() const
{
    // Add words in author name to keywords
    std::set<std::string> nameKeywords = parseStringToWords(name_);
    std::set<std::string> authorKeywords = parseStringToWords(author_);
    std::set<std::string> allKeywords = setUnion(nameKeywords, authorKeywords);
    allKeywords.insert(isbn_);
    return allKeywords;
}

std::string Book::displayString() const
{
    std::string display = name_;
    display += "\nAuthor: " + author_ + " ISBN: " + isbn_;
    display += "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}