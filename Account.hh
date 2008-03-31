#ifndef ACCOUNT
#define ACCOUNT
#include "TransactionManager.hh"

// We have three account types
enum account_type {Savings, Checking, MoneyMarket};

// Chosen to use floats because we don't need highly accurate precision.
class Account {
	const unsigned int id;
	const account_type type;
	float balance;
	TransactionManager* tm;
	
	static unsigned int last_account_id;
public:
	Account(const float initial_balance, const account_type its_type);
	float do_transaction(const float amount);

	unsigned int get_id (void) const;
	account_type get_type(void) const;
	float get_balance (void) const;

	void save(void) const;

	static unsigned int get_last_account_id (void);
};

#endif // ACCOUNT
