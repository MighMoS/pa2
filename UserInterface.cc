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
		if (month > 12)
		{
			cout << "That is not a valid choice.\n";
			pressEnter ();
			continue;
		}
		valid_month = Month (month - 1); // Adjust for 0 base

		cout << "Enter the day of the month: ";
		cin >> day;

		valid = Date::is_valid_date (year, valid_month, day);
		if (!valid)
		{
			cout << "That is not a correct date.\n";
			pressEnter ();
			continue;
		}
		else
		{
			todays_date = new Date (year, valid_month, day);
			if (!todays_date)
			{
				std::cerr << "Error allocating today's date.\n";
				exit (1);
			}
		}
			
		// Date should not be freed -- or interesting things will happen
		valid = Bank::set_date (todays_date);
		if (!valid)
		{
			bool sane = false;
			while (!sane)
			{
				string input;
				cout << "That date is older than the current one!\n";
				cout << "Override? (Y/N): ";
				cin >> input; // I'ma use this because its already here.
				if (input[0] == 'Y' || 'y')
				{
					sane = true;
					Bank::set_date (todays_date, true);
				}
				else if (input[0] == 'N' || 'n')
				{
					sane = true;
					continue;
				}
			}
		}
	} while (!valid);

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
		cout << "\t\t1. Checking\n";
		cout << "\t\t2. Savings\n";
		cout << "\t\t3. Money Market\n";
		cout << "\t\t4. Cancel\n";
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

	cust_trans = new Transaction (first_acct, type, money, *Bank::get_date());
	cust_trans->process();
	delete cust_trans;
	if (type == Transfer)
	{
		// This is a withdraw, so subtract money
		cust_trans = new Transaction (second_acct, type,
				money * -1, *Bank::get_date());
		cust_trans->process();
		delete cust_trans;
	}
}

void UserInterface::ListAllAccounts (void)
{
	clearScreen();
	vector<Account*> all_accts;
	string input;

	all_accts = Account::get_all_accounts ();
	for (unsigned int i = 0; i < all_accts.size (); i++)
	{
		cout << *(all_accts[i]) << endl;

		if (i % 3 == 2)
		{
			do
			{
				cout << "Enter  n for Next, or q for Quit: ";
				cin >> input;
			} while (input[0] != 'n' && input[0] != 'N' &&
					input[0] != 'q' && input[0] != 'Q');
			clearScreen();
			if (input [0] == 'Q' || input[0] == 'q')
				break;
		}
		if (i==all_accts.size()-1)
		{
			cout << "Press Enter to Continue";
			pressEnter();
		}
	}
	for (unsigned int i = 0; i < all_accts.size (); i++)
		delete all_accts[i];
}

void UserInterface::lookup_by_name()
{
	clearScreen();
	vector<Customer*> all_custs;
	all_custs= Customer::get_all_custs();
	vector<Customer*> results;
	string search;
	string input;
	
	
	cout << "Enter the Name of the Customer you are looking for: ";
	cin >> search;
	clearScreen();
	for(unsigned int i=0;i<all_custs.size();i++)
	{
		if (all_custs[i]->testName(search))
			results.push_back(all_custs[i]);
	}
	
	for (unsigned int i = 0; i < results.size (); i++)
	{
		cout << "Customer " << results[i]->get_ID() << endl;
		cout << "Name: " << results[i]->get_FName() << " "
			<< results[i]->get_LName() << endl << endl;

		if (i % 5 == 4)
		{
			do
			{
				cout << "Enter  n for Next, or q for Quit: ";
				cin >> input;
			} while (input[0] != 'n' && input[0] != 'N' &&
					input[0] != 'q' && input[0] != 'Q');
			clearScreen();
			if (input [0] == 'Q' || input[0] == 'q')
				break;
		}
		if (i==results.size()-1)
		{
			cout << "Press Enter to Continue";
			pressEnter();
		}
	}
	if (results.size()==0)
	{
		cout << "No Customers found with matching data." << endl;
		pressEnter();
	}
	
		for (unsigned int i = 0; i < all_custs.size (); i++)
		delete all_custs[i];

}

void UserInterface::lookup_by_address()
{
	
	clearScreen();
	vector<Customer*> all_custs;
	all_custs= Customer::get_all_custs();
	vector<Customer*> results;
	string search;
	string input;
	
	
	cout << "Enter part of the Address of the Customer you are looking for: ";
#ifndef WINDOWS
	cin.sync();
	cin.get();
#endif
	cin.get();
	getline(cin, search);
	cin.putback('a');
	clearScreen();
	for(unsigned int i=0;i<all_custs.size();i++)
	{
		if (all_custs[i]->testAddress(search))
			results.push_back(all_custs[i]);
	}
	
	for (unsigned int i = 0; i < results.size (); i++)
	{
		cout << "Customer " << results[i]->get_ID() << endl;
		cout << "Name: " << results[i]->get_FName() << " "
			<< results[i]->get_LName() << endl << endl;

		if (i % 5 == 4)
		{
			do
			{
				cout << "Enter  n for Next, or q for Quit: ";
				cin >> input;
			} while (input[0] != 'n' && input[0] != 'N' &&
					input[0] != 'q' && input[0] != 'Q');
			clearScreen();
			if (input [0] == 'Q' || input[0] == 'q')
				break;
		}
		if (i==results.size()-1)
		{
			cout << "Press Enter to Continue";
			pressEnter();
		}
	}
	if (results.size()==0)
	{
		cout << "No Customers found with matching data." << endl;
		pressEnter();
	}
	
		for (unsigned int i = 0; i < all_custs.size (); i++)
		delete all_custs[i];

}


void UserInterface::write_financial_report()
{
	clearScreen();
	vector<Account*> all_accts;
	float total_money=0;
	float estimate_interest=0;
	account_type type;
	
	all_accts = Account::get_all_accounts ();
	
	for(unsigned int i=0;i<all_accts.size();i++)
	{
		total_money+=(*all_accts[i]).get_balance();
		type = (*all_accts[i]).get_type();
		switch(type)
		{
			case Savings:
				estimate_interest += (((*all_accts[i]).get_balance()) * .015);
				break;
			case MoneyMarket:
				estimate_interest += (((*all_accts[i]).get_balance()) * .030);
				break;
			default:
				break;
		}
	}
	std::stringstream stream;
	std::ofstream file;
	stream << "reports/F_" <<((*Bank::get_date()).get_month()) << '_' << ((*Bank::get_date()).get_year()) << ".txt";
	file.open(stream.str().c_str());
	if (!file.is_open())
	{
		std::cerr << "Could not open " << stream.str() << " for writing.\nCheck\
		check to make sure that the folder exists, and that your\
		permissions are correct.\n";
		exit (1);
	}
	
	file << "Total Money in Bank: " << total_money << endl;
	file << "Previous Months Interest: " << (Bank::get_last_interest()) << endl;
	file << "Estimate of This Months interest: " << estimate_interest << endl;
	file.close();
	for (unsigned int i = 0; i < all_accts.size (); i++)
		delete all_accts[i];
}

void UserInterface::write_account_report()
{
	clearScreen();
	vector<Account*> all_accts;
	vector<Account*> inactive, below, above;
	vector<unsigned int> custs;
	account_type type;
	unsigned int check=0, save=0, mon=0;
	
	all_accts = Account::get_all_accounts ();
	
	for(unsigned int i=0;i<all_accts.size();i++)
	{
		if (!(*all_accts[i]).is_active())
			inactive.push_back(all_accts[i]);
		if ((*all_accts[i]).is_over_FDIC())
		{
			above.push_back(all_accts[i]);
			custs.push_back((*all_accts[i]).get_owner());
		}
		type = (*all_accts[i]).get_type();
		switch(type)
		{
			case Checking:
				if( (*all_accts[i]).get_balance()<100)
					below.push_back(all_accts[i]);
				check++;
				break;
			case Savings:
				if( (*all_accts[i]).get_balance()<1000)
					below.push_back(all_accts[i]);
				save++;
				break;
			case MoneyMarket:
				if( (*all_accts[i]).get_balance()<10000)
					below.push_back(all_accts[i]);
				mon++;
				break;
			default:
				break;
		}
	}
	
	std::stringstream stream;
	std::ofstream file;
	stream << "reports/A_" <<((*Bank::get_date()).get_month()) << '_' << ((*Bank::get_date()).get_year()) << ".txt";
	file.open(stream.str().c_str());
	if (!file.is_open())
	{
		std::cerr << "Could not open " << stream.str() << " for writing.\nCheck\
		check to make sure that the folder exists, and that your\
		permissions are correct.\n";
		exit (1);
	}
	
	file << "Number of Checking Accounts: " << check << endl;
	file << "Number of Savings Accounts: " << save << endl;
	file << "Number of Money Market Accounts: " << mon << endl << endl;
	file << "All Accounts Under the Minimum Balance: " << endl << endl;
	for(unsigned int i=0;i<below.size();i++)
		file << (*below[i]) << endl << endl;
	file << endl <<"All Accounts over the FDIC Maximum Balance: " << endl << endl;
	for(unsigned int i=0;i<above.size();i++)
		file << (*above[i]) << endl << endl;
	file << endl <<"All Customers with accounts over the FDIC Maximum Balance: " << endl << endl;
	for(unsigned int i=0;i<custs.size();i++)
	{
		Customer cust(custs[i]);
		file << "Customer " << cust.get_ID() << endl;
		file << cust.get_FName() << " " << cust.get_LName() << endl;
		file << (cust.get_Address()) << endl << endl;
	}	
	file.close();
	for (unsigned int i = 0; i < all_accts.size (); i++)
		delete all_accts[i];
}

void UserInterface::write_customer_reports()
{
	clearScreen();
	account_type type;
	vector<Account*> all_accts;
	all_accts = Account::get_all_accounts ();
	vector<Transaction*> transactions;
	for(unsigned int i=0;i<all_accts.size();i++)
	{
		std::stringstream stream;
		std::ofstream file;
		stream << "reports/customer/" << all_accts[i]->get_id()
		       << '_' << ((*Bank::get_date()).get_month()) << '_' 
		       << ((*Bank::get_date()).get_year()) << ".txt";
		file.open(stream.str().c_str());
		if (!file.is_open())
		{
			std::cerr << "Could not open " << stream.str() << " for writing.\nCheck\
			check to make sure that the folder exists, and that your\
			permissions are correct.\n";
			exit (1);
		}
		
		Customer cust(all_accts[i]->get_owner());
		transactions=all_accts[i]->get_all_Transactions();
		file << cust.get_FName() << " " << cust.get_LName() << endl;
		file << cust.get_Address() << endl << endl;
		
		type=all_accts[i]->get_type();
		switch(type)
		{
			case Checking:
				file << "Checking ";
				break;
			case Savings:
				file << "Savings ";
				break;
			case MoneyMarket:
				file << "Money Market ";
				break;
		}
		file << "Account number: " << all_accts[i]->get_id() << endl;
		file << "Starting Balance: " << all_accts[i]->get_beggining_balance() << endl;
		file << "Ending Balance: " << all_accts[i]->get_balance() << endl << endl;
		
		file << "Total Amount deposited in account: " << all_accts[i]->all_deposits() << endl;
		file << "Total Amount withdrawn from account: " << all_accts[i]->all_withdrawls() << endl << endl;
		
		file << "List of this months Transactions: " << endl;
		
		for(unsigned int i=0;i<transactions.size();i++)
		{
			file << *transactions[i] << endl;
			delete transactions[i];
		}
		transactions.clear();
		file.close();
	}
	for (unsigned int i = 0; i < all_accts.size (); i++)
		delete all_accts[i];
}
