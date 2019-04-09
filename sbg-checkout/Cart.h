#ifndef _CART_H_
#define _CART_H_

// To improve code readability
typedef int ItemID;

struct ItemData
{
	std::string	itemName;
	double		price;
};

class Cart
{
public:
	Cart() {};
	~Cart() {};
};


#endif // _CART_H_
