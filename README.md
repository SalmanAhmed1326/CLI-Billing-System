# Billing System - README

## Overview

This C program is a simple billing system for managing customers, products, and purchases. It supports various operations like adding customers, adding products, calculating bills, saving/loading data to/from files, and searching customers by phone number. The system also allows for product and customer removal from the system.

## Features

1. **Add Customer**: Allows the addition of a customer with their name, address, phone number, and balance.
2. **Add Product**: Adds a product with details like name, price, category, and quantity.
3. **Display Customers**: Displays a list of all customers in the system.
4. **Display Products**: Displays a list of all products in the system.
5. **Add Purchase**: Records a purchase made by a customer, updating the product inventory and customer purchase history.
6. **Calculate Bill**: Calculates the total bill for a customer, including GST and any existing balance.
7. **Remove Product**: Allows removal of a product from the system.
8. **Remove Customer**: Removes a customer from the system.
9. **Save Data to Files**: Saves all customer and product data to text files.
10. **Search Customer by Phone**: Search for a customer using the last four digits of their phone number.

## Files

- `customers.txt`: Stores customer details (ID, name, address, phone number, balance).
- `products.txt`: Stores product details (ID, name, category, price, quantity).

## Compilation

To compile the program, run the following command in the terminal:

```
gcc -o billing_system billing_system.c
```

Where `billing_system.c` is the name of the source code file.

## Running the Program

To run the program, use the following command:

```
./billing_system
```

## Menu Options

1. **Add Customer**: Adds a new customer to the system.
2. **Add Product**: Adds a new product to the system.
3. **Display Customers**: Displays all customers.
4. **Display Products**: Displays all products.
5. **Add Purchase**: Adds a new purchase for a customer.
6. **Calculate Bill**: Calculates the total bill for a customer, including GST.
7. **Remove Product**: Removes a product from the system.
8. **Remove Customer**: Removes a customer from the system.
9. **Save Data to Files**: Saves the current data to text files.
10. **Search Customer by Phone**: Allows searching for a customer by the last 4 digits of their phone number.

## Example of Customer Record

```
ID: 1, Name: John Doe, Address: 1234 Elm Street, Phone: 1234567890, Balance: 0.00
```

## Example of Product Record

```
ID: 1, Category: Electronics, Name: Laptop, Price: 1000.00, Quantity: 10
```

## Example of Bill Calculation

After purchasing products, the system will calculate the total bill, including the 18% GST and the customer's previous balance (if any).

```
GST (18%): Rs 180.00
Total Amount of Already Purchased Products: Rs 500.00
Total Amount of Newly Purchased Products: Rs 400.00
Total Payment for Customer John Doe: Rs 1080.00
```

## File Operations

- **Saving Data**: The system saves the customer and product data to `customers.txt` and `products.txt` for persistence between program runs.
- **Loading Data**: When the program starts, it loads the saved data from the files if available.

## Future Enhancements

- Implement advanced error handling and input validation.
- Add support for different payment methods.
- Enhance customer search with more filters.
- Include product search and sorting by different attributes.
