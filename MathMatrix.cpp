#include "MathMatrix.h"
#include <iostream>
using namespace std;

// default constructor
MathMatrix::MathMatrix() : Matrix<double>(0,0), n(0) { }

// alternate constructor
MathMatrix::MathMatrix(int n) : Matrix<double>(n,n), n(n) { }

// return size of matrix
int MathMatrix::get_size() const
{
	return n;
}

// 1-norm of a matrix
double MathMatrix::one_norm() const
{
	//A vector object the length of the number of columns in the matrix to temporarily store,
	MathVector temp(ncols);
	//Loop on columns
	for (int j=0; j<ncols; j++)
	{
		//Declare empty norm
		double norm =0;
		//for each column go across each row element
		for (int i=0; i<nrows; i++)
		{
			//Add the absolute value of that element to the current value of norm
			norm+=fabs((*this)(i,j));
		}
		//Set the same index of vector object to the column loop iteration number
		temp[j] = norm;
	}
	//Declare norm variable
	double norm = 0;
	//Loop through vector object
	for (int i=0; i < ncols; i++)
	{
		//Set norm as highest value in the vector
		if (temp[i] > ncols) { norm = temp[i]; };
	}
	//Return norm value
	return norm;
}

// 2-norm of a matrix
double MathMatrix::two_norm() const
{
	double norm = 0;
	//Loop on columns
	for (int i=0; i<ncols; i++)
	{
		//Loop through the row 
		for (int r=0; r<nrows; r++)
		{
			//Add the square of the absolute value to the current norm value
			norm+=(fabs((*this)(i,r)))*(fabs((*this)(i,r)));
		}
	}
	//Return square root of value as the norm
	return sqrt(norm);
}

// uniform norm of a matrix 
double MathMatrix::uniform_norm() const
{
	//Vector object initialised with number of rows
	MathVector temp(nrows);
	//Loop on rows
	for (int i=0; i<nrows; i++)
	{
		//Declare norm variable as 0
		double norm = 0;
		//Loop through columns
		for (int j=0; j<ncols; j++)
		{
			//Add absolute value to the current value of norm
			norm+=fabs((*this)(i,j));
		}
		//Add summed value to vector object
		temp[i] = norm;
	}
	//Declare norm variable equal to 0
	double norm = 0;
	//Loop through vector
	for (int i=0; i < nrows; i++)
	{
		//Set norm equal to biggest value in vector
		if (temp[i] > norm) { norm = temp[i]; };
	}
	//Return norm value
	return norm;
}

// overloaded matrix by matrix multiplication
MathMatrix MathMatrix::operator*(const MathMatrix& a) const
{
	if (n != a.get_size()) { throw "Matricies do not commute"; }
	//Create matrix object of the correct size to hold the resulting matrix from multiplication
	MathMatrix temp(n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			temp(i,j) = 0.0;

	//Go across the rows of the matrix the method was called on
	for (int i=0; i<n; i++)
	{
		//Go across the columns on the matrix that was passed as a parameter
		for (int j=0; j<n; j++)
		{
			//Declare empty variable to hold the multiplication result
			double sum = 0;
			for (int k=0; k<n; k++)
			{
				//Multiply corresoponding elements
				sum+=(*this)(i, k) * a(k, j); 
			}
			//Set element in temp at the corresponding loop iteration index to the result
			temp(i, j) = sum;
		}
	}
	//Return the new matrix
	return temp;
}

// overloaded multiplication of matrix by a vector 
MathVector MathMatrix::operator*(const MathVector& v) const
{
	if (n != v.size()) { throw "Matrix and Vector do not"; }
	//Create matrix object of the correct size to hold the resulting matrix from multiplication
	MathVector temp(v.size());
	//Go across the rows of the matrix the method was called on
	for (int i=0; i<nrows; i++)
	{
		//Declare empty variable to hold the multiplication result
		double sum = 0;
		//Go across the columns on the matrix that was passed as a parameter
		for (int j=0; j<ncols; j++)
		{
			sum+=(*this)(i, j) * v[0];
		}
		//Set element in temp at the corresponding loop iteration index to the result
		temp[i] = sum;
	}
	return temp;
}

// compute the lower triangular form, L, in the LU factorisation
MathMatrix MathMatrix::compute_lower() const
{
	MathMatrix temp(*this), L(n);
	double mult;
	int i,j,k;
	for (k=0; k<n-1; k++) {
		for (i=k+1; i<n; i++) {
			if (temp(k,k) == 0) { throw "Pivot is zero!"; }
			mult = temp(i,k)/temp(k,k);
			temp(i,k) = mult;
			for (j=k+1; j<n; j++) {
				temp(i,j) -= mult*temp(k,j);
			}
		}
	}
	for (i=0; i<n; i++)
		L(i,i) = 1.0;
	for (i=1; i<n; i++)
		for (j=0; j<i; j++)
			L(i,j) = temp(i,j);
	return L;
}

// compute the upper triangular form, U, in the LU factorisation
MathMatrix MathMatrix::compute_upper() const
{
	MathMatrix temp(*this), U(n);
	double mult;
	int i, j, k;
	for (k=0; k<n-1; k++) {
		for (i=k+1; i<n; i++) {
			if (temp(k,k) == 0) { throw "Pivot is zero!"; }
			mult = temp(i,k)/temp(k,k);
			temp(i,k)=mult;
			for (j=k+1; j<n; j++) {
				temp(i,j) -= mult*temp(k,j);
			}
		}
	}
	for (i=0; i<n; i++)
		for (j=i; j<n; j++)
			U(i,j) = temp(i,j);
	return U;
}

// compute the inverse matrix
MathMatrix MathMatrix::inverse() const
{
	if(det() == 0.0) { throw "There is no inverse to this Matrix"; }
	MathMatrix P = MathMatrix(n);
	reorder((*this), n, P);
	MathMatrix U((P*(*this)).compute_upper().backwardInv());
	MathMatrix L((P*(*this)).compute_lower().forwardInv());
	return U*L*P;
}

// compute the condition number of the matrix double condition_num() const;
double MathMatrix::condition_num() const
{
	double temp = 0.0;
	if (det() == 0.0) { throw "Determinant is Zero, cannot calculate a condition number!"; }
	temp = uniform_norm()*inverse().uniform_norm();
	return temp;
}

void MathMatrix::reorder(const MathMatrix& a, int n, MathMatrix& p)
{
	int i,j,k;
	MathVector pvt;
	int pvtk,pvti;
	MathVector scale;
	double aet, tmp, mult;
	MathMatrix temp;

	pvt = MathVector(n);
	temp = MathMatrix(n);

	//Copy matrix into temp
	temp = a;

	for (k = 0; k < n; k++) pvt[k] = k;

	scale = MathVector(n);
	for (k = 0; k < n; k++) 
	{
		scale[k] = 0;
		for (j = 0; j < n; j++) 
		{
			if (fabs(scale[k]) < fabs(temp(k,j))) 
			{
				scale[k] = fabs(temp(k, j));
			}
		}
	}

	for (k = 0; k < n - 1; k++)   // main elimination loop
	{  
		// Find the pivot in column k in rows pvt[k], pvt[k+1], ..., pvt[n-1]
		int pc = k; 
		aet = fabs(temp(pvt[k],k)/scale[k]);
		for (i = k + 1; i < n; i++) {
			tmp = fabs(temp(pvt[i],k)/scale[pvt[i]]); 
			if (tmp > aet) {
				aet = tmp; 
				pc = i;
			}
		}
		if (aet == 0) 
		{ 
			cout << ("Pivot is 0");
			exit(1); 
		}
		if (pc != k)
		{        // swap pvt[k] and pvt[pc]
			int ii = pvt[k];
			pvt[k] = pvt[pc];
			pvt[pc] = ii;
		}

		// now eliminate the column entries logically below mx[pvt[k]][k]
		pvtk = pvt[k];   // pivot row
		for (i = k + 1; i < n; i++)
		{
			pvti = pvt[i];
			if (temp(pvti,k) != 0) 
			{
				mult = temp(pvti,k)/temp(pvtk,k); 
				temp(pvti,k) = mult;
				for (j = k + 1; j < n; j++)
				{
					temp(pvti,j) -= mult*temp(pvtk,j);
				}
			}
		}
	}
	for (i=0; i<n; i++){
		p(i,pvt[i])=1.0;
	}

}

double MathMatrix::det() const
{
	double det = 0.0;
	if (n==0)
		throw "Empty Matrix!";
	else if (n == 1)
		det = (*this)(0,0);
	else if (n == 2)
		det = (*this)(0,0) * (*this)(1,1) - (*this)(1,0) * (*this)(0,1);
	else{
		MathMatrix sub(n-1);
		int l;
		for (int i=0;i<n;i++)
		{
			for(int j=1; j<n; j++){
				l=0;
				for(int k=0; k<n; k++){
					if(k!=i){
						sub(j-1,l)=(*this)(j,k);
						l++;
					}
				}
			}
			det += pow(-1,i) * (*this)(0,i) * sub.det();
		}
	}
	return det;
}

MathMatrix MathMatrix::forwardInv() const
{
	MathMatrix inv(n);
	MathVector e(n),temp(n);
	int i, j, k;
	for(k=0; k<n; k++){
		if(k!=0)
			e[k-1]=0.0;
		e[k]=1.0;
		temp=e;
		for (i=1; i<n; i++)
			for (j=0; j<i; j++)
				temp[i] -= (*this)(i,j)*temp[j];
		for(i=0; i<n; i++)
			inv(i,k)=temp[i];
	}
	return inv;
}

MathMatrix MathMatrix::backwardInv() const
{
	MathMatrix inv(n);
	MathVector e(n),temp(n);
	int i, j, k;
	for(k=0; k<n; k++){
		if(k!=0)
			e[k-1]=0.0;
		e[k]=1.0;
		temp=e;
		for (i=n-1; i>= 0; i--) {
			for (j=i+1; j<n; j++) {
				temp[i] -= (*this)(i,j)*temp[j];
			}
			temp[i] /= (*this)(i,i);
		}
		for(i=0; i<n; i++)
			inv(i,k)=temp[i];
	}
	return inv;
}

//Need to implement own version of this to be able to set variable 'n'
std::istream& operator>>(std::istream& is, MathMatrix& m){
	int n;
	if (!m.n) {
		cout << "Please input the size of the matrix\n";
		is >> n;
		if (n < 0) throw "read error - negative matrix size";
		// prepare the matrix to hold n elements
		m = MathMatrix(n);
	}
	// input the elements
	std::cout << "input " << m.n * m.n << " matrix elements" << std::endl;
	for (int i = 0; i < m.n*m.n; i++) is >> m.v[i];
	// return the stream object
	return is;
}