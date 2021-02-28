

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
	m_FacetNumber     = 0;
	m_Distance        = 0.0;

}

FacetNode::~FacetNode()
{

}

