#ifndef ACCOUNT
#define ACCOUNT
#include "TransactionManager.hh"

// We have three account types
enum account_type {Checking, Savings, MoneyMarket};

// Chosen to use floats because we don't need highly accurate precision.
class Account {
	const unsigned int id;
	float balance;
	const account_type type;
	//TransactionManager* tm;
	
	static unsigned int last_account_id;
public:
	Account (const float initial_balance, const account_type its_type);
	Account (const unsigned int id,
			const float init_bal,
			const account_type type);

	float do_transaction(const float amount);

	unsigned int get_id (void) const;
	account_type get_type(void) const;
	float get_balance (void) const;

	void save(void) const;

	static void set_last_account_id (const unsigned int lastID);
	static unsigned int get_last_account_id (void);
	static Account* get_account_by_id (const unsigned int accID);
};

#endif // ACCOUNT
