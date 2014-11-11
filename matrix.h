/**
* \file Vector.h
* \brief Matrix template class definition & implementation
* \author Saqib Hussain S194491
* \date 01/12/2013
* \copyright Saqib Hussain 2013
*/

#ifndef MATRIX_H  //include guard
#define MATRIX_H

#include <iostream>  //generic IO
#include <fstream>   //file IO
#include <stdexcept> //provides exceptions
#include "vector.h"  //we use Vector in Matrix implementation

/**
* \class Matrix Template
* \brief Redefinition of the Matrix class to work with Templates
*/
template <typename T>
class Matrix {
protected:
	Vector<T> v;    /**< Vector used to store the matrix elements */  
	int nrows;		/**< number of rows of the matrix */  
	int ncols;		/**< number of columns of the matrix */  

public:
	/**
	*\brief Default Constructor, uses default constructor for v
	* Constructs an empty matrix and vector
	*/
	Matrix(); 

	/**
	*\brief Alternate Constructor
	* Build a Matrix using number of rows and columns
	*\param Nrows - Int number of rows
	*\param Ncols - Int number of Columns
	*/
	Matrix(int Nrows, int Ncols); 

	/**
	*\brief Alternate Constructor - Vector
	* Build a Matrix using a Vector
	*\param v - Vector
	*/
	Matrix(const Vector<T>& v);

	/**
	*\brief Copy Constructor
	* Build a Matrix using another Matrix
	*\param m - Matrix
	*/
	Matrix(const Matrix<T>& m); // copy constructor

	/**
	*\brief Accessor
	*\return int - Number of rows of Matrix
	*/
	int getNrows() const; 

	/**
	*\brief Accessor
	*\return int - Number of columns of Matrix
	*/
	int getNcols() const;

	/**
	*\brief Overloaded Function Call Operator for assignment
	* Allows accessing the matrix by (i, j)
	*\param i - Int - Index for row
	*\param j - Int - Index for column
	*\return Pointer to the template datatype for writing
	*/
	T& operator() (int i, int j); 

	/**
	*\brief Overloaded Function Call Operator for Reading
	* Allows accessing the matrix by (i, j)
	*\param i - Int - Index for row
	*\param j - Int - Index for column
	*\return Template datatype for Reading
	*/
	T operator() (int i, int j) const; 

	/**
	*\brief Overloaded assignment operator
	*\param m - Matrix
	*\return Matrix after assignation is complete
	*/
	Matrix<T>& operator=(const Matrix& m); 

	/**
	*\brief Overloaded Comparison Operator
	* Returns true or false depending on whether or not the Matrix passed as an argument is equal to Matrix upon which the method was called
	*\param m - Matrix
	*\return Bool
	*/
	bool operator==(const Matrix& m) const;

	/**
	*\brief Overloaded operator for Keyboard Input
	* Overloaded operator for inputting a Matrix from keyboard
	*\param is - Input Stream
	*\param m - Matrix
	*\return Input Stream
	*/
	template <typename T> friend std::istream& operator>>(std::istream& is, Matrix<T>& m);

	/**
	*\brief Overloaded operator for Screen Output
	* Overloaded operator for outputting a Matrix to screen
	*\param os - Output Stream
	*\param m - Matrix
	*\return Output Stream
	*/
	template <typename T> friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

	/**
	*\brief Overloaded operator for File Input
	* Overloaded operator for inputting a Matrix from file. Compatible with file output operator.
	*\param ifs - Input File Stream
	*\param m - Matrix
	*\return Input File Stream
	*/
	template <typename T> friend std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m);

	/**
	*\brief Overloaded operator for File Output
	* Overloaded operator for outputting a Matrix to file. Compatible with file input operator.
	*\param ofs - Output File Stream
	*\param m - Matrix
	*\return Output File Stream
	*/
	template <typename T> friend std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m);
};

// Note: There is no strict need for a copy constructor or 
// assignment operator in the Matrix class since the 
// compiler versions of these methods will work OK. It will copy/assign 
// the values of nrows and ncols and call the Vector copy 
// constructor/assignment operator automatically for the 
// Vector part v inside the Matrix. However they are written
// for clarity and understanding


// CONSTRUCTORS
/*=
*Default constructor (empty matrix)
*/
template<typename T>
Matrix<T>::Matrix() : nrows(0), ncols(0), v(0) {}

/*
* Alternate constructor - creates a matrix with the given values
*/
template<typename T>
Matrix<T>::Matrix(int Nrows, int Ncols)
{
	//check input
	if(Nrows < 0 || Ncols < 0) throw std::invalid_argument("matrix size negative");
	nrows = Nrows;
	ncols = Ncols;
	//if rownumber <= 0 or colnumber <= 0 then the program creates a 0-sized vector
	if (nrows <= 0 || ncols <= 0)
		v = Vector<T>(0);  // empty matrix, nothing to allocate
	else
		v = Vector<T>(nrows*ncols);
}


/*
* Alternate constructor - creates a matrix from a vector
*/
template<typename T>
Matrix<T>::Matrix(const Vector<T>& x) : v(x), nrows(x.size()), ncols(1)
{
}

/*
* Copy constructor
*/
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m) : v(m.v), nrows(m.getNrows()), ncols(m.getNcols())
{
}


// ACCESSOR METHODS
/*
* Get back matrix rows
*/
template<typename T>
int Matrix<T>::getNrows() const { return nrows; }

/*
* Get back matrix cols
*/
template<typename T>
int Matrix<T>::getNcols() const { return ncols; }

// OVERLOADED FUNCTION CALL OPERATORS
/*
* Operator() - returns with a specified value of matrix for write
*/
template<typename T>
T& Matrix<T>::operator() (int i, int j) {

	if (i>nrows-1 || j>ncols-1 || i<0 || j<0 ) throw std::out_of_range("matrix access error");
	return v[i*ncols+j];
}

/*
* Operator() - returns with a specified value of matrix for read
*/
template<typename T>
T Matrix<T>::operator() (int i, int j) const {
	//if the given parameters (coordinates) are out of range
	if (i>nrows-1 || j>ncols-1 || i<0 || j<0 ) throw std::out_of_range("matrix access error");
	return v[i*ncols+j];
}

/*
* Operator= - assignment
*/
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m)
{
	nrows = m.nrows;
	ncols = m.ncols;

	v = m.v;

	return *this;
}


/*
* equiv - comparison function, returns true if the given matrices are the same
*/
template<typename T>
bool Matrix<T>::operator==(const Matrix& a) const {

	//if the sizes do not match return false
	if ( (nrows != a.nrows) || (ncols != a.ncols) ) return false;

	//compare all of the elements
	for (int i=0;i<nrows;i++) {
		for (int j=0;j<ncols;j++) {
			if ((*this)(i,j) != a(i,j)) return false; 
		}
	}

	return true;
}


// INPUT AND OUTPUT
/*
* keyboard input , user friendly
*/
template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m) {

	int nrows, ncols;
	if (!m.nrows) {
		std::cout << "input the number of rows for the matrix" << std::endl;
		is >> nrows;
		std::cout << "input the number of cols for the matrix" << std::endl;
		is >> ncols;
		//check input 
		if(nrows < 0 || ncols < 0) throw std::invalid_argument("read error - negative matrix size");

		// prepare the matrix to hold n elements
		m = Matrix<T>(nrows, ncols);
	}
	// input the elements
	std::cout << "input "<< m.nrows * m.ncols << " matrix elements" << std::endl;
	for (int i=0; i<m.nrows*m.ncols; i++) is >> m.v[i];
	// return the stream object
	return is;
}

/* 
* screen output, user friendly
*/
template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {

	if (&m.v) {
		os << "The matrix elements are" << std::endl;
		for (int i=0; i<m.nrows;i++) {
			for (int j=0;j<m.ncols;j++) {
				os << m(i,j)  << " ";
			}
			os << "\n";
		}
		os << std::endl;
	}
	else
	{
		os << "Matrix is empty." << std::endl;
	}
	return os;
}

/*
* file input - raw data, compatible with file writing operator
*/
template<typename T>
std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m) {

	int nrows, ncols;

	// read size from the file
	ifs >> nrows; ifs>> ncols;
	//check input sanity
	if(nrows < 0 || ncols < 0) throw std::invalid_argument("file read error - negative matrix size");

	// prepare the vector to hold n elements
	m = Matrix<T>(nrows, ncols);

	// input the elements
	for (int i=0; i<nrows*ncols; i++) ifs >> m.v[i];

	// return the stream object
	return ifs;
}
/*
* file output - raw data, comaptible with file reading operator
*/
template<typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m) {
	//put matrix rownumber in first line (even if it is zero)
	ofs << m.nrows << std::endl;
	//put matrix columnnumber in second line (even if it is zero)
	ofs << m.ncols << std::endl;
	//put data in third line (if size==zero nothing will be put)
	for (int i=0; i<m.nrows; i++) {
		for (int j=0; j<m.ncols; j++) ofs << m(i,j)  <<  " ";
		ofs << std::endl;
	}
	return ofs;
}






#endif