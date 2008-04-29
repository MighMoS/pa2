#include <iostream>

#include "Bank.hh"
#include "common.hh"
#include "UserInterface.hh"

using std::cout;
using std::endl;

static void output_interest_and_fees ();
static void test_process_accounts ();
static void test_write_customer_report ();

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
	test_process_accounts ();
	test_write_customer_report ();
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
	Account* acct;
	bool failed_any_tests = false;
	cout << "Testing process accounts...\n";
	Bank::process_accounts ();
	// Customer 1 is Mickey Mouse, his accounts are 1 (checking) and 2 (savings)
	// Customer 2 is Daffy Duck; his accounts are 3 (checking) and 4 (money market)
	// Customer 3 is Road runner; his account is 5 (checking)

	// What should happen is that mickey is fined $5, and then gets no interest
	// Daffy Duck shouldn't be fined, and should gain no interest
	// RR should get no interest

	acct = Account::get_account_by_id (1);
	// acct 1 had 100 - 75 = 25 - 5 = 20 + 1000000 = 1000020
	if (!(acct->get_balance() == 999995))
	{
		cout << "Account 1 had " << acct->get_balance() << ". Expected 999995.\n";
		failed_any_tests = true;
	}
	else
		cout << "Account 1: OK\n";
	delete acct;
	acct = Account::get_account_by_id (2);
	if (!(acct->get_balance() == 0))
	{
		cout << "Account 2 had " << acct->get_balance() << ". Expected 0\n";
		failed_any_tests = true;
	}
	else
	{
		cout << "Account 2: OK\n";
	}
	delete acct;
	acct = Account::get_account_by_id (3);
	if (!(acct->get_balance() == 100))
	{
		cout << "Account 3 had " << acct->get_balance () << ". Expected 100\n";
		failed_any_tests = true;
	}
	else
	{
		cout << "Account 3: OK\n";
	}
	delete acct;

	// Account 4 should not exist.
	acct = NULL;
	acct = Account::get_account_by_id (4);
	if (acct)
	{
		cout << "Account 4 exists with balance of " << acct->get_balance() << ". Expected Account 4 to be non-existant.\n";
		failed_any_tests = true;
	}
	else
	{
		cout << "Account 4: OK\n";
	}
	delete acct; // Should be safe
	acct = Account::get_account_by_id (5);
	if (!(acct->get_balance() == 100))
	{
		cout << "Account 5 had " << acct->get_balance () << ". Expected 100\n";
		failed_any_tests = true;
	}
	else
	{
		cout << "Account 5: OK\n";
	}
	
	if (failed_any_tests)
	{
		cout << "\n\n\tTHERE WERE ERRORS IN TESTING process_accounts\n";
	}
	else
		cout << "\n\n\tProcess accounts passed successfully\n";
}

static void test_write_customer_report ()
{
}
