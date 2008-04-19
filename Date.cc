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

/* Date::is_valid_date
 * Checks to make sure that a date CAN occur
 *
 * PARAMETERS: a ushort year, Month, and a ushort day
 *
 * Notes: doesn't check to see how logical a date is.
 *   January 16, 1423 would return true
 *
 *   Also doesn't consider leap years.
 */
bool Date::is_valid_date (const unsigned short i_yr, const Month i_mo,
	const unsigned short i_day)
{
	// No month has more than 31 days.
	if (i_day > 31 || i_yr < 100) // Reject the '96 or '04 format
		return false;
	if (i_mo == February && i_day > 29)
		return false;
	// Thirty days hath September, April, June, and November
	if ((i_mo == April || i_mo == June ||
		i_mo == September || i_mo == November) && i_day > 30)
		return false;
	// All the rest have 31 (except for the corner case above)
	return true;
}
