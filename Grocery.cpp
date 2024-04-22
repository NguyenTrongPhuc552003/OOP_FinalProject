//
// Created by Trong_Phuc on 21/04/2024.
//

#include "Grocery.h"

// Constructor for Grocery class that initializes the name, price and quantity of the product
Grocery::Grocery(const string& name, double price, int quantity) : Product(name, price, quantity) {}

// Display the details of the product
void Grocery::displayDetails() {
    cout << "Grocery: " << name << ", Price: $" << price << ", Quantity: " << quantity << endl;
}

// Calculate the total price of the product
double Grocery::calculateTotalPrice() {
    return price * quantity;
}

// Return the type of the product
bool Grocery::type() {
    return false;
}