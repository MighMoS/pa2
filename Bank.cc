#include <iostream>
#include <fstream>

#include "Account.hh"
#include "Bank.hh"
#include "customer.hh"

using std::endl;

void Bank::log_transaction (const unsigned int id, const account_type type,
		const float amount)
{
	std::cout << "STUB: LOG_TRANSACTION. ID = " << id << ", amount = " << amount 
		<< endl;
}

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

Transaction::Transaction (const unsigned int account_id,
		const transaction_type its_type,
		const float the_amount) :
#if 0
		const short its_year,
		const short its_month,
		const short its_day):
	year (its_year), month (its_month), day (its_day),
#endif
	id (account_id), amount (the_amount), type (its_type)
{
}

void Transaction::process (void)
{
	Account* acct;
	acct = Account::get_account_by_id (id);
	if (!acct)
	{
		std::cerr << "Account " << id << " doesn't exist to be processed. This shouldn't happen!\n";
		exit (1);
	}

	// We don't have to worry about the account type, because all can
	// add/subtract money. Also, the amount is presigned (negative if needed)
	acct->do_transaction (amount);

	delete acct;
}

#if 0
// Rough Sketch of what it should do. In this plan save doesn't care where
// its writing, because some higher level method can worry about that.
void Transaction::save(std::ofstream& output)
{
	static const char sep = ' ';
	output << year << sep << month << sep << day << sep << type << amount
		<< std::endl;
}
#endif
