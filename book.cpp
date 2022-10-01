#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

// Derived Book class from Product
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author):
	Product(category, name, price, qty),
	ISBN_(ISBN),
	author_(author)
{

}

Book::~Book()
{

}

// getters for the two new variables
string Book::getISBN() const
{
	return ISBN_;
}

string Book::getAuthor() const
{
	return author_;
}

// find the keywords to be used for the Book object. Find keywords in the author's name as well as the name of the book.
set<string> Book::keywords() const
{
	set<string> allKeys;
	allKeys.insert(ISBN_);
	set<string> nameKeys = parseStringToWords(name_);
	set<string> authorKeys = parseStringToWords(author_);
	set<string>::iterator it;
	for(it = nameKeys.begin(); it != nameKeys.end(); ++it){
		allKeys.insert(*it);
	}
	for(it = authorKeys.begin(); it != authorKeys.end(); ++it){
		allKeys.insert(*it);
	}
	return allKeys;
}

// Implement displayString() and dump() functions to output information on the Book instance
string Book::displayString() const{
	string priceStr = to_string(price_);
	int endIndex = priceStr.find(".") + 3;
	priceStr = priceStr.substr(0, endIndex);
	
	string qtyStr = to_string(qty_);
	string output = name_ + "\n" + "Author: " + author_ + " ISBN: " + ISBN_ + "\n" + priceStr + " " + qtyStr + " left.";
	return output;
}

void Book::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}

