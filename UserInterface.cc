#include <iostream>
#include <fstream>
#include <sstream>

#include "UserInterface.hh"
#include "customer.hh"

using std::cout;
using std::cin;
using std::endl;

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
std::ofstream file;
	char ch;

	cin.sync();
	cout << endl;
	ch = cin.get();
	ch = cin.get();

} // pressEnter ()



void UserInterface::displayMainMenu (){
  
      	bool done = false;
	int  choice;
	unsigned int ID;

	while (!done)
	{

		clearScreen ();

		cout << "\t               MAIN MENU\n\n";
		cout << "\t              SPARTAN BANK\n\n";
		cout << "\t            1. Manage Customer\n";
		cout << "\t            2. New Customer\n";
		cout << "\t            3. Look up Customer\n";
		cout << "\t            4. Preform Administrative Duties\n";
		cout << "\t            5. Exit\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			ID=obtainCustomerID();
			if (ID!=0)
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
		case 5:
			done = true;
			break;

     	default:
			cout << "\nNot a valid choice\n";
          	pressEnter();
			break;
		}	}
}

unsigned int UserInterface::obtainCustomerID()
{
	bool working=true;
	std::ofstream file;
	std::stringstream stream;
	string temp;
	unsigned int ID;
	do
	{
		clearScreen();
		if (!working)
			cout << "Incorrect User ID.  Customer may not Exist.\n";
		cout << "Enter the Users Customer ID(0 to Quit): ";
		cin >> ID;
		stream << ID;
		temp="customer"+stream.str()+".txt";
		file.open(temp.c_str());
		working = (file.is_open() && ID != 0);
	}
	while (!working);
	file.close();
	
	return ID;
}

void UserInterface::manage_customer(unsigned int ID)
{
	Customer bloke(ID);
	//if Customer == NULL, break.
	bool done=false;
	int choice;

	while (!done)
	{
		clearScreen();
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
			clearScreen();
			bloke.get_customer_info();
			pressEnter();
			break;
		case 2:
			bloke.transfer_money();
			break;
		case 3:
			bloke.withdraw_money();
			break;
		case 4:
			bloke.deposit_money();
			break;
		case 5:
			bloke.change_customer_info();
			break;
		case 6:
			bloke.close_account();
			break;
		case 7:
			if (bloke.delete_customer())
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
	string first, last, street, city, state, zip;
	Address* addr;
	cout << "Enter customer's first name: ";
	cin >> first;
	cout << "Enter customer's last name: ";
	cin >> last;
	
	cout << "Enter the customer's address\n";
	cout << "\tstreet: ";
	cin.sync();
	cin.get();
	getline (cin, street);
	cout << "\tcity: ";
	cin >> city;
	cout << "\tstate: ";
	cin >> state;
	cout << "\tzip: ";
	cin >> zip;
	
	addr = new Address (street, city, state, zip);
	
	Customer customer (first, last, addr);
	customer.save ();
	clearScreen();
	cout << "Customer Created Sucsessfully." << endl << "Your customer ID is " << customer.get_ID();
	pressEnter();
}

void UserInterface::customer_lookup()
{
	bool done=false;
	int choice;
	while(!done)
	{
		clearScreen();
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
			//lookup_by_name();
			break;
		case 2:
			//lookup_by_address();
			break;
		case 3:
			//list_all_accounts();
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
	//Need to implement Monthly Interest and Fee accural.
}
