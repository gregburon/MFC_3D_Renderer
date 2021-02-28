


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
#include <list>
#include "defines.h"
#include "Object3D.h"
#include "Matrix.h"
#include <typeinfo.h>
#include <io.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "homework2.h"
#include "homework2Doc.h"
#include "FacetNode.h"
#include "algorithm"
#include "Material.h"

/****************************************************/
/*                                                  */
/*  Default constructors and destructors for the    */
/*  Object3D class.                                 */
/*                                                  */
/****************************************************/

Object3D::Object3D()
{
	m_RotationDegreesX     = 45.0;
	m_RotationDegreesY     = 0.0;
	m_RotationDegreesZ     = 0.0;
	m_ScaleX               = 50.0;
	m_ScaleY               = 50.0;
	m_ScaleZ               = 50.0;
	m_ShearX               = 0.0;
	m_ShearY               = 0.0;
	m_ShearZ               = 0.0;
	m_TransX               = 0.0;
	m_TransY               = 0.0;
	m_TransZ               = 0.0;

	m_LineThickness        = 1;
	m_LightIndex           = -1;

	m_MaterialIndex        = GOLD;

}

Object3D::~Object3D()
{

}




/****************************************************/
/*                                                  */
/*  Set Functions for the Object3D class.           */
/*                                                  */
/****************************************************/

void Object3D::SetObjectName(string name)
{
	this->m_Name = name;
}

void Object3D::SetObjectPoint(const int& pos, point pt)
{
	this->m_Points[pos]._x = pt._x;
	this->m_Points[pos]._y = pt._y;
	this->m_Points[pos]._z = pt._z;
	this->m_Points[pos]._h = pt._h;
}



void Object3D::SetObjectFacet(facet fct)
{
	this->m_Facets.push_back(fct);
}

void Object3D::SetObjectRotationXVal(double val)
{
	this->m_RotationDegreesX = val;
}

void Object3D::SetObjectRotationYVal(double val)
{
	this->m_RotationDegreesY = val;
}

void Object3D::SetObjectRotationZVal(double val)
{
	this->m_RotationDegreesZ = val;
}

void Object3D::SetObjectScaleXVal(double val)
{
	this->m_ScaleX = val;
}

void Object3D::SetObjectScaleYVal(double val)
{
	this->m_ScaleY = val;
}

void Object3D::SetObjectScaleZVal(double val)
{
	this->m_ScaleZ = val;
}

void Object3D::SetObjectShearXVal(double val)
{
	this->m_ShearX = val;
}

void Object3D::SetObjectShearYVal(double val)
{
	this->m_ShearY = val;
}

void Object3D::SetObjectShearZVal(double val)
{
	this->m_ShearZ = val;
}

void Object3D::SetObjectTransXVal(double val)
{
	this->m_TransX = val;
}

void Object3D::SetObjectTransYVal(double val)
{
	this->m_TransY = val;
}

void Object3D::SetObjectTransZVal(double val)
{
	this->m_TransZ = val;
}

void Object3D::SetPointVectorSize(int val)
{
	this->m_Points.resize(val);
}

void Object3D::SetFacetListSize(int val)
{
	this->m_Facets.resize(val);
}

void Object3D::SetObjectLineThickness(int val)
{
	this->m_LineThickness = val;
}

void Object3D::SetObjectMaterialIndex(int val)
{
	this->m_MaterialIndex = val;
}




/****************************************************/
/*                                                  */
/*  Get Functions for the Object3D class.           */
/*                                                  */
/****************************************************/

string Object3D::GetObjectName()
{
	return this->m_Name;
}

int Object3D::GetObjectRotationValX()
{
	return this->m_RotationDegreesX;
}

int Object3D::GetObjectRotationValY()
{
	return this->m_RotationDegreesY;
}

int Object3D::GetObjectRotationValZ()
{
	return this->m_RotationDegreesZ;
}

int Object3D::GetObjectRotationValX() const
{
	return this->m_RotationDegreesX;
}

int Object3D::GetObjectRotationValY() const
{
	return this->m_RotationDegreesY;
}

int Object3D::GetObjectRotationValZ() const
{
	return this->m_RotationDegreesZ;
}

double Object3D::GetObjectScaleXVal() const
{
	return this->m_ScaleX;
}

double Object3D::GetObjectScaleYVal() const
{
	return this->m_ScaleY;
}

double Object3D::GetObjectScaleZVal() const
{
	return this->m_ScaleZ;
}

double Object3D::GetObjectShearXVal() const
{
	return this->m_ShearX;
}

double Object3D::GetObjectShearYVal() const
{
	return this->m_ShearY;
}

double Object3D::GetObjectShearZVal() const
{
	return this->m_ShearZ;
}

