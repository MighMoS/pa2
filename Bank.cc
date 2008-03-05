#include <iostream>

#include "Bank.hh"

void Bank::log_transaction (const int id, const account_type type, const float amount)
{
	std::cout << "STUB: LOG_TRANSACTION. ID = " << id << ", amount = " << amount 
		<< std::endl;
}

void Bank::write_customer_report (...)
{
	std::cout << "STUB: WRITE CUSTOMER REPORT\n";
}

Transaction::Transaction (const int account_id, const float the_amount):
	id (account_id), amount (the_amount)
{
};
