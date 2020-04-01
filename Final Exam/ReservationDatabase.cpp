// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

void ReservationDatabase::loadFromReservations()
{
	ifstream inFile("Reservations.dat", ios::in | ios::binary);
	if (inFile)
	{
		while (inFile.peek() != EOF)
		{
			reservations.resize(reservations.size() + 1);
			inFile.read(reinterpret_cast<char*>(&reservations[reservations.size() - 1]), sizeof(Reservation));
		}
	}
	inFile.close();
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

unsigned int ReservationDatabase::numReservations( string IDNumber )
{
	unsigned int num = 0;
	for (vector<Reservation>::iterator it = reservations.begin(); it != reservations.end(); ++it)
	{
		if (it->getIDNumber() == IDNumber)
		{
			num++;
		}
	}
	return num;
}

void ReservationDatabase::displayReservations( string IDNumber )
{
	cout << "Name\t"
		<< "Fare\t"
		<< "Mobile\t"
		<< "Room Type\t"
		<< "Number of Rooms\t\t"
		<< "Check In Date\t"
		<< "Check Out Date" << endl;
	for (vector<Reservation>::iterator it = reservations.begin(); it != reservations.end(); ++it)
	{
		if (it->getIDNumber() == IDNumber)
		{
			it->displayReservation();
		}
	}
}

void ReservationDatabase::saveToReservationFile()
{
	ofstream outFile("Reservations.dat", ios::out | ios::binary);
	if (outFile)
	{
		for (int i = 0; i < reservations.size(); i++)
		{
			outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
		}
	}
	outFile.close();
}