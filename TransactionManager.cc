#include <fstream>
#include <sstream>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif

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
 *     bounced check: $100
 *
 * RETURNS:
 *   true if a fee was charged, false otherwise.
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

/* Do we even need a vector of transactions? We could just dump everything but
 * the amount of the transaction (the 5th thing written out)
 */
void TransactionManager::apply_fines ()
{
	float curr_balance;
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

	for (unsigned int i = 0; i < transactions.size(); i++)
	{
		curr_balance += transactions[i]->get_amount ();
#ifdef DEBUG
		std::cerr << "curr_balance is: " << curr_balance << std::endl;
#endif
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
