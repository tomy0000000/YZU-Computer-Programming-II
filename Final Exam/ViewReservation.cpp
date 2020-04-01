// ViewReservation.cpp
// Member-function definitions for class ViewReservation.
#include <iostream>
#include <string>
using namespace std;
#include "ViewReservation.h" // ViewReservation class definition

// ViewReservation constructor initializes data members
ViewReservation::ViewReservation( ReservationDatabase &theReservationDatabase,
                                  AvailableRoomsDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomsDatabase( theAvailableRoomsDatabase )
{
} // end ViewReservation constructor

void ViewReservation::execute()
{
   string IDNumber;
   cout << "\nPlease enter your ID number: ";
   cin >> IDNumber;

   if( reservationDatabase.numReservations( IDNumber ) )
      reservationDatabase.displayReservations( IDNumber );
   else
      cout << "\nThere is no your reservation information!\n";
}