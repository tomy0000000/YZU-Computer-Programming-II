// string class member-function definitions.

#include "String.h" // string class definition

string::string()
{
   bx.buf[ 0 ] = '\0';
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::iterator string::begin()
{
   if( myRes == 15 )
      return bx.buf;
   else
      return bx.ptr;
}

string::iterator string::end()
{
   if( myRes == 15 )
      return bx.buf + mySize;
   else
      return bx.ptr + mySize;
}

size_t string::size() const
{
   return mySize;
}

unsigned int string::capacity() const
{
   return myRes;
}

void string::insert( iterator p, char c )
{
	if (mySize == myRes)
	{
		//Reallocation
		int posNum = 0;
		for (iterator it = begin(); it != end(); it++)
		{
			if (it != p)
			{
				posNum++;
			}
			else {
				break;
			}
		}
		iterator oldBegin = begin();
		iterator tmp = begin();
		unsigned int oldCap = myRes;
		unsigned int newCap;
		if (oldCap == 15)
		{
			newCap = 31;
		}
		else if (oldCap == 31)
		{
			newCap = 47;
		}
		else {
			newCap = myRes * 1.5;
		}
		myRes = newCap;
		iterator tempPtr = new char[myRes + 1]();
		for (mySize = 0; mySize < oldCap; mySize++)
		{
			*(tempPtr + mySize) = *(tmp + mySize);
		}
		*(tempPtr + myRes) = '\0';
		bx.ptr = tempPtr;
		p = bx.ptr + posNum;
		if (oldCap > 15)
		{
			delete[] oldBegin;
		}
	}

	// inserting
	iterator it = end();
	for (; it != p; it--)
	{
		*it = *(it - 1);
	}

	*p = c;
	mySize++;
}

void string::erase( iterator p )
{
   iterator start = ( myRes == 15 ? bx.buf : bx.ptr );
   for( iterator it = p + 1; it != start + mySize; it++ )
      *( it - 1 ) = *it;

   mySize--;
}

bool operator==( string &lhs, std::string &rhs )
{
   if( lhs.myRes != rhs.capacity() )
      return false;

   if( lhs.mySize != rhs.size() )
      return false;

   string::iterator tempPtr = ( lhs.myRes == 15 ? lhs.bx.buf : lhs.bx.ptr );
   for( unsigned int i = 0; i < lhs.mySize; i++ )
      if( tempPtr[ i ] != rhs[ i ] )
         return false;

   return true;
}