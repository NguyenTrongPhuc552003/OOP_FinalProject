//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_GROCERY_H
#define TEST_GROCERY_H

#include "Product.h"

class Grocery : public Product {
public:
    // Constructor for Grocery class that takes a name, price, and quantity
    Grocery(const string& name, double price, int quantity);

    // Function prototypes
    void displayDetails() override;
    double calculateTotalPrice() override;
    bool type() override;
};

#endif //TEST_GROCERY_H
