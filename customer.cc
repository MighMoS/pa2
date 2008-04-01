#include "Address.hh"
#include "customer.hh"
#include "UserInterface.hh"

#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;

unsigned int Customer::lastCustomerID = 0;

Customer::Customer(unsigned int id)
{
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
	file >> street >> city >> state >> zip;
		address = new Address(street,city,state,zip);
}

Customer::Customer(string firstn, string lastn, Address* addr) :
	F_Name (firstn), L_Name (lastn), address (addr)
{
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
		cout << Accounts[i] << " ";
	file << endl;
	file << address << endl;

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
		cout << *address;
	//If (has account) cout Account type and balance.   Do for all 3 account types.
}

unsigned int Customer::getLastCustomerID (void)
{
	return lastCustomerID;
}
