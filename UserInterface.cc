#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Account.hh"
#include "Bank.hh"
#include "common.hh"
#include "customer.hh"
#include "Date.hh"
#include "Transaction.hh"
#include "UserInterface.hh"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

/* UserInterface::clearScreen ()
 *
 * Clears the screen by writing 40 blank lines
 */
void UserInterface::clearScreen ()
{
	for (int i = 0; i < 40; i++)
		cout << endl;
}  // clearScreen ()


/* UserInterface::pressEnter
 *
 * Waits until the user presses enter.
 *
 * NOTES: Implementation depends on the platform.
 */
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


/* UserInterface::set_date ()
 * Asks the user what today's date is, and gets the bank to set it, after
 * making sure that it's alright.
 *
 * NOTES: The new date can not be older than the current date.
 */
void UserInterface::set_date ()
{
	Date* todays_date;
	Month valid_month;
	unsigned short day, month, year;
	bool valid = false;

	do 
	{
		clearScreen ();
		cout << "Today's year is (YYYY format): ";
		cin >> year;

		cout << "\t1. January\n\t2. February\n\t3. March\n";
		cout << "\t4. April\n\t5. May\n\t6. June\n";
		cout << "\t7.July\n\t8. August\n\t9. September\n";
		cout << "\t10. October\n\t11. November\n\t12. December\n";
		cout << "Select today's month: ";
		cin >> month;

		cout << "Enter the day of the month: ";
		cin >> day;

		//valid = Date::is_valid (year, month, day);
		if (!valid)
		{
			cout << "That is not a correct date.\n";
			pressEnter ();
		}
	} while (!valid);
#if 0
	valid_month = convert_to_month (month);
	todays_date = new Date (year, valid_month, day);
	Bank::set_date (todays_date);
#endif
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

/* UserInterface::create_new_customer
 *
 * Prompts the user to enter the new customer's information.
 *
 * NOTES: Can not fail.
 *
 */
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

	clearScreen();
	cout << "Customer Created Successfully." << endl << "Your customer ID is " << customer.get_ID();
	pressEnter();
}

/* UserInterface::create_account
 * 
 * Asks the user which type of account they would like created, and how much
 *   money will be initially deposited.
 *
 * PARAMETERS: A customer for whom the account will be created.
 *
 * NOTES: Creation of the account will FAIL if the user already has an account
 *   of that type. In this case the user will be notified and prompted for a
 *   different account type.
 */
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
 * PARAMETERS: A Customer for whom we're dealing with, and a transaction_type
 *   for what type of transaction is occurring
 *
 * NOTES:
 *   Transfers are TO acct_no FROM acct_no; this is stored in two transactions
 */
void UserInterface::move_money(const Customer& cust, const transaction_type type)
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
