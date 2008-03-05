#ifndef BANK
#define BANK
#include "Account.hh"

class Bank {
public:
	static void log_transaction (const int id, const account_type type, 
			const float amount);
	static void write_customer_report (...);
};

// XXX: Is this needed?
class Transaction {
	const int id;
	const float amount;

	public:
	int get_account_id (void) const;
	float get_amount (void) const;
	Transaction (const int account_id, const float the_amount);
};

#endif // BANK
