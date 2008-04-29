#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Account.hh"
#include "Bank.hh"
#include "Transaction.hh"
#include "TransactionManager.hh"

using std::endl;
using std::string;
using std::vector;

unsigned int Account::last_account_id = 0; 

// Creates a new account, with ID based on previous last highest ID
// The first transaction is the "Initial Deposit"
// Automatically saves itself.
Account::Account (const float initial_balance, const account_type its_type, const unsigned int custID) :
	id (++last_account_id), 
	balance (0),
	type (its_type),
	owner (custID),
	fined (false)
{
	Transaction trns (id, InitialDeposit, initial_balance,
				*Bank::get_date());
	// We must save to the disk first,
	//   or Transaction will be unable to find us
	tm = new TransactionManager (id);
	save ();
	Bank::save ();
	trns.process();
};	

// Creates an Account object from one already on disk
Account::Account (const unsigned int its_id,
		const float init_bal, 
		const account_type acct_type,
		const unsigned int custID,
		const bool has_fine) :
	id (its_id), balance (init_bal), type (acct_type),
	owner (custID), fined (has_fine)
{
	tm = new TransactionManager (id);
}

std::ostream& operator << (std::ostream& os, const Account& rhs)
{
	os << "Owners ID: " << rhs.owner << endl;
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

unsigned int Account::get_owner(void) const
{
	return owner;
}

float Account::apply_interest (void)
{
	float interest;
	interest = tm->apply_interest ();
	save ();
	return interest;
}

void Account::apply_fines (void)
{
	tm->apply_fines ();
	save();
}

void Account::archive (void)
{
	tm->archive_this_month ();
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
	if (!file.is_open())
	{
		std::cerr << "Could not open " << path << " for writing.\n\
		Check to make sure that the directory exists, and that your\
		permissions are correct.\n";
		exit (1);
	}
	
/* Format is:
 * 81 (Owners customer ID)
 * Checking (type of account)
 * 25.02 (balance)
 */
 	file << owner << endl;
	file << type << endl;
	file << balance << endl;
	file << fined << endl;

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
	unsigned int own;
	bool fined;

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
	file >> own;
	file >> type;
	file >> bal;
	file >> fined;

	file.close();

	return new Account (accID, bal, (account_type) type, own, fined);
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
	for (unsigned int i = 0; i <= Account::get_last_account_id (); i++)
	{
		Account* acct = Account::get_account_by_id (i);
		if (acct == NULL)
			continue;
		all_accts.push_back (acct);
	}

	return all_accts;
}

bool Account::is_over_FDIC()
{
	return (balance > 100000);
}

bool Account::is_active()
{
	TransactionManager tm(id);
	return (tm.get_last_transaction().get_date().get_year() < (*Bank::get_date()).get_year());
}

float Account::get_beggining_balance()
{
	vector<Transaction*> transactions;
	transactions=tm->get_all_transactions();
	float oldbal= transactions[0]->get_amount();
	for(unsigned int i=0;i<transactions.size();i++)
	{
		delete transactions[i];
	}
	return oldbal;
}
vector<Transaction*> Account::get_all_Transactions()
{
	return tm->get_all_transactions();
}

float Account::all_deposits()
{
	vector<Transaction*> transactions;
	transactions=tm->get_all_transactions();
	float dep=0;
	for(unsigned int i=0;i<transactions.size();i++)
	{
		if(transactions[i]->get_amount() >=0)
			dep += transactions[i]->get_amount();
		delete transactions[i];
	}
	return dep;
}
float Account::all_withdrawls()
{
	vector<Transaction*> transactions;
	transactions=tm->get_all_transactions();
	float with=0;
	for(unsigned int i=0;i<transactions.size();i++)
	{
		if(transactions[i]->get_amount() <0)
			with += transactions[i]->get_amount();
		delete transactions[i];
	}
	return with;
}
