#ifndef ACCOUNT
#define ACCOUNT
#include <ostream>
#include <vector>

#include "TransactionManager.hh"
#include "Transaction.hh"

// We have three account types
enum account_type {Checking, Savings, MoneyMarket};

// Chosen to use floats because we don't need highly accurate precision.
class Account {
	const unsigned int id;
	float balance;
	const account_type type;
	const unsigned int owner;

	bool fined;
	TransactionManager* tm;
	
	static unsigned int last_account_id;

	friend std::ostream& operator << (std::ostream& os, const Account& rhs);

public:
	Account (const float initial_balance, const account_type its_type, const unsigned int custID);
	Account (const unsigned int id,
			const float init_bal,
			const account_type type,
			const unsigned int custID,
			const bool has_fine);

	float do_transaction(const float amount);

	unsigned int get_id (void) const;
	account_type get_type(void) const;
	float get_balance (void) const;
	unsigned int get_owner(void) const;

	/* These are needed for process monthly accounts,
	 * and the apply*s just forward to the TM
	 */
	float apply_interest (void);
	void apply_fines (void);
	void archive (void);
	void set_unfined (void) {fined = false;};
	void set_fined (void) {fined = true;save();};
	bool is_fined (void) {return fined;};
	
	bool is_over_FDIC(); //Returns true if balance is over 100,000
	bool is_active(); //Returns true if a transaction has been made in the past year
	
	//These are all based on the transactions since archive was last called.
	float get_beggining_balance(); //Get the origional balance
	std::vector<Transaction*> get_all_Transactions(); // Returns all the transactions for this account
	float all_deposits(); //Returns the total amount going into the account
	float all_withdrawls(); //Returns the total ammount leaving the account

	void save(void) const;

	static void set_last_account_id (const unsigned int lastID);
	static unsigned int get_last_account_id (void);
	static Account* get_account_by_id (const unsigned int accID);
	static std::vector <Account*> get_all_accounts (void);
};

#endif // ACCOUNT
