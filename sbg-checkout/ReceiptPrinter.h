#ifndef _RECEIPTPRINTER_H_
#define _RECEIPTPRINTER_H_

#include <sstream>
#include <string>
#include "Cart.h"


class ReceiptPrinter
{
private:
	std::ostringstream m_ReceiptData;

public:
	ReceiptPrinter() {};
	~ReceiptPrinter() {};

	// Print sections/headers
	void AddReceiptHeader();
	void AddItemsHeader();
	void AddDiscountHeader();

	// Add data to the receipt
	void AddItem(const ItemData& item);
	void AddDiscount(const ItemData& item, const int& amount);
	void AddTotal(const double& amount);

	// Print to console
	void Print();

	// Empty the buffer
	void ClearAllData() { m_ReceiptData.clear(); }
};

#endif // _RECEIPTPRINTER_H_