#include "UserInterface.hh"


void UserInterface::clearScreen ()
//
// clears the screen
//
{

	for (int i = 0; i < 40; i++)
		cout << endl;
}  // clearScreen ()


void UserInterface::pressEnter()
{

	char ch;

	cin.sync();
	cout << endl;
	ch = getchar ();

} // pressEnter ()



void UserInterface::displayMainMenu (){
  
	bool done = false;
	int  choice;

	while (!done)
	{

		clearScreen ();

		cout << "\t               MAIN MENU\n\n";
		cout << "\t              SPARTAN BANK\n\n";
		cout << "\t            1. Manage Customer\n";
		cout << "\t            2. New Customer\n";
		cout << "\t            3. List All Accounts\n";
		cout << "\t            4. Preform Administrative Duties\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			unsigned int ID=obtainCustomerID();
			manage_customer(ID);
			break;
			
		case 2:
			create_new_customer();
			break;
		
		case 3:
			list_all_accounts();
			break;
			
		case 4:
			admin_duties();
			break;
				
     	default:
			cout << "\n\nNot a valid choice\n";
          	pressEnter();
			break;
		}	}
}

unsigned int UserInterface::obtainCustomerID()
{
	clearScreen();
	unsigned int ID;
	cout << "Enter the Users Customer ID:"
	cin >> ID;
	return ID;
}

void UserInterface::manage_customer(unsigned int ID)
{
	cout << "Managing customer...\n";
	//1. list Customer information
	//2. transfer money
	//3. Withdraw money
	//4. Deposit money
	//5. Change customer information
	//6. Close account
	//7. Remove Customer
	//8. Return to main menu
}

void UserInterface::create_new_customer()
{
	cout << "Customer created...\n";
	//Prompt user for information (last name, First name, Address)
	//Intialize Customer class with information
	//customer.save
}

void UserInterface::list_all_accounts()
{
	cout << "ACCOUNTS!\n";
	//Access the list of accounts
	//while !done
	//for (int i=0;i<4;i++)
		//output account
	//press enter
}

void UserInterface::admin_duties()
{
	cout << "Admin noise!\n";
	//Nothing to implement in this version
}
