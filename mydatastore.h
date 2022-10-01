#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore{
	public: 
		~MyDataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void addToCart(std::string username, Product* p);
		void viewCart(std::string username);
		void buyCart(std::string username);
	private:

		// create four data structures:
		// 1. productList: to store a set of all products added
		// 2. usernameMap: to map between inputted usernames (as strings) to the User objects they correspond to
		// 3. productsKeyMap: to map between a keyword and the set of all products that use that keyword
		// 4. usersCartMap: to map between a User instance and a FIFO vector of all products that are currently in their cart.

		std::set<Product*> productList;
		std::map<std::string, User*> usernameMap;
		std::map<std::string, std::set<Product*>*> productsKeyMap;
		std::map<User*, std::vector<Product*>*> usersCartMap;
};


#endif