#ifndef BANK
#define BANK
#include <fstream>

#include "Account.hh"

class Bank {
public:
	static void save_status (void);
	static void log_transaction (const unsigned int id,
			const account_type type, 
			const float amount);
	static void write_customer_report (...);
};

#endif // BANK
