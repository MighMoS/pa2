#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Account.hh"
#include "Bank.hh"

using std::endl;
using std::string;
using std::vector;

unsigned int Account::last_account_id = 0; 

// Creates a new account, with ID based on previous last highest ID
// Automatically saves itself.
Account::Account (const float initial_balance, const account_type its_type) :
	id (++last_account_id), 
	balance (initial_balance),
	type (its_type)
{
	save ();
};	

// Creates an Account object from one already on disk
Account::Account (const unsigned int its_id,
		const float init_bal, 
		const account_type acct_type) :
	id (its_id), balance (init_bal), type (acct_type)
{
}

std::ostream& operator << (std::ostream& os, const Account& rhs)
{
	os << "Account ID: " << rhs.id << " (";
	switch (rhs.get_type())
	{
		case Savings: os << "savings"; break;
		case Checking: os << "checking"; break;
		case MoneyMarket: os << "money market"; break;
	}
	os << ")\nBalance: " << rhs.balance << endl;

	return os;
}

/* fancy name for "add or subtract money". Should ONLY be called through
 * Transaction::process.
 */
float Account::do_transaction (const float amount)
{
	balance += amount;
	save();

	return balance;
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

/* Account::get_account_by_id
 * PARAMETERS: accID is an account number to fetch
 *
 * RETURNS:
 *  A handle to account if it was found, or NULL if nothing was found.
 *  The handle MUST BE FREED by the calling function.
 */
Account* Account::get_account_by_id (const unsigned int accID)
{
	float bal;
	const static string customer_s = "accounts/";
	const static string txt = ".txt";
	unsigned int type; // Wrong, but works

	string path;
	std::stringstream stream; // Used for converting int to string
	std::ifstream file;

	stream << accID;

	path = customer_s + stream.str() + txt;

	file.open (path.c_str());

	// We just return NULL here, because we may just want to see if
	// something exists or not.
	if (!file.is_open())
	{
		//std::cerr << "Invalid account id: " << accID << endl;
		return NULL;
	}

	file >> type;
	file >> bal;

	file.close();

	return new Account (accID, bal, (account_type) type);
}

/* Account::get_all_accounts
 *  Obtains a handle to ALL accounts found in the system.
 * 
 * RETURNS: a vector of account handles
 *  THESE MUST BE FREED BY THE CALLING FUNCTION
 */
vector <Account*> Account::get_all_accounts (void)
{
	vector <Account*> all_accts;

	// Iterate through all accounts, no acct_no will be higher than the
	// next one we'll create.
	for (unsigned int i = 0; i < Account::get_last_account_id (); i++)
	{
		Account* acct = Account::get_account_by_id (i);
		if (acct == NULL)
			continue;
		all_accts.push_back (acct);
	}

	return all_accts;
}
