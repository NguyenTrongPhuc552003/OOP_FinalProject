#include "Normal.h"

// Constructor
Normal::Normal(const string& name, const string& address, const string& email) : Customer(name, address, email) {}

// Method
double Normal::applyDiscount(double totalPrice) const {
    // Normal customers get no discount
    return totalPrice;
}

// Getter
string Normal::getType() const {
    return "Normal";
}