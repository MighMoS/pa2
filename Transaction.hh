#ifndef TRANSACTION
#define TRANSACTION
enum transaction_type {Deposit, Withdrawal, Check, Transfer, Interest, BankFee};

class Transaction {
	const unsigned int id;
	const float amount;
	const transaction_type type;

	//const short year, month, day;

	public:
	
	unsigned int get_account_id (void) const;
	float get_amount (void) const;
	void save(std::ofstream& output) const;

	Transaction (const unsigned int account_id,
			const transaction_type its_type,
			const float the_amount);
#if 0
			const short its_year,
			const short its_month,
			const short its_day);
#endif
	// Fires off the transaction to happen
	void process (void);
};

#endif
