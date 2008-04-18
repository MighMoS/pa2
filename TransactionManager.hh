#ifndef TRANSACTIONMANAGER
#define TRANSACTIONMANAGER
#include <vector>
#include <fstream>

#include "Transaction.hh"

class Log
{
	std::vector <Transaction> transactions;
	std::ofstream logFile;
	unsigned int owner_id;

	public:
	Log (unsigned int owner_id);
	void record_transaction (Transaction t);
};

class TransactionManager
{
	const int id;
	Log* monthLog;
	Log* archiveLog;

	public:
	TransactionManager (unsigned int owner_id);
	void archive_this_month ();
	void record_transaction (Transaction *t);
	bool check_for_fines ();
};

#endif //TRANSACTIONMANAGER
