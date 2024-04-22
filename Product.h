//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_PRODUCT_H
#define TEST_PRODUCT_H

// Include necessary libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Product {
protected:
    // Declare attributes
    string name;
    double price{};
    int quantity{};

public:
    // Constructor and Destructor
    Product() = default;
    Product(string name, double price, int quantity);
    virtual ~Product() = default;

    // Pure virtual functions
    virtual void displayDetails() = 0; // Pure virtual function for displaying product details
    virtual double calculateTotalPrice() = 0; // Pure virtual function for calculating total price
    virtual bool type() = 0; // Pure virtual function for checking product type

    // Getter and setter methods
    void setPrice(double newPrice);
    void setQuantity(int newQuantity); // May be unnecessary !
    string getName() const;
    double getPrice() const;
    int getQuantity() const;

    // Overload operator < for sorting
    bool operator < (const Product& other) const;
};

#endif //TEST_PRODUCT_H
