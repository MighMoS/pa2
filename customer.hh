#ifndef CUSTOMER
#define CUSTOMER

#include <string>
#include <vector>

#include "Address.hh"
#include "Account.hh"

/* Customer holds a pointer to an Address so that Address can be initialized later*/
class Customer
{
private:
	std::vector<unsigned int> Accounts;
	string F_Name;
	string L_Name;
	Address* address;
	const int ID;

	static unsigned int lastCustomerID;
public:
	Customer(const unsigned int id);  //Initialize customer off of their ID from a file.
	Customer(const string firstn, const string lastn, Address* addr);
	~Customer();

	void save(void) const;

	void set_Address (Address* new_add);
	void change_name (const string& first, const string& last);

	int get_ID() const {return ID;}
	string get_FName() const {return F_Name;}
	string get_LName() const {return L_Name;}
	Address& get_Address() const {return *address;}
	std::vector<unsigned int> get_Accounts() const {return Accounts;}
	
	void get_customer_info () const;
	bool add_Account(const account_type type, const float bal);
	void remove_Account (const unsigned int acc);
	int search_Accounts (const unsigned int acc) const;
	bool has_account (const account_type type) const;
	
	void change_customer_info();
	void close_account();

	bool delete_customer();

	static void setLastCustomerID(const unsigned int lastID);
	static unsigned int getLastCustomerID(void);
	static std::vector<Customer*> get_all_custs();
	
	bool testName(string name);
	bool testAddress(string add);
};

#endif
