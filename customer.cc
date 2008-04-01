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
	if (!file.is_open())
	{
		std::cerr << "Could not open file: " << path << endl;
		return;
	}
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

	file.close();
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
	Account* acct;
	cout << F_Name << " " << L_Name << endl;
	if (address != NULL)
		cout << *address << endl;

	if (has_account(Checking))
	{
		acct = Account::get_account_by_id (Accounts[0]);
		cout << "Checking account number: " << acct->get_id () <<
			endl << "Account Balance: " << acct->get_balance () << endl;

		delete acct;
	}
	if (has_account(Savings))
	{
		acct = Account::get_account_by_id (Accounts[1]);
		cout << "Savings account number: " << acct->get_id () <<
			endl << "Account Balance: " << acct->get_balance () << endl;

		delete acct;
	}
	if (has_account(MoneyMarket))
	{
		acct = Account::get_account_by_id (Accounts[2]);
		cout << "Money Market account number: " << acct->get_id () <<
			endl << "Account Balance: " << acct->get_balance () << endl;

		delete acct;
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
	if (has_account(type))
		return false;
	Account* acct;
	acct = new Account (bal, type);

	if (!acct)
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

