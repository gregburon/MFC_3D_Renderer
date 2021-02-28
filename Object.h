

/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #1                  */
/*    Created By: Greg Buron                     */
/*    October 7, 2001                            */
/*                                               */
/*                                               */
/*************************************************/

#ifndef OBJECT3D_H
#define OBJECT3D_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "defines.h"



class Object3D
{

public:

	// Default constructor/destructor
	Object3D();
	~Object3D();

	// Set Private Member variable functions.
	void          SetObjectName(string name);
	void          SetObjectPoint(const int& pos, point pt);
	void          SetObjectConnectivity(const int& pos, line ln);
	void          SetObjectRotationValue(int val);
	void          SetObjectScaleXVal(double val);
	void          SetObjectScaleYVal(double val);
	void          SetObjectShearXVal(double val);
	void          SetObjectShearYVal(double val);
	void          SetObjectTransXVal(double val);
	void          SetObjectTransYVal(double val);

	// Get Private Member variable functions.
	string        GetObjectName();
	int           GetObjectRotationValue();
	int           GetObjectRotationValue() const;
	double        GetObjectScaleXVal() const;
	double        GetObjectScaleYVal() const;
	double        GetObjectShearXVal() const;
	double        GetObjectShearYVal() const;
	double        GetObjectTransXVal() const;
	double        GetObjectTransYVal() const;
	double        GetObjectMaxXVal();
	double        GetObjectMinXVal();
	double        GetObjectMaxYVal();
	double        GetObjectMinYVal();

	// Data structure accessory functions
	void          SetPointVectorSize(int val);
	void          SetConnectivityVectorSize(int val);

	// Overloaded operators
	Object  operator=(const Object& rhs);


private:
	// variable declarations
	string         m_Name;
	vector<point>  m_Points;
	vector<facet>  m_Facets;

	int            m_RotationDegrees;
	double         m_ScaleX;
	double         m_ScaleY;
	double         m_ScaleZ;
	double         m_ShearX;
	double         m_ShearY;
	double         m_ShearZ;
	double         m_TransX;
	double         m_TransY;
	double         m_TransZ;

};


#endif