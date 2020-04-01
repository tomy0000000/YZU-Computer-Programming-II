// AvailableRoomsDatabase.cpp
// Member-function definitions for class AvailableRoomsDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

//int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
extern bool leapYear(unsigned int year);
extern void computeCurrentDate(Date &currentDate);

void AvailableRoomsDatabase::loadAvailableRooms()
{
	ifstream inFile("Available Rooms.dat", ios::in | ios::binary);
	if (inFile)
	{
		while (inFile.peek() != EOF)
		{
			availableRooms.resize(availableRooms.size() + 1);
			inFile.read(reinterpret_cast<char*>(&availableRooms[availableRooms.size() - 1]), sizeof(AvailableRooms));
		}
	}
	else {
		initilizeAvailableRooms();
	}
	inFile.close();
}

void AvailableRoomsDatabase::initilizeAvailableRooms()
{
	int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date today;
	computeCurrentDate(today);
	for (int i = 0; i < 6; i++)
	{
		int tmp_y, tmp_m, tmp_d, from_d;
		if (today.getMonth() + i > 12)
		{
			tmp_y = today.getYear() + 1;
			tmp_m = today.getMonth() + i - 12;
		}
		else {
			tmp_y = today.getYear();
			tmp_m = today.getMonth() + i;
		}
		tmp_d = days[tmp_m];
		from_d = ((i == 0) ? today.getDay() : 1);
		for (int j = from_d; j <= tmp_d; j++)
		{
			AvailableRooms tmp;
			tmp.setDate(tmp_y, tmp_m, j);
			availableRooms.push_back(tmp);
		}
	}
}

void AvailableRoomsDatabase::adjustAvailableRooms()
{
	vector<vector<AvailableRooms>::iterator> to_be_remove;
	Date today;
	computeCurrentDate(today);

	for (vector<AvailableRooms>::iterator it = availableRooms.begin(); it != availableRooms.end(); ++it)
	{
		if (it->getDate() < today)
		{
			to_be_remove.push_back(it);
		}
	}

	for (vector<vector<AvailableRooms>::iterator>::iterator it_for_remove = to_be_remove.begin(); it_for_remove != to_be_remove.end(); it_for_remove++)
	{
		availableRooms.erase(*it_for_remove);
	}
}

void AvailableRoomsDatabase::displayAvailableRooms(const Date &checkInDate, const Date &checkOutDate)
{
	cout << "Available Rooms: \n\n"
		<< "Date\t\t"
		<< "Superior Room\t"
		<< "Deluxe Room\t"
		<< "Deluxe Twin Room\t"
		<< "Superior Suite\t"
		<< "Deluxe Suite" << endl;
	vector<AvailableRooms>::iterator from, to;
	findIterators(checkInDate, checkOutDate, from, to);
	for (vector<AvailableRooms>::iterator it = from; it != to; it++)
	{
		cout << it->getDate().getYear() << "-"
			<< it->getDate().getMonth() << "-"
			<< it->getDate().getDay() << "\t";
		for (int i = 1; i < 6; i++)
		{
			cout << it->getAvailableRooms()[i] << "\t\t" << ((i == 3) ? "\t" : "");
		}
		cout << endl;
	}
}

unsigned int AvailableRoomsDatabase::findMinNumRooms(unsigned int roomType,
	const Date &checkInDate, const Date &checkOutDate)
{
	int min = 10;
	for (vector<AvailableRooms>::iterator it = availableRooms.begin(); it != availableRooms.end(); ++it)
	{
		if (it->getDate() >= checkInDate && it->getDate() < checkOutDate)
		{
			int this_day_ava_room = it->getAvailableRooms()[roomType];
			if (this_day_ava_room < min)
			{
				min = this_day_ava_room;
			}
		}
	}
	return min;
}

void AvailableRoomsDatabase::decreaseAvailableRooms(unsigned int roomType, unsigned int numRooms,
	const Date &checkInDate, const Date &checkOutDate)
{
	for (vector<AvailableRooms>::iterator it = availableRooms.begin(); it != availableRooms.end(); ++it)
	{
		if (it->getDate() >= checkInDate && it->getDate() < checkOutDate)
		{
			it->decreaseAvailableRooms(roomType, numRooms);
		}
	}
}

void AvailableRoomsDatabase::saveAvailableRooms()
{
	ofstream outFile("Available Rooms.dat", ios::out | ios::binary);
	if (outFile)
	{
		for (int i = 0; i < availableRooms.size(); i++)
		{
			outFile.write(reinterpret_cast<const char*>(&availableRooms[i]), sizeof(AvailableRooms));
		}
	}
	outFile.close();
}

void AvailableRoomsDatabase::findIterators(const Date &checkInDate, const Date &checkOutDate,
	vector< AvailableRooms >::iterator &checkInIterator,
	vector< AvailableRooms >::iterator &checkOutIterator)
{
	for (vector<AvailableRooms>::iterator it = availableRooms.begin(); it != availableRooms.end(); ++it)
	{
		if (it->getDate() == checkInDate)
		{
			checkInIterator = it;
		}
		if (it->getDate() == checkOutDate)
		{
			checkOutIterator = it;
		}
	}
}