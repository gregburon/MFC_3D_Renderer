


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
#include "Vector.h"

/****************************************************/
/*                                                  */
/*  Constructor/Destructor for the Vector class.    */
/*                                                  */
/****************************************************/
Vector::Vector()
{
	m_values[X] = 0.0;
	m_values[Y] = 0.0;
	m_values[Z] = 0.0;
	m_values[H] = 0.0;
}

Vector::~Vector()
{

}

void Vector::ResetVector()
{
	m_values[X] = 0.0;
	m_values[Y] = 0.0;
	m_values[Z] = 0.0;
	m_values[H] = 0.0;
}


/****************************************************/
/*                                                  */
/*  Set Functions for the Vector class.             */
/*                                                  */
/****************************************************/

void Vector::SetVectorX(double x)
{
	this->m_values[X] = x;
}

void Vector::SetVectorY(double y)
{
	this->m_values[Y] = y;
}

void Vector::SetVectorZ(double z)
{
	this->m_values[Z] = z;
}

void Vector::SetVectorH(double h)
{
	this->m_values[H] = h;
}


void Vector::SetVector(double x, double y, double z)
{
	this->m_values[X] = x;
	this->m_values[Y] = y;
	this->m_values[Z] = z;
	this->m_values[H] = 0.0;
}

/****************************************************/
/*                                                  */
/*  Get Functions for the Vector class.             */
/*                                                  */
/****************************************************/

double Vector::GetVectorX()
{
	return this->m_values[X];
}

double Vector::GetVectorY()
{
	return this->m_values[Y];
}

double Vector::GetVectorZ()
{
	return this->m_values[Z];
}

double Vector::GetVectorX() const
{
	return this->m_values[X];
}

double Vector::GetVectorY() const
{
	return this->m_values[Y];
}

double Vector::GetVectorZ() const
{
	return this->m_values[Z];
}

double Vector::GetVectorH()
{
	return this->m_values[H];
}

double Vector::GetVectorH() const
{
	return this->m_values[H];
}

Vector Vector::GetVector()
{
	return *this;
}

Vector Vector::GetVector() const
{
	return *this;
}



/****************************************************/
/*                                                  */
/*  Utility Functions for the Vector class.         */
/*                                                  */
/****************************************************/

double Vector::Length()
{
	return sqrt(pow(this->m_values[X], 2.0) + 
		        pow(this->m_values[Y], 2.0) + 
				pow(this->m_values[Z], 2.0));
}


void Vector::NormalizeVector()
{
	double length = this->Length();

	this->m_values[X] = this->m_values[X] / length;
	this->m_values[Y] = this->m_values[Y] / length;
	this->m_values[Z] = this->m_values[Z] / length;
}


double Vector::DotProduct(const Vector& rhs)
{
	return (this->m_values[X] * rhs.m_values[X]) +
		   (this->m_values[Y] * rhs.m_values[Y]) + 
		   (this->m_values[Z] * rhs.m_values[Z]);
}


double Vector::DotProduct(const Vector& rhs) const
{
	return (this->m_values[X] * rhs.m_values[X]) +
		   (this->m_values[Y] * rhs.m_values[Y]) + 
		   (this->m_values[Z] * rhs.m_values[Z]);
}

void Vector::CrossProduct(const Vector& lhs, const Vector& rhs)
{
	this->m_values[X] = (lhs.m_values[Y] * rhs.m_values[Z]) - (lhs.m_values[Z] * rhs.m_values[Y]);
	this->m_values[Y] = (lhs.m_values[Z] * rhs.m_values[X]) - (lhs.m_values[X] * rhs.m_values[Z]);
	this->m_values[Z] = (lhs.m_values[X] * rhs.m_values[Y]) - (lhs.m_values[Y] * rhs.m_values[X]);
}

void Vector::Divide(const double& val)
{
	this->m_values[X] /= val;
	this->m_values[Y] /= val;
	this->m_values[Z] /= val;
}

/****************************************************/
/*                                                  */
/*  Overloaded Operators for the Vector class.      */
/*                                                  */
/****************************************************/

Vector& Vector::operator=(const Vector& rhs)
{
	this->m_values[X] = rhs.m_values[X];
	this->m_values[Y] = rhs.m_values[Y];
	this->m_values[Z] = rhs.m_values[Z];
	this->m_values[H] = rhs.m_values[H];

	return *this;
}

Vector Vector::operator+(const Vector& rhs)
{
	this->m_values[X] = this->m_values[X] + rhs.m_values[X];
	this->m_values[Y] = this->m_values[Y] + rhs.m_values[Y];
	this->m_values[Z] = this->m_values[Z] + rhs.m_values[Z];
	this->m_values[H] = 0.0;

	return *this;
}

Vector Vector::operator-(const Vector& rhs)
{
	this->m_values[X] = this->m_values[X] - rhs.m_values[X];
	this->m_values[Y] = this->m_values[Y] - rhs.m_values[Y];
	this->m_values[Z] = this->m_values[Z] - rhs.m_values[Z];
	this->m_values[H] = 0.0;

	return *this;
}



