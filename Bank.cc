#include <iostream>
#include <fstream>

#include "Account.hh"
#include "Bank.hh"
#include "customer.hh"

using std::endl;

// I'm not sure if we want to do things like this anymore.
// TODO: decide before pa3
#if 0
void Bank::log_transaction (const unsigned int id, const account_type type,
		const float amount)
{
	std::cout << "STUB: LOG_TRANSACTION. ID = " << id << ", amount = " << amount 
		<< endl;
}
#endif

// XXX: I'm not even sure what parameters this would take.
void Bank::write_customer_report (...)
{
	std::cout << "STUB: WRITE CUSTOMER REPORT\n";
}

void Bank::save (void)
{
	const static char bank[] = "bank.txt";
	std::ofstream file;

	file.open (bank);
	if (!file.is_open())
		std::cerr << "ERROR OPENING FILE: " << bank << endl;
	file << Customer::getLastCustomerID() << endl;
	file << Account::get_last_account_id() << endl;

	file.close();
}

bool Bank::init (void)
{
	unsigned int lastCust, lastAcct;
	const static char bank[] = "bank.txt";
	std::ifstream file;
	file.open (bank);
	if (!file.is_open())
		return false;

	file >> lastCust >> lastAcct;

	Customer::setLastCustomerID (lastCust);
	Account::set_last_account_id (lastAcct);

	file.close();
	return true;
}

