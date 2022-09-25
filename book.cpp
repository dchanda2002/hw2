#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author):
	Product(category, name, price, qty),
	ISBN_(ISBN),
	author_(author)
{

}

Book::~Book()
{

}

string Book::getISBN() const
{
	return ISBN_;
}

string Book::getAuthor() const
{
	return author_;
}

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

string Book::displayString() const{
	string priceStr = to_string(price_);
	string qtyStr = to_string(qty_);
	string output = "Category: " + category_ + "\nName: " + name_ + "\nPrice: " + priceStr + "\n Quantity: " + qtyStr + 
									"\nISBN: " + ISBN_ + "\nAuthor: " + author_ + "\n";
	return output;
}

void Book::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}

