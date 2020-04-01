// AvailableRooms.cpp
// Member-function definitions for class AvailableRooms.
#include "AvailableRooms.h" // AvailableRooms class definition

AvailableRooms::AvailableRooms()
{
   for( unsigned int i = 0; i < 6; i++ )
      availableRooms[ i ] = totalNumRooms[ i ];
}

void AvailableRooms::setDate( unsigned int year, unsigned int month, unsigned int day )
{
   date.setYear( year );
   date.setMonth( month );
   date.setDay( day );
}

Date AvailableRooms::getDate()
{
   return date;
}

void AvailableRooms::initilizeAvailableRooms()
{
   for( unsigned int i = 0; i < 6; i++ )
      availableRooms[ i ] = totalNumRooms[ i ];
}

unsigned int* AvailableRooms::getAvailableRooms()
{
   return availableRooms;
}

void AvailableRooms::decreaseAvailableRooms( unsigned int roomType, unsigned int numRooms )
{
   availableRooms[ roomType ] -= numRooms;
}

void AvailableRooms::increaseAvailableRooms( unsigned int roomType, unsigned int numRooms )
{
   availableRooms[ roomType ] += numRooms;
}
