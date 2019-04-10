// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "ReceiptPrinter.h"

int main(int argc, char* argv[])
{
	using json = nlohmann::json;

	// Check if we have the filename as parameter
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <JSON data file>" << std::endl;
		return 1;
	}

	// Check if we can open the file
	std::ifstream jsonFile(argv[1]);
	if (jsonFile.fail())
	{
		std::cerr << "Error opening \"" << argv[1] << "\". Check if the file exists, permissions are correct and try again." << std::endl;
		return 1;
	}

	// Auxiliary variables
	json			jsonData;
	Cart			cart;
	ItemData		item;
	ReceiptPrinter	rp;

	// Read data
	jsonFile >> jsonData;

	for (json::iterator it = jsonData["purchases"].begin(); it != jsonData["purchases"].end(); ++it)
	{
		if ((*it)["amount"] <= 0)
			continue;

		item.itemName	= (*it)["name"];
		item.price		= (*it)["price"];
		item.amount		= (*it)["amount"];

		cart.AddItem((*it)["id"], item);
	}

	// Apply promotions
	cart.FinishPurchase(rp);

	// Print receipt
	rp.Print();

	return 0;
}
