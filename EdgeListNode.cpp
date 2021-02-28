
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
#include "EdgeListNode.h"


EdgeListNode::EdgeListNode()
{
	m_x1				 = 0;
	m_x2				 = 0;
	m_y			    	 = 0;

	m_IRed_x1			 = 0;
	m_IGreen_x1			 = 0;
	m_IBlue_x1			 = 0;

	m_IRed_x2			 = 0;
	m_IGreen_x2			 = 0;
	m_IBlue_x2			 = 0;

	// Normals constructed by Vector class.

	m_Depth_x1           = 0.0;	// ?
	m_Depth_x2           = 0.0;
}

EdgeListNode::~EdgeListNode()
{

}


bool EdgeListNode::operator <(const EdgeListNode& rhs)
{
	if(this->m_y < rhs.m_y)
		return true;

	return false;
}

EdgeListNode& EdgeListNode::operator =(const EdgeListNode& rhs)
{
	this->m_x1          = rhs.m_x1;
	this->m_x2          = rhs.m_x2;
	this->m_y           = rhs.m_y;
	this->m_IRed_x1     = rhs.m_IRed_x1;
	this->m_IGreen_x1   = rhs.m_IGreen_x1;
	this->m_IBlue_x1    = rhs.m_IBlue_x1;
	this->m_IRed_x2     = rhs.m_IRed_x2;
	this->m_IGreen_x2   = rhs.m_IGreen_x2;
	this->m_IBlue_x2    = rhs.m_IBlue_x2;

	this->m_Normal_x1   = rhs.m_Normal_x1;
	this->m_Normal_x2   = rhs.m_Normal_x2;

	return *this;
}


