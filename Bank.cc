#include <fstream>
#include <iostream>

#include "Account.hh"
#include "Bank.hh"
#include "Date.hh"
#include "customer.hh"
#include "Transaction.hh"

using std::endl;
using std::vector;

Date* Bank::today = NULL;

void Bank::save (void)
{
	const static char bank[] = "bank.txt";
	std::ofstream file;

	file.open (bank);
	if (!file.is_open())
	{
		std::cerr << "ERROR OPENING FILE: " << bank << endl;
		exit (1);
	}
	file << Customer::getLastCustomerID() << endl;
	file << Account::get_last_account_id() << endl;
	file << *today;

	file.close();
}

bool Bank::init (void)
{
	std::ifstream file;
	Date* date;
	string month_string;
	unsigned short year, day;
	Month month;
	unsigned int lastCust, lastAcct;
	const static char bank[] = "bank.txt";

	file.open (bank);
	if (!file.is_open())
		return false;

	file >> lastCust >> lastAcct;

	/* Do this manually */
	file >> year >> month_string >> day;
	month = Date::string_to_month (month_string);
	date = new Date (year, month, day);
	if (!date)
	{
		std::cerr << "Error allocating date\n";
		exit (1);
	}

	set_date (date, true);

	Customer::setLastCustomerID (lastCust);
	Account::set_last_account_id (lastAcct);


	// Date does not need to be freed
	file.close();
	return true;
}


/* Go through all accounts in the system, and apply monthly duties
 * (apply interest, fees, etc)
 *
 * RETURNS:
 *   Currently always returns true, but could return false in the future in
 *   case of error
 */
bool Bank::process_accounts ()
{
	vector <Account*> all_accounts;

	all_accounts = Account::get_all_accounts ();

	// Iterate through all accounts, no acct_no will be higher than the
	// next one we'll create.
	for (unsigned int i = 0; i < all_accounts.size (); i++)
	{
		all_accounts[i]->apply_interest ();
		all_accounts[i]->apply_fines();
		// TODO archive month, prep new month

		delete all_accounts[i]; // Delete each handle as we go
	}

	return true;
}

/* Bank::set date ()
 * Sets the current date of the bank
 *
 * PARAMETERS:
 *   A pointer to a date object. The second parameter should NEVER
 * be supplied except by Bank::init.
 *
 * POSTCONIDTIONS:
 *   The date will be set to a later date than it was.
 *
 * NOTES: 
 *   Will fail if the new date is /before/ the old date.
 */
bool Bank::set_date (Date* newday, const bool override)
{
	/* Someone's told us they don't care about sanity checking */
	if (override)
	{
		today = newday;
		return true;
	}

	if (*newday < *today)
		return false;
	delete today;
	today = newday;
	save ();

	return true;
}

const Date* Bank::get_date (void)
{
	return today;
}
