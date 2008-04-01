#include "TransactionManager.hh"

TransactionManager::TransactionManager (unsigned int owner_id) : id (owner_id)
{
}

void TransactionManager::archive_this_month ()
{
}

void TransactionManager::record_transaction (Transaction *t)
{
}

bool TransactionManager::check_for_fines ()
{
	return false;
}
