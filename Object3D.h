
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
#include <list>
#include "defines.h"
#include "Camera.h"
#include "Vector.h"
#include "FacetNode.h"
#include "Material.h"



class Object3D
{

public:

	// Default constructor/destructor
	Object3D();
	~Object3D();

	// Set Private Member variable functions.
	void          SetObjectName(string name);
	void          SetObjectFacet(facet fct);
	void          SetObjectRotationXVal(double val);
	void          SetObjectRotationYVal(double val);
	void          SetObjectRotationZVal(double val);
	void          SetObjectScaleXVal(double val);
	void          SetObjectScaleYVal(double val);
	void          SetObjectScaleZVal(double val);
	void          SetObjectShearXVal(double val);
	void          SetObjectShearYVal(double val);
	void          SetObjectShearZVal(double val);
	void          SetObjectTransXVal(double val);
	void          SetObjectTransYVal(double val);
	void          SetObjectTransZVal(double val);	
	void          SetObjectLineThickness(int val);
	void          SetObjectMaterialIndex(int val);


	// Get Private Member variable functions.
	string        GetObjectName();
	int           GetObjectRotationValX();
	int           GetObjectRotationValY();
	int           GetObjectRotationValZ();
	int           GetObjectRotationValX() const;
	int           GetObjectRotationValY() const;
	int           GetObjectRotationValZ() const;
	double        GetObjectScaleXVal() const;
	double        GetObjectScaleYVal() const;
	double        GetObjectScaleZVal() const;
	double        GetObjectShearXVal() const;
	double        GetObjectShearYVal() const;
	double        GetObjectShearZVal() const;
	double        GetObjectTransXVal() const;
	double        GetObjectTransYVal() const;
	double        GetObjectTransZVal() const;
	int           GetObjectLineThickness();
	int           GetObjectLineThickness() const;
	int           GetObjectMaterialIndex();
	int           GetObjectMaterialIndex() const;

	// Get a corner value from the m_Facets list.
	int           GetFacetCorner1(int facet_index);
	int           GetFacetCorner2(int facet_index);
	int           GetFacetCorner3(int facet_index);

	// Data structure accessory functions
	void          SetPointVectorSize(int val);
	void          SetObjectPoint(const int& pos, point pt);
	void          SetFacetListSize(int val);
	void          GenerateFacetDistanceVector(const Camera& camera, const int& ProjectionType);
	void          GenerateVertexNormalVector();
	void          SortFacetDistanceVector();
	int           GetFacetDistancesVectorSize();
	void          GetVertexNormal(Vector& VertexNormal, const int& vertex);

	// Overloaded operators
	Object3D      operator=(const Object3D& rhs);




	// Object data structures.
	vector<FacetNode>  m_FacetDistances;	// list of distances and normals of each facet.
	string             m_Name;				// name of object.
	vector<point>      m_Points;			// point data.
	vector<facet>      m_Facets;			// connectivity data.
	vector<Vector>     m_VertexNormals;		// a normal for each vertex.

	int                m_LightIndex;
	int                m_MaterialIndex;

private:

	// variable declarations
	int                m_RotationDegreesX;
	int                m_RotationDegreesY;
	int                m_RotationDegreesZ;
	double             m_ScaleX;
	double             m_ScaleY;
	double             m_ScaleZ;
	double             m_ShearX;
	double             m_ShearY;
	double             m_ShearZ;
	double             m_TransX;
	double             m_TransY;
	double             m_TransZ;

	int                m_LineThickness;



};


#endif



