#include "product.h"

class Clothing : public Product
{
	public:
		Clothing(const std::string category, const std::string name, double price, 
		int qty, std::string size, std::string brand);
		~Clothing();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
	protected:
		std::string _size;;
		std::string _brand;

};