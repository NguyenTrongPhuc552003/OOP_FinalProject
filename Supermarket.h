//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_SUPERMARKET_H
#define TEST_SUPERMARKET_H

#include "Product.h"

class Supermarket {
private:
    vector<Product*> products; // List of products in the supermarket

public:
    // Constructor and Destructor
    Supermarket() = default;
    Supermarket(const vector<Product*>& products);
    ~Supermarket();

    // Supporting methods
    vector<Product*> getProducts();
    Product* binarySearch(const string& productName);

    // Main methods
    void addProduct(Product* product);
    void removeProduct(const string& productName);
    void displayProductDetails();
    double calculateTotalRevenue();
    void sortProductsByName();
};

#endif //TEST_SUPERMARKET_H
