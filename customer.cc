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

	unsigned int temp;
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
	for (int i=0;i<3;i++)
	{
		file >> temp;
		Accounts[i]=temp;
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
	 * Bob Jenkins   (Name)
	 * 20 30 50  (the 3 account Numbers)
	 * 1003 Some St, Somewhere, CA, 23412  (Address)
	 */
	file << F_Name << " " << L_Name << endl;
	for (unsigned int i = 0; i < 3; i++)
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
	save();
}

void Customer::close_account()
{
	bool repeat=true;
	unsigned int choice;
	while(repeat)
	{
		cout << "Select account to close (";
		if (has_account(Checking))
		{
			cout << Accounts[0] << ". Checking ";
		}
		if (has_account(Savings))
		{
			cout << Accounts[1] << ". Savings ";
		}
		if (has_account(MoneyMarket))
		{
			cout << Accounts[2] << ". Money Market";
		}
		cout << ")" << endl;
		cin >> choice;
		if (choice == 0)
			break;
		if (choice != Accounts[0]&& choice != Accounts[1] && choice != Accounts[2])
			cout << "Not a valid Choice, please enter a Valid choice, or 0 to quit." << endl;
		else
			repeat=false;
	}
	if (choice!=0)
	{
		string path;
		std::stringstream stream; // Used for converting int to string
		std::ofstream file;
		stream << choice;
		path = "accounts/" + stream.str() + ".txt";
		remove(path.c_str());
		if (choice == Accounts[0])
			Accounts[0]=0;
		if (choice == Accounts[1])
			Accounts[1]=0;
		if (choice == Accounts[2])
			Accounts[2]=0;
	}
	save();

}

// Should this be UserInterface::delete_customer ?
bool Customer::delete_customer()
{
	string temp="a";
	if (Accounts[0]==0 && Accounts[1]==0 && Accounts[2]==0)
	{
		while (temp[0]!='Y' && temp[0]!='y' && temp[0]!='N' && temp[0]!='n')
		{
			cout << "Are you sure you wish to Delete this Customers accounts?" << endl;
			cin >> temp;
			if (temp[0]!='Y' && temp[0]!='y' && temp[0]!='N' && temp[0]!='n')
			cout << endl << "Please Enter Y for yes, or N for no." << endl;
		}
		if (temp[0]=='N' && temp[0]=='n')
		{	cout << "No Action taken." << endl;
			return false;
		}
		string path;
		std::stringstream stream; // Used for converting int to string
		std::ofstream file;
		stream << ID;
		path = "customers/" + stream.str() + ".txt";
		remove(path.c_str());
		return true;	
	}
		cout << "Customer Still has Active accounts.  Close Customers Accounts before Removing the Customer." << endl;
		return false;
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

