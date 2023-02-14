#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand) : Product(category, name, price, qty)
{
	_size = size;
	_brand = brand;
}

Clothing::~Clothing()
{}

std::set<std::string> Clothing::keywords() const{
	std::set<std::string> _namesList = parseStringToWords(name_);
	std::set<std::string> _brandList = parseStringToWords(_brand);
	std::set<std::string> listFull = setUnion(_namesList, _brandList);
	listFull.insert(_size);
	return listFull;
}

std::string Clothing::displayString() const{
	std::string finalDisp = name_ + "\nSize: " + _size + " Brand: " + _brand + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return finalDisp;
}


void Clothing::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << _size << std::endl;
	os << _brand << std::endl;
}