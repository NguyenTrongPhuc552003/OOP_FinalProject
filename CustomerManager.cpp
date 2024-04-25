#include "CustomerManager.h"

CustomerManager::CustomerManager()
{

}

CustomerManager::~CustomerManager()
{
	for (int i = 0; i < customers.size(); i++)
		delete customers[i];
	customers.resize(0);
}

void CustomerManager::SaveFile()
{
	ofstream file;
	file.open("Customer.csv");
	if (file.is_open())
	{
		file << customers.size() << endl;
		for (int i = 0; i < customers.size(); i++)
			customers[i]->saveFile(file);
		file.close();
	}
}

void CustomerManager::addCustomer(Customer* customer)
{
	customers.push_back(customer);
	CustomerManager::SaveFile();
}

int CustomerManager::loginCheck(const string& name)
{
	if (customers.size() == 0) return 0;

	for (int i = 0; i < customers.size(); i++)
	{
		if (customers[i]->getName() == name)
			return 1;
		else return 0;
	}
}