/***************************************************
File:			main.cpp
Description:	Main method to test the Matrix and Vector Template
Classes and the Math Vector&Matrix Classes
Author:			Saqib Hussain S194491
Organisation:	School of Engineering, Cranfield University
Email:			s.m.hussain@cranfield.ac.uk
Copyright:		Copyright Saqib Hussain 2013
***************************************************/

#include "Complex.h"
#include "MathMatrix.h"
#include "MathVector.h"
#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	bool run = true;
	while (run)
	{
		cout << "Which Class Would You Like To Test?";
		cout << "\n(1)Vector Template Class";
		cout << "\n(2)Matrix Template Class";
		cout << "\n(3)MathVector Class";
		cout << "\n(4)MathMatrix Class";
		cout << "\n\nPlease enter your choice:";
		int classChoice;
		cin >> classChoice;
		switch (classChoice)
		{
		case 1: //Testing Vector Template Class
			{
				cout << "\n\n****************************"
					"\nTesting the Vector Template Class"
					"\n****************************";
				Vector<Complex> v; //Declare
				cout << "\nPlease enter the Vector of Complex Numbers\n";
				cin >> v;		   //Read in vector
				cout << v;		   //Print vector  
				break;
			}
		case 2: //Testing Matrix Template Class
			{
				cout << "\n\n****************************"
					"\nTesting the Matrix Template Class"
					"\n****************************";
				Matrix<Complex> m; //Declare
				cout << "\nPlease enter the Matrix of Complex Numbers\n";
				cin >> m;		   //Read in Matrix
				cout << m;		   //Print Matrix  
				break;
			}
		case 3: //Testing MathVector Class
			{
				cout << "\n\n****************************"
					"\nTesting the MathVector Class"
					"\n****************************";
				//New object of type MathVector
				MathVector mV;
				cout << "\nPlease enter the Vector:\n";
				//Use overloaded operator to read in vector size and values
				cin >> mV;
				//Ask which type of norm they wish to compute
				cout << "Which norm would you like to compute: l1 norm (1), l2 norm(2) or uniform norm (3)? ";
				int norm;
				cin >> norm;
				//Switch on selection
				switch (norm)
				{
				case(1):
					cout << "\nThe l1 norm is: " << mV.one_norm() << "\n";
					break;
				case(2):
					cout << "\nThe l2 norm is: " << mV.two_norm() << "\n";
					break;
				case(3):
					cout << "\nThe uniform norm is: " << mV.uniform_norm() << "\n";
					break;
				}  
				break;
			}
		case 4:
			{
				cout << "\n\n****************************"
					"\nTesting the MathMatrix Class"
					"\n****************************";
				cout << "\n\nWhat would you like to do?";
				cout << "\n(1)Matrix Norms";
				cout << "\n(2)Matrix by Matrix Multiplication";
				cout << "\n(3)Matrix by Vector Multiplication";
				cout << "\n(4)Compute Lower and Upper Triangles of a Matrix";
				cout << "\n(5)Compute the Inverse of a Matrix";
				cout << "\n(6)Compute the Condition Number of a Matrix";
				cout << "\n(7)Compute the Determinant of a Matrix";
				cout << "\n\nPlease enter your choice:";
				int choice;
				cin >> choice;
				switch (choice)
				{
				case 1:
					{
						cout << "\nTesing Matrix Norms\n"
							"*******************\n";
						MathMatrix M;
						cin >> M;
						cout << "Which norm would you like to compute: l1 norm (1), l2 norm(2) or uniform norm (3)? ";
						int norm = 0;
						cin >> norm;
						switch (norm)
						{
						case(1):
							cout << "\nThe l1 norm is: " << M.one_norm() << "\n";
							break;
						case(2):
							cout << "\nThe l2 norm is: " << M.two_norm() << "\n";
							break;
						case(3):
							cout << "\nThe uniform norm is: " << M.uniform_norm() << "\n";
							break;
						}
						break;
					}
				case 2:
					{
						try
						{
							cout << "\nTesing Matrix by Matrix Multiplication\n"
								"**************************************\n";
							cout << "Please input the first Matrix M1:\n";
							MathMatrix M1;
							cin >> M1;
							cout << "Please input the second Matrix M2, make sure it is the same size as M1:\n";
							MathMatrix M2;
							cin >> M2;
							cout << "Multiplying M1 by M2...\n";
							cout <<	(M1*M2);
						}
						catch (const char* msg)	{ cerr << msg << '\n'; }
						break;
					}
				case 3:
					{
						try 
						{
							cout << "\nTesing Matrix by Vector Multiplication\n"
								"**************************************\n";
							cout << "Please input the Matrix M1:\n";
							MathMatrix M1;
							cin >> M1;
							cout << "Please input the Vector V1, make sure it is the same size as M1:\n";
							MathVector V1;
							cin >> V1;
							cout << "Multiplying M1 by M2...\n";
							cout << M1*V1;
						}
						catch (const char* msg)  {	cerr << msg << '\n'; }
						break;
					}
				case 4:
					{
						try
						{
							cout << "\nTesing L & U Triangular form of Matricies\n"
								"*****************************************\n";
							cout << "Please input the Matrix M1:\n";
							MathMatrix M1;
							cin >> M1;
							cout << "Computing Lower Triangle:\n";
							cout << M1.compute_lower();
							cout << "Computing Lower Triangle:\n";
							cout << M1.compute_upper();
						}
						catch (const char* msg)  {	cerr << msg << '\n'; }
						break;
					}
				case 5:
					{
						try
						{
							cout << "\nTesing The Inverse of a Matrix\n"
								"*******************************\n";
							cout << "Please input the Matrix M1:\n";
							MathMatrix M1;
							cin >> M1;
							cout << "Computing Inverse...\n";
							cout << M1.inverse();
						}
						catch (const char* msg)  {	cerr << msg << '\n'; }
						break;
					}
				case 6:
					{
						cout << "\nTesing The Condition Number of a Matrix\n"
							"***************************************\n";
						try
						{
							cout << "Please input the Matrix M1:\n";
							MathMatrix M1;
							cin >> M1;
							cout << "Computing The Condition Number...\n";
							cout << M1.condition_num() << endl;
						}
						catch (const char* msg)  {	cerr << msg << '\n'; }
						break;
					}
				case 7:
					{
						cout << "\nTesing The Determinant of a Matrix\n"
							"**********************************\n";
						try
						{
							cout << "Please input the Matrix M1:\n";
							MathMatrix M1;
							cin >> M1;
							cout << "Computing The Condition Number...\n";
							cout << M1.det() << endl;
						}
						catch (const char* msg)  {	cerr << msg << '\n'; }
						break;
					}
				default :
					{
						cout << "Unrecognised Selection!\n\n";
						break;
					}
				}//End Math Matrix Switch
				break;
			}
		default :
			{
				cout << "Unrecognised Selection!\n\n";
				break;
			}
		} //End main Switch
		//Check if you want to run the application again
		bool run2 = true;
		do {
			cout << "Do you want to run the application again?" << endl;
			cout << "Yes or No: ";
			string input;
			cin.clear();
			cin.sync();
			getline (cin, input);
			transform(input.begin(), input.end(), input.begin(), tolower);
			if (input == "yes")
				run2 = false;
			else if (input == "no")
			{
				run2 = false;
				run = false;
			}
		}
		while (run2);
	}//End main while loop
}
