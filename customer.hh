#ifndef CUSTOMER
#define CUSTOMER

#include <iostream>
#include <string>
#include <vector>
#include "Address.hh"
#include "Account.hh"
using std::vector;
using std::string;

/* Customer holds a pointer to an Address so that Address can be initialized later*/
class Customer
{
private:
	vector<int> Accounts;
	string F_Name;
	string L_Name;
	Address* address;
	int ID;

	static unsigned int lastCustomerID;
public:
	Customer(unsigned int id);  //Initialize customer off of their ID from a file.
	Customer(string firstn, string lastn, Address* addr);
	~Customer();

	void save(void) const;

	void set_First(string name){F_Name=name;}
	void set_Last(string name){L_Name=name;}
	void set_Address (Address* new_add);

	int get_ID(){return ID;}
	string get_FName(){return F_Name;}
	string get_LName(){return L_Name;}
	Address& get_Address(){return *address;}
	vector<int> get_Accounts(){return Accounts;}
	
	void get_customer_info();	
	bool add_Account(const account_type type, const float bal);
	void remove_Account(int acc);
	int search_Accounts(int acc);
	bool has_account(const account_type type);
	
	void transfer_money();
	void withdraw_money();
	void deposit_money();
	void change_customer_info();
	void close_account();
	float get_account_balance(unsigned int accID);

	bool delete_customer();

	static void setLastCustomerID(const unsigned int lastID);
	static unsigned int getLastCustomerID(void);
};

#endif
