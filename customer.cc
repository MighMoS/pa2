#include "customer.hh"

unsigned int Customer::lastCustomerID = 0;

Customer::Customer(unsigned int id)
{
	ID=id;
	//Search customer file for their ID.
	//read in that Information to intialize F_Name L_Name Address
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

void Customer::change_customer_info()
{
	string newfirstname, newlastname;
	Address* newaddress;
	//prompt user for new First name
	//prompt user for new Last name
	//prompt user for new Address
	//newaddress = new Address(string, string, blah);
	F_Name=newfirstname;
	L_Name=newlastname;
	set_Address (newaddress);
}

void Customer::close_account()
{
	//prompt user for account that needs to be closed.
	//call account.remove
}

bool Customer::delete_customer()
{
	//prompt user if they're sure.
	//delete the customer.
	//return true if customer is deleted.
}
