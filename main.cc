#include "Bank.hh"
#include "UserInterface.hh"

int main ()
{
	Bank::init (); // Load all saved statuses from disk

	UserInterface::displayMainMenu ();

	Bank::save (); // Save all statuses to disk

	return 0;
}
