#include "UserInterface.hh"
#include "customer.cc"

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
		cout << "\t            3. Look up Customer\n";
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
			customer_lookup();
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
	Customer bloke(ID);
	bool done=false
	int choice;
	while (!done)
	{
		clearscreen();
		cout << "\t               Manage Customer\n\n";
		cout << "\t                SPARTAN BANK\n\n";
		cout << "\t               1. List Customer Information\n";
		cout << "\t               2. Transfer Money\n";
		cout << "\t               3. Withdraw Money\n";
		cout << "\t               4. Deposit Money\n";
		cout << "\t               5. Change Customer Information\n";
		cout << "\t               6. Close acount\n";
		cout << "\t               7. Remove Customer\n";
		cout << "\t               8. Return to Main Menu\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;
		
		switch(choice)
		{
		case 1:
			bloke.get_customer_info();
			break;
		case 2:
			bloke.Transfermoney();
			break;
		case 3:
			bloke.withdrawmondey();
			break;
		case 4:
			bloke.depositmoney();
			break;
		case 5:
			bloke.changecustomerinfo();
			break;
		case 6:
			bloke.closeaccount();
			break;
		case 7:
			if (bloke.deletecustomer())
				done=true;			
			break;
		case 8:
			done=true;
			break;
		default:
			cout << "\n\nNot a valid choice\n";
          	pressEnter();
			break;
		}
	}
}
void UserInterface::create_new_customer()
{
	cout << "Customer created...\n";
	//Prompt user for information (last name, First name, Address)
	//Intialize Customer class with information
	//customer.save
}

void UserInterface::customer_lookup()
{
	bool done=false;
	int choice;
	while(!done)
	{
		clearscreen();
		cout << "\t               Lookup Customer \n\n";
		cout << "\t                SPARTAN BANK\n\n";
		cout << "\t               1. By Customer Name\n";
		cout << "\t               2. By Customer Address\n";
		cout << "\t               3. List all Accounts\n";
		cout << "\t               4. Return to Main Menu\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;
		
		switch(choice)
		{
		case 1:
			lookup_by_name();
			break;
		case 2:
			lookup_by_address();
			break;
		case 3:
			list_all_accounts();
			break;
		case 4:
			done=true;
			break;
		default:
			cout << "\n\nNot a valid choice\n";
          	pressEnter();
			break;
		} 	
	}
}

void UserInterface::admin_duties()
{
	cout << "Admin noise!\n";
	//Nothing to implement in this version
}
