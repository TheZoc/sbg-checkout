# sbg-checkout

This is my implementation of the C++ Programming Test by SBG Sports Software.


## Problem: Supermarket Check Out

We’d like you to design a supermarket checkout that calculates the total price of a number of items.

Items are stored with their unit price.

Some items are eligible for discounts based on the following 2 deal types:
- buy 3 identical items and pay for 2
- buy 3 (in a set of items) and the cheapest is free

No other deal types need to be considered for the purposes of this exercise.

The output from the C++ program should be the customer receipt. This should show the price of each item bought and the grand total.

You may choose any sensible means of accepting input and producing output.

You should submit to us the C++ source code and any associated documentation.


## Instructions

After building the solution using the appropriate compiler, a command line application will be available with a sample input file (`fruits.json`) at the output directory.

The executable requires a single command line parameter as the input data:

On Windows: `sbg-checkout.exe fruits.json`
On macOS: `./sbg-checkout.exe fruits.json`

The receipt will be printed to the console. It can easily be saved by redirecting the output to a file.


## Remarks

- Data input and output were planned to be as simple as possible, using a JSON file for input and console for output.

- While researching UK receipts samples, I wasn't able to find a consistent standard to follow. I decided to follow a simple scheme that's easy to read and I found suitable for the test.

- For the sake of simplicity, the discount rules were applied in `Cart::FinishPurchase()`.

- The shopping list (stored in `m_itemInventory`) is converted to a sorted set before the rules processing. This allows the data to be arranged in an optimal way to apply the required rules, reducing the complexity.


## Compatibility

Tested using:
- Visual Studio Community 2017 Version 15.9.11
- Apple LLVM version 10.0.1 (clang-1001.0.46.3)


## Third part libraries

- Uses [Json for Modern C++](https://github.com/nlohmann/json) for input data parsing.
