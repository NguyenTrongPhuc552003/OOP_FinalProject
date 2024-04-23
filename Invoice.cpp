// #include "Invoice.h"

// // Constructors
// Invoice::Invoice(int invoiceNumber) : invoiceNumber(invoiceNumber) {}

// // Methods
// void Invoice::addProduct(Product* product) {
//     products.push_back(product);
// }

// // Virtual Methods
// double Invoice::calculateTotalAmount() const {
//     double total = 0.0;
//     for (const auto& product : products) {
//         total += product->getPrice();
//     }
//     return total;
// }

// void Invoice::displayInvoiceDetails() const {
//     cout << "Invoice Number: " << invoiceNumber << endl;
//     cout << "Products:\n";
//     for (const auto& product : products) {
//         cout << " - " << product->getName() << ": $" << product->getPrice() << endl;
//     }
//     cout << "Total Amount: $" << calculateTotalAmount() << endl;
// }

#include "Invoice.h"

// Constructors
Invoice::Invoice(int invoiceNumber) : invoiceNumber(invoiceNumber) {}

// Methods
void Invoice::addProduct(Product* product) {
    products.push_back(product);
}

// Virtual Methods
double Invoice::calculateTotalAmount() const {
    double total = 0.0;
    for (const auto& product : products) {
        total += product->getPrice() * product->getQuantity();
    }
    return total;
}

string Invoice::getCurrentDate() const {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream date;
    date << 1 + ltm->tm_mon << "/" << ltm->tm_mday << "/" << 1900 + ltm->tm_year;
    return date.str();
}

void Invoice::displayInvoiceDetails() const {
    string billDetails;

    cout << "Invoice Number: " << invoiceNumber << endl;
    cout << "Products:\n";

    billDetails += "Invoice Number: " + to_string(invoiceNumber) + "\n";
    billDetails += "Products:\n";

    for (const auto& product : products) {
        cout << product->getName() << " - " << product->getQuantity() << " - $" << product->getPrice() << " - " << getCurrentDate() << endl;
        billDetails += product->getName() + " - " + to_string(product->getQuantity()) + " - $" + to_string(product->getPrice()) + " - " + getCurrentDate() + "\n";
    }

    cout << "Total Amount: $" << calculateTotalAmount() << endl;
    billDetails += "Total Amount: $" + to_string(calculateTotalAmount()) + "\n";

    cout << billDetails << endl;

    ofstream outputFile("Bill.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << billDetails;
        outputFile.close(); // Đóng tệp sau khi ghi
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}
