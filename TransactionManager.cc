#include <fstream>
#include <sstream>

#ifdef DEBUG
#include <iostream>
#endif

#include "Bank.hh"
#include "Date.hh"
#include "Transaction.hh"
#include "TransactionManager.hh"

TransactionManager::TransactionManager (const unsigned int owner_id) :
	acct_id (owner_id)
{
}

void TransactionManager::archive_this_month ()
{
}

/* Do we even need a vector of transactions? We could just dump everything but
 * the amount of the transaction (the 5th thing written out)
 */
void TransactionManager::apply_fines ()
{
	bool fined = false;
	float curr_balance;
	std::ifstream ifile;
	std::stringstream ss;

	ss << "logs/c" << acct_id << ".txt";
	ifile.open (ss.str().c_str());
	if (!ifile.is_open())
	{
		std::cerr << "Error opening file " << ss.str().c_str() << ".\n";
		exit (1);
	}

	// fill up transactions
	// forall (trans)
	// 	curr_balance += amount;
	// 	if (curr_balance < min)
	// 	  apply_correct_fine ()
	// 	  fined = true; // Don't fine multiple times for the same infraction
	// 	else
	// 	  fined = false; // We're above min, start fining again

	ifile.close ();
}
