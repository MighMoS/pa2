#include <iostream>
#include <string>

#include "Date.hh"

using std::string;

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

/* Writes out a Date in the format YYYY MM DD */
std::ostream& operator << (std::ostream& os, const Date& rhs)
{
	os << rhs.year << " " << Date::month_to_string (rhs.month) << " " << rhs.day;

	return os;
}

std::istream& operator >> (std::istream& is, Date& rhs)
{
	string month_string;
	is >> rhs.year;
	is >> month_string;
	is>> rhs.day;

	rhs.month = Date::string_to_month (month_string);

	return is;
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

string Date::month_to_string (const Month mo)
{
	switch (mo)
	{
		case January: return string("January");
		case February: return string("February");
		case March: return string("March");
		case April: return string("April");
		case May: return string("May");
		case June: return string("June");
		case July: return string("July");
		case August: return string("August");
		case September: return string("September");
		case October: return string("October");
		case November: return string("November");
		case December: return string("December");
	}
}

/* Date::string_to_month
 * Returns a Month representation of a month.
 *
 * NOTES: Returns January if we get something weird.
 */
Month Date::string_to_month (const string mo)
{
	Month month;
	if (mo == "January")
		return month = January;
	if (mo == "February")
		return month = February;
	if (mo == "March")
		return month = March;
	if (mo == "April")
		return month = April;
	if (mo == "May")
		return month = May;
	if (mo == "June")
		return month = June;
	if (mo == "July")
		return month = July;
	if (mo == "August")
		return month = August;
	if (mo == "September")
		return month = September;
	if (mo == "October")
		return month = October;
	if (mo == "November")
		return month = November;
	if (mo == "December")
		return month = December;
	
	// For some reason we've gotten garbage!
	return month = January;
}
