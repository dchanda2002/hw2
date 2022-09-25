#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)
{

}

Movie::~Movie()
{

}

string Movie::getGenre() const
{
	return genre_;
}

string Movie::getRating() const
{
	return rating_;
}

set<string> Movie::keywords() const
{
	set<string> allKeys;
	allKeys.insert(genre_);
	set<string> nameKeys = parseStringToWords(name_);
	set<string>::iterator it;
	for(it = nameKeys.begin(); it != nameKeys.end(); ++it){
		allKeys.insert(*it);
	}
	return allKeys;
}

string Movie::displayString() const{
	string priceStr = to_string(price_);
	string qtyStr = to_string(qty_);
	string output = "Category: " + category_ + "\nName: " + name_ + "\nPrice: " + priceStr + "\n Quantity: " + qtyStr + 
									"\nGenre: " + genre_ + "\nRating: " + rating_ + "\n";
	return output;
}

void Movie::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}