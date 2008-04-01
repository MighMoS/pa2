#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Account.hh"
#include "Bank.hh"

using std::string;
using std::endl;

unsigned int Account::last_account_id = 0; 

// Creates a new account, with ID based on previous last highest ID
Account::Account (const float initial_balance, const account_type its_type) :
	id (++last_account_id), type (its_type), balance (initial_balance)
{
};	

Account::Account (const unsigned int its_id,
		const float init_bal, 
		const account_type acct_type) :
	id (its_id), balance (init_bal), type (acct_type)
{
}

// XXX: Should this really be handled here? I don't think so. Something higher
// level like Bank ``might should'', so that we can more better handle things
// like logging
float Account::do_transaction (const float amount)
{
	//XXX: This is now wrong, and should be handled by the tm
	Bank::log_transaction (id, type, amount);
	return balance += amount;
}

unsigned int Account::get_id (void) const
{
	return id;
}

account_type Account::get_type(void) const
{
	return type;
}

float Account::get_balance (void) const
{
	return balance;
}

/* save. Save an account to the disk.
 * Takes no parameters, does not alter the account.
 * Opens account/_ID_.txt, and writes out the nessisary info.
 * We don't care if something was there earlier, its not anymore.
 */
void Account::save (void) const
{
	const static string customer_s = "accounts/";
	const static string txt = ".txt";

	string path;
	std::stringstream stream; // Used for converting int to string
	std::ofstream file;

	stream << id;

	path = customer_s + stream.str() + txt;
	file.open (path.c_str());

	file << type << endl;
	file << balance << endl;

	file.close();
}

void Account::set_last_account_id (const unsigned int lastID)
{
	last_account_id = lastID;
}

unsigned int Account::get_last_account_id (void)
{
	return last_account_id;
}

Account* Account::get_account_by_id (const unsigned int accID)
{
	float bal;
	const static string customer_s = "accounts/";
	const static string txt = ".txt";
	unsigned int type; // Wrong, but works
	Account* acct;

	string path;
	std::stringstream stream; // Used for converting int to string
	std::ifstream file;

	stream << accID;

	path = customer_s + stream.str() + txt;

	file.open (path.c_str());
	if (!file.is_open())
	{
		std::cerr << "Invalid account id: " << accID << endl;
		exit (1);
	}

	file >> type;
	file >> bal;

	file.close();

	return acct = new Account (accID, bal, (account_type) type);
}
