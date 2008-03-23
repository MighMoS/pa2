#ifndef CUSTOMER
#define CUSTOMER

#include <iostream>
#include <string>
#include <vector>
#include "Address.hh"

class Customer
{
private:
	int ID;
	string F_Name;
	string L_Name;
	Address address;
	vector<int> Accounts;
	static unsigned int lastCustomerID;
public:
	void set_ID(int num){ID=num};
	void set_First(string name){F_Name=name};
	void set_Last(string name){L_Name=name};
	void set_Address(Address add){address=add;};
	int get_ID(){return ID};
	string get_FName(){return F_Name};
	string get_LName(){return L_Name};
	Address& get_Address(){return address};
	vector<int> get_Accounts(){return Accounts};
	
	void add_Account(string type);
	void remove_Account(int acc);
	int search_Accounts(int acc);
	void update_Address(string Address);
};
