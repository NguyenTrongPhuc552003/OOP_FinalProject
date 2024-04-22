//
// Created by Trong_Phuc on 21/04/2024.
//

#ifndef TEST_STORAGE_H
#define TEST_STORAGE_H

#include "Product.h"

const string fileName = "products.csv"; // File name to save/load products

class Storage {
protected:
    // Function to process content of a line
    static string contentProcessor(const string& line, size_t commaPos1, size_t commaPos2);

public:
    // Function prototypes
    static bool saveProductsToFile(const vector<Product*>&);
    static bool loadProductsFromFile(vector<Product*>&);
    static bool updateProductsFromFile(const string& productName, double newPrice, int newQuantity);
    static bool clearProductsFile();
};

#endif //TEST_STORAGE_H
