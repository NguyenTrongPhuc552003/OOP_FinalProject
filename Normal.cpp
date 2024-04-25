#include "Normal.h"

// Constructor
Normal::Normal(const string& name, const string& address, const string& email) : Customer(name, address, email) {}

// Method
double Normal::applyDiscount(double totalPrice) const {
    // Normal customers get no discount
    return totalPrice;
}

void Normal::saveFile(ofstream& file)
{
    file << name << ',' << address << ',' << email << ',' << "Normal" << endl;
}

// Getter
string Normal::getType() const {
    return "Normal";
}