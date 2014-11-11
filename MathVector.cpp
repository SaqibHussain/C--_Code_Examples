#include "MathVector.h"

// default constructor (empty vector)
MathVector::MathVector() : Vector() {}



// alternate constructor 
MathVector::MathVector(int Num) : Vector(Num) {}


double MathVector::one_norm() const
{
	//Variable to hold norm
	double norm = 0;
	//Loop through vector elements
	for (int i=0; i < num; i++)
	{
		this->num;
		//Keep adding the element's absolute value to the current value of norm
		norm+= fabs(pdata[i]);
	}
	//Return the norm value after finished looping
	return norm;
}

double MathVector::two_norm() const
{
	double norm = 0;
	for (int i=0; i < num; i++)
	{
		//Keep adding the squared value of each element to the current value of norm
		norm+=(pdata[i]*pdata[i]);
	}
	//Return the square root of norm.
	return sqrt(norm);
}

double MathVector::uniform_norm() const
{
	double norm = 0;
	for (int i=0; i < num; i++)
	{
		//If the absolute value of any element is bigger than the current value of norm, set norm equal to it
		if (fabs(pdata[i]) > norm) { norm = fabs(pdata[i]); };
	}
	return norm;
}