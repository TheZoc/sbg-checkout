#ifndef _CART_H_
#define _CART_H_

#include <unordered_map>
#include <string>

class ReceiptPrinter;

// To improve code readability
typedef int ItemID;

struct ItemData
{
	std::string	itemName;
	double		price;
	int			amount;
};

class Cart
{
private:
	std::unordered_map<ItemID, ItemData>	m_itemInventory;

public:
	Cart() {};
	~Cart() {};

	void	AddItem(const int& id, const ItemData& itemData);
	void	FinishPurchase(ReceiptPrinter& rp);

private:
	void	PrintReceipt(ReceiptPrinter& rp, const std::unordered_map<ItemID, int>& discountList);
};


#endif // _CART_H_
