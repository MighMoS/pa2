#ifndef BANK
#define BANK
#include <fstream>

#include "Account.hh"

class Bank {
public:
	static void log_transaction (const int id, const account_type type, 
			const float amount);
	static void write_customer_report (...);
};

// XXX: This isn't all, is it?
enum transaction_type {Deposit, Withdrawal, Check};

// XXX: Is this needed? And should we do this or use a time_t object?
class Transaction {
	const int id;
	const float amount;
	const short year, month, day;
	const transaction_type type;

	public:
	
	int get_account_id (void) const;
	float get_amount (void) const;
	void save(std::ofstream& output);

	Transaction (const int account_id,
			const transaction_type its_type,
			const float the_amount,
			const short its_year,
			const short its_month,
			const short its_day);
};

#endif // BANK
