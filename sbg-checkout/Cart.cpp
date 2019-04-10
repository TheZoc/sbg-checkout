#include "Cart.h"
#include "ReceiptPrinter.h"
#include <algorithm> 
#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>

void Cart::AddItem(const int& id, const ItemData& itemData)
{
	// Check if the item exists. If it does, increment the count.
	auto it = m_itemInventory.find(id);
	if (it != m_itemInventory.end())
	{
		m_itemInventory[id].amount += itemData.amount;
		return;
	}

	// Item not found - Add it!
	m_itemInventory[id]	= itemData;
}

void Cart::FinishPurchase(ReceiptPrinter& rp)
{
	// When finishing the purchase, create a set sorted by individual item price. Do not touch the original map!
	using priceComparator = std::function<bool(const std::pair<const int&, const ItemData&>&, const std::pair<const int&, const ItemData&>&)>;

	priceComparator priceCmp = [](const std::pair<const int&, const ItemData&>& a, const std::pair<const int&, const ItemData&>& b)
	{
		return a.second.price > b.second.price;
	};

	std::set<std::pair<ItemID, ItemData>, priceComparator> orderedShoppingList(m_itemInventory.cbegin(), m_itemInventory.cend(), priceCmp);
	
	// Keep track of the deals that were applied
	std::unordered_map<ItemID, int> discountedItems;
	
	// Go from the most expensive to the cheapest item, applying deals
	int extraItems = 0;
	for (auto it = orderedShoppingList.cbegin(); it != orderedShoppingList.cend(); ++it)
	{
		// Rule #1 - For each 3 identical items, 1 is free!
		{
			int discountedAmount = 0;

			// Check if this item is already being discounted and take it into account!
			auto dIt = discountedItems.find(it->first);
			if (dIt != discountedItems.end())
				discountedAmount = dIt->second;

			int freeItems = (it->second.amount - discountedAmount) / 3;
			if (freeItems > 0)
			{
				discountedItems[it->first] = freeItems + discountedAmount;
			}
		}
		
		// Rule #2 - For each 3 non-identical items, the cheapest item in the cart is free!
		{
			extraItems += it->second.amount % 3;

			// I'm using (extraItems / 3 > 0) instead of (extraItems > 3) to stay "future proof".
			// In a imaginary scenario where new rules were to be added, this would detect the cases were 2+ items would need to be discounted at the same time.
			int freeItems = (extraItems / 3);
			if (freeItems > 0)
			{
				// Check if there is an available item to be discounted, starting from the cheapest one.
				auto revIterator = orderedShoppingList.cend();

				while (--revIterator != orderedShoppingList.cbegin())
				{
					auto dIt = discountedItems.find(revIterator->first);

					// This simplifies the logic ahead
					if (dIt == discountedItems.end())
						dIt = discountedItems.insert(discountedItems.begin(), { revIterator->first, 0 });

					// Check if we have enough to give discount only using this item
					if (revIterator->second.amount >= (dIt->second + freeItems))
					{
						dIt->second		+= freeItems;
						extraItems		-= freeItems * 3;
						break;
					}
					else
					{
						// Discount as much as we can from this item and then keep going.
						int discAmount	= (dIt->second + freeItems) - revIterator->second.amount;
						dIt->second		+= discAmount;
						extraItems		-= discAmount * 3;
						continue;
					}
				}
			}
		}
	}

	// We're done processing the items! Print the receipt.
	PrintReceipt(rp, discountedItems);
}

void Cart::PrintReceipt(ReceiptPrinter& rp, const std::unordered_map<ItemID, int>& discountList)
{
	double total = 0;

	rp.AddReceiptHeader();
	rp.AddItemsHeader();

	for (const auto& it : m_itemInventory)
	{
		rp.AddItem(it.second);
		total += it.second.amount * it.second.price;
	}

	rp.AddDiscountHeader();

	for (const auto& it : discountList)
	{
		rp.AddDiscount(m_itemInventory[it.first], it.second);
		total -= m_itemInventory[it.first].price * it.second;
	}

	rp.AddTotal(total);
}

