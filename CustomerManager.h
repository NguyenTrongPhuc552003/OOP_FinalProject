

#ifndef TEST_CUSTOMERMANAGER_H
#define TEST_CUSTOMERMANAGER_H

#include "Customer.h"

class CustomerManager {
private:
    vector<Customer*> customers;

public:
    // Constructor and Destructor
    CustomerManager();
    ~CustomerManager();

    // Supporting methods


    // Main methods
    void addCustomer(Customer*);
    void SaveFile();
    int loginCheck(const string&);

};

#endif //TEST_CUSTOMERMANAGER_H
