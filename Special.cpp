#include "Special.h"

// Constructor
Special::Special(const string& name, const string& address, const string& email) : Customer(name, address, email) {}

// Method
double Special::applyDiscount(double totalPrice) const {
    // Special customers get 10% discount
    return totalPrice * 0.9;
}

void Special::saveFile(ofstream& file)
{
    file << name << ',' << address << ',' << email << ',' << "Special" << endl;
}

// Getter
string Special::getType() const {
    return "Special";
}