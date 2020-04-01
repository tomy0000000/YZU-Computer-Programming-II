// AvailableRoomsDatabase.h
// AvailableRoomsDatabase class definition.
#ifndef AVAILABLE_ROOMS_DATABASE_H
#define AVAILABLE_ROOMS_DATABASE_H

#include <vector>
#include "AvailableRooms.h" // AvailableRooms class definition

class AvailableRoomsDatabase
{
public:
	void loadAvailableRooms();
	void displayAvailableRooms(const Date &checkInDate, const Date &checkOutDate);
	unsigned int findMinNumRooms(unsigned int roomType, const Date &checkInDate, const Date &checkOutDate);

	void decreaseAvailableRooms(unsigned int roomType, unsigned int numRooms,
		const Date &checkInDate, const Date &checkOutDate);
	void saveAvailableRooms();
private:
	vector< AvailableRooms > availableRooms; // vector of the available rooms for next 6 months

	void initilizeAvailableRooms(); // initilize availableRooms for next 6 months
	void adjustAvailableRooms();    // adjust AvailableRooms for the current date

	// set checkInIterator pointing to the element of availableRooms corresponding to checkInDate;
	// set checkOutIterator pointing to the element of availableRooms corresponding to checkOutDate; 
	void findIterators(const Date &checkInDate, const Date &checkOutDate,
		vector< AvailableRooms >::iterator &checkInIterator,
		vector< AvailableRooms >::iterator &checkOutIterator);
}; // end class AvailableRoomsDatabase

#endif // AVAILABLE_ROOMS_DATABASE_H