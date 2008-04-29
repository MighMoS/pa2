#ifndef DATE
#define DATE
#include <iostream>
#include <string>

enum Month {January, February, March, April, May, June,
		July, August, September, October, November, December};

class Date {
	unsigned short year;
	Month month;
	unsigned short day;

	friend std::ostream& operator << (std::ostream& os, const Date& rhs);
	friend std::istream& operator >> (std::istream& is, Date& rhs);

	public:
	Date (const unsigned short i_year, const Month i_month,
		const unsigned short i_day);
		
	unsigned short get_year() {return year;};

	bool operator < (const Date& rhs) const;

	static bool is_valid_date (const unsigned short i_yr, const Month i_mo,
		const unsigned short i_day);
	static std::string month_to_string (const Month mo);
	static Month string_to_month (const std::string mo);
};

#endif
