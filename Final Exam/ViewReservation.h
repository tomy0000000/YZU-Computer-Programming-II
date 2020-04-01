// ViewReservation.h
// ViewReservation class definition.
#ifndef VIEW_CANCEL_RESERVATION_H
#define VIEW_CANCEL_RESERVATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

class ViewReservation
{
public:
   ViewReservation( ReservationDatabase &, AvailableRoomsDatabase & );
   void execute();
private:
   ReservationDatabase &reservationDatabase;
   AvailableRoomsDatabase &availableRoomsDatabase;
}; // end class ViewReservation

#endif // VIEW_CANCEL_RESERVATION_H