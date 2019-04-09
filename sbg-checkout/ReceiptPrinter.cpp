#include "ReceiptPrinter.h"
#include <sstream>
#include <iomanip>
#include <iostream>


void ReceiptPrinter::AddReceiptHeader()
{
	std::ios prevFormatting(nullptr);
	prevFormatting.copyfmt(m_ReceiptData);

	m_ReceiptData << "SBG Sports Sample Market\n";
	m_ReceiptData << "99 Sample Address\n";
	m_ReceiptData << "London, UK\n";
	m_ReceiptData << "example@example.org\n";
	m_ReceiptData << "555-5555-5555\n";
	m_ReceiptData << std::setfill('=') << std::setw(78) << "\n";
	m_ReceiptData << "\n";

	m_ReceiptData.copyfmt(prevFormatting);
}

void ReceiptPrinter::AddItemsHeader()
{
	std::ios prevFormatting(nullptr);
	prevFormatting.copyfmt(m_ReceiptData);

	m_ReceiptData << std::setw(30) << std::left << "Item Name";
	m_ReceiptData << std::setw(20) << "Price per unit";
	m_ReceiptData << std::setw(12) << "Amount";
	m_ReceiptData << std::setw(15) << std::right << "Total Price";
	m_ReceiptData << "\n";
	m_ReceiptData << std::setfill('-') << std::setw(78) << "\n";

	m_ReceiptData.copyfmt(prevFormatting);
}

void ReceiptPrinter::AddDiscountHeader()
{
	std::ios prevFormatting(nullptr);
	prevFormatting.copyfmt(m_ReceiptData);

	m_ReceiptData << "\n";
	m_ReceiptData << std::setw(30) << std::left << "Item Name";
	m_ReceiptData << std::setw(20) << "Price per unit";
	m_ReceiptData << std::setw(12) << "Amount";
	m_ReceiptData << std::setw(15) << std::right << "Total Discount";
	m_ReceiptData << "\n";
	m_ReceiptData << std::setfill('+') << std::setw(78) << "\n";

	m_ReceiptData.copyfmt(prevFormatting);
}

void ReceiptPrinter::AddItem(const ItemData& item)
{
	std::ios prevFormatting(nullptr);
	prevFormatting.copyfmt(m_ReceiptData);

	// Double formatting
	m_ReceiptData << std::fixed << std::showpoint << std::setprecision(2);

	// Item data
	m_ReceiptData << std::setw(30) << std::left << item.itemName;
	m_ReceiptData << std::setw(20) << item.price;
	m_ReceiptData << std::setw(12) << item.amount;
	m_ReceiptData << std::setw(15) << std::right << item.amount * item.price;
	m_ReceiptData << "\n";

	m_ReceiptData.copyfmt(prevFormatting);
}

void ReceiptPrinter::AddDiscount(const ItemData& item, const int& amount)
{
	std::ios prevFormatting(nullptr);
	prevFormatting.copyfmt(m_ReceiptData);

	// Double formatting
	m_ReceiptData << std::fixed << std::showpoint << std::setprecision(2);

	// Item data
	m_ReceiptData << std::setw(30) << std::left << item.itemName;
	m_ReceiptData << std::setw(20) << item.price;
	m_ReceiptData << std::setw(12) << amount;
	m_ReceiptData << std::setw(15) << std::right <<  amount * item.price * (-1); // Reminder: If we print "-" before the value, it confuses the alignment function
	m_ReceiptData << "\n";

	m_ReceiptData.copyfmt(prevFormatting);
}

void ReceiptPrinter::AddTotal(const double& amount)
{
	std::ios prevFormatting(nullptr);
	prevFormatting.copyfmt(m_ReceiptData);

	// Double formatting
	m_ReceiptData << std::fixed << std::showpoint << std::setprecision(2);

	// Total
	m_ReceiptData << "\n";
	m_ReceiptData << std::setfill(':') << std::setw(78) << "\n";
	m_ReceiptData << std::setfill(' ') << std::setw(30) << std::left  << "Total:";
	m_ReceiptData << std::setw(47) << std::right << amount;
	m_ReceiptData << "\n";

	m_ReceiptData.copyfmt(prevFormatting);
}

void ReceiptPrinter::PrintToConsole()
{
	std::cout << m_ReceiptData.str();
}
