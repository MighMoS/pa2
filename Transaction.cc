#include <iostream>
#include <fstream>
#include <sstream>

#include "Account.hh"
#include "Transaction.hh"

using std::endl;

Transaction::Transaction (const unsigned int account_id,
		const transaction_type its_type,
		const float the_amount,
		const Date& its_date) :
	id (account_id), amount (the_amount), type (its_type), date (its_date) 
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

	save ();

	delete acct;
}

void Transaction::save() const
{
	std::ofstream file;
	std::stringstream stream;
	Account* acct;
	static const char logs[] = "logs/";
	static const char txt[] = ".txt";
	static const char sep = ' ';

	acct = Account::get_account_by_id (id);
	if (!acct)
	{
		std::cerr << "error allocating account\n";
		exit (1);
	}

	// Open logs/c1.txt for example: current log for account 1
	stream << logs << 'c' << id << txt;
	
	// We always append to the file.
	file.open (stream.str().c_str(), std::ios::app);
	if (!file.is_open())
	{
		std::cerr << "Could not open " << stream.str() << " for writing.\nCheck\
		check to make sure that the folder exists, and that your\
		permissions are correct.\n";
		exit (1);
	}
	file << date << endl << type << sep << amount << endl << endl;

	if (acct) delete acct;
	file.close();
}

float Transaction::get_amount (void) const
{
	return amount;
}
