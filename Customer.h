//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_CUSTOMER_H
#define TEST_CUSTOMER_H

#include "Product.h"

class Customer {
protected:
    // Attributes
    string name;
    string address;
    string email;

public:
    // Constructor
    Customer(const string&, const string&, const string&);

    virtual double applyDiscount(double) const = 0; // Pure virtual function
    virtual string getType() const = 0; // Pure virtual function
    virtual void saveFile(ofstream&) = 0;

    // Getter
    const string& getName() const;
    const string& getAddress() const;
    const string& getEmail() const;
};

#endif //TEST_CUSTOMER_H
