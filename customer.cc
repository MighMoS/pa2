#include "customer.hh"

unsigned int Customer::lastCustomerID = 0;



	Customer::Customer(unsigned int id)
	{
		ID=id;
		//Search customer file for their ID.
		//read in that Information to intialize F_Name L_Name Address
	}
	Customer::void add_Account(string type);
	
	Customer::void remove_Account(int acc);
	
	Customer::int search_Accounts(int acc);
	
	
	Customer::void transfer_money()
	{
		//choose account
		//prompt second account (one of the customers 3 accounts, and then option for a completely different account.)
		//prompt money amount
		//call account1.withdraw(money)
		//call account2.deposit(money)
	}
	
	Customer::void withdraw_mondey()
	{
		//choose account
		//prompt money amount
		//call account.withdraw(money)
	}
	
	Customer::void deposit_money()
	{
		//choose acocunt
		//prompt money amount
		//call account.deposit(money)
	}
	
	Customer::void change_customer_info()
	{
		string newfirstname, newlastname;
		Address newaddress;
		//prompt user for new First name
		//prompt user for new Last name
		//prompt user for new Address
		F_Name=newfirstname;
		L_Name=newlastname;
		address=newaddress;
	}
	
	Customer::void close_account()
	{
		//prompt user for account that needs to be closed.
		//call account.remove
	}
	
	Customer::bool delete_customer()
	{
		//prompt user if they're sure.
		//delete the customer.
		//return true if customer is deleted.
	}
