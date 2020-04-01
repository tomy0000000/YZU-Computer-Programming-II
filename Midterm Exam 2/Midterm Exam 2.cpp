// Polynomial test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include "Polynomial - 1061519 - mid2.h"

int enterChoice();

template< typename T >
void testPolynomials( Polynomial< T > multiplicand[], Polynomial< T > multiplier[] );

template< typename T >
void input( Polynomial< T > multiplicand[], Polynomial< T > multiplier[] );

const int numTestCases = 9;

int main()
{
   Polynomial< vector< Term > > multiplicand1[ numTestCases ];
   Polynomial< vector< Term > > multiplier1[ numTestCases ];
   Polynomial< list< Term > > multiplicand2[ numTestCases ];
   Polynomial< list< Term > > multiplier2[ numTestCases ];

   int choice = enterChoice();

   switch( choice )
   {
   case 1:
      testPolynomials( multiplicand1, multiplier1 );
      break;
   case 2:
      testPolynomials( multiplicand2, multiplier2 );
      break;
   default:
      cout << "Program should never get here!";
   }

   system( "pause" );
}

int enterChoice()
{
   cout << "Enter your choice\n"
      << " 1 - test vector< Term >\n"
      << " 2 - test list< Term >\n";

   int menuChoice;
   do
   {
      cout << "? ";
      cin >> menuChoice;
   } while( ( menuChoice < 1 ) || ( menuChoice > 2 ) );
   cout << endl;

   return menuChoice;
} // end function enterChoice

template< typename T >
void testPolynomials( Polynomial< T > multiplicand[], Polynomial< T > multiplier[] )
{
   input( multiplicand, multiplier );

   for( int i = 0; i < numTestCases; i++ )
   {
      cout << multiplicand[ i ] << endl;
      cout << multiplier[ i ] << endl;
      cout << multiplicand[ i ] * multiplier[ i ] << endl << endl;
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i < numTestCases; i++ )
   {
      outFile << multiplicand[ i ] << endl;
      outFile << multiplier[ i ] << endl;
      outFile << multiplicand[ i ] * multiplier[ i ] << endl << endl;
   }

   outFile.close();
}

template< typename T >
void input( Polynomial< T > multiplicand[], Polynomial< T > multiplier[] )
{
   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ofstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int k = 0; k < numTestCases; k++ )
   {
      int numTerms;
      inFile >> numTerms;
      Term *terms = new Term[ numTerms ];
      for( int i = 0; i < numTerms; i++ )
         inFile >> terms[ i ].coef >> terms[ i ].expon;
      for( int i = 0; i < numTerms; i++ )
         multiplicand[ k ].insert( terms[ i ] );

      delete[] terms;
      inFile >> numTerms;
      terms = new Term[ numTerms ];
      for( int i = 0; i < numTerms; i++ )
         inFile >> terms[ i ].coef >> terms[ i ].expon;
      for( int i = 0; i < numTerms; i++ )
         multiplier[ k ].insert( terms[ i ] );
   }

   inFile.close();
}
