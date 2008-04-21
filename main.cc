#include "Bank.hh"
#include "UserInterface.hh"

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

	UserInterface::displayMainMenu ();

	Bank::save (); // Save all statuses to disk

	return 0;
}
