// Reservation.cpp
// Member-function definitions for class Reservation.
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
#include "Date.h"
#include "Reservation.h" // Reservation class definition

unsigned int roomRate[] = { 0,5390,6270,6270,6820,8470 };

void Reservation::setReservation( unsigned int inputRoomType, unsigned int inputNumRooms,
                                  Date inputCheckInDate, Date inputCheckOutDate,
                                  string inputIDNumber, string inputName, string inputMobile )
{
   roomType = inputRoomType;
   numRooms = inputNumRooms;
   checkInDate = inputCheckInDate;
   checkOutDate = inputCheckOutDate;
   setIDNumber( inputIDNumber );
   setName( inputName );
   setMobile( inputMobile );
   setFare(roomRate[inputRoomType] * inputNumRooms);
}

void Reservation::setIDNumber( string theIDNumber )
{
   strcpy_s( IDNumber, 12, theIDNumber.c_str() );
}

void Reservation::setName( string theName )
{
   strcpy_s( name, 12, theName.c_str() );
}

void Reservation::setMobile( string theMobile )
{
   strcpy_s( mobile, 12, theMobile.c_str() );
}

void Reservation::setFare(int theFare)
{
	fare = theFare;
}

string Reservation::getIDNumber()
{
   return IDNumber;
}

unsigned int Reservation::getFare()
{
	return fare;
}

unsigned int Reservation::getRoomType()
{
   return roomType;
}

unsigned int Reservation::getNumRooms()
{
   return numRooms;
}

Date Reservation::getCheckInDate()
{
   return checkInDate;
}

Date Reservation::getCheckOutDate()
{
   return checkOutDate;
}

bool Reservation::equalID( string id1, string id2 )
{
	return id1 == id2;
}

void Reservation::displayReservation()
{
	string roomNames[] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room", "Superior Suite", "Deluxe Suite" };
	cout << name << "\t"
		<< fare << "\t"
		<< mobile << "\t"
		<< roomNames[roomType] << "\t"
		<< numRooms << "\t\t\t"
		<< checkInDate.getYear() << "-" << checkInDate.getMonth() << "-" << checkInDate.getDay() << "\t"
		<< checkOutDate.getYear() << "-" << checkOutDate.getMonth() << "-" << checkOutDate.getDay() << endl;
}