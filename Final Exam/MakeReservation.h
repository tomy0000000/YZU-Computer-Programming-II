// MakeReservation.h
// MakeReservation class definition.
#ifndef MAKE_RESERVATION_H
#define MAKE_RESERVATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

class MakeReservation
{
public:
   MakeReservation( ReservationDatabase &, AvailableRoomsDatabase & );
   void execute();
private:
   Reservation newReservation;
   ReservationDatabase &reservationDatabase;
   AvailableRoomsDatabase &availableRoomsDatabase;

   void computeAvailableMonths( Date currentDate, Date availableMonths[] );
   void inputCheckInDates( Date &checkInDate, Date, Date[], unsigned int &, unsigned int &, unsigned int & );
   void inputCheckOutDates( Date &checkOutDate, Date, Date[], unsigned int, unsigned int, unsigned int );
}; // end class MakeReservation

#endif // MAKE_RESERVATION_H