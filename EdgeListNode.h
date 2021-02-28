






/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#ifndef EDGELISTNODE_H
#define EDGELISTNODE_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <list>
#include "defines.h"
#include "Vector.h"


class EdgeListNode
{
public:
	EdgeListNode();
	~EdgeListNode();

	bool           operator <(const EdgeListNode& rhs);
	EdgeListNode&  operator =(const EdgeListNode& rhs);

	int       m_x1;
	int       m_x2;
	int       m_y;

	// Variables for Gouraud shading.
	double    m_IRed_x1;
	double    m_IGreen_x1;
	double    m_IBlue_x1;
	double    m_IRed_x2;
	double    m_IGreen_x2;
	double    m_IBlue_x2;

	// Variables for Phong shading.
	Vector    m_Normal_x1;
	Vector    m_Normal_x2;


	double    m_Depth_x1;
	double    m_Depth_x2;
};




#endif

