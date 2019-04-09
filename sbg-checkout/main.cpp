// sbg-checkout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "ReceiptPrinter.h"


void WriteSampleJSON();

int main()
{
	using json = nlohmann::json;

	// Write our testing data to a file
	// WriteSampleJSON();

	// TODO: Make this a command line argument
	std::ifstream jsonfile("fruits.json");
	json j;
	jsonfile >> j;

	// Test boilerplate code
	ReceiptPrinter rp;
	rp.AddReceiptHeader();
	rp.AddItemsHeader();

	ItemData item;
	for (json::iterator it = j["purchases"].begin(); it != j["purchases"].end(); ++it)
	{
		item.itemName	= (*it)["name"];
		item.price		= (*it)["price"];

		rp.AddItem(item, (*it)["amount"]);
	}

	rp.AddDiscountHeader();
	rp.AddDiscount(item, 1);
	rp.AddTotal(12345.87);

	rp.PrintToConsole();
}

void WriteSampleJSON()
{
	using json = nlohmann::json;

	json j;

	j =
	{
		{
			"purchases",
			{
				{
					{"id", 1},
					{"name", "Banana Bunch"},
					{"price", 2.1},
					{"amount", 8}
				},
				{
					{"id", 2},
					{"name", "Jackfruit"},
					{"price", 5.5},
					{"amount", 2}
				},
				{
					{"id", 7},
					{"name", "Black Diamond Apple"},
					{"price", 30.87},
					{"amount", 2}
				},
				{
					{"id", 4},
					{"name", "IAC 'Honey Bud' Pineapple"},
					{"price", 20.77},
					{"amount", 2}
				}
			}
		}
	};

	// Write to file
	std::ofstream o("fruits.json");
	o << std::setw(4) << j << std::endl;
}
