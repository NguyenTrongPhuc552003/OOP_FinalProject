//
// Created by Trong_Phuc on 21/04/2024.
//

#include "Storage.h"
#include "Electronic.h"
#include "Grocery.h"
#include "Supermarket.h"

// Function to process content of a line
string Storage::contentProcessor(const string& line, size_t commaPos1, size_t commaPos2) {
    string result;
    size_t commaCounter = 0;
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            commaCounter++;
        }
        else {
            if (commaCounter == commaPos1) {
                result += line[i];
            }
            if (commaCounter == commaPos2) {
                break;
            }
        }
    }
    return result;
}

// Function to save products to file
bool Storage::saveProductsToFile(vector<Product*> products, bool updateMode) {
    // Check if file is exist or not
    // 0: Tao moi
    // 1:
    // - Content is empty: ios::out
    // - Content is exist:
    //   + Call to LoadFile function
    //   + Checking to the same product's name: change price, quantity or append (using for loop)
    if (products.empty()) {
		cout << "No products to save!\n";
		return false;
	}
    vector<Product*> loadedProducts;
    bool existProducts = loadProductsFromFile(loadedProducts);
    bool isExist = false;
    if (updateMode) {
        goto updateModeAnnotation; // Jump to update mode
    }
    if (existProducts && !loadedProducts.empty()) { // Check if file is empty
        for (const auto& pro : loadedProducts) { // Check if product is already exist
            for (const auto& input : products) {
                if (input->getName() == pro->getName()) {
                    cout << "Product " << input->getName() << " is already exist in file!\n";
                    cout << "Do you want to update it? (Y/N): ";
                    char choice;
                    cin >> choice;
                    if (choice == 'Y' || choice == 'y') {
                        pro->setPrice(input->getPrice());
                        pro->setQuantity(input->getQuantity());
                    }
                    // Remove all products that are already exist in file
                    products.erase(remove(products.begin(), products.end(), input), products.end());
                    break;
                }
            }
        }
        isExist = true;
        loadedProducts.insert(loadedProducts.end(), products.begin(), products.end()); // Append new products to loaded products
    }
updateModeAnnotation:
    ofstream outFile(fileName, ios::out); // Open file for writing
    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing: " << fileName << endl;
        return false;
    }
    vector<Product*> tempProducts = (isExist ? loadedProducts : products);
    for (const auto& product : tempProducts) {
        outFile << product->type() << ',' << product->getName() << ',' << product->getPrice() << "," << product->getQuantity() << endl;
    }
    outFile.close();
    cout << "Products saved to CSV file: " << fileName << endl;
    return true;
}

// Function to load products from file
bool Storage::loadProductsFromFile(vector<Product*>& products) {
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << fileName << endl;
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string name = contentProcessor(line, 1, 2);
        double price = stod(contentProcessor(line, 2, 3));
        int quantity = stoi(line.substr(line.find_last_of(',') + 1));
        if (line.find_first_of('1') != string::npos) products.push_back(new Electronic(name, price, quantity));
        else products.push_back(new Grocery(name, price, quantity));
    }

    inFile.close();
    if (products.empty()) { // No data is stored
		cout << "File is empty!\n";
		return false;
    }
    return true;
}

// Function to update products data
bool Storage::updateProductsFromFile(vector<Product*>& loadedProducts) {
    if (Storage::loadProductsFromFile(loadedProducts)) { // Check if file is empty
        cout << "Enter product name to update: ";
        string name;
        cin >> name;

        // Search for product by name
        Supermarket supSearcher(loadedProducts); // Create a temporary supermarket to search for products
        Product* product = supSearcher.binarySearch(name); // Search for product by name
        if (product) { // If product is found
            // Update product details
            cout << "Enter new price for " << product->getName() << ": ";
            double price;
            cin >> price;

            cout << "Enter new quantity for " << product->getName() << ": ";
            int quantity;
            cin >> quantity;

            for (const auto& product : loadedProducts) { // Update product details
                if (product->getName() == name) {
					product->setPrice(price);
					product->setQuantity(quantity);
                    break;
				}
			}

            // Clear file and save updated products
            return Storage::saveProductsToFile(loadedProducts, true);
        } else {
            cout << "Product not found!\n";
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

// Function to clear products file
bool Storage::clearProductsFile() {
    ofstream outFile(fileName, ios::out);
    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing: " << fileName << endl;
        return false;
    }
    outFile.close();
    return true;
}