// Date.h
// Date class definition.
#ifndef DATA_H
#define DATA_H

class Date
{
	friend void computeCurrentDate(Date &currentDate);
public:
	Date();
	void setYear(unsigned int);
	void setMonth(unsigned int);
	void setDay(unsigned int);
	unsigned int getYear();
	unsigned int getMonth();
	unsigned int getDay();
	//   void computeCurrentDate(); // compute the next date of the current date
	bool operator==(const Date &date2);
	//   bool operator>( Date & );
	bool operator<(const Date &date2);
	bool operator>=(const Date &date2);
	//   bool operator<=( Date & );
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

#endif // DATA_H