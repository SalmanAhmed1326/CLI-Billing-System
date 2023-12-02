#include <stdio.h>
#include <string.h>

// Define structures for customer and product
struct Customer {
    int id;
    char name[50];
    char address[100];
    char phone[15]; // Added phone number field
    double balance;
};

struct Product {
    int id;
    char category[50];
    char name[50];
    double price;
    int quantity;
};

struct Purchase {
    int customerId;
    int productId;
    int quantity;
};

// Declare arrays to store customer, product, and purchase data
struct Customer customers[100];
struct Product products[100];
struct Purchase purchases[1000];  // Assuming a purchase array size
int numCustomers = 0;
int numProducts = 0;
int numPurchases = 0;

// Function to display the added customer
void displayAddedCustomer(const struct Customer *customer) {
    printf("Added Customer:\n");
    printf("ID: %d, Name: %s, Address: %s, Phone: %s, Balance: %.2lf\n",
           customer->id, customer->name, customer->address, customer->phone, customer->balance);
}

// Function to display the added product
void displayAddedProduct(const struct Product *product) {
    printf("Added Product:\n");
    printf("ID: %d, Category: %s, Name: %s, Price: %.2lf, Quantity: %d\n",
           product->id, product->category, product->name, product->price, product->quantity);
}

void addCustomer() {
    struct Customer newCustomer;
    printf("Enter customer name: ");
    scanf("%s", newCustomer.name);
    printf("Enter customer address: ");
    scanf("%s", newCustomer.address);
    printf("Enter customer phone number: "); // Ask for phone number
    scanf("%s", newCustomer.phone);
    newCustomer.id = numCustomers + 1;
    newCustomer.balance = 0.0;
    customers[numCustomers++] = newCustomer;
    printf("Customer added successfully.\n");
}

void addProduct() {
    struct Product newProduct;
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    printf("Enter product price: ");
    scanf("%lf", &newProduct.price);
    printf("Enter product category: ");
    scanf("%s", newProduct.category);
    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);
    newProduct.id = numProducts + 1;
    products[numProducts++] = newProduct;
    printf("Product added successfully.\n");
}


/// Save customer and product data to files
void saveDataToFile() {
    FILE *customerFile = fopen("customers.txt", "w");
    FILE *productFile = fopen("products.txt", "w");

    if (customerFile && productFile) {
        for (int i = 0; i < numCustomers; i++) {
            fprintf(customerFile, "%d %s %s %s %.2lf\n", customers[i].id, customers[i].name, customers[i].address, customers[i].phone, customers[i].balance);
        }

        for (int i = 0; i < numProducts; i++) {
            fprintf(productFile, "%d %s %s %.2lf %d\n", products[i].id, products[i].category, products[i].name, products[i].price, products[i].quantity);
        }

        fclose(customerFile);
        fclose(productFile);
        printf("Data saved to files.\n");
    } else {
        printf("Error opening files for writing.\n");
    }
}

// Load customer and product data from files
void loadDataFromFile() {
    FILE *customerFile = fopen("customers.txt", "r");
    FILE *productFile = fopen("products.txt", "r");

    if (customerFile && productFile) {
        while (fscanf(customerFile, "%d %s %s %s %lf", &customers[numCustomers].id, customers[numCustomers].name, customers[numCustomers].address, customers[numCustomers].phone, &customers[numCustomers].balance) == 5) {
            numCustomers++;
        }

        while (fscanf(productFile, "%d %s %s %.2lf %d", &products[numProducts].id, products[numProducts].category, products[numProducts].name, &products[numProducts].price, &products[numProducts].quantity) == 5) {
            numProducts++;
        }

        fclose(customerFile);
        fclose(productFile);
        printf("Data loaded from files.\n");
    } else {
        printf("Error opening files for reading.\n");
    }
}


void displayCustomers() {
    printf("Customer List:\n");
    for (int i = 0; i < numCustomers; i++) {
        displayAddedCustomer(&customers[i]);
    }
}

void displayProducts() {
    printf("Product List:\n");
    for (int i = 0; i < numProducts; i++) {
        displayAddedProduct(&products[i]);
    }
}

void removeCustomer(int customerId) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerId) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < numCustomers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            numCustomers--;
            printf("Customer removed successfully.\n");
            printf("---------------------------------------\n");
            return;
        }
    }
    printf("Customer not found.\n");
}

void removeProduct(int productId) {
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == productId) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < numProducts - 1; j++) {
                products[j] = products[j + 1];
            }
            numProducts--;
            printf("Product removed successfully.\n");
            printf("------------------------------\n");
            return;
        }
    }
    printf("Product not found.\n");
}
void addPurchase(int customerId, int productId, int quantity) {
    // Check if the product exists
    struct Product *product = NULL;
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id == productId) {
            product = &products[i];
            break;
        }
    }

    if (product == NULL) {
        printf("Product not found in the product list. Purchase not added.\n");
        return;
    }
    // Display product name along with ID
    printf("Product ID: %d, Name: %s\n", product->id, product->name);

    // Check if the customer wants to remove the product from the purchase
    char choice;
    printf("Do you want to continue with this product (Y/N)? ");
    scanf(" %c", &choice);
    if (choice == 'N' || choice == 'n') {
        printf("Product removed from purchase.\n");
        return;
    }

    // Check if there is enough quantity available
    if (product->quantity >= quantity) {
        // Product exists and quantity is available, add the purchase
        struct Purchase newPurchase;
        newPurchase.customerId = customerId;
        newPurchase.productId = productId;
        newPurchase.quantity = quantity;
        purchases[numPurchases++] = newPurchase;

        // Update product quantity
        product->quantity -= quantity;

        printf("Purchase added successfully.\n");
    } else {
        printf("Insufficient product quantity.\n");
    }
}


