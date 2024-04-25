//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_SPECIAL_H
#define TEST_SPECIAL_H

#include "Customer.h"

class Special : public Customer {
public:
    // Constructor
    Special(const string&, const string&, const string&);

    // Method
    double applyDiscount(double) const override;

    void saveFile(ofstream&);
    // Getter
    string getType() const override;
};

#endif //TEST_SPECIAL_H