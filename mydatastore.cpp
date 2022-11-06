#include <sstream>
#include <iomanip>
#include "mydatastore.h"

using namespace std;

// Create a new destructor that deletes all memory stored on the heap

MyDataStore::~MyDataStore()
{
	map<string, set<Product*>*>::iterator it1;
	for(it1 = productsKeyMap.begin(); it1 != productsKeyMap.end(); ++it1){
		delete it1->second;
	}
	map<User*, vector<Product*>*>::iterator it3;
	for(it3 = usersCartMap.begin(); it3 != usersCartMap.end(); ++it3){
		delete it3->second;
	}
}

// Add the new product inputted as a parameter into the list of items in the database. Adds the product to productList, and 
// then adds the product to the productsKeyMap by finding all of its keywords and adding the product into the list 
// wherever one of its keywords is a key.

void MyDataStore::addProduct(Product* p){
	productList.insert(p);
	set<string> keywordSet = p->keywords();	
	set<string>::iterator it;
	for(it = keywordSet.begin(); it != keywordSet.end(); ++it){
		if(productsKeyMap.find(*it) == productsKeyMap.end()){
			set<Product*>* products = new set<Product*>();
			productsKeyMap[*it] = products;
		}
		productsKeyMap[*it]->insert(p);
	}
}

// Adds a new User object to the database by inputting into the usersCartMap. Uses the name of the user as the string 
// username that will be used as the key to access that user from the map.

void MyDataStore::addUser(User* u){
	vector<Product*>* cart = new vector<Product*>();
	usersCartMap[u] = cart;
	usernameMap[convToLower(u->getName())] = u;
}

// This function performs both the AND and OR searches. type = 1 for OR and type = 0 for AND.
// Takes in a vector of strings, which are the terms that have been searched.
// Iterates through the terms entered and accesses the products that those keywords map to. 
// Performs setUnion() or setIntersection() from util.h file to perform the OR or AND search.
// Returns a vector of Product instances, which are all the products that satisfy the search.

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
	set<Product*> resultsSet;

	// If there is only one search item, no need for setUnion() or setIntersection() - just return the Products
	// that the keyword maps to.

	if(terms.size() == 1){
		if(productsKeyMap.find(terms.back()) != productsKeyMap.end()){
			resultsSet = *productsKeyMap[terms.back()];
		} 
		vector<Product*> resultsVector(resultsSet.begin(), resultsSet.end());
		return resultsVector;
	}

	// If there is more than one search item, it depends on whether OR or AND search is performed.

	vector<string>::iterator it;
	bool isFirstItem = true;
	for(it = terms.begin(); it != terms.end(); ++it){
		if(type){

			// Only try to Union with the set if the search term is valid

			if(productsKeyMap.find(*it) != productsKeyMap.end()){
				if(resultsSet.empty() && isFirstItem){
					isFirstItem = false;			
					resultsSet = *productsKeyMap[*it];			// initialize the resultsSet if its empty
				} else {
					resultsSet = setUnion(resultsSet, *productsKeyMap[*it]);
				}
			}
		} else {

			// If a single term is not found in the map, the AND search must have no results.

			if(productsKeyMap.find(*it) == productsKeyMap.end()){
				vector<Product*> resultsVector;
				return resultsVector;
			} else {
				if(resultsSet.empty() && isFirstItem){
					isFirstItem = false;
					resultsSet = *productsKeyMap[*it];			// initialize the resultsSet if its empty
				} else {
					resultsSet = setIntersection(resultsSet, *productsKeyMap[*it]);
				}
			}
		}
	}

	// convert the set to a vector and return.

	vector<Product*> resultsVector(resultsSet.begin(), resultsSet.end());
	return resultsVector;
}

// this function replicates the input file to generate the output file that will contain the state of the database after
// the program's commands take place. 

void MyDataStore::dump(ostream& ofile){
	ofile << "<products>\n";
	set<Product*>::iterator it1;
	for(it1 = productList.begin(); it1 != productList.end(); ++it1){
		(*it1)->dump(ofile);
	}
	ofile << "</products>\n" << "<users>\n";
	map<User*, vector<Product*>*>::iterator it2;
	for(it2 = usersCartMap.begin(); it2 != usersCartMap.end(); ++it2){
		it2->first->dump(ofile);
	}
	ofile << "</users>" << endl;
}

// implementation of the ADD command. Takes in the user's string username, along with the product
// instance to be added. Finds the user using usernameMap and adds product to the userCartMap if the user is valid.

void MyDataStore::addToCart(string username, Product* p){
	User* u = usernameMap[username];
	if(usersCartMap.find(u) == usersCartMap.end()){
		cout << "Invalid Request" << endl;
	} else {
		usersCartMap[u]->push_back(p);
	}
}

// implementation of the VIEWCART command. Takes in the user's string username, and finds the user using usernameMap.
// Displays the contents of the set that the username maps to, in usersCartMap.

void MyDataStore::viewCart(string username){
	User* u = usernameMap[username];
	if(usersCartMap.find(u) == usersCartMap.end()){
		cout << "Invalid username" << endl;
	} else {
		int count = 1;
		vector<Product*>::iterator it;
		vector<Product*> cart = *usersCartMap[u];
		for(it = cart.begin(); it != cart.end(); ++it){
			cout << "Item " << count << endl;
			string productInfo = (*it)->displayString();
			cout << productInfo << "\n" << endl;
			count++;
		}
	}
}

// implementation of the BUYCART command. Takes in the user's string username, and finds the user using usernameMap. 
// Takes care of the buying transaction, updating all user and product values as neccesary and updating the data structures
// in MyDataStore.

void MyDataStore::buyCart(string username){
	User* u = usernameMap[username];
	if(usersCartMap.find(u) == usersCartMap.end()){
		cout << "Invalid username" << endl;
	} else {
		vector<Product*>* keepProducts = new vector<Product*>();
		vector<Product*> cart = *usersCartMap[u];
		vector<Product*>::iterator it;
		for(it = cart.begin(); it != cart.end(); ++it){
			int itemQty = (*it)->getQty();
			double userBalance = u->getBalance();
			double itemPrice = (*it)->getPrice();
			if(itemQty > 0 && userBalance >= itemPrice){
				u->deductAmount(itemPrice);
				(*it)->subtractQty(1);
			} else {
				keepProducts->push_back(*it);		// another vector is used to keep track of which products to keep - in the correct order.
			}
		}
		usersCartMap[u] = keepProducts;
	}
}
