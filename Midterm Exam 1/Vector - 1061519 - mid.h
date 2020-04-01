#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

// vector class template definition
template< typename T >
class vector
{
   template< typename T >
   friend bool operator==( vector< T > &lhs, std::vector< T > &rhs );
public:
   using iterator = T*;

   vector();

   ~vector();

   iterator begin();

   iterator end();

   size_t size() const;

   size_t capacity() const;

   // The vector is extended by inserting a new element before the element
   // at the specified position, effectively increasing the container size by one.
   // This causes an automatic reallocation of the allocated storage space
   // if -and only if- the new vector size surpasses the current vector capacity.
   // Relocates all the elements that were after position to their new positions.
   void insert( iterator position, const T val );

   // Removes from the vector a single element.   
   // This effectively reduces the container size by one.   
   // Relocates all the elements after the element erased to their new positions.
   void erase( iterator position );

private:
   T *myFirst = nullptr;
   T *myLast = nullptr;
   T *myEnd = nullptr;
}; // end class template vector


template< typename T >
vector< T >::vector()
{
	myFirst = new T[0]();
	myLast = myEnd = myFirst;
}

template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

template< typename T >
typename vector< T >::iterator vector< T >::begin()
{
   return myFirst;
}

template< typename T >
typename vector< T >::iterator vector< T >::end()
{
   return myLast;
}

template< typename T >
size_t vector< T >::size() const
{
   return ( myLast - myFirst );
}

template< typename T >
size_t vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

template< typename T >
void vector< T >::insert( iterator position, const T val )
{
	if (myLast == myEnd)
	{
		//Reallocation
		int posNum = 0;
		for (iterator p = myFirst; p != myEnd; p++)
		{
			if (p != position)
			{
				posNum++;
			}
			else {
				break;
			}
		}
		iterator oldmyFirst = myFirst;
		iterator oldmyLast = myLast;
		iterator tmp = myFirst;
		unsigned int newCap = (capacity() < 4) ? capacity() + 1 : capacity() * 1.5;
		myFirst = new T[newCap]();
		myEnd = myFirst + newCap;
		for (myLast = myFirst; tmp != oldmyLast; myLast++, tmp++)
		{
			*myLast = *tmp;
		}
		position = myFirst + posNum;
		delete [] oldmyFirst;
	}

	// inserting
	iterator p = myLast;
	for (; p != position; p--)
	{
		*p = *(p - 1);
	}

	*position = val;
	myLast++;
}

template< typename T >
void vector< T >::erase( iterator position )
{
   for( iterator p = position + 1; p != myLast; p++ )
      *( p - 1 ) = *p;

   myLast--;
}

template< typename T >
bool operator==( vector< T > &lhs, std::vector< T > &rhs )
{
   if( lhs.capacity() != rhs.capacity() )
      return false;

   if( lhs.size() != rhs.size() )
      return false;

   for( unsigned int i = 0; i < lhs.size(); i++ )
      if( lhs.myFirst[ i ] != rhs[ i ] )
         return false;

   return true;
}

#endif