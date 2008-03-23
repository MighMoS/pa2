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
	static void list_all_accounts();
	static void admin_duties();
};

#endif USERINTERFACE
