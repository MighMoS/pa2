#include <iostream>
#include <fstream>

#include "Bank.hh"

void Bank::log_transaction (const unsigned int id, const account_type type,
		const float amount)
{
	std::cout << "STUB: LOG_TRANSACTION. ID = " << id << ", amount = " << amount 
		<< std::endl;
}

// XXX: I'm not even sure what parameters this would take.
void Bank::write_customer_report (...)
{
	std::cout << "STUB: WRITE CUSTOMER REPORT\n";
}

Transaction::Transaction (const unsigned int account_id,
		const transaction_type its_type,
		const float the_amount,
		const short its_year,
		const short its_month,
		const short its_day):
	id (account_id), type (its_type), amount (the_amount),
	year (its_year), month (its_month), day (its_day)
{
}

// Rough Sketch of what it should do. In this plan save doesn't care where
// its writing, because some higher level method can worry about that.
void Transaction::save(std::ofstream& output)
{
	static const char sep = ' ';
	output << year << sep << month << sep << day << sep << type << amount
		<< std::endl;
}
