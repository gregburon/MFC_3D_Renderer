
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
#include <list>
#include "defines.h"
#include "FacetNode.h"


FacetNode::FacetNode()
{
	m_FacetNumber		 = 0;
	m_Distance			 = 0.0;

	m_CenterPoint._x	= 0.0;
	m_CenterPoint._y	= 0.0;
	m_CenterPoint._z	= 0.0;
	m_CenterPoint._h	= 1.0;

	m_Normal.ResetVector();

}

FacetNode::~FacetNode()
{

}


bool FacetNode::operator <(const FacetNode& rhs)
{
	if(this->m_Distance > rhs.m_Distance)
		return true;

	return false;
}

/*
FacetNode& FacetNode::operator =(const FacetNode& rhs)
{
	this->m_FacetNumber		 = rhs.m_FacetNumber;
	this->m_Distance		 = rhs.m_Distance;

	this->m_CenterPoint._x	 = rhs.m_CenterPoint._x;
	this->m_CenterPoint._y	 = rhs.m_CenterPoint._y;
	this->m_CenterPoint._z	 = rhs.m_CenterPoint._z;
	this->m_CenterPoint._h	 = rhs.m_CenterPoint._h;

	return *this;
}
*/