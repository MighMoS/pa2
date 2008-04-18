#include <iostream>

#include "Bank.hh"
#include "UserInterface.hh"

using std::cout;
using std::cin;
using std::endl;

void UserInterface::displayMainMenu ()
{
  
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
		}
	}
}

void UserInterface::manage_customer(const unsigned int ID)
{
	Customer bloke(ID);
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
		cout << "\t               5. Add Account\n";
		cout << "\t               6. Change Customer Information\n";
		cout << "\t               7. Close account\n";
		cout << "\t               8. Remove Customer\n";
		cout << "\t               9. Return to Main Menu\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;
		
		switch(choice)
		{
		case 1:
			clearScreen();
			bloke.get_customer_info();
			cout << endl << endl <<"Press any key to Continue"; 
			pressEnter();
			break;
		case 2:
			move_money (bloke, Transfer);
			break;
		case 3:
			move_money (bloke, Withdrawal);
			break;
		case 4:
			move_money (bloke, Deposit);
			break;
		case 5:
			create_account(bloke);
			bloke.save();
			break;
		case 6:
			clearScreen();
			change_customer_info (bloke);
			clearScreen();
			cout << "Customer Data Changed Successfully.";
			pressEnter();
			break;
		case 7:
			clearScreen();
			bloke.close_account();
			break;
		case 8:
			if (bloke.delete_customer())
				done=true;
			else
				pressEnter();		
			break;
		case 9:
			done=true;
			break;
		default:
			cout << "\n\nNot a valid choice\n";
          	pressEnter();
			break;
		}
	}
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
			cout << "Not implemented in this version.\n";
			pressEnter ();
			break;
		case 2:
			cout << "Not implemented in this version.\n";
			pressEnter ();
			//lookup_by_address();
			break;
		case 3:
			ListAllAccounts ();
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
	unsigned int choice;
	bool done = false;
	while(!done)
	{
		clearScreen();
		cout << "\t               Administrative Functions \n\n";
		cout << "\t                SPARTAN BANK\n\n";
		cout << "\t               1. Monthly Process Accounts\n";
		cout << "\t               2. Write Financial Report\n";
		cout << "\t               3. Write Accounts Report\n";
		cout << "\t               4. Write Customer Report\n";
		cout << "\t               5. Return to Main Menu\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;
		
		switch(choice)
		{
		case 1:
			if (Bank::process_accounts ())
			{
				cout << "Accounts processed successfully.\n";
				pressEnter ();
			}
			else 
			{
				std::cerr << "ERROR PROCESSING ACCOUNTS.\n";
				pressEnter ();
			}
			break;
		case 2:
			cout << "Write financial report is not implemented in this version.\n";
			pressEnter();
			break;
		case 3:
			cout << "Write accounts report is not implemented in this version.\n";
			pressEnter();
			break;
		case 4:
			cout << "Write customer report is not implemented in this version.\n";
			pressEnter();
			break;
		case 5:
			done=true;
			break;
		default:
			cout << "\n\nNot a valid choice\n";
          	pressEnter();
			break;
		} 	
	}
}

void UserInterface::change_customer_info(Customer& cust)
{
	unsigned int choice;
	bool done = false;

	while (!done)
	{
		clearScreen();
		cout << "\t\t\tUpdate Customer information\n\n";
		cout << "\t\t\tSPARTAN BANK\n\n";
		cout << "\t\t\t1. Update customer name\n";
		cout << "\t\t\t2. Update customer address\n";
		cout << "\t\t\t3. Return to previous menu\n";
		cout << "Enter your choice and press <ENTER>: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			string newfirstname, newlastname;

			cout << "Please enter Customers New Information.\n";
			cout << "First Name: ";
			cin >> newfirstname;
			cout << "Last Name: ";
			cin >> newlastname;
			cust.change_name (newfirstname, newlastname);
		}
		case 2:
		{
			string newadd, newcit, newstat, newzip;
			Address* newaddress;

			cout << "Enter the street address: ";
			cin.sync();
#ifndef WINDOWS
			cin.get();
#endif
			getline(cin, newadd);
			cout << "City: ";
			getline (cin,newcit);
			cout << "State: ";
			getline (cin, newstat);
			cout << "Zip Code: ";
			cin >> newzip;

			newaddress= new Address(newadd,newcit,newstat,newzip);
			if (newaddress)
				cust.set_Address (newaddress);
			else
			{
				std::cerr << "Unable to set address.\n";
				pressEnter ();
			}
		}
		case 3:
		{
			done = true;
			break;
		}
		default:
		{
			cout << "Not a valid option.\n";
			pressEnter();
		}
		}
	}
}

