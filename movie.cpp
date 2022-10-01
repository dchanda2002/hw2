#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

// Derived Movie class from Product
Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)
{

}

Movie::~Movie()
{

}

// getters for the two new variables
string Movie::getGenre() const
{
	return genre_;
}

string Movie::getRating() const
{
	return rating_;
}

// find the keywords to be used for the Movie object. Include the genre as a keyword.
set<string> Movie::keywords() const
{
	set<string> allKeys;
	allKeys.insert(convToLower(genre_));
	set<string> nameKeys = parseStringToWords(name_);
	set<string>::iterator it;
	for(it = nameKeys.begin(); it != nameKeys.end(); ++it){
		allKeys.insert(*it);
	}
	return allKeys;
}

// Implement displayString() and dump() functions to output information on the Movie instance
string Movie::displayString() const{
	string priceStr = to_string(price_);
	int endIndex = priceStr.find(".") + 3;
	priceStr = priceStr.substr(0, endIndex);

	string qtyStr = to_string(qty_);
	string output = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + priceStr + " " + qtyStr + " left.";
	return output;
}

void Movie::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}