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
        // Get the current date and time
        int year = localTime.tm_year + 1900;
        int month = localTime.tm_mon + 1;
        int day = localTime.tm_mday;
        int hour = localTime.tm_hour;
        int minute = localTime.tm_min;
        int second = localTime.tm_sec;

        date = to_string(year) + "-" + to_string(month) + "-" + to_string(day) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
    }
    else {
        cout << "Cannot get the current information of time" << endl;
    }
    return date;
}

string Invoice::returnSyntaxPrice(string price) {
    size_t dotPosition = price.find(".");
    string output = price.substr(0, dotPosition) + "VND";
    return output;
}

void Invoice::displayInvoiceDetails(vector<Product*> data) {
    string billDetails;
    string readLine;
    unsigned int currentInvoiceNumber = 0;

    if (data.empty()) {
		cout << "No products to display." << endl;
		return;
	}

    ifstream inputFile("Bill.csv");
    if (!inputFile.is_open()) {
		cout << "Error open file!";
	}

    while (inputFile.good() && getline(inputFile, readLine)) {
        if (readLine.find("Invoice Number: ") != string::npos) { // Check if the line contains the invoice number
			currentInvoiceNumber = stoi(readLine.substr(readLine.find("Invoice Number: ") + 16));
		}
	}
    inputFile.close();

    if (currentInvoiceNumber == 0) {
        billDetails += "Invoice Number: " + to_string(invoiceNumber) + "\n";
    }
    else {
        billDetails += "Invoice Number: " + to_string(currentInvoiceNumber + 1) + "\n";
    }
    billDetails += "Products:\n";

    for (const auto& product : data) {   
        billDetails += product->getName() + "," + to_string(product->getQuantity()) + "," + returnSyntaxPrice(to_string(product->getPrice())) + "," + getCurrentDate() + ",\n";
    }
    billDetails += "Total Amount: " + returnSyntaxPrice(to_string(calculateTotalAmount(data))) + "\n";
    cout << billDetails << endl;
    ofstream outputFile("Bill.csv", ios::app);
    if (outputFile.is_open()) {
        outputFile << billDetails << endl;
        outputFile.close();
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

void Invoice::readInvoiceFile() {
    string categories[4] = { "Name", "Quantity", "Price", "Date" };
    string readLine, stored;
    unsigned int i = 0;
    ifstream inputFile("Bill.csv");

    if (!inputFile.is_open()) {
        cout << "Error open file!";
    }
    while (inputFile.good()) {
        getline(inputFile, readLine);
        if (readLine.find(',') != string::npos) {
            for (unsigned j = 0; j < readLine.length(); j++) {
                if (readLine[j] == ',') {
                    cout << categories[i++] << ": " << stored;
                    cout << (i == 4 ? "\n" : ", ");
                    stored = "";
                }
                else {
                    stored += readLine[j];
                }
            }
            i = 0;
        }
        else {
            cout << readLine << endl;
        }
    }
    inputFile.close();
}