#ifndef TRANSACTIONMANAGER
#define TRANSACTIONMANAGER
#include <vector>

#include "Account.hh"
#include "Transaction.hh"

class TransactionManager
{
	std::vector <Transaction> transactions;
	const unsigned int acct_id;
	const account_type type;

	public:
	TransactionManager (const unsigned int owner_id,
			const account_type its_type);
	void apply_fines ();
	void archive_this_month ();
};

#endif //TRANSACTIONMANAGER
