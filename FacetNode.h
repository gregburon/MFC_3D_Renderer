

/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#ifndef FACETNODE_H
#define FACETNODE_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <list>
#include "defines.h"
#include "Vector.h"

class FacetNode
{
public:
	FacetNode();
	~FacetNode();

	bool         operator <(const FacetNode& rhs);
//	FacetNode&   operator =(const FacetNode& rhs);

	int       m_FacetNumber;
	double    m_Distance;
	Vector    m_Normal;
	point     m_CenterPoint;
};




#endif













