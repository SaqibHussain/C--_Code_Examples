/**
* \file Vector.h
* \brief Vector template class definition and implementation
* \author Saqib Hussain S194491
* \date 01/12/2013
* \copyright Saqib Hussain 2013
*/

#ifndef VECTOR_H //Include guard
#define VECTOR_H

#include <iostream> //Generic IO operations
#include <fstream>  //File IO operations
#include <stdexcept> //provides exceptions

using namespace std;
/**
* \class Vector Template
* \brief Redefinition of the vector class to work with Templates
*/
template <typename T>
class Vector {
protected:
	int num; /**< Number of elements*/
	T* pdata; /**< Pointer to the data */
	void Init(int Num); /**< private function since user should not call it */
public:
	/**
	*\brief Default Constructor
	* Constructs an empty Vector
	*/
	Vector(); 

	/**
	*\brief Alternate Constructor
	* it is explicit since implicit type conversion int -> vector doesn't make sense
	*\param Num - Size of Vector
	*/
	explicit Vector(int Num); 

	/**
	*\brief Copy Constructor
	* Constructs a copy of another given vector
	*\param v - Reference to another Vector
	*/
	Vector(const Vector<T>& v); // copy constructor

	/**
	*\brief Destructor
	* Destructor is virtual since it is a good thing to have virtual destr. in base class
	*/
	virtual ~Vector(); 

	/**
	*\brief Accessor
	*\return int -  nummber of elements inside vector
	*/
	int size() const; 

	/**
	*\brief Overloaded assignment operator
	*\param v - Vector
	*\return Vector after assignation is complete
	*/
	Vector<T>& operator= (const Vector& v); 

	/**
	*\brief Overloaded Array Access Operator for Writing
	*\param i - Int - Position of element in vector
	*\return Pointer to Vector element pdata
	*/
	T& operator[] (int i); 

	/**
	*\brief Overloaded Array Access Operator for Reading
	*\param i - Vector
	*\return Vector element pdata
	*/
	T operator[] (int i) const; 

	/**
	*\brief Overloaded Comparison Operator
	* Returns true or false depending on whether or not the Vector passed as an argument is equal to vector upon which the method was called
	*\param v - Vector
	*\return Bool
	*/
	bool operator==(const Vector& v) const; 

	/**
	*\brief Overloaded operator for Keyboard Input
	* Overloaded operator for inputting a vector from keyboard
	*\param is - Input Stream
	*\param v - Vector
	*\return Input Stream
	*/
	template <typename T> friend istream& operator>>(std::istream& is, Vector<T>& v);

	/**
	*\brief Overloaded operator for Screen Output
	* Overloaded operator for outputting a vector to screen
	*\param os - Output Stream
	*\param v - Vector
	*\return Output Stream
	*/
	template <typename T> friend ostream& operator<<(std::ostream& os, const Vector<T>& v);// screen output

	/**
	*\brief Overloaded operator for File Input
	* Overloaded operator for inputting a vector from file. Compatible with file output operator.
	*\param ifs - Input File Stream
	*\param v - Vector
	*\return Input File Stream
	*/
	template <typename T> friend ifstream& operator>>(std::ifstream& ifs, Vector<T>& v);

	/**
	*\brief Overloaded operator for File Output
	* Overloaded operator for outputting a vector to file. Compatible with file input operator.
	*\param ofs - Output File Stream
	*\param v - Vector
	*\return Output File Stream
	*/
	template <typename T> friend ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v);
};


// CONSTRUCTORS
// default constructor (empty vector)
template<typename T>
Vector<T>::Vector() : num(0), pdata(0) {}

// initialise data, called by the constructors
template<typename T>
void Vector<T>::Init(int Num)
{
	//check input sanity
	if(Num < 0) throw std::invalid_argument("vector size negative");
	num = Num;
	if (num <= 0)
		pdata = 0;  // empty vector, nothing to allocate
	else {
		pdata = new T[num];  // Allocate memory for vector
		for (int i=0; i<num; i++) pdata[i] = 0.0;
	}
}

// alternate constructor
template<typename T>
Vector<T>::Vector(int Num)
{
	Init(Num);
}

// copy constructor
template<typename T>
Vector<T>::Vector(const Vector<T>& copy)
{
	Init(copy.size()); // allocate the memory 

	// copy the data members (if vector is empty then pdata==0 and num==0)
	for (int i=0; i<num; i++) pdata[i]=copy.pdata[i]; 
}

// DESTRUCTOR
template<typename T>
Vector<T>::~Vector()
{
	delete [] pdata; // free the dynamic memory 
}


// OVERLOADED OPERATORS
// assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& copy)
{
	if (this == &copy) return *this; // Can't copy self to self (that is v = v 
	// in main is dealt with)
	delete [] pdata; // delete existing memory
	Init(copy.size()); // create new memory then copy data
	for (int i=0; i<num; i++) pdata[i] = copy.pdata[i]; 
	return *this;
}


// array access operator for assigning values
template<typename T>
T& Vector<T>::operator[](int i)
{
	//check the range, throw appropriate exception 
	if(i<0 || i>=num) throw std::out_of_range("vector access error");
	return pdata[i];
}

// array access operator for reading values
template<typename T>
T Vector<T>::operator[](int i) const
{
	//check the range, throw appropriate exception 
	if(i<0 || i>=num) throw std::out_of_range("vector access error");
	return pdata[i];
}

// SIZE
// return the size of the vector
template<typename T>
int Vector<T>::size() const
{
	return num;
}

// COMPARISON
template<typename T>
bool Vector<T>::operator==(const Vector& v) const
{	
	if (num != v.num) throw std::invalid_argument("incompatible vector sizes\n"); 
	for (int i=0; i<num; i++) if ((*this)[i] != v[i]) return false;
	return true;
}


// INPUT AND OUTPUT
// keyboard input - user friendly
template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v)
{
	if (!v.num) {
		int n;

		std::cout << "input the size for the vector" << std::endl;
		is >> n;
		//check input sanity
		if(n < 0) throw std::invalid_argument("read error - negative vector size");

		// prepare the vector to hold n elements
		v = Vector<T>(n);
	}
	// input the elements
	std::cout << "input "<< v.num <<" vector elements" << std::endl;
	for (int i=0; i<v.num; i++) is >> v[i];

	// return the stream object
	return is;
}

// file input - raw data, compatible with file writing operator
template<typename T>
std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v) 
{
	int n;

	// read size from the file
	ifs >> n;
	//check input sanity
	if(n < 0) throw std::invalid_argument("file read error - negative vector size");

	// prepare the vector to hold n elements
	v = Vector<T>(n);

	// input the elements
	for (int i=0; i<n; i++) ifs >> v[i];

	// return the stream object
	return ifs;
}

// screen output - user friendly
template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
	if (v.pdata) {
		for (int i=0; i<v.size(); i++) os << v[i]  << " ";
		os << std::endl;
	}
	else
	{
		os << "Vector is empty." << std::endl;
	}
	return os;
}

// file output - raw data, comaptible with file reading operator
template<typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v)
{
	//put vector size in first line (even if it is zero)
	ofs << v.size() << std::endl;
	//put data in second line (if size==zero nothing will be put)
	for (int i=0; i<v.size(); i++) ofs << v[i]  <<  " ";
	ofs << std::endl;
	return ofs;
}


#endif