// Date.cpp
// Member-function definitions for class Date.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "Date.h"

extern bool leapYear(unsigned int year);

Date::Date()
{
	year = 2000;
	month = 0;
	day = 0;
}

void Date::setYear(unsigned int y)
{
	year = (y >= 2000) ? y : 2000; // sets year
} // end function setYear

void Date::setMonth(unsigned int m)
{
	month = (m <= 12 && m >= 1) ? m : 1; // sets month
} // end function setMonth

void Date::setDay(unsigned int d)
{
	int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && leapYear(year))
		day = (d <= 29 && d >= 1) ? d : 1;
	else
		day = (d <= days[month] && d >= 1) ? d : 1;
} // end function setDay

unsigned int Date::getYear()
{
	return year;
}

unsigned int Date::getMonth()
{
	return month;
}

unsigned int Date::getDay()
{
	return day;
}

bool Date::operator==(const Date &date2)
{
	return (year == date2.year && month == date2.month && day == date2.day);
}

bool Date::operator<(const Date &date2)
{
	if (year != date2.year)
	{
		return (year < date2.year);
	}
	if (month != date2.month)
	{
		return (month < date2.month);
	}
	if (day != date2.day)
	{
		return (day < date2.day);
	}
	return false;
}

bool Date::operator>=(const Date &date2)
{
	return !(*this < date2);
}