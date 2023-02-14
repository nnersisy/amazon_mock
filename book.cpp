#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, string ISBN, string author) : Product(category, name, price, qty)
{
	_ISBN = ISBN;
	_author = author;
}

Book::~Book()
{}

std::set<std::string> Book::keywords() const{
	std::set<std::string> _namesList = parseStringToWords(name_);
	std::set<std::string> _authorList = parseStringToWords(_author);
	std::set<std::string> listFull = setUnion(_namesList, _authorList);
	listFull.insert(_ISBN);
	return listFull;
}

std::string Book::displayString() const{
	std::string finalDisp = name_ + "\nAuthor: " + _author + " ISBN: " + _ISBN + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return finalDisp;
}


void Book::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << _ISBN << std::endl;
	os << _author << std::endl;
}