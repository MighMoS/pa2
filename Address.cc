#include <iostream>
#include "Address.hh"

std::ostream& operator << (std::ostream& os, const Address& rhs);

Address::Address (const string& str,
			const string& cty,
			const string& ste,
			const string& zip) :
	street (str), city (cty), state (ste), zip_code (zip)
{
}
