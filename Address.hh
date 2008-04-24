#ifndef ADDRESS
#define ADDRESS
#include <ostream>
#include <string>

using std::string;

class Address
{
	string street;
	string city;
	string state;
	string zip_code;

	friend std::ostream& operator << (std::ostream& os, const Address& rhs);
	
	public:
	Address (const string& str, const string& cty, const string& ste, const string& zip);
			
	void set (const string& str, const string& cty, const string& ste, const string& zip);
	
	string get_street(){return street;}

};
#endif
