// EvergreenLaurelHotel.cpp
// Member-function definitions for class EvergreenLaurelHotel.
#include <iostream>
#include <iomanip>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition
#include "ViewReservation.h" // ViewReservation class definition

unsigned int displayMainMenu();
void computeCurrentDate(Date &currentDate);
bool leapYear(unsigned int year); // if the year is a leap year, return true; otherwise, return false

int main()
{
	cout << "Evergreen Laurel Hotel Online Reservation System\n";

	ReservationDatabase reservationDatabase;
	AvailableRoomsDatabase availableRoomsDatabase;

	reservationDatabase.loadFromReservations();
	availableRoomsDatabase.loadAvailableRooms();

	MakeReservation makeReservation(reservationDatabase, availableRoomsDatabase);
	ViewReservation viewReservation(reservationDatabase, availableRoomsDatabase);

	// enumeration constants represent submenu options
	enum MenuOption { MAKE_RESERVATION = 1, VIEW_CANCEL_RESERVATION, EXIT };
	bool userExited = false; // user has not chosen to exit

	// loop while user has not chosen option to exit system
	while (!userExited)
	{
		// show main menu and get user selection
		unsigned int mainMenuSelection = displayMainMenu();

		// decide how to proceed based on user's menu selection
		switch (mainMenuSelection)
		{
			// user chose to perform one of three transaction types
		case MAKE_RESERVATION:
			// create new Withdrawal transaction
			makeReservation.execute();
			break;
		case VIEW_CANCEL_RESERVATION:
			viewReservation.execute();
			break;
		case EXIT: // user chose to terminate session
			cout << "\nExiting the system...\n\n";
			reservationDatabase.saveToReservationFile();
			availableRoomsDatabase.saveAvailableRooms();
			userExited = true; // this ATM session should end
			break;
		default: // user did not enter an integer from 1-4
			cout << "\nYou did not enter a valid selection. Try again." << endl;
			break;
		} // end switch
	} // end while

	system("pause");
} // end main

// display the main menu and return an input selection
unsigned int displayMainMenu()
{
	cout << "\nMain menu:" << endl;
	cout << "1 - Make Reservation" << endl;
	cout << "2 - View/Cancel Reservation" << endl;
	cout << "3 - Exit\n" << endl;
	cout << "Enter a choice: ";
	unsigned int choice;
	cin >> choice;
	return choice; // return user's selection
} // end function displayMainMenu

void computeCurrentDate(Date &currentDate)
{
	struct tm today;
	time_t tmp = time(0);
	localtime_s(&today, &tmp);
	currentDate.setYear(today.tm_year + 1900);
	currentDate.setMonth(today.tm_mon + 1);
	currentDate.setDay(today.tm_mday);
}

bool leapYear(unsigned int year)
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}