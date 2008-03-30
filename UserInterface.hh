#ifndef USERINTERFACE
#define USERINTERFACE

class UserInterface
{
public:
	static void pressEnter();
	static void clearScreen();
	static void displayMainMenu;
	static unsigned int obtainCustomerID();
	static void manage_customer(unsigned int ID);
	static void create_new_customer();
	static void admin_duties();
	static void customer_lookup();
};

#endif USERINTERFACE
