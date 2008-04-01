#include <iostream>
#include <fstream>
#include <sstream>

#include "UserInterface.hh"
#include "customer.hh"
#include "Account.hh"

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
			pressEnter();
			break;
		case 2:
			bloke.transfer_money();
			break;
		case 3:
			bloke.withdraw_money();
			break;
		case 4:
			deposit_money(bloke);
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
			cout << "Customer Data Changed Sucsessfully.";
			pressEnter();
			break;
		case 7:
			bloke.close_account();
			break;
		case 8:
			if (bloke.delete_customer())
				done=true;			
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
		cout << "Enter the intial Deposit for the account: ";
		cin >> balance;	
		cust.add_Account(typeofaccount,balance);
		clearScreen();
		cout << "Account Added Sucsessfully";
		pressEnter();
	}
}

void UserInterface::deposit_money(Customer& cust)
{
	vector<int> cust_accounts;
	unsigned int choice, money;
	Transaction* cust_trans;

	cust_accounts = cust.get_Accounts();

	cout << "Deposit into which account number? (";

	for (unsigned int i = 0; i < cust_accounts.size(); i++)
	{
		if (cust_accounts[i])
			cout << cust_accounts[i] << " ";
	}
	cout << "): ";

	cin >> choice;
	cout << "Enter amount to deposit: $";
	cin >> money;

	cust_trans = new Transaction (choice, Deposit, money);
	cust_trans->process();
	delete cust_trans;
}

void UserInterface::admin_duties()
{
	cout << "Admin noise!\n";
	//Need to implement Monthly Interest and Fee accural.
}
