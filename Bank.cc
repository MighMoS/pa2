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
	{
		std::cerr << "ERROR OPENING FILE: " << bank << endl;
		return;
	}
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
static void add_interest (Account* acct)
{
	static const float savings_monthly_interest_rate = 0.015;
	static const float moneymkt_monthly_interest_rate = 0.030;
	float interest_earned;
	Transaction* trans;

	if (acct->get_type() == Checking)
		return;

	if (acct->get_type() == Savings)
		interest_earned = acct->get_balance ()
			* savings_monthly_interest_rate;
	else if (acct->get_type () == MoneyMarket)
		interest_earned = acct->get_balance ()
			* moneymkt_monthly_interest_rate;

	trans = new Transaction (acct->get_id (), Interest, interest_earned);
	trans->process ();
	delete trans;
}

/* PRECONDITION:
 *   acct is != NULL. This should only be called by Bank::process_accounts.
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
						BankFee, CHECK_FEE);
			break;
		case Savings:
			if (acct->get_balance() < SAVNG_MIN)
				trans = new Transaction (acct->get_id (),
						BankFee, SAVNG_FEE);
			break;
		case MoneyMarket:
			if (acct->get_balance() < MMRKT_MIN)
				trans = new Transaction (acct->get_id (),
						BankFee, MMRKT_FEE);
	}

	if (trans)
	{
		trans->process ();
		delete trans;
	}
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
		add_interest (all_accounts[i]);
		charge_fees (all_accounts[i]);
		// archive month, prep new month

		delete all_accounts[i]; // Delete each handle as we go
	}

	return true;
}

