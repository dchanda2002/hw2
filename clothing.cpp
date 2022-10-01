#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

// Derived Clothing class from Product
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{

}

Clothing::~Clothing()
{

}

// getters for the two new variables
string Clothing::getSize() const
{
	return size_;
}

string Clothing::getBrand() const
{
	return brand_;
}

// find the keywords to be used for the Clothing object. Find keywords in the brand as well as the name.
set<string> Clothing::keywords() const
{
	set<string> allKeys;
	set<string> nameKeys = parseStringToWords(name_);
	set<string> brandKeys = parseStringToWords(brand_);
	set<string>::iterator it;
	for(it = nameKeys.begin(); it != nameKeys.end(); ++it){
		allKeys.insert(*it);
	}
	for(it = brandKeys.begin(); it != brandKeys.end(); ++it){
		allKeys.insert(*it);
	}
	return allKeys;
}

// Implement displayString() and dump() functions to output information on the Clothing instance
string Clothing::displayString() const{
	string priceStr = to_string(price_);
	int endIndex = priceStr.find(".") + 3;
	priceStr = priceStr.substr(0, endIndex);
	
	string qtyStr = to_string(qty_);
	string output = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + priceStr + " " + qtyStr + " left.";
	return output;
}

void Clothing::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}