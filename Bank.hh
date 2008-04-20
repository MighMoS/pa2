#ifndef BANK
#define BANK

#include "Account.hh"
#include "Date.hh"
#include "customer.hh"

class Bank {
	static Date* today;
public:
	static void save_status (void);
	static void log_transaction (const unsigned int id,
			const account_type type, 
			const float amount);
	static void write_customer_report (...);
	static void save (void);
	static bool init (void);
	static bool process_accounts ();

	static bool set_date (Date* newday, const bool override = false);

	friend void Customer::setLastCustomerID(const unsigned int lastID);
	friend void Account::set_last_account_id (const unsigned int lastID);
};

#endif // BANK
