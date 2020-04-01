// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "MakeReservation.h" // MakeReservation class definition

extern bool leapYear(unsigned int year);

// MakeReservation constructor initializes base-class data members
MakeReservation::MakeReservation(ReservationDatabase &theReservationDatabase,
	AvailableRoomsDatabase &theAvailableRoomsDatabase)
	: reservationDatabase(theReservationDatabase),
	availableRoomsDatabase(theAvailableRoomsDatabase)
{
} // end MakeReservation constructor

// performs transaction
void MakeReservation::execute()
{
	Date today, availableMonths[6], checkInDate, checkOutDate;
	unsigned int checkInYMCode, firstDay, lastDay;

	computeCurrentDate(today);
	computeAvailableMonths(today, availableMonths);

	inputCheckInDates(checkInDate, today, availableMonths, checkInYMCode, firstDay, lastDay);
	inputCheckOutDates(checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay);

	cout << "Check in date: "
		<< checkInDate.getYear() << "-"
		<< checkInDate.getMonth() << "-"
		<< checkInDate.getDay() << endl;
	cout << "Check out date: "
		<< checkOutDate.getYear() << "-"
		<< checkOutDate.getMonth() << "-"
		<< checkOutDate.getDay() << endl;
	cout << endl;

	availableRoomsDatabase.displayAvailableRooms(checkInDate, checkOutDate);
	unsigned int roomType = -1;
	while (roomType < 1 || roomType > 5)
	{
		cout << "Select Room Type: \n"
			<< "1. Superior Room\n"
			<< "2. Deluxe Room\n"
			<< "3. Deluxe Twin Room\n"
			<< "4. Superior Suite\n"
			<< "5. Deluxe Suite\n"
			<< "? ";
		cin >> roomType;
		cin.ignore();
	}
	int maxNumRoom = availableRoomsDatabase.findMinNumRooms(roomType, checkInDate, checkOutDate);

	unsigned int numRoom = -1;
	while (numRoom < 1 || numRoom > maxNumRoom)
	{
		cout << "Number of rooms ( "
			<< maxNumRoom << " rooms available ): ";
		cin >> numRoom;
		cin.ignore();
	}

	string idNumber, name, mobile;
	cout << "ID Number: ";
	cin >> idNumber;
	cin.ignore();
	cout << "Name: ";
	cin >> name;
	cin.ignore();
	cout << "Mobile Phone: ";
	cin >> mobile;
	cin.ignore();

	availableRoomsDatabase.decreaseAvailableRooms(roomType, numRoom, checkInDate, checkOutDate);
	newReservation.setReservation(roomType, numRoom, checkInDate, checkOutDate, idNumber, name, mobile);
	cout << "Name\t"
		<< "Fare\t"
		<< "Mobile\t"
		<< "Room Type\t"
		<< "Number of Rooms\t\t"
		<< "Check In Date\t"
		<< "Check Out Date" << endl;
	newReservation.displayReservation();
	reservationDatabase.pushBack(newReservation);

	cout << "Reservation successfully!" << endl;
}

void MakeReservation::computeAvailableMonths(Date currentDate, Date availableMonths[])
{
	for (int i = 0; i < 6; i++)
	{
		Date tmp;
		if (currentDate.getMonth() + i <= 12)
		{
			tmp.setMonth(currentDate.getMonth() + i);
			tmp.setYear(currentDate.getYear());
		}
		else {
			tmp.setMonth(currentDate.getMonth() + i - 12);
			tmp.setYear(currentDate.getYear() + 1);
		}
		availableMonths[i] = tmp;
	}
}

void MakeReservation::inputCheckInDates(Date &checkInDate, Date currentDate, Date availableMonths[], unsigned int &checkInYMCode, unsigned int &firstDay, unsigned int &lastDay)
{
	int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	cout << "Please Input Check In Date\n\nMonth:\n";
	for (int i = 0; i < 6; i++)
	{
		cout << i + 1 << ". "
			<< availableMonths[i].getYear() << "-"
			<< availableMonths[i].getMonth() << endl;
	}
	while (checkInYMCode < 1 || checkInYMCode > 6)
	{
		cout << "? ";
		cin >> checkInYMCode;
		cin.ignore();
	}
	checkInDate.setYear(availableMonths[checkInYMCode - 1].getYear());
	checkInDate.setMonth(availableMonths[checkInYMCode - 1].getMonth());
	firstDay = ((checkInDate.getMonth() == currentDate.getMonth()) ? currentDate.getDay() : 1);
	lastDay = days[checkInDate.getMonth()];
	if (checkInYMCode == 6)
	{
		lastDay--;
	}

	int tmp_d = -1;
	while (tmp_d < firstDay || tmp_d > lastDay)
	{
		cout << "Day (" << firstDay << " ~ " << lastDay << "):";
		cin >> tmp_d;
		cin.ignore();
	}
	checkInDate.setDay(tmp_d);
}

void MakeReservation::inputCheckOutDates(Date &checkOutDate, Date checkInDate, Date availableMonths[],
	unsigned int checkInYMCode, unsigned int firstDay, unsigned int lastDay)
{
	int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	cout << "Please Input Check Out Date\n\nMonth:\n";
	int from_month_index = checkInYMCode-1;
	if (checkInDate.getDay() == days[checkInDate.getMonth()])
	{
		from_month_index++;
	}
	for (int i = from_month_index; i < 6; i++)
	{
		cout << i + 1 << ". "
			<< availableMonths[i].getYear() << "-"
			<< availableMonths[i].getMonth() << endl;
	}
	int tmp_ym = -1;
	while (tmp_ym < from_month_index || tmp_ym > 6)
	{
		cout << "? ";
		cin >> tmp_ym;
		cin.ignore();
	}
	checkOutDate.setYear(availableMonths[tmp_ym - 1].getYear());
	checkOutDate.setMonth(availableMonths[tmp_ym - 1].getMonth());
	firstDay = ((checkOutDate.getMonth() == checkInDate.getMonth()) ? checkInDate.getDay() + 1 : 1);
	lastDay = days[checkOutDate.getMonth()];

	int tmp_d = -1;
	while (tmp_d < firstDay || tmp_d > lastDay)
	{
		cout << "Day (" << firstDay << " ~ " << lastDay << "):";
		cin >> tmp_d;
		cin.ignore();
	}
	checkOutDate.setDay(tmp_d);
}