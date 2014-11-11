/**
 * \file MathVector.h
 * \brief MathVector class defintion
 * \author Saqib Hussain S194491
 * \date 01/12/2013
 * \copyright Saqib Hussain 2013
 */

#ifndef MATH_VECTOR_H //include guard 
#define MATH_VECTOR_H
#include "vector.h"

/**
* \class MathVector
* \brief Inherits the Vector Template class using doubles
*/
class MathVector : public Vector<double> {
public:
	/**
	*\brief Default constructor
	* Constructs an empty MathVector object
	*/
	MathVector(); 

	/**
	*\brief Alternate Constructor
		* Constructs a MathVector object of the given size
*\param n - Int - Vector size
	*/
	MathVector(int n); 

	/**
	*\brief Method to compute l1 norm
		* Calculates the l1 norm of the MathVector object the method is called on
*\return double L1 norm
	*/
	double one_norm() const; 

	/**
	*\brief Method to compute l2 norm
		* Calculates the l2 norm of the MathVector object the method is called on
*\return double l2 norm
	*/
	double two_norm() const;

	/**
	*\brief Method to compute uniform norm
		* Calculates the uniform norm of the MathVector object the method is called on
*\return double uniform norm
	*/
	double uniform_norm() const; 
};

#endif