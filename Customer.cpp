#include "Customer.h"


// Constructor
Customer::Customer(const string& name, const string& address, const string& email) : name(name), address(address), email(email) {}

// Getter
const string& Customer::getName() const {
	return name;
}

const string& Customer::getAddress() const {
	return address;
}

const string& Customer::getEmail() const {
	return email;
}