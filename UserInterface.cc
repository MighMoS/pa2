#include <iostream>
#include <fstream>
#include <sstream>

#include "Account.hh"
#include "Bank.hh"
#include "customer.hh"
#include "UserInterface.hh"

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
#ifndef WINDOWS
	ch = cin.get();
#endif
	ch = cin.get();

} // pressEnter ()



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

unsigned int UserInterface::obtainCustomerID()
{
	bool working=true;
	std::ifstream file;
	string temp;
	unsigned int ID;
	do
	{
		std::stringstream stream;
		clearScreen();
		if (!working)
			cout << "Incorrect User ID.  Customer may not Exist.\n";
		cout << "Enter the Users Customer ID(0 to Quit): ";
		cin >> ID;
		stream << ID;
		temp="customers/"+stream.str()+".txt";
		file.open(temp.c_str());
		working = (file.is_open() || ID == 0);
	}
	while (!working);
	if (file.is_open())
		file.close();
	
	return ID;
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
			bloke.change_customer_info();
			bloke.save();
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
#ifndef WINDOWS
	cin.get();
#endif
	getline (cin, street);
	cout << "\tcity: ";
	getline (cin, city);
	cout << "\tstate: ";
	getline (cin, state);
	cout << "\tzip: ";
	getline (cin, zip);
	
	addr = new Address (street, city, state, zip);
	
	Customer customer (first, last, addr);
	customer.save ();

	clearScreen();
	cout << "Customer Created Successfully." << endl << "Your customer ID is " << customer.get_ID();
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

void UserInterface::create_account(Customer &cust)
{
	account_type typeofaccount;
	float balance;
	int choice;
	bool done=false;
	while (!done)
	{
		clearScreen();
		cout << "Which type of account would you like?" << endl;
		cout << "\t         1. Checking\n";
		cout << "\t         2. Savings\n";
		cout << "\t         3. Money Market\n";
		cout << "\t         4. Cancel\n";
		cin >> choice;
		switch(choice)
		{
		case 1:
			typeofaccount=Checking;
			done=true;
			break;
		case 2:
			typeofaccount=Savings;
			done=true;
			break;
		case 3:
			typeofaccount=MoneyMarket;
			done=true;
			break;
		case 4:
			done=true;
			break;
		default:
			cout << endl << "Not a Valid option, please pick a valid option(1-4)";
			pressEnter();
			break;
		}
	}
	if (choice!=4)
	{
		clearScreen();
		cout << "Enter the initial Deposit for the account: ";
		cin >> balance;
		clearScreen();	
		if (cust.add_Account(typeofaccount,balance))
			cout << "Account Added Successfully";
		else
			cout << "Adding account Failed: Customer already owns an account of that Type.";
		pressEnter();
	}
}

/* UserInterface::move_money
 *   Asks the customer what they'd like to deposit or withdraw to / from
 *
 * NOTES:
 *   Transfers are TO acct_no FROM acct_no; this is stored in two transactions
 */
void UserInterface::move_money(Customer& cust, const transaction_type type)
{
	vector<unsigned int> cust_accounts;
	unsigned int first_acct, second_acct;
	float money;
	Transaction* cust_trans;

	cust_accounts = cust.get_Accounts();

	cout << (type == Withdrawal ? "Withdraw from" : "Deposit to" );
	cout << " which account number? (enter 0 to go back)\n";

	for (unsigned int i = 0; i < cust_accounts.size(); i++)
	{
		if (cust_accounts[i])
		{
			cout << "\t" << cust_accounts[i] << ": ";
			switch ((account_type)i)
			{
				case Checking: cout << "Checking"; break;
				case Savings: cout << "Savings"; break;
				case MoneyMarket: cout << "Money market"; break;
			}
			cout << endl;
		}
	}

	cin >> first_acct;
	if (first_acct == 0)
		return;

	if (type == Transfer)
	{
		cout << "Withdraw from account number: ";
		cin >> second_acct;
	}

	cout << "Enter amount: $";
	cin >> money;

	if (type == Withdrawal)
		money *= -1;

	cust_trans = new Transaction (first_acct, type, money);
	cust_trans->process();
	delete cust_trans;
	if (type == Transfer)
	{
		// This is a withdraw, so subtract money
		cust_trans = new Transaction (second_acct, type, money * -1);
		cust_trans->process();
		delete cust_trans;
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

void UserInterface::ListAllAccounts (void)
{
	vector<Account*> all_accts;
	string input;

	all_accts = Account::get_all_accounts ();
	for (unsigned int i = 0; i < all_accts.size (); i++)
	{
		cout << *(all_accts[i]);

		if (i % 2 == 1)
		{
			do
			{
				cout << "Enter  n for Next, or q for Quit: ";
				cin >> input;
			} while (input[0] != 'n' && input[0] != 'N' &&
					input[0] != 'q' && input[0] != 'Q');
			if (input [0] == 'Q' || input[0] == 'q')
				break;
		}
	}
	for (unsigned int i = 0; i < all_accts.size (); i++)
		delete all_accts[i];
}
