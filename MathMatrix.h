/**
* \file MathMatrix.h
* \brief Mathmatrix class defintion
* \author Saqib Hussain S194491
* \date 01/12/2013
* \copyright Saqib Hussain 2013
*/

#ifndef MATH_MATRIX_H //include guard 
#define MATH_MATRIX_H

#include "Matrix.h"
#include "MathVector.h"

using namespace std;

/**
* \class MathMatrix
* \brief Mathmatrix class inherits the Matrix Template class using doubles
*/
class MathMatrix : public Matrix<double>
{
private:
	int n; /**< size of the square matrix*/ 
public:
	/**
	*\brief default constructor
	* Construct an empty matrix
	*/
	MathMatrix();

	/**
	*\brief alternate constructor
	* Construct a matrix of the given size
	*\param n - Size of square matrix
	*/
	MathMatrix(int n); 

	/**
	*\brief Accessor Method to return matrix size
	* Return the size of the square matrix
	*\return Int - Matrix Size
	*/
	int get_size() const; 

	/**
	*\brief Method to calculate L1 Norm
	* Calculate and return the l1 norm of the matrix the method is called on
	*\return double - l1 norm
	*/
	double one_norm() const;

	/**
	*\brief Method to Calculate L2 Norm
	*Calculate and return the l2 norm of the matrix the method is called on
	*\return double - L2 norm
	*/
	double two_norm() const; 

	/**
	*\brief Method to Calculate L2 Norm
	* Calculate and return the uniform norm of the matrix the method is called on
	*\return double - Uniform Norm
	*/
	double uniform_norm() const; 

	/**
	*\brief Overloaded operator for MathMatrix MathMatrix multiplication
	* Overloaded operator for multiplying the MathMatrix object the method was called on by the one passed as a parameter
	*\param a - MathMatrix Reference
	*\return MathMatrix
	*/
	MathMatrix operator*(const MathMatrix& a) const; 

	/**
	*\brief Overloaded operator for MathMatrix MathVector Multiplication
	*Overloaded operator for multiplying the MathMatrix object the method was called on by the MathVector object passed as a parameter
	*\param v - MathVector Reference
	*\return MathMatrix
	*/
	MathVector operator*(const MathVector& v) const; 

	/**
	*\brief Method to computer lower triangular form in LU Factorisation
	* Returns a MathMatrix with the lower triangluar form of the MathMatrix object the method was called on
	*\return MathMatrix
	*/
	MathMatrix compute_lower() const;

	/**
	*\brief Method to computer upper triangular form in LU Factorisation
	* Returns a MathMatrix with the upper triangluar form of the MathMatrix object the method was called on
	*\return MathMatrix
	*/
	MathMatrix compute_upper() const;

	/**
	*\brief Method to compute the inverse matrix
	* Computes the inverse of the MathMatrix object the method was called on
	*\return MathMatrix
	*/
	MathMatrix inverse() const;

	/**
	*\brief Method to compute the condition number
	* Computes the condition number of the MathMatrix object the method was called on
	*\return double - Condition Number
	*/
	double condition_num() const;

	/**
	*\brief Method to compute the Permutation Matrix
	* Produces the Permutation MathMatrix object P using the MathMatrix object A passed as a parameter
	*\param a - MathMatrix - Reference to initial matrix
	*\param n - Int - Matrix size
	*\param p - MathMatrix Reference 
	*/
	static void reorder(const MathMatrix& a, int n, MathMatrix& p);

	/**
	*\brief Method to compute the determinant
	* Calculates the determinant of the MathMatrix object the method was called on
	*\return double - Determinant
	*/
	double det() const;

	/**
	*\brief Method to perform forward substiution
	* Performs forward substituition on the MathMatrix object the method was called on
	*\return MathMatrix
	*/
	MathMatrix forwardInv() const;

	/**
	*\brief Method to perform backward substiution
	* Performs backward substituition on the MathMatrix object the method was called on
	*\return MathMatrix
	*/
	MathMatrix backwardInv() const;

	/**
	*\brief Overloaded operator for Keyboard Input
	* Overloaded operator for inputting a Matrix from keyboard
	*\param is - Input Stream
	*\param m - MathMatrix - Reference
	*\return Input Stream
	*/
	friend std::istream& operator>>(std::istream& is, MathMatrix& m);
};


#endif