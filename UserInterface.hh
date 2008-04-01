#ifndef USERINTERFACE
#define USERINTERFACE
#include "customer.hh"

class UserInterface
{
public:
	static void pressEnter();
	static void clearScreen();
	static void displayMainMenu ();
	static unsigned int obtainCustomerID();
	static void manage_customer(unsigned int ID);
	static void create_new_customer();
	static void admin_duties();
	static void customer_lookup();
	static void create_account(Customer &cust);

	// For dealing with accounts
	static void transfer_money (Customer& cust);
	static void withdraw_money (Customer& cust);
	static void deposit_money (Customer& cust);
};

#endif // USERINTERFACE
