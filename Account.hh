#ifndef ACCOUNT
#define ACCOUNT
#include <ostream>
#include <vector>

// We have three account types
enum account_type {Checking, Savings, MoneyMarket};

// Chosen to use floats because we don't need highly accurate precision.
class Account {
	const unsigned int id;
	float balance;
	const account_type type;
	const unsigned int owner;
	//TransactionManager* tm;
	
	static unsigned int last_account_id;

	friend std::ostream& operator << (std::ostream& os, const Account& rhs);

public:
	Account (const float initial_balance, const account_type its_type, const unsigned int custID);
	Account (const unsigned int id,
			const float init_bal,
			const account_type type,
			const unsigned int custID);

	float do_transaction(const float amount);

	unsigned int get_id (void) const;
	account_type get_type(void) const;
	float get_balance (void) const;
	unsigned int get_owner(void) const;

	void save(void) const;

	static void set_last_account_id (const unsigned int lastID);
	static unsigned int get_last_account_id (void);
	static Account* get_account_by_id (const unsigned int accID);
	static std::vector <Account*> get_all_accounts (void);
};

#endif // ACCOUNT
