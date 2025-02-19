#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}

std::set<std::string> Movie::keywords() const
{
    // Add words in author name to keywords
    std::set<std::string> allKeywords = parseStringToWords(name_);
    allKeywords.insert(genre_);
    allKeywords.insert(rating_);
    return allKeywords;
}

std::string Movie::displayString() const
{
    std::string display = name_;
    display += "\nGenre: " + genre_ + " Rating: " + rating_;
    display += "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}