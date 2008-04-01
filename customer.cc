#include "Address.hh"
#include "customer.hh"
#include "UserInterface.hh"
#include "Account.hh"

#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;

unsigned int Customer::lastCustomerID = 0;

Customer::Customer(unsigned int id)
{
	Accounts.resize(3);
	Accounts[0]=0;
	Accounts[1]=0;
	Accounts[2]=0;
	int numbofacc, temp;
	ID=id;
	string path;
	string street,city,state,zip;
	std::stringstream stream; // Used for converting int to string
	std::ifstream file;

	stream << ID;

	path = "customers/" + stream.str() + ".txt";
	file.open (path.c_str());
	file >> F_Name >> L_Name;
	file >> numbofacc;
	for (int i=0;i<numbofacc;i++)
	{
		file >> temp;
		Accounts.push_back(temp);
	}
	file.sync();
	file.get();
	getline(file, street);
	file >>city >> state >> zip;
	address = new Address(street,city,state,zip);

}

Customer::Customer(string firstn, string lastn, Address* addr) :
	F_Name (firstn), L_Name (lastn), address (addr)
{
	Accounts.resize(3);
	Accounts[0]=0;
	Accounts[1]=0;
	Accounts[2]=0;
	ID = ++lastCustomerID;
}

Customer::~Customer()
{
	if (address)
		delete address;
}

/* Customer::save. Save a customer to the disk.
 * Takes no parameters, does not alter customer.
 * Opens customers/_ID_.txt, and writes out the necessary info.
 * We don't care if something was there earlier, its not anymore.
 */
void Customer::save (void) const
{
	const static string customer_s = "customers/";
	const static string txt = ".txt";

	string path;
	std::stringstream stream; // Used for converting int to string
	std::ofstream file;

	stream << ID;

	path = customer_s + stream.str() + txt;
	file.open (path.c_str()); 

	/* Format is:
	 * Bob Jenkins
	 * 2
	 * 30 50
	 * 1003 Some St, Somewhere, CA, 23412
	 */
	file << F_Name << " " << L_Name << endl;
	file << Accounts.size();
	for (unsigned int i = 0; i < Accounts.size(); i++)
		file << " " << Accounts[i];
	file << endl;
	file << *address << endl;

	file.close();
}

void Customer::set_Address(Address* new_add)
{
	if (address)
		delete address;
	address=new_add;
}

void Customer::transfer_money()
{
	//choose account
	//prompt second account (one of the customers 3 accounts, and then option for a completely different account.)
	//prompt money amount
	//call account1.withdraw(money)
	//call account2.deposit(money)
}

void Customer::withdraw_money()
{
	//choose account
	//prompt money amount
	//call account.withdraw(money)
}

void Customer::deposit_money()
{
	//choose acocunt
	//prompt money amount
	//call account.deposit(money)
}

// Should this be UserInterface:: ?
void Customer::change_customer_info()
{
	string newfirstname, newlastname;
	string newadd, newcit, newstat, newzip;
	cout << "Please enter Customers New Information." << endl;
	cout << "First Name: ";
	cin >> newfirstname;
	cout << "Last Name: ";
	cin >> newlastname;
	cout << "Street Address: ";
	cin.sync();
	cin.get();
	getline(cin, newadd);
	cout << "City: ";
	cin >> newcit;
	cout << "State: ";
	cin >> newstat;
	cout << "Zip Code: ";
	cin >> newzip;
	F_Name=newfirstname;
	L_Name=newlastname;
	Address* newaddress= new Address(newadd,newcit,newstat,newzip);
	set_Address (newaddress);
}

void Customer::close_account()
{
	//prompt user for account that needs to be closed.
	//call account.remove
}

// Should this be UserInterface::delete_customer ?
bool Customer::delete_customer()
{
	//prompt user if they're sure.
	//delete the customer.
	//return true if customer is deleted.
	return true;
}

void Customer::get_customer_info ()
{
	cout << F_Name << " " << L_Name << endl;
	if (address != NULL)
		cout << *address << endl;
	if (has_account(Checking))
	{
		cout << "Checking account number: " << Accounts[0] <<
			endl << "Account Balance: " << get_account_balance(Accounts[0]) << endl;
	}
	if (has_account(Savings))
	{
		cout << "Savings account number: " << Accounts[1] <<
			endl << "Account Balance: " << get_account_balance(Accounts[0]) << endl;
	}
	if (has_account(MoneyMarket))
	{
		cout << "Money Market account number: " << Accounts[2] <<
			endl << "Account Balance: " << get_account_balance(Accounts[0]) << endl;
	}
}

void Customer::setLastCustomerID (const unsigned int lastID)
{
	lastCustomerID = lastID;
}

unsigned int Customer::getLastCustomerID (void)
{
	return lastCustomerID;
}

/* Adds an account assuming the customer doesn't already have one of the same type.
 * Takes advantage of the fact that enums are numbers, and so we can use them as an 
 * index
 */
bool Customer::add_Account(const account_type type, const float bal)
{
	Account* acct;
	acct = new Account (bal, type);

	if (has_account (type) || !acct)
		return false;

	Accounts[type] = acct->get_id();
	acct->save();
	
	delete acct;
	return true;
}

bool Customer::has_account (const account_type type)
{
	return Accounts[type];
}

float Customer::get_account_balance(unsigned int accID)
{
	const static string customer_s = "accounts/";
	const static string txt = ".txt";

	string path;
	std::stringstream stream; // Used for converting int to string
	std::ifstream file;

	stream << accID;

	path = customer_s + stream.str() + txt;
	file.open (path.c_str());
	file >> accID;
	file.sync();
	file.get();
	float bal;
	file >> bal;
	return bal;	
}
