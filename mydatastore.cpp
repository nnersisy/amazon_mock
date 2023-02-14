#include "util.h"
#include "mydatastore.h"
#include "user.h"
#include "product.h"

using namespace std;

MyDataStore::~MyDataStore()
{
	for(set<Product*>::iterator i = products.begin(); i != products.end(); i++)
	{
		delete *i;
	}

	for(map<string, User*>::iterator j = users.begin(); j != users.end(); j++)
	{
		delete j->second;
	}
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;
	for(set<Product*>::iterator i = products.begin(); i != products.end(); i++)
	{
		(*i)->dump(ofile);
	}
	ofile << "</products>" << "\n";
	ofile << "<users>" << "\n";
	for(map<string, User*>::iterator j = users.begin(); j != users.end(); j++)
	{
		j->second->dump(ofile);
	}
	ofile << "</users>" << "\n";
}

//add product
void MyDataStore::addProduct(Product* p)
{
	products.insert(p);
	set<string> _keys = p->keywords();

	for(set<string>::iterator i = _keys.begin(); i != _keys.end(); i++)
	{
		if(keys.find(*i) != keys.end())
		{
			keys.find(*i)->second.insert(p);
		}
		else{
			set<Product*> newp;
			newp.insert(p);
			keys.insert(make_pair(*i, newp));
		}
	}
}

//add user
void MyDataStore::addUser(User* u)
{
	users[u->getName()] = u;
	std::vector<Product*> que = std::vector<Product*>();
	cart.insert(make_pair(u->getName(), que));
}

//search 
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::set<Product*> newp;
	std::vector<Product*> hits;

	if(terms.size() == 0)
	{
		std::cout << "No term given" << std::endl;
		std::vector<Product*> empty;
		return empty;
	}
	if(type != 1 && type != 0)
	{
		std::cout << "Unknown search" << std::endl;
	}

	if(type == 1)
	{
		for(size_t i = 0; i < terms.size(); i++)
		{
			std::map<std::string, std::set<Product*>>::iterator it = keys.find(convToLower(terms[i]));
			if(it != keys.end())
			{
				newp = setUnion(newp, it->second);
			}
		}
	
	}
	else if(type == 0)
	{
			std::map<std::string, std::set<Product*>>::iterator j = keys.find(convToLower(terms[0]));
			if(j != keys.end())
			{
				newp = j->second;
			}
			if(terms.size() > 1)
			{
				for(size_t k = 1; k < terms.size(); k++)
				{
					std::map<std::string, std::set<Product*>>::iterator it = keys.find(convToLower(terms[k]));
					if(it != keys.end())
					{
						newp = setIntersection(newp, it->second);
					}
				}
				
			}

	}

	std::set<Product*>::iterator i;
	for(std::set<Product*>::iterator i = newp.begin(); i != newp.end(); i++)
	{
		hits.push_back(*i);
	}
	return hits;
}

//viewCart
void MyDataStore::viewCart(string userName)
{
	if(users.find(userName) != users.end())
	{
		for(size_t i = 0; i < cart.find(userName)->second.size(); i++)
		{
			cout << "Item: " << i+1 << endl;
			cout << cart.find(userName)->second[i]->displayString() << endl;
		}
	}
	else if(cart.find(userName) == cart.end())
	{
		cout << "Invalid username" << endl;
	}
}

//addCart
void MyDataStore::addCart(std::string userName, int index, std::vector<Product*> p)
{
	  // map<string,vector<Product*>>::iterator it;
		// for (it = cart.begin(); it != cart.end(); it++)
    //    {
		// 		 cout << it->first << endl;
    //    }	
	if(cart.find(userName) != cart.end())
	{
		cart.find(userName)->second.push_back(p[index]);
		//return;
	}
	else if (cart.find(userName) == cart.end()) 
	{
    std::cout << "Invalid request" << std::endl;
    return;
  }
}

//buyCart
void MyDataStore::buyCart(std::string userName)
{
	map<string, vector<Product*>>::iterator it = cart.find(userName);
	if(it == cart.end())
	{
		cout << "Invalid username" << endl;
		return;
	}
		User* us = users.find(userName)->second;
		vector<Product*> oldp = it->second;

			for(vector<Product*>::iterator j = oldp.begin(); j != oldp.end(); ++j)
			{
				Product* temp = *j;
				if(us->getBalance() >= temp->getPrice() && temp->getQty() >= 1 )
				{
					temp->subtractQty(1);
					us->deductAmount(temp->getPrice());
				}
				else{

					continue;
					 }
			}
		oldp.erase(oldp.begin());

		cart[userName] = oldp;
}