void calculateBill(int customerId) {
    double totalBill = 0.0;
    double gstRate = 0.18; // Assuming a GST rate of 18% (you can change this as needed)

    printf("Bill for Customer ID %d:\n", customerId);

    printf("%-5s %-30s %-10s %-10s %-15s %-15s\n", "ID", "Product Name", "Category", "Quantity", "Unit Price", "Total Price");

    double alreadyPurchasedTotal = 0.0; // Initialize the total for already purchased products
    double newPurchasedTotal = 0.0;     // Initialize the total for newly purchased products

    for (int i = 0; i < numPurchases; i++) {
        if (purchases[i].customerId == customerId) {
            for (int j = 0; j < numProducts; j++) {
                if (products[j].id == purchases[i].productId) {
                    double itemTotalPrice = purchases[i].quantity * products[j].price;
                    printf("%-5d %-30s %-10s %-10d %-15.2lf %-15.2lf\n",
                           products[j].id, products[j].name, products[j].category,
                           purchases[i].quantity, products[j].price, itemTotalPrice);

                    // Check if the product is newly added (quantity purchased is greater than available)
                    if (purchases[i].quantity > products[j].quantity) {
                        double newProductPrice = (purchases[i].quantity - products[j].quantity) * products[j].price;
                        newPurchasedTotal += newProductPrice;
                    } else {
                        alreadyPurchasedTotal += itemTotalPrice; // This is an already purchased product
                    }
                    break;
                }
            }
        }
    }

    // Calculate GST amount and add it to the total bill
    double gstAmount = (alreadyPurchasedTotal + newPurchasedTotal) * gstRate;
    totalBill += gstAmount;

    // Deduct any previously paid balance by the customer
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerId) {
            double previousBalance = customers[i].balance;
            totalBill += previousBalance;

            if (previousBalance > 0) {
                printf("Previous Balance Deducted: %.2lf\n", previousBalance);
            }

            customers[i].balance = totalBill;
            float pay= customers[i].balance+alreadyPurchasedTotal;
            customers[i].balance= pay;

            printf("-------------------------------------------------------------\n");
            printf("GST (18%%): Rs %.2lf\n", gstAmount);
            printf("Total Amount of Already Purchased Products: Rs %.2lf\n", previousBalance);
            printf("Total Amount of Newly Purchased Products:  Rs %.2lf\n", alreadyPurchasedTotal);
            printf("Total Payment for Customer %s \t : Rs %.2lf \n", customers[i].name,pay );
            printf("-------------------------------------------------------------\n");
            printf("Thank You For Visiting...\nVisit Again\n\n\n\n!!");
            return;
        }
        
    }

    printf("Customer not found.\n");
}

// Search for a customer based on the last 4 digits of their phone number
void searchCustomerByPhone() {
    char searchDigits[5];
    printf("Enter the last 4 digits of the customer's phone number: ");
    scanf("%s", searchDigits);

    printf("Matching Customers:\n");
    for (int i = 0; i < numCustomers; i++) {
        if (strlen(customers[i].phone) >= 4 &&
            strcmp(customers[i].phone + strlen(customers[i].phone) - 4, searchDigits) == 0) {
            displayAddedCustomer(&customers[i]);
    
        } else {
            printf("Customer Not Exists\n");

        }
        
    }
    
}

int main() {
    // Load data from files at the start of the program
    loadDataFromFile();

    int choice;
    while (1) {
        printf("Billing System Menu:\n");
        printf("1. Add Customer\n");
        printf("2. Add Product\n");
        printf("3. Display Customers\n");
        printf("4. Display Products\n");
        printf("5. Add Purchase\n");
        printf("6. Calculate Bill\n");
        printf("7. Remove Product\n");
        printf("8. Remove Customer\n");
        printf("9. Save Data to Files\n");
        printf("10. Search Customer by Phone\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                displayCustomers();
                break;
            case 4:
                displayProducts();
                break;
            case 5: {
            int customerId, productId, quantity;
            printf("Enter customer ID: ");
            scanf("%d", &customerId);
            displayProducts();
            while (1) {
                printf("Enter product ID (or -1 to stop): ");
                scanf("%d", &productId);
                if (productId == -1) {
                    break;
                }
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addPurchase(customerId, productId, quantity);
            }
                printf("Purchases added successfully.\n");
                break;
            }
            case 6:
                int customerId;
                printf("Enter customer ID for billing: ");
                scanf("%d", &customerId);
                calculateBill(customerId);
                break;
            case 7:
                int removeProductId;
                printf("Enter product ID to remove: ");
                scanf("%d", &removeProductId);
                removeProduct(removeProductId);
                break;
            case 8:
                int removeCustomerId;
                printf("Enter customer ID to remove: ");
                scanf("%d", &removeCustomerId);
                removeCustomer(removeCustomerId);
                break;
            case 9:
                // Save data to files
                saveDataToFile();
                break;
            case 10:
                searchCustomerByPhone(); // Call the search function
                break;
            case 11:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}