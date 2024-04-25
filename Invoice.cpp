#include "Invoice.h"

// Constructors
Invoice::Invoice(int invoiceNumber) : invoiceNumber(invoiceNumber) {}

// Methods
void Invoice::addProduct(Product* product) {
    products.push_back(product);
}

// Virtual Methods
double Invoice::calculateTotalAmount(vector<Product*> data) {
    double total = 0.0;
    for (const auto& product : data) {
        total += product->getPrice() * product->getQuantity();
    }
    return total;
}

string Invoice::getCurrentDate() {
    string date;
    time_t currentTime = time(nullptr);
    struct tm localTime;

    if (localtime_s(&localTime, &currentTime) == 0) {
        // Lấy thông tin về thời gian hiện tại
        int year = localTime.tm_year + 1900;
        int month = localTime.tm_mon + 1;
        int day = localTime.tm_mday;
        int hour = localTime.tm_hour;
        int minute = localTime.tm_min;
        int second = localTime.tm_sec;

        date = to_string(year) + "-" + to_string(month) + "-" + to_string(day) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
    }
    else {
        cout << "Không thể lấy thông tin về thời gian hiện tại." << endl;
    }
    return date;
}

string Invoice::returnSyntaxPrice(string price) {

    size_t dotPosition = price.find(".");

    string output = price.substr(0, dotPosition);

    output += "VND";

    return output;
}

void Invoice::displayInvoiceDetails(vector<Product*> data) {
    string billDetails;

    billDetails += "Invoice Number: " + to_string(invoiceNumber) + "\n";
    billDetails += "Products:\n";

    for (const auto& product : data) {
        
        billDetails += product->getName() + "," + to_string(product->getQuantity()) + "," + returnSyntaxPrice(to_string(product->getPrice())) + "," + getCurrentDate() + "\n";
    }

    billDetails += "Total Amount: " + returnSyntaxPrice(to_string(calculateTotalAmount(data))) + "\n";

    cout << billDetails << endl;

    ofstream outputFile("Bill.csv", ios::app);
    if (outputFile.is_open()) {
        outputFile << billDetails;
        outputFile.close();
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

void Invoice::readInvoiceFile() {
    string nameProduct;
    string quantityProduct;
    string priceProduct;
    string currentDate;
    ifstream inputFile("Bill.csv");

    if (!inputFile.is_open()) {
        cout << "Error open file!";
    }

    while (inputFile.good()) {
        getline(inputFile, nameProduct, ',');
        getline(inputFile, quantityProduct, ',');
        getline(inputFile, priceProduct, ',');
        getline(inputFile, currentDate, ',');

        cout << "Product Name: " << nameProduct << endl;
        cout << "Quantiry: " << quantityProduct << endl;
        cout << "Price: " << priceProduct << endl;
        cout << "Date: " << currentDate << endl;
    }

}


