//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_ELECTRONIC_H
#define TEST_ELECTRONIC_H

#include "Product.h"

class Electronic : public Product {
public:
    // Constructor for Electronic class that takes a name, price, and quantity
    Electronic(const string& name, double price, int quantity);

    // Function prototypes
    void displayDetails() override;
    double calculateTotalPrice() override;
    bool type() override;
};

#endif //TEST_ELECTRONIC_H
