#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const
{
    return brand_;
}

std::set<std::string> Clothing::keywords() const
{
    // Add words in author name to keywords
    std::set<std::string> nameKeywords = parseStringToWords(name_);
    std::set<std::string> brandKeywords = parseStringToWords(brand_);
    std::set<std::string> allKeywords = setUnion(nameKeywords, brandKeywords);
    allKeywords.insert(size_);
    return allKeywords;
}

std::string Clothing::displayString() const
{
    std::string display = name_;
    display += "\nSize: " + size_ + " Brand: " + brand_;
    display += "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

void Clothing::dump(std::ostream& os) const
{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}