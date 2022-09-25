#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{

}

Clothing::~Clothing()
{

}

string Clothing::getSize() const
{
	return size_;
}

string Clothing::getBrand() const
{
	return brand_;
}

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

string Clothing::displayString() const{
	string priceStr = to_string(price_);
	string qtyStr = to_string(qty_);
	string output = "Category: " + category_ + "\nName: " + name_ + "\nPrice: " + priceStr + "\n Quantity: " + qtyStr + 
									"\nSize: " + size_ + "\nBrand: " + brand_ + "\n";
	return output;
}

void Clothing::dump(ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}