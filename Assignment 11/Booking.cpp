//
//  Booking.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "Booking.h"
#include "MovieDatabase.h"
#include <iostream>
using std::cout;
using std::endl;

Booking::Booking() {}
string Booking::getEmail() { return string(email); }
int Booking::getMovieCode() { return movieCode; }
int Booking::getDateCode() { return dateCode; }
int Booking::getSessionTimeCode() { return sessionTimeCode; }
int Booking::getNumTickets(int ticketType) { return numTickets[ticketType]; }
string Booking::getSeletedSeat(int number) { return seletedSeats[number]; }

void Booking::setEmail(string theEmail) {
  unsigned long length = theEmail.size();
  length = (length < 40 ? length : 39);
  for (int i = 0; i < length; i++) {
    email[i] = theEmail[i];
  }
  email[length] = '\0';
}

void Booking::setMovieCode(int theMovieCode) {
  movieCode = (theMovieCode > 0 ? theMovieCode : 0);
}

void Booking::setDateCode(int theDateCode) {
  dateCode = (theDateCode > 0 ? theDateCode : 0);
}

void Booking::setSessionTimeCode(int theSessionTimeCode) {
  sessionTimeCode = (theSessionTimeCode > 0 ? theSessionTimeCode : 0);
}

void Booking::setNumTickets(int theNumTickets[]) {
  for (int i = 0; i < 4; i++) {
    numTickets[i] = (theNumTickets[i] > 0 ? theNumTickets[i] : 0);
  }
}

void Booking::setSeletedSeats(string theSeletedSeats[], int numSeats) {
  for (int i = 0; i < numSeats; i++) {
    seletedSeats[i][0] = theSeletedSeats[i][0];
    seletedSeats[i][1] = theSeletedSeats[i][1];
    seletedSeats[i][2] = '\0';
  }
  cout << endl;
}

void Booking::displayBooking(MovieDatabase &movieDatabase) {
  cout << "\t\t\t\tNo. of Tickets\t\tPrice\t\tSubtotal" << endl;
  int Num = 0, Price = 0, Sub = 0, Total = 0;
  char ticketType[4][15] = {"Adult\t\t\t", "Concession\t\t", "Disability\t\t",
                            "Elderly\t\t\t"};
  for (int i = 0; i < 4; i++) {
    if (numTickets[i] != 0) {
      Num = numTickets[i];
      Price = movieDatabase.getMovie(movieCode).getPrice(i);
      Sub = Num * Price;
      Total += Sub;
      cout << ticketType[i] << Num << "\t\t\t\t\t" << Price << "\t\t\t" << Sub
           << endl;
    }
  }
  cout << endl << "Total Amount For Tickets: " << Total << endl;
}
