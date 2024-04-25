//
// Created by Trong_Phuc on 21/04/2024.
//

#include "Manager.h"
#include "Grocery.h"
#include "Electronic.h"
#include "Storage.h"

#include "Normal.h"
#include "Special.h"

// Constructor for Manager class that takes a reference to a Supermarket object
Manager::Manager(Supermarket& supermarket, CustomerManager& customerManager) : supermarket(supermarket), customerManager(customerManager) {}

// Main loop for the program
void Manager::loop() {
    int choice;
    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 0:
                cout << "Thanks for using our program !\n";
                break;
            case 1:
                addProduct();
                break;
            case 2:
                removeProduct();
                break;
            case 3:
                sortProductsByName();
                break;
            case 4:
                searchProduct();
                break;
            case 5:
                displayProductDetails();
                break;
            case 6:
                calculateTotalRevenue();
                break;
            case 7:
                loadProductsFromFile();
                break;
            case 8:
                saveProductsToFile();
                break;
            case 9:
                updateProductFromFile();
                break;
            case 10:
                clearProductsFile();
                break;
            case 11:
                showInvoice();
                break;
            case 12:
                addCustomer();
                break;
            default:
                cout << "Invalid choice!\n";
        }
        system("pause");
        system("cls");
    } while (choice != 0);
}

// Display the main menu
void Manager::displayMainMenu() {
    cout << "========== Supermarket Management System ==========\n";
    for (int i = 0; i < menuOptionsSize; i++) {
        cout << menuOptions[i] << endl;
    }
}

// Add a product to the supermarket
void Manager::addProduct() {
    string name;
    double price;
    int quantity;
    bool valid;
    do {
        valid = true;
        cout << "Enter product name: ";
        getline(cin, name);
        if (name.find(',') != string::npos) {
            cout << "Product name cannot contain comma (',') character!\n";
            valid = false;
        }
    } while (!valid);
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;

    char type;
    cout << "Enter product type (G for Grocery, E for Electronic): ";
    cin >> type;

    Product* product = nullptr;
    if (type == 'G') {
        product = new Grocery(name, price, quantity);
    } else if (type == 'E') {
        product = new Electronic(name, price, quantity);
    }
    if (product) {
        supermarket.addProduct(product);
        cout << "Product added successfully!\n";
    } else {
        cout << "Invalid product type!\n";
    }
}

// Remove a product from the supermarket
void Manager::removeProduct() {
    supermarket.displayProductDetails();
    cout << "Are you want to remove all current products? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
		supermarket.clearProducts();
		cout << "All products removed successfully!\n";
		return;
	}
    string name;
    cout << "Enter product name to remove: ";
    cin >> name;
    Product* product = supermarket.binarySearch(name);
    if (product) {
        supermarket.removeProduct(name);
        cout << "Product removed successfully!\n";
    } else {
        cout << "Product not found!\n";
    }
}

// Sort products by name
void Manager::sortProductsByName() {
    supermarket.sortProductsByName();
    cout << "Products sorted by name!\n";
}

// Search for a product by name
void Manager::searchProduct() {
    string name;
    cout << "Enter product name to search: ";
    cin >> name;
    Product* product = supermarket.binarySearch(name);
    if (product) {
        cout << "Product found:\n";
        product->displayDetails();
    } else {
        cout << "Product not found!\n";
    }
}

// Display details of all products
void Manager::displayProductDetails() {
    supermarket.displayProductDetails();
}

// Calculate total revenue of the supermarket
void Manager::calculateTotalRevenue() {
    double revenue = supermarket.calculateTotalRevenue();
    cout << "Total revenue: $" << revenue << endl;
}

// Load products from CSV file
void Manager::loadProductsFromFile() {
    vector<Product*> loadedProducts;
    if (Storage::loadProductsFromFile(loadedProducts)) {
        cout << "Products loaded from file: " << fileName << endl;
        for (Product* product : loadedProducts) {
            supermarket.addProduct(product);
        }
    }
}

// Save products to CSV file
void Manager::saveProductsToFile() {
    if (Storage::saveProductsToFile(supermarket.getProducts())) {
        cout << "Products saved successfully!\n";
    } else {
        cout << "Failed to save products to CSV.\n";
    }
}

// Update products from CSV file
void Manager::updateProductFromFile() {
    vector<Product*> product;
    if (Storage::updateProductsFromFile(product)) {
        cout << "Product updated successfully!\n";
    } else {
        cout << "Failed to update product.\n";
    }
}

void Manager::showInvoice() {
    Invoice invoice;
    string choice;
    cout << "1. Import the current bill" << endl;
    cout << "2. Import the bill of file" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == "1") {
        invoice.displayInvoiceDetails(supermarket.getProducts());
    }
    else {
        invoice.readInvoiceFile();
    }
}

// Clear products file
void Manager::clearProductsFile() {
    if (Storage::clearProductsFile()) {
        cout << "Products file cleared successfully!\n";
    } else {
        cout << "Failed to clear products file.\n";
    }
}

//
void Manager::addCustomer()
{
    int option;

    do {
        system("cls");
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Return" << endl;
        cin >> option;
    } while (option != 1 && option != 2 && option != 0);

    if (option == 1) // login
    {
        string name;
        cout << "Enter name:";
        cin.ignore();
        getline(cin, name);

        int loginResult = customerManager.loginCheck(name);
        if (loginResult == 1)
            cout << "Login successfully" << endl;
        else
            cout << "Failed to login" << endl;

    }
    else if (option == 2) // sign in
    {
        string name;
        string address;
        string email;
        char type;

        cout << "Enter name:";
        cin.ignore();
        getline(cin, name);
        cout << "Enter address:";
        getline(cin, address);
        cout << "Enter email:";
        getline(cin, email);
        cout << "Enter type(N normal, S special): ";
        cin >> type;

        Customer* customer = nullptr;
        if (type == 'N')
        {
            customer = new Normal(name, address, email);
        }
        else if (type == 'S')
        {
            customer = new Special(name, address, email);
        }
        customerManager.addCustomer(customer);
    }
    else if (option == 0) // return to main menu
        return;
}