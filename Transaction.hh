#ifndef TRANSACTION
#define TRANSACTION
#include "Date.hh"
#include <ostream>

enum transaction_type {Deposit, Withdrawal, Check, Transfer, Interest, BankFee, InitialDeposit};

class Transaction {
	const unsigned int id;
	const float amount;
	const transaction_type type;
	const Date date;
	
	friend std::ostream& operator << (std::ostream& os, const Transaction& rhs);

	public:
	
	unsigned int get_account_id (void) const;
	float get_amount (void) const;
	Date get_date();
	void save() const;

	Transaction (const unsigned int account_id,
			const transaction_type its_type,
			const float the_amount,
			const Date& its_date);

	// Fires off the transaction to happen
	void process (void);
};

#endif