double Object3D::GetObjectTransXVal() const
{
	return this->m_TransX;
}

double Object3D::GetObjectTransYVal() const
{
	return this->m_TransY;
}

double Object3D::GetObjectTransZVal() const
{
	return this->m_TransZ;
}

int Object3D::GetObjectLineThickness()
{
	return this->m_LineThickness;
}

int Object3D::GetObjectLineThickness() const
{
	return this->m_LineThickness;
}

int Object3D::GetFacetDistancesVectorSize()
{
	return this->m_FacetDistances.size();
}


int Object3D::GetObjectMaterialIndex()
{
	return this->m_MaterialIndex;
}

int Object3D::GetObjectMaterialIndex() const
{
	return this->m_MaterialIndex;
}

int Object3D::GetFacetCorner1(int facet_index)
{
	return this->m_Facets[facet_index]._corner1;
}

int Object3D::GetFacetCorner2(int facet_index)
{
	return this->m_Facets[facet_index]._corner2;
}

int Object3D::GetFacetCorner3(int facet_index)
{
	return this->m_Facets[facet_index]._corner3;
}



/****************************************************/
/*                                                  */
/*  Overloaded operators for the Object3D class.    */
/*                                                  */
/****************************************************/

Object3D Object3D::operator =(const Object3D& rhs)
// This function copies the object in the right hand side variable 
// into the object calling the function.  The object is first cleared
// and then the contents of the rhs object are copied over.
{
	// ensure deep copy.
	this->m_Name = rhs.m_Name;

	// Resize the vector and list.
	this->m_Points.resize(rhs.m_Points.size());
	this->m_Facets.resize(rhs.m_Facets.size());

	// copy the vector of points.
	this->m_Points = rhs.m_Points;

	// copy the list of facets
	this->m_Facets = rhs.m_Facets;

	// copy the list of facet distances
	this->m_FacetDistances = rhs.m_FacetDistances;


	this->m_RotationDegreesX   = rhs.m_RotationDegreesX;
	this->m_RotationDegreesY   = rhs.m_RotationDegreesY;
	this->m_RotationDegreesX   = rhs.m_RotationDegreesZ;

	this->m_ScaleX              = rhs.m_ScaleX;
	this->m_ScaleY              = rhs.m_ScaleY;
	this->m_ScaleZ              = rhs.m_ScaleZ;

	this->m_ShearX              = rhs.m_ShearX;
	this->m_ShearY              = rhs.m_ShearY;
	this->m_ShearZ              = rhs.m_ShearZ;

	this->m_TransX              = rhs.m_TransX;
	this->m_TransY              = rhs.m_TransY;
	this->m_TransZ              = rhs.m_TransZ;

	this->m_LineThickness       = rhs.m_LineThickness;
	this->m_MaterialIndex       = rhs.m_MaterialIndex;
	this->m_LightIndex          = rhs.m_LightIndex;

	return *this;
}


/****************************************************/
/*                                                  */
/*  Utility Functions for the Object3D class.       */
/*                                                  */
/****************************************************/

