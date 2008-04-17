#include "Bank.hh"
#include "UserInterface.hh"

// Uncomment the following line if compiling on a Microsoft Windows platform.
//#define WINDOWS

int main ()
{
	Bank::init (); // Load all saved statuses from disk

	UserInterface::displayMainMenu ();

	Bank::save (); // Save all statuses to disk

	return 0;
}
