#include <iostream>

#include "Account.hh"
#include "Transaction.hh"

Transaction::Transaction (const unsigned int account_id,
		const transaction_type its_type,
		const float the_amount) :
#if 0
		const Date its_date) :
		date (its_date),

#endif
	id (account_id), amount (the_amount), type (its_type)
{
}

void Transaction::process (void)
{
	Account* acct;
	acct = Account::get_account_by_id (id);
	if (!acct)
	{
		std::cerr << "Account " << id << " doesn't exist to be processed. This shouldn't happen!\n";
		exit (1);
	}

	// We don't have to worry about the account type, because all can
	// add/subtract money. Also, the amount is presigned (negative if needed)
	acct->do_transaction (amount);

	// save ();

	delete acct;
}

#if 0
// Rough Sketch of what it should do. In this plan save doesn't care where
// its writing, because some higher level method can worry about that.
void Transaction::save()
{
	static const char sep = ' ';
	output << year << sep << month << sep << day << sep << type << amount
		<< std::endl;
}
#endif
