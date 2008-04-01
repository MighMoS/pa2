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
	static void customer_lookup();

	// For dealing with accounts
	static void create_account(Customer &cust);
	static void move_money (Customer& cust, transaction_type type);
	static void ListAllAccounts (void);

	static void admin_duties();

};

#endif // USERINTERFACE
