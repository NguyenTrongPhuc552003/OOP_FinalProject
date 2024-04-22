//
// Created by Trong_Phuc on 21/04/2024.
//

#include "Storage.h"
#include "Electronic.h"
#include "Grocery.h"

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
bool Storage::saveProductsToFile(const vector<Product*>& products) {
    ofstream outFile(fileName, ios::app | ios::out);
    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing: " << fileName << endl;
        return false;
    }

    for (const auto& product : products) {
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
        if (line.empty()) {
            cout << "File is empty!\n";
            return false;
        }
        istringstream iss(line);
        string name = contentProcessor(line, 1, 2);
        double price = stod(contentProcessor(line, 2, 3));
        int quantity = stoi(line.substr(line.find_last_of(',') + 1));
        if (line.find_first_of('1') != string::npos) products.push_back(new Electronic(name, price, quantity));
        else products.push_back(new Grocery(name, price, quantity));
    }

    inFile.close();
    cout << "Products loaded from file: " << fileName << endl;
    return true;
}

// Function to update products data
bool Storage::updateProductsFromFile(const string& productName, double newPrice, int newQuantity) {
    // Read the entire CSV file into memory
    vector<string> lines;
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << fileName << endl;
        return false;
    }

    string l;
    while (getline(inFile, l)) {
        lines.push_back(l);
    }
    inFile.close();

    // Modify the data in memory
    bool found = false;
    for (auto& line : lines) {
        istringstream iss(line);
        string name;
        double price;
        int quantity;
        char comma;
        if (getline(iss, name, ',') &&
            iss >> price >> comma >> quantity) {
            if (name == productName) {
                found = true;
                // Update price and quantity
                price = newPrice;
                quantity = newQuantity;
                // Rebuild the line with updated values
                ostringstream oss;
                oss << name << "," << price << "," << quantity;
                line = oss.str();
                break; // No need to continue searching
            }
        }
    }

    if (!found) {
        cerr << "Error: Product not found in CSV file: " << productName << endl;
        return false;
    }

    // Write the modified data back to the CSV file
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << fileName << endl;
        return false;
    }

    for (const auto& line : lines) {
        outFile << line << endl;
    }
    outFile.close();

    cout << "Product updated in CSV file: " << fileName << endl;
    return true;
}

// Function to clear products file
bool Storage::clearProductsFile() {
    ofstream outFile(fileName, ios::trunc);
    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing: " << fileName << endl;
        return false;
    }
    outFile.close();
    cout << "Products file cleared: " << fileName << endl;
    return true;
}