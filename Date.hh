#ifndef DATE
#define DATE

enum Month {January, February, March, April, May, June,
		July, August, September, October, November, December};

class Date {
	unsigned short year;
	Month month;
	unsigned short day;

	public:
	Date (const unsigned short i_year, const Month i_month,
		const unsigned short i_day);

	bool operator < (const Date& rhs) const;

	static bool is_valid_date (const unsigned short i_yr, const Month i_mo,
	const unsigned short i_day);
};

#endif
