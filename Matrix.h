


/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "defines.h"
#include "Object.h"
#include "Vector.h"




class Matrix
{

public:

	// function declarations
	Matrix();
	~Matrix();

	void Reset();

	void SetMatrix(const int& TYPE, const Object3D& obj, 
		           const Vector VPN, const Vector VUP, 
				   const Vector VRP, const Vector COP,
				   int projection);



	// Three dimensional matrix setup functions.
	void SetCOPShearMatrix(const Vector& COP);
	void SetProjectionMatrix(const Vector& COP, int ProjectionType);
	void SetModelingMatrix(const Vector& VRP, const Vector& VUP, const Vector& VPN);

	void SetWorldMatrix(const int& RotX, const int& RotY, const int& RotZ,
						const double& ScaleX, const double& ScaleY, const double& ScaleZ,
						const double& ShearX, const double& ShearY, const double& ShearZ,
						const double& TransX, const double& TransY, const double& TransZ);

	void   Multiply(const Matrix& lhs, const Matrix& rhs);

	point  ApplyMatrixToPoint(const point& pt);
	point  ApplyMatrixToPoint(const point& pt) const;


	double m_values[4][4];

};


#endif