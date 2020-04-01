// AvailableRooms.h
// AvailableRooms class definition. Represents the number of available rooms of each type for one day.
#ifndef AVAILABLE_ROOMS_H
#define AVAILABLE_ROOMS_H

#include "Date.h" // Date class definition

class AvailableRooms
{
public:
   AvailableRooms();
   void setDate( unsigned int year, unsigned int month, unsigned int day );
   Date getDate();
   void initilizeAvailableRooms();
   unsigned int *getAvailableRooms();
   void decreaseAvailableRooms( unsigned int roomType, unsigned int numRooms );
   void increaseAvailableRooms( unsigned int roomType, unsigned int numRooms );
private:
   Date date;
   unsigned int availableRooms[ 6 ]; // number of available rooms for each room type
   unsigned int totalNumRooms[ 6 ] = { 0, 9, 5, 3, 5, 4 }; // total number of rooms for each room type
}; // end class AvailableRooms

#endif // AVAILABLE_ROOMS_H