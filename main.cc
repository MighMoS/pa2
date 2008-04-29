#include <iostream>

#include "Bank.hh"
#include "common.hh"
#include "UserInterface.hh"

using std::cout;
using std::endl;

static void output_interest_and_fees ();
static void test_process_accounts ();

int main ()
{
	// Load all saved statuses from disk
	// If we fail to do so, create a new bank, with sane defaults.
	//   ... because obviously its January 1st, 2005
	if (!Bank::init ())
	{
		Customer::setLastCustomerID (0);
		Account::set_last_account_id (0);
		Bank::set_date (new Date (2005, Month (0), 1), true);
		Bank::save ();
	}

#ifndef DRIVER
	UserInterface::displayMainMenu ();
#else
	output_interest_and_fees ();
	//test_process_accounts ();
#endif

	Bank::save (); // Save all statuses to disk

	return 0;
}

// This is currently copied and pasted, something better should be done
//   (common include file, perhaps)
static void output_interest_and_fees ()
{
	cout << "Interest and fees are as follows:\n";
	cout << "Checking:\t0\% monthly interest\n\t\t$100 min\t($5 penalty)\n\n";
	cout << "Savings:\t1.5\% monthly interest\n\t\t$1,000 min\t($5 penalty)\n\n";
	cout << "Money market:\t3.0\% monthly interest\n\t\t$10,000 min\t($100 penalty)\n\n";
}

static void test_process_accounts ()
{
	Bank::process_accounts ();
	// Customer 1 is Mickey Mouse, his accounts are 1 (checking) and 2 (savings)
	// Customer 2 is Daffy Duck; his accounts are 3 (checking) and 4 (money market)
	// Customer 3 is Road runner; his account is 5 (checking)
}
