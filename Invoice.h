//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_INVOICE_H
#define TEST_INVOICE_H

#include "Product.h"

class Invoice {
protected:
    // Attributes
    int invoiceNumber;
    vector<Product*> products;

public:
    // Constructors
    Invoice() = default;
    Invoice(int);

    // Methods
    void addProduct(Product*);

    // Virtual Methods
    virtual double calculateTotalAmount(vector<Product*> data);
    void displayInvoiceDetails(vector<Product*> data);
    string getCurrentDate();
    void readInvoiceFile();
    string returnSyntaxPrice(string price);
};

#endif //TEST_INVOICE_H
