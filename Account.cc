#include <iostream>

#include "Account.hh"
#include "Bank.hh"

unsigned int Account::last_account_id = 0; 

// Creates a new account, with ID based on previous last highest ID
Account::Account (const float initial_balance, const account_type its_type) :
	id (last_account_id++), type (its_type), balance (initial_balance)
{
};	

// XXX: Should this really be handled here? I don't think so. Something higher
// level like Bank ``might should'', so that we can more better handle things
// like logging
float Account::do_transaction (const float amount)
{
	//XXX: This is now wrong, and should be handled by the tm
	Bank::log_transaction (id, type, amount);
	return balance += amount;
}

unsigned int Account::get_id (void) const
{
	return id;
}

account_type Account::get_type(void) const
{
	return type;
}

float Account::get_balance (void) const
{
	return balance;
}

unsigned int Account::get_last_account_id (void)
{
	return last_account_id;
}