void Object3D::GenerateFacetDistanceVector(const Camera& camera, const int& ProjectionType)
// This function sets up the initial m_FacetDistance vector upon creation of
// an object in the object manager.  The m_FacetDistance data structure (vector)
// is generated by calculating the distance of each facet from the the current
// Center of Projection point.
{
	Matrix    WorldMatrix;
	Matrix    ModelingMatrix;
	Matrix    ShearMatrix;
	Matrix    ProjectionMatrix;

	Matrix    WM_Matrix;
	Matrix    WMS_Matrix;
	Matrix    WMSP_Matrix;


	// Get the vectors necessary to set up the matrices.
	Vector VUP = camera.GetCameraVUP_Vector();
	Vector VPN = camera.GetCameraVPN_Vector();
	Vector VRP = camera.GetCameraVRP_Vector();
	Vector COP = camera.GetCameraCOP_Vector();

	// Set up the matrices.
	WorldMatrix.SetWorldMatrix(this->m_RotationDegreesX, this->m_RotationDegreesY, 
		                       this->m_RotationDegreesZ, this->m_ScaleX, this->m_ScaleY, 
							   this->m_ScaleZ, this->m_ShearX, this->m_ShearY,
							   this->m_ShearZ, this->m_TransX, this->m_TransY, this->m_TransZ);

	ModelingMatrix.SetModelingMatrix(VRP, VUP, VPN);
	ShearMatrix.SetCOPShearMatrix(COP);
	ProjectionMatrix.SetProjectionMatrix(COP, ProjectionType);

	// Put the matrices together for a final modeling matrix.
	WM_Matrix.Multiply(ModelingMatrix, WorldMatrix);
	WMS_Matrix.Multiply(ShearMatrix, WM_Matrix);
	WMSP_Matrix.Multiply(ProjectionMatrix, WMS_Matrix);


	// Ensure the m_FacetDistances is empty.
	this->m_FacetDistances.clear();


	// Points in temp_object are now in u,v,n coordinate system.  We can 
	// now determine the distance from the point on the facet to the observer.
	for(int index = 0; index < this->m_Facets.size(); ++index)
	{
		// Create a new FacetNode;
		FacetNode NewFacetNode;

		// Points A, B, and C are in u,v,n and are the corners of the facet.
		point PointA = WMSP_Matrix.ApplyMatrixToPoint(this->m_Points[this->m_Facets[index]._corner1 -1]);
		point PointB = WMSP_Matrix.ApplyMatrixToPoint(this->m_Points[this->m_Facets[index]._corner2 -1]);
		point PointC = WMSP_Matrix.ApplyMatrixToPoint(this->m_Points[this->m_Facets[index]._corner3 -1]);

		// Calcuate the point that is the center of the facet.
		point  FacetCenterPoint;
		FacetCenterPoint._h = 1.0;

		FacetCenterPoint._x = PointC._x;
		FacetCenterPoint._y = PointC._y;
		FacetCenterPoint._z = PointC._z;

		double distance_x = camera.GetCameraCOP_U() - PointC._x;
		double distance_y = camera.GetCameraCOP_V() - PointC._y;
		double distance_z = camera.GetCameraCOP_N() - PointC._z;

		// Depths of facets are kept as their actual depths squared.
		double distance = pow(distance_x, 2.0) + pow(distance_y, 2.0) + pow(distance_z, 2.0);

		// Calculate the normal, the cross product of the first 
		// and second vectors of the facet. 
		Vector FacetNormal;

		Vector vBA, vCB;

		vBA.SetVector((PointB._x - PointA._x), 
			          (PointB._y - PointA._y), 
					  (PointB._z - PointA._z));

		vCB.SetVector((PointC._x - PointB._x), 
			          (PointC._y - PointB._y), 
					  (PointC._z - PointB._z));

		FacetNormal.CrossProduct(vCB, vBA);

		FacetNormal.NormalizeVector();

		// Set the NewFacetNode values.
		NewFacetNode.m_CenterPoint    = FacetCenterPoint;	// in u,v,n coords
		NewFacetNode.m_FacetNumber    = index + 1;	
		NewFacetNode.m_Distance       = distance;
		NewFacetNode.m_Normal         = FacetNormal;		// in u,v,n coords

		// Add the NewFacetNode to the list.
		this->m_FacetDistances.push_back(NewFacetNode);

	}// end for

	// When the m_FacetDistances list is finished, sort the list 
	// in order of decreasing distance to the observer.
	this->SortFacetDistanceVector();
}

void Object3D::GenerateVertexNormalVector()
// This function generates the m_VertexNormals data structure for the 
// Gouraud shading algorithm.
{
	this->m_VertexNormals.clear();

	this->m_VertexNormals.resize(this->m_Points.size() + 1);  // points start at 1

	for(int facet_number=1; facet_number<this->m_Facets.size(); ++facet_number)
	{
		for(int corner=0; corner<3; ++corner)
		{
			int vertex;
			
			if(corner == 0)
				vertex = this->m_Facets[facet_number]._corner1;
			else if(corner == 1)
				vertex = this->m_Facets[facet_number]._corner2;
			else if(corner == 2)
				vertex = this->m_Facets[facet_number]._corner3;

			int  facet_distances_index= 0;

			for(int i=0; i<this->m_FacetDistances.size(); ++i)
			{
				if(m_FacetDistances[i].m_FacetNumber == facet_number)
				{
					facet_distances_index = i;
					break;
				}// end if
			}// end for

			this->m_VertexNormals[vertex] = this->m_VertexNormals[vertex] + 
				                            this->m_FacetDistances[facet_distances_index].m_Normal;

		}// end for
	}// end if

	for(int j=0; j<this->m_VertexNormals.size(); ++j)
	{
		this->m_VertexNormals[j].NormalizeVector();
	}// end for
}



void Object3D::SortFacetDistanceVector()
// This function sorts the facet list for a given object based on the facet's
// distance to the observer.  Facets are sorted in order of greatest distance
// to the observer to the shortest distance to the observer.
{
	std::sort(this->m_FacetDistances.begin(), this->m_FacetDistances.end());	  
}




void Object3D::GetVertexNormal(Vector& VertexNormal, const int& vertex)
{
	VertexNormal = this->m_VertexNormals[vertex];
}




