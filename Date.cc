#include "Date.hh"

/* Date::Date()
 * Constructs a new date, in YYYY MM DD format.
 */
Date::Date (const unsigned short i_year, const Month i_month, const unsigned short i_day) :
year (i_year), month (i_month), day (i_day)
{
}

bool Date::operator < (const Date& rhs) const
{
	if (year < rhs.year)
		return true;
	else if (year > rhs.year)
		return false;
	if (month < rhs.month)
		return true;
	else if (month > rhs.month)
		return false;
	if (day < rhs.day)
		return true;
	
	return false;
}

