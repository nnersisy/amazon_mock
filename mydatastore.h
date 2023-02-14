#include "util.h"
#include "datastore.h"
#include <map>
#include <deque>

class MyDataStore : public DataStore{
	public:
		~MyDataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void viewCart(std::string userName);
		void addCart(std::string userName, int index, std::vector<Product*> p);
		void buyCart(std::string userName);
	private:
		std::set<Product*> products;
		std::map<std::string, User*> users;
		std::map<std::string, std::vector<Product*>> cart;
		std::map<std::string, std::set<Product*>> keys;

};