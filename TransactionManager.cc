#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

#include "Bank.hh"
#include "Date.hh"
#include "Transaction.hh"
#include "TransactionManager.hh"

TransactionManager::TransactionManager (const unsigned int owner_id) :
	acct_id (owner_id)
{
}

void TransactionManager::archive_this_month ()
{
	Account* acct;
	std::ofstream file;
	std::stringstream ss;
	
	ss << "logs/a" << acct_id << ".txt";
	file.open (ss.str().c_str(), std::ios::app);
	if (!file.is_open())
	{
		std::cerr << "Error opening file " << ss.str().c_str() << std::endl;
		exit (1);
	}

	acct = Account::get_account_by_id (acct_id);
	file << *Bank::get_date() << std::endl << acct->get_balance () << std::endl;
	file.close ();

	ss.clear();
	ss << "logs/c" << acct_id << ".txt";
	file.open (ss.str().c_str(), std::ios::out | std::ios::trunc);
	
	// Write out the inital balance to the new file.
	file << *Bank::get_date() << std::endl;
	file << InitialDeposit << " " << acct->get_balance () << std::endl;
	file.close ();
}

/* PRECONDITION:
 *   acct is != NULL.
 * RULES:
 *   Checking: $100 minimum balance
 *     ($5 fee)
 *     bounced check: $5
 *
 *   Savings: $1,000 minimum balance
 *     ($5 fee)
 *
 *   MoneyMarket: $10,000 min bal
 *     ($100 fee)
 *
 * POSTCONDITIONS:
 *   acct may have less $$ in it if rules were violated.
 */
static void charge_fees (Account* acct)
{
	const static float CHECK_MIN = 100;
	const static float CHECK_FEE = -5;
	const static float SAVNG_MIN = 1000;
	const static float SAVNG_FEE = -5;
	const static float MMRKT_MIN = 10000;
	const static float MMRKT_FEE = -100;

	Transaction* trans = NULL;

	switch (acct->get_type())
	{
		case Checking:
			if (acct->get_balance() < CHECK_MIN)
				trans = new Transaction (acct->get_id (),
						BankFee, CHECK_FEE,
						*Bank::get_date());
			break;
		case Savings:
			if (acct->get_balance() < SAVNG_MIN)
				trans = new Transaction (acct->get_id (),
						BankFee, SAVNG_FEE,
						*Bank::get_date());
			break;
		case MoneyMarket:
			if (acct->get_balance() < MMRKT_MIN)
				trans = new Transaction (acct->get_id (),
						BankFee, MMRKT_FEE,
						*Bank::get_date());
	}

	if (trans && !acct->is_fined ())
	{
		acct->set_fined ();
		trans->process ();
	}
	else
		acct->set_unfined ();

	delete trans;
}

/* TransactionManager::apply_fines
 * Applies fines to its owning account based on some rules stated above.
 */
void TransactionManager::apply_fines ()
{
	float curr_balance=0;
	std::ifstream ifile;
	std::stringstream ss;
	std::vector<Transaction*> transactions;

	ss << "logs/c" << acct_id << ".txt";
	ifile.open (ss.str().c_str());
	if (!ifile.is_open())
	{
		std::cerr << "Error opening file " << ss.str().c_str() << ".\n";
		exit (1);
	}

	// fill up transactions
	while (!ifile.eof())
	{
		Date* date;
		unsigned short year, day;
		std::string month;
		Transaction* trns;
		float amount;
		unsigned int type; // Really a TransactionType
		
		// Read in the date and rest of the transaction
		ifile >> year >> month >> day;
		ifile >> type >> amount;
		date = new Date (year, Date::string_to_month (month), day);
		trns = new Transaction (acct_id, transaction_type (type),
					amount, *date);
		if (!date || !trns)
		{
			std::cerr << "Error allocating memory!\n";
			exit (1);
		}
		delete date;

		transactions.push_back (trns);
	}

	// Iterate through each transaction testing to see if we've incurred a fine
	for (unsigned int i = 0; i < transactions.size(); i++)
	{
		curr_balance += transactions[i]->get_amount ();
		Account* acct = Account::get_account_by_id (acct_id);
		if (acct)
		{
			charge_fees (acct);
			delete acct;
		}
		delete transactions[i];
	}

	ifile.close ();
}



Transaction TransactionManager::get_last_transaction()
{

	std::ifstream ifile;
	std::stringstream ss;
	Transaction* trns=NULL;

	ss << "logs/c" << acct_id << ".txt";
	ifile.open (ss.str().c_str());
	if (!ifile.is_open())
	{
		std::cerr << "Error opening file " << ss.str().c_str() << ".\n";
		exit (1);
	}

	// Run to the last transaction
	while (!ifile.eof())
	{
		Date* date;
		unsigned short year, day;
		std::string month;
		float amount;
		unsigned int type; // Really a TransactionType
		
		// Read in the date and rest of the transaction
		ifile >> year >> month >> day;
		ifile >> type >> amount;
		date = new Date (year, Date::string_to_month (month), day);
			delete trns;
		trns = new Transaction (acct_id, transaction_type (type),
					amount, *date);
		if (!date || !trns)
		{
			std::cerr << "Error allocating memory!\n";
			exit (1);
		}
		delete date;
	}
	return *trns;
}



/* PRECONDITION:
 *   acct is != NULL. This should only be called by Bank::process_accounts
 *   and only after acct has been verified to exist.
 * RULES:
 *   Checking have no interest.
 *   Savings monthly interest = 1.5%
 *   MoneyMarket montly interest = 3.0%
 * POSTCONDITION:
 *    (if it was not a checking acct) acct will have more money in it
 */
float TransactionManager::apply_interest ()
{
	static const float savings_monthly_interest_rate = 0.015;
	static const float moneymkt_monthly_interest_rate = 0.030;
	float interest_earned;
	Transaction* trans;
	Account* acct;
	acct = Account::get_account_by_id (acct_id);
	if (!acct)
		std::cerr << "Error allocating account\n";
	if (acct->get_type() == Checking)
		return 0.0;

	if (acct->get_type() == Savings)
		interest_earned = acct->get_balance () * savings_monthly_interest_rate;
	else if (acct->get_type () == MoneyMarket)
		interest_earned = acct->get_balance () * moneymkt_monthly_interest_rate;

	trans = new Transaction (acct->get_id (), Interest,
			interest_earned, *Bank::get_date());
	trans->process ();
	delete trans;

	return interest_earned;
}

std::vector<Transaction*> TransactionManager::get_all_transactions()
{
	
	std::ifstream ifile;
	std::stringstream ss;
	std::vector<Transaction*> transactions;

	ss << "logs/c" << acct_id << ".txt";
	ifile.open (ss.str().c_str());
	if (!ifile.is_open())
	{
		std::cerr << "Error opening file " << ss.str().c_str() << ".\n";
		exit (1);
	}

	// fill up transactions
	while (!ifile.eof())
	{
		Date* date;
		unsigned short year, day;
		std::string month;
		Transaction* trns;
		float amount;
		unsigned int type; // Really a TransactionType
		
		// Read in the date and rest of the transaction
		ifile >> year >> month >> day;
		ifile >> type >> amount;
		date = new Date (year, Date::string_to_month (month), day);
		trns = new Transaction (acct_id, transaction_type (type),
					amount, *date);
		if (!date || !trns)
		{
			std::cerr << "Error allocating memory!\n";
			exit (1);
		}
		delete date;

		transactions.push_back (trns);
		char ch;
		ch=ifile.peek();
		while (ch=='\n')
		{
		ifile.get(ch);
		ch=ifile.peek();
		}
	}
	return transactions;
}
