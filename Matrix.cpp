


/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/


#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "Object3D.h"
#include "defines.h"
#include <typeinfo.h>
#include <io.h>
#include <fstream>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "Matrix.h"
#include "Vector.h"


Matrix::Matrix()
{
	// Set the values in the modeling matrix.
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			m_values[i][j] = 0.0;
		}// end for
	}// end for
		
	// setup for homogeneous coordinate
	// system matrix.
	m_values[3][3] = 1.0;
}

Matrix::~Matrix()
{

}


void Matrix::SetWorldMatrix(const int& RotX, const int& RotY, const int& RotZ,
							const double& ScaleX, const double& ScaleY, const double& ScaleZ,
							const double& ShearX, const double& ShearY, const double& ShearZ,
							const double& TransX, const double& TransY, const double& TransZ)
// This function creates a transformation matrix based on an object's 
// rotation, translation, shear, and scale values.  
{
	// World Matrix temporaries
	Matrix RotationX;
	Matrix RotationY;
	Matrix RotationZ;
	Matrix Scale;
	Matrix ShearingX;
	Matrix ShearingY;
	Matrix ShearingZ;
	Matrix Temp1, Temp2, Temp3, Temp4, Temp5;

	double RotationRadiansX = RotX * PI / 180;
	double RotationRadiansY = RotY * PI / 180;
	double RotationRadiansZ = RotZ * PI / 180;

	double ShearRadiansX    = atan(10.0 / ShearX);
	double ShearRadiansY    = atan(10.0 / ShearY);
	double ShearRadiansZ    = atan(10.0 / ShearZ);

	// Set up the RotationX matrix.
	RotationX.m_values[0][0] = 1.0;
	RotationX.m_values[1][1] = cos(RotationRadiansX);
	RotationX.m_values[1][2] = (-1) * sin(RotationRadiansX);
	RotationX.m_values[2][1] = sin(RotationRadiansX);
	RotationX.m_values[2][2] = cos(RotationRadiansX);
	RotationX.m_values[3][3] = 1.0;

	// Set up the Rotation Y matrix.
	RotationY.m_values[0][0] = cos(RotationRadiansY);
	RotationY.m_values[0][2] = sin(RotationRadiansY);
	RotationY.m_values[1][1] = 1.0;
	RotationY.m_values[2][0] = (-1) * sin(RotationRadiansY);
	RotationY.m_values[2][2] = cos(RotationRadiansY);
	RotationY.m_values[3][3] = 1.0;

	// Set up the Rotation Z matrix.
	RotationZ.m_values[0][0] = cos(RotationRadiansZ);
	RotationZ.m_values[0][1] = (-1) * sin(RotationRadiansZ);
	RotationZ.m_values[1][0] = sin(RotationRadiansZ);
	RotationZ.m_values[1][1] = cos(RotationRadiansZ);
	RotationZ.m_values[2][2] = 1.0;
	RotationZ.m_values[3][3] = 1.0;

	// Set up the Scale matrix.
	Scale.m_values[0][0] = ScaleX;
	Scale.m_values[1][1] = ScaleY;
	Scale.m_values[2][2] = ScaleZ;
	Scale.m_values[3][3] = 1.0;

	// Set up the ShearX matrix.
	ShearingX.m_values[0][0] = 1.0;
	ShearingX.m_values[0][1] = 1.0 / tan(ShearRadiansX);
	ShearingX.m_values[1][1] = 1.0;
	ShearingX.m_values[2][2] = 1.0;
	ShearingX.m_values[3][3] = 1.0;

	// Set up the ShearY matrix.
	ShearingY.m_values[0][0] = 1.0;
	ShearingY.m_values[1][0] = 1.0 / tan(ShearRadiansY);
	ShearingY.m_values[1][1] = 1.0;
	ShearingY.m_values[2][2] = 1.0;
	ShearingY.m_values[3][3] = 1.0;

	// Set up the ShearZ matrix.
	ShearingZ.m_values[0][0] = 1.0;
	ShearingZ.m_values[1][1] = 1.0;
	ShearingZ.m_values[2][0] = 1.0 / tan(ShearRadiansZ);
	ShearingZ.m_values[2][2] = 1.0;
	ShearingZ.m_values[3][3] = 1.0;

	// Do the matrix multiplications to obtain the world
	// matrix.
	Temp1.Multiply(RotationY, RotationX);
	Temp2.Multiply(RotationZ, Temp1);
	Temp3.Multiply(ShearingX, Temp2);
	Temp4.Multiply(ShearingY, Temp3);
	Temp5.Multiply(ShearingZ, Temp4);
	this->Multiply(Scale,     Temp5);

	// Insert the translation values into the final matrix.
	this->m_values[0][3] = TransX;
	this->m_values[1][3] = TransY;
	this->m_values[2][3] = TransZ;
	
}


void Matrix::SetModelingMatrix(const Vector& VRP, const Vector& VUP, const Vector& VPN)
// This function will produce a matrix that will convert the points of the object 
// from an x,y,z coordinate system to the u,v,n coordinate system.
{

	Vector u, v, n, N_Cross_VUP;

	double R_Dot_U = 0.0;
	double R_Dot_V = 0.0;
	double R_Dot_N = 0.0;

	// Ensure the incoming matrix is clear.
	this->Reset();

	// Get the n vector (View Plane Normal) from the camera information.
	n.SetVector(VPN.GetVectorX(), VPN.GetVectorY(), VPN.GetVectorZ());

	// Normalize the n vector.
	n.NormalizeVector();

	// Get the u vector from the cross product of the n vector and VUP vector.

	N_Cross_VUP.CrossProduct(n, VUP);
	N_Cross_VUP.NormalizeVector();

	// Set the u vector to the normalized NxVUP vector.
	u = N_Cross_VUP;

	// Get the v vector by getting the cross product of the u and the n vector.
	v.CrossProduct(u, n);

	R_Dot_U = VRP.DotProduct(u);
	R_Dot_V = VRP.DotProduct(v);
	R_Dot_N = VRP.DotProduct(n);

	// Set up the modeling matrix with the values derived above.
	this->m_values[0][0] = u.GetVectorX();
	this->m_values[0][1] = u.GetVectorY();
	this->m_values[0][2] = u.GetVectorZ();
	this->m_values[0][3] = (-1) * R_Dot_U;

	this->m_values[1][0] = v.GetVectorX();
	this->m_values[1][1] = v.GetVectorY();
	this->m_values[1][2] = v.GetVectorZ();
	this->m_values[1][3] = (-1) * R_Dot_V;

	this->m_values[2][0] = n.GetVectorX();
	this->m_values[2][1] = n.GetVectorY();
	this->m_values[2][2] = n.GetVectorZ();
	this->m_values[2][3] = (-1) * R_Dot_N;

	this->m_values[3][0] = 0.0;
	this->m_values[3][1] = 0.0;
	this->m_values[3][2] = 0.0;
	this->m_values[3][3] = 1.0;
}


void Matrix::SetCOPShearMatrix(const Vector& COP)
{
	Vector COP_Normalized;

	// This matrix will ensure that the COP is along the n axis
	// by shearing the view to an appropriate amount, which will 
	// in effect make the view look as if it is not on the n axis.
	COP_Normalized = COP;
	COP_Normalized.NormalizeVector();

	// Make sure the matrix is reset.
	this->Reset();

	// Set the shear matrix values.
	this->m_values[0][0] = 1.0;
	this->m_values[0][2] = (-1) * (COP_Normalized.GetVectorX()/COP_Normalized.GetVectorZ());
	this->m_values[1][1] = 1.0;
	this->m_values[1][2] = (-1) * (COP_Normalized.GetVectorY()/COP_Normalized.GetVectorZ());
	this->m_values[2][2] = 1.0;
	this->m_values[3][3] = 1.0;

}

void Matrix::SetProjectionMatrix(const Vector& COP, int ProjectionType)
{
	switch(ProjectionType)
	{
	case PARALLEL:
		this->m_values[0][0] = 1.0;
		this->m_values[1][1] = 1.0;
		this->m_values[2][2] = 1.0;
		this->m_values[3][3] = 1.0;
		break;

	case PERSPECTIVE:
		this->m_values[0][0] = 1.0;
		this->m_values[1][1] = 1.0;
		this->m_values[2][2] = 1.0;
		this->m_values[3][2] = -1.0 / COP.GetVectorZ();
		this->m_values[3][3] = 1.0;
		break;
	}// end switch
}


point Matrix::ApplyMatrixToPoint(const point& pt)
{
	point  temp;

	double original_x = pt._x;
	double original_y = pt._y;
	double original_z = pt._z;
	double original_h = pt._h;

	temp._x      = original_x * this->m_values[0][0] +
			       original_y * this->m_values[0][1] +
				   original_z * this->m_values[0][2] +
				   original_h * this->m_values[0][3];


	temp._y      = original_x * this->m_values[1][0] +
			       original_y * this->m_values[1][1] +
				   original_z * this->m_values[1][2] +
				   original_h * this->m_values[1][3];

	
	temp._z      = original_x * this->m_values[2][0] +
			       original_y * this->m_values[2][1] +
				   original_z * this->m_values[2][2] +
				   original_h * this->m_values[2][3];

	temp._h      = original_x * this->m_values[3][0] +
				   original_y * this->m_values[3][1] +
				   original_z * this->m_values[3][2] +
				   original_h * this->m_values[3][3];

	// Put the points in standard homogeneous coordinate system.
	temp._x = temp._x / temp._h;
	temp._y = temp._y / temp._h;
	temp._z = temp._z / temp._h;
	temp._h = temp._h / temp._h;

	return temp;
}


point Matrix::ApplyMatrixToPoint(const point& pt) const
{
	point temp;

	double original_x = pt._x;
	double original_y = pt._y;
	double original_z = pt._z;
	double original_h = pt._h;

	temp._x      = original_x * this->m_values[0][0] +
			       original_y * this->m_values[0][1] +
				   original_z * this->m_values[0][2] +
				   original_h * this->m_values[0][3];


	temp._y      = original_x * this->m_values[1][0] +
			       original_y * this->m_values[1][1] +
				   original_z * this->m_values[1][2] +
				   original_h * this->m_values[1][3];

	
	temp._z      = original_x * this->m_values[2][0] +
			       original_y * this->m_values[2][1] +
				   original_z * this->m_values[2][2] +
				   original_h * this->m_values[2][3];

	temp._h      = original_x * this->m_values[3][0] +
				   original_y * this->m_values[3][1] +
				   original_z * this->m_values[3][2] +
				   original_h * this->m_values[3][3];

	// Put the points in standard homogeneous coordinate system.
	temp._x = temp._x / temp._h;
	temp._y = temp._y / temp._h;
	temp._z = temp._z / temp._h;
	temp._h = temp._h / temp._h;

	return temp;
}

void Matrix::Multiply(const Matrix& lhs, const Matrix& rhs)
{
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			this->m_values[i][j] = 0.0;

			for(int k=0; k<4; ++k)
			{
				this->m_values[i][j] = this->m_values[i][j] +
					                   lhs.m_values[i][k] * rhs.m_values[k][j];
			}// end for
		}// end for
	}// end for
}


void Matrix::Reset()
{
	// Set the values in the modeling matrix.
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			m_values[i][j] = 0.0;
		}// end for
	}// end for
		
	// setup for homogeneous coordinate
	// system matrix.
	m_values[3][3] = 1.0;
}