#ifndef TRANSACTIONMANAGER
#define TRANSACTIONMANAGER
#include <vector>

#include "Transaction.hh"

class TransactionManager
{
	std::vector <Transaction> transactions;
	const unsigned int acct_id;

	public:
	TransactionManager (const unsigned int owner_id);
	float apply_interest ();
	void apply_fines ();
	void archive_this_month ();
	Transaction get_last_transaction();
	std::vector<Transaction*> get_all_transactions();
};

#endif //TRANSACTIONMANAGER
