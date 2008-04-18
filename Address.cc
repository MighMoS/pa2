#include <iostream>
#include <string>

#include "Address.hh"

using std::cout;
using std::endl;
using std::string;

std::ostream& operator << (std::ostream& os, const Address& rhs)
{
	os << rhs.street << endl << rhs.city << " " << rhs.state << " " << rhs.zip_code;

	return os;
}

Address::Address (const string& str,
			const string& cty,
			const string& ste,
			const string& zip) :
	street (str), city (cty), state (ste), zip_code (zip)
{
}

void Address:: set (const string& str,
			const string& cty,
			const string& ste,
			const string& zip)
{
	street=str;
	city=cty;
	state=ste;
	zip_code=zip;
}
