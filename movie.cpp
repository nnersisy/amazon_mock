#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) : 
Product(category, name, price, qty)
{
	rating_ = rating;
	genre_ = genre;
}

Movie::~Movie()
{}

std::set<std::string> Movie::keywords() const{
	std::set<std::string> _namesList = parseStringToWords(name_);
	std::set<std::string> _genreList = parseStringToWords(genre_);
	std::set<std::string> listFull = setUnion(_namesList, _genreList);
	_genreList.insert(genre_);
	return listFull;
}

std::string Movie::displayString() const{
	std::string finalDisp = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return finalDisp;
}

void Movie::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << genre_ << std::endl;
	os << rating_ << std::endl;
}