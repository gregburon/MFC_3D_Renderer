



/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "defines.h"


class Vector
{
public:
	Vector();
	~Vector();

	void		ResetVector();

	void        SetVectorX(double x);
	void        SetVectorY(double y);
	void        SetVectorZ(double z);
	void        SetVectorH(double h);

	void        SetVector(double x, double y, double z);
	void        NormalizeVector();

	double      GetVectorX();
	double      GetVectorY();
	double      GetVectorZ();
	double      GetVectorH();
	Vector      GetVector();

	double      GetVectorX() const;
	double      GetVectorY() const;
	double      GetVectorZ() const;
	double      GetVectorH() const;
	Vector      GetVector() const;

	double      Length();

	double      DotProduct(const Vector& rhs);
	double      DotProduct(const Vector& rhs) const;
	void        CrossProduct(const Vector& lhs, const Vector& rhs);
	void        Divide(const double& val);

	Vector&     operator=(const Vector& rhs);
	Vector      operator+(const Vector& rhs);
	Vector      operator-(const Vector& rhs);



private:
	double m_values[4];
};


#endif