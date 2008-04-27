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
	void apply_fines ();
	void archive_this_month ();
};

#endif //TRANSACTIONMANAGER
