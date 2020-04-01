#ifndef VECTOR_H
#define VECTOR_H

// VecIterator class template definition
template< typename T >
class VecIterator
{
   template< typename U > friend class vector;
public:
   VecIterator( T *p = nullptr ) // default constructor
      : ptr( p )
   {
   }

   VecIterator( const VecIterator &iteratorToCopy ) // copy constructor
      : ptr( iteratorToCopy.ptr )
   {
   }

   ~VecIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const VecIterator& operator=( const VecIterator &right )
   {
      if( &right != this ) // avoid self-assignment
         ptr = right.ptr;
      return *this; // enables x = y = z, for example
   }

   bool operator==( const VecIterator &right ) const // equal to
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VecIterator &right ) const // not equal to
   {
      return ptr != right.ptr;
   }

   T& operator*() const // dereferencing operator
   {
      return *ptr;
   }

   // overloaded class member access operator
   T* operator->() const
   {
      return ptr;
   }

   VecIterator& operator++() // prefix increment operator
   {
      ++ptr;
      return *this;
   }

private:
   T *ptr = nullptr; // keep a pointer to vector
}; // end class template VecIterator


template< typename T > class Polynomial;

// vector class template definition
template< typename T >
class vector
{
public:
   using iterator = VecIterator< T >;

   vector(); // Default constructor; Constructs an empty vector

             // Copy constructor; Constructs a vector with a copy of each of the elements in x.
   vector( const vector &x );

   ~vector(); // Destructor; Destroys the vector.

   // Returns a pointer pointing to the first element in the vector.
   // If the vector is empty, the returned pointer shall not be dereferenced.
   iterator begin() const;

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   // Returns a bool value indicating whether the vector is empty.
   bool empty() const;

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   unsigned int size() const;

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   unsigned int capacity() const;

   // The vector is extended by inserting a new element before the element at the specified position,
   // effectively increasing the container size by one.   
   // This causes an automatic reallocation of the allocated storage space.   
   // Relocates all the elements that were after position to their new positions.
   iterator insert( iterator position, const T val );

   // Removes from the vector the element at the specified position.   
   // This effectively reduces the vector size by one.   
   // Relocates all the elements after the element erased to their new positions.
   iterator erase( iterator position );

private:
   T *myFirst = nullptr;
   T *myLast = nullptr;
   T *myEnd = nullptr;
}; // end class template vector


// Default constructor; Constructs an empty vector
template< typename T >
vector< T >::vector()
   : myFirst( nullptr ),
     myLast( nullptr ),
     myEnd( nullptr )
{
} // end vector default constructor

// Copy constructor; Constructs a vector with a copy of each of the elements in x
template< typename T >
vector< T >::vector( const vector< T > &x )
   : myFirst( x.capacity() == 0 ? nullptr : new T[ x.capacity() ] ),
      myLast( x.capacity() == 0 ? nullptr : myFirst + x.size() ),
       myEnd( x.capacity() == 0 ? nullptr : myFirst + x.capacity() )
{
   for( unsigned int i = 0; i < size(); i++ )
      myFirst[ i ] = x.myFirst[ i ];
} // end vector copy constructor

// Destructor; Destroys the vector
template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete [] myFirst;
} // end destructor

// Returns a pointer pointing to the first element in the vector.
template< typename T >
typename vector< T >::iterator vector< T >::begin() const
{
   return iterator( myFirst );
}

// Returns an pointer pointing to the past-the-end element in the vector.
template< typename T >
typename vector< T >::iterator vector< T >::end() const
{
   return iterator( myLast );
}

// Returns a bool value indicating whether the vector is empty.
template< typename T >
bool vector< T >::empty() const
{
   return ( myLast == myFirst );
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
template< typename T >
unsigned int vector< T >::size() const
{
   return ( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
template< typename T >
unsigned int vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

// The vector is extended by inserting a new element before the element at the specified position,
template< typename T >
VecIterator< T > vector< T >::insert( iterator position, const T val )
{
	unsigned int tmppos = position.ptr - myFirst;
	if (myFirst == myLast)
	{
		myFirst = new T[1]();
		myLast = myFirst + 1;
		myEnd = myFirst + 1;
		myFirst[0] = val;
		return position;
	}
	else if (myLast == myEnd) {
		unsigned int oldSize = size();
		unsigned int newCap = (capacity() < 4) ? capacity()+1 : capacity()*1.5;
		T* tmp = new T[newCap]();
		iterator it = begin();
		for (int i = 0; it != end(); i++, ++it)
		{
			tmp[i] = *it;
		}
		delete[] myFirst;
		myFirst = tmp;
		myLast = myFirst + oldSize;
		myEnd = myFirst + newCap;
		position = myFirst + tmppos;
	}

	if (position == myLast + 1)
	{
		myFirst[size()] = val;
		myLast++;
		return position;
	}
	myLast++;
	T tmp = *position;
	*position = val;
	iterator it1 = position;
	++(it1);
	for (; it1 != end(); ++it1)
	{
		T tmmp = *it1;
		*it1 = tmp;
		tmp = tmmp;
	}
	return position;
}

// Removes from the vector the element at the specified position.   
template< typename T >
VecIterator< T > vector< T >::erase( iterator position )
{
	iterator it1 = position;
	iterator it2 = it1;
	++it2;
	for ( ; it2 != end(); ++it1, ++it2)
	{
		*it1 = *it2;
	}
	myLast--;
	return position;
}

#endif