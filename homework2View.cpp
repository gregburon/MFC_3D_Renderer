
/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#include <typeinfo.h>

using namespace std;

#include "stdafx.h"
#include "homework2.h"
#include "homework2Doc.h"
#include "homework2View.h"
#include "Matrix.h"
#include "float.h"
#include "limits.h"
#include "defines.h"

#include "ObjectManager.h"
#include "ViewParameters.h"
#include "ProjectionMethod.h"
#include "TransformationParameters.h"
#include "LineThickness.h"
#include "Material.h"
#include "MaterialPropertyPage.h"
#include "MaterialSelectorDialog.h"
#include "ZBufferParameters.h"
#include "EdgeListNode.h"
#include <iomanip>
#include <algorithm>

#include <io.h>
#include <fstream>
#include <string.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CHomework2View, CView)

BEGIN_MESSAGE_MAP(CHomework2View, CView)
	//{{AFX_MSG_MAP(CHomework2View)
	ON_COMMAND(IDM_OBJECT_MANAGER, OnObjectManager)
	ON_COMMAND(IDM_TRANSFORMATION, OnTransformationParameters)
	ON_COMMAND(IDM_VIEWING, OnViewPalette)
	ON_COMMAND(ID_PARAMETERS_PROJECTIONMETHOD, OnProjectionMethod)
	ON_COMMAND(IDM_WIRE_FRAME, OnWireFrame)
	ON_COMMAND(IDM_WIRE_FRAME_DEPTH_CUE, OnWireFrameDepthCue)
	ON_COMMAND(IDM_WIRE_FRAME_BACKFACE_ELIMINATION, OnWireFrameBackfaceElimination)
	ON_COMMAND(IDM_PAINTERS_ALGORITHM, OnPaintersAlgorithm)
	ON_COMMAND(ID_OPTIONS_LINETHICKNESS, OnOptionsLinethickness)
	ON_COMMAND(ID_OPTIONS_BACKGROUNDCOLOR, OnOptionsBackgroundcolor)
	ON_COMMAND(ID_MATERIALSELECTOR, OnMaterialSelector)
	ON_COMMAND(IDM_PAINTERS_ALGORITHM_TRACED_FACETS, OnPaintersAlgorithmTracedFacets)
	ON_COMMAND(IDM_AMBIENT_LIGHT_PROPERTIES, OnAmbientLightProperties)
	ON_COMMAND(ID_POINT_LIGHT_1, OnPointLight1)
	ON_COMMAND(ID_POINT_LIGHT_2, OnPointLight2)
	ON_COMMAND(ID_POINT_LIGHT_3, OnPointLight3)
	ON_COMMAND(ID_POINT_LIGHT_4, OnPointLight4)
	ON_COMMAND(ID_POINT_LIGHT_5, OnPointLight5)
	ON_COMMAND(IDM_DRAW_AXIS, OnDrawAxis)
	ON_COMMAND(IDM_GOURAUD_SHADING, OnGouraudShading)
	ON_COMMAND(IDM_PHONG_SHADING, OnPhongShading)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_MOUSE_CAMERA_PAN, OnMouseCameraPan)
	ON_COMMAND(IDM_MATERIAL_EDITOR, OnMaterialEditor)
	ON_COMMAND(IDM_Z_BUFFER_PARAMETERS, OnZBufferParameters)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





/********************************************************/
/*                                                      */
/*   Three Dimensional Constructor/Destructor functions */
/*                                                      */
/********************************************************/

CHomework2View::CHomework2View()
{
	m_DisplayType               = WIREFRAME;
	m_DrawAxis                  = false;
	m_MouseCameraPanEnable      = false;

	m_Materials.clear();
	
	for(int i=0; i<NUM_MATERIALS; ++i)
	{
		Material NewMaterial(i);
		m_Materials.push_back(NewMaterial);
	}// end for

	m_MaterialPropertiesSheets.SetTitle("Material Editor");
	m_MaterialPropertiesSheets.SetActivePage(0);
	m_MaterialPropertiesSheets.EnableStackedTabs(false);

	for(int j=0; j<NUM_MATERIALS; ++j)
	{
		string tab_string = m_Materials[j].GetMaterialName();
		m_MaterialPropertyPages[j].m_psp.pszTitle = tab_string.c_str();
		m_MaterialPropertyPages[j].m_psp.dwFlags|=PSP_USETITLE;
		m_MaterialPropertyPages[j].m_Name    = m_Materials[j].GetMaterialName();
		m_MaterialPropertyPages[j].m_KaRed   = m_Materials[j].GetMaterialKaRed();
		m_MaterialPropertyPages[j].m_KaGreen = m_Materials[j].GetMaterialKaGreen();
		m_MaterialPropertyPages[j].m_KaBlue  = m_Materials[j].GetMaterialKaBlue();
		m_MaterialPropertyPages[j].m_KdRed   = m_Materials[j].GetMaterialKdRed();
		m_MaterialPropertyPages[j].m_KdGreen = m_Materials[j].GetMaterialKdGreen();
		m_MaterialPropertyPages[j].m_KdBlue  = m_Materials[j].GetMaterialKdBlue();
		m_MaterialPropertyPages[j].m_KsRed   = m_Materials[j].GetMaterialKsRed();
		m_MaterialPropertyPages[j].m_KsGreen = m_Materials[j].GetMaterialKsGreen();
		m_MaterialPropertyPages[j].m_KsBlue  = m_Materials[j].GetMaterialKsBlue();
		m_MaterialPropertyPages[j].m_SpecularExponent  = m_Materials[j].GetMaterialSpecularExponent();

		m_MaterialPropertiesSheets.AddPage(&m_MaterialPropertyPages[j]);
	}// end for

}


CHomework2View::~CHomework2View()
{

}


BOOL CHomework2View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


void CHomework2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_ZBufferParametersDialog.screen_rows = cy;
	m_ZBufferParametersDialog.screen_cols = cx;
}



/********************************************************/
/*                                                      */
/*   Three Dimensional Transformation Drawing functions */
/*                                                      */
/********************************************************/

void CHomework2View::OnDraw(CDC* pDC)
// The OnDraw() function is a wrapper for the drawing of the
// objects in the pDoc->m_Objects vector.
{
	CHomework2Doc* pDoc = GetDocument();

	int        i =0;
	CRect      rect;
	CDC        MemDC;
	CBitmap    MemBitmap;
	CBrush     BackgroundBrush = RGB(m_BackgroundColorDialog.m_BackgroundRedValue,
		                             m_BackgroundColorDialog.m_BackgroundGreenValue,
									 m_BackgroundColorDialog.m_BackgroundBlueValue);

	GetClientRect(rect);
	MemDC.CreateCompatibleDC(pDC);
	MemBitmap.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	CBitmap *pOldBitmap = MemDC.SelectObject(&MemBitmap);
	MemDC.FillRect(&rect, &BackgroundBrush);

	DrawObjects(&MemDC, rect);

	// Flip the back buffer to the screen.
	pDC->BitBlt(0, 0, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	
	DeleteObject(MemDC);
	DeleteObject(MemBitmap);
	DeleteObject(pOldBitmap);
	DeleteObject(BackgroundBrush);
}

void CHomework2View::DrawWorldCoordinateAxis(CDC* MemDC, const RECT& rect, 
											 const Matrix& CoordMatrix)
// The DrawWorldCoordinateAxis() function draws the coordinate axis on the
// rendering surface.
{
	CHomework2Doc* pDoc = GetDocument();

	COLORREF pen_color = RGB(255,255,0);
	CPen     pen;
	int      unit_u_pixels, unit_v_pixels;
	int      direction		=  POSITIVE;
	int      axis			=  X;

	pen.CreatePen(PS_SOLID, 1, pen_color);
	MemDC->SelectObject(&pen);
	MemDC->SetBkColor(RGB(m_BackgroundColorDialog.m_BackgroundRedValue,
		                  m_BackgroundColorDialog.m_BackgroundGreenValue,
						  m_BackgroundColorDialog.m_BackgroundBlueValue));

	MemDC->SetTextColor(pen_color);


	// Determine the units of the screen.
	GetUnitVectorPixels(rect, unit_u_pixels, unit_v_pixels);

	// Draw the positive X axis line.
	DrawAxisLine(MemDC, rect, axis, CoordMatrix, pen, 
		         direction, unit_u_pixels, unit_v_pixels);

	// Draw the positive Y axis line.
	axis		= Y;

	DrawAxisLine(MemDC, rect, axis, CoordMatrix, pen, 
		         direction, unit_u_pixels, unit_v_pixels);

	// Draw the positive Z axis line.
	axis		= Z;

	DrawAxisLine(MemDC, rect, axis, CoordMatrix, pen, 
		         direction, unit_u_pixels, unit_v_pixels);


	// Make the pen dotted for negative axes.
	pen.DeleteObject();
	pen.CreatePen(PS_DOT, 1, pen_color);
	MemDC->SelectObject(&pen);

	// Draw the negative X axis line.
	axis		= X;
	direction	= NEGATIVE;

	DrawAxisLine(MemDC, rect, axis, CoordMatrix, pen, 
		         direction, unit_u_pixels, unit_v_pixels);

	// Draw the negative Y axis line.
	axis		= Y;

	DrawAxisLine(MemDC, rect, axis, CoordMatrix, pen, 
		         direction, unit_u_pixels, unit_v_pixels);

	// Draw the negative Z axis line.
	axis		= Z;

	DrawAxisLine(MemDC, rect, axis, CoordMatrix, pen, 
		         direction, unit_u_pixels, unit_v_pixels);


	// Release the pen memory.
	pen.DeleteObject();
}


void CHomework2View::DrawAxisLine(CDC* MemDC, const RECT& rect, 
								  const int& axis, const Matrix& CoordMatrix, 
								  const CPen& pen, const int& direction, 
								  const int& unit_u_pixels, const int& unit_v_pixels)
// The DrawAxisLine() function determines which coordinate axis line to draw and outputs
// the appropriate line to the MemDC.
{
	point AxisBegin;
	point AxisEnd;
	point AxisBeginUVN;
	point AxisEndUVN;

	AxisBegin._x   = 0.0;
	AxisBegin._y   = 0.0;
	AxisBegin._z   = 0.0;
	AxisBegin._h   = 1.0;

	if(axis == X)
		AxisEnd._x = direction * AXIS_LENGTH;
	else
		AxisEnd._x = 0.0;

	if(axis == Y)
		AxisEnd._y = direction * AXIS_LENGTH;
	else
		AxisEnd._y = 0.0;

	if(axis == Z)
		AxisEnd._z = direction * AXIS_LENGTH;
	else
		AxisEnd._z = 0.0;

	AxisEnd._h     = 1.0;

	AxisBeginUVN = CoordMatrix.ApplyMatrixToPoint(AxisBegin);
	AxisEndUVN   = CoordMatrix.ApplyMatrixToPoint(AxisEnd);

	// Draw the axis line segment.
	MemDC->MoveTo((AxisBeginUVN._x * unit_u_pixels) + rect.right/2,
		          (AxisBeginUVN._y * unit_v_pixels * -1) + rect.bottom/2);
    MemDC->LineTo((AxisEndUVN._x * unit_u_pixels) + rect.right/2,
		          (AxisEndUVN._y * unit_v_pixels * -1) + rect.bottom/2);

	// Output the name of the axis on the positive axis line.
	if(direction == POSITIVE && axis == X)
		MemDC->TextOut((AxisEndUVN._x * unit_u_pixels) + rect.right/2, 
		               (AxisEndUVN._y * unit_v_pixels * -1) + rect.bottom/2, "x");

	else if(direction == POSITIVE && axis == Y)
		MemDC->TextOut((AxisEndUVN._x * unit_u_pixels) + rect.right/2, 
		               (AxisEndUVN._y * unit_v_pixels * -1) + rect.bottom/2, "y");

	else if(direction == POSITIVE && axis == Z)
		MemDC->TextOut((AxisEndUVN._x * unit_u_pixels) + rect.right/2, 
		               (AxisEndUVN._y * unit_v_pixels * -1) + rect.bottom/2, "z");

}



void CHomework2View::DrawObjects(CDC* MemDC, const RECT& rect)
// The DrawObjects() function draws all of the objects currently active within
// the document to the screen.  It is assumed that the objects all have a data
// structure m_FacetDistances which contain the facet numbers, their distance 
// to the observer, and their normals in sorted (descending) order.  This function
// determines of all the objects that are in the document m_Objects vector, which
// facets of those objects are farthest, and draws them first under the appropriate
// scheme.  
{
	CHomework2Doc* pDoc = GetDocument();

	bool    not_done      = true;
	int     unit_u_pixels = 0;
	int     unit_v_pixels = 0;
	
	point PointLightUVN[MAX_LIGHTS];

	vector<Matrix> WorldMatrix;
	Matrix  ModelingMatrix;
	Matrix  ShearMatrix;
	Matrix  ProjectionMatrix;

	Matrix  WM_Matrix;
	Matrix  WMS_Matrix;
	Matrix  WMSP_Matrix;

	int     objects_size  = pDoc->m_Objects.size();

	// Set the number of world matrices to the number of currently
	// active objects.
	WorldMatrix.resize(objects_size);

	// Generate the world matrices for each object.
	for(int a=0; a<objects_size; ++a)
	{
		WorldMatrix[a].SetWorldMatrix(pDoc->m_Objects[a].GetObjectRotationValX(),
			                          pDoc->m_Objects[a].GetObjectRotationValY(),
									  pDoc->m_Objects[a].GetObjectRotationValZ(),
									  pDoc->m_Objects[a].GetObjectScaleXVal(),
									  pDoc->m_Objects[a].GetObjectScaleYVal(),
									  pDoc->m_Objects[a].GetObjectScaleZVal(),
									  pDoc->m_Objects[a].GetObjectShearXVal(),
									  pDoc->m_Objects[a].GetObjectShearYVal(),
									  pDoc->m_Objects[a].GetObjectShearZVal(),
									  pDoc->m_Objects[a].GetObjectTransXVal(),
									  pDoc->m_Objects[a].GetObjectTransYVal(),
									  pDoc->m_Objects[a].GetObjectTransZVal());
	}

	if(m_DisplayType == GOURAUD_SHADING ||
	   m_DisplayType == PHONG_SHADING)
	{
		// If the objects are to be Gouraud or Phong shaded, 
		// generate the vertex normal vector for each object.
		for(int b=0; b<pDoc->m_Objects.size(); ++b)
		{
			pDoc->m_Objects[b].GenerateVertexNormalVector();
		}// end for

		// Reset the z buffer for Gouraud and Phong shading.
		ResetZBuffer();


	}// end if

	// Get the vectors necessary to set up the matrices.
	Vector VUP = pDoc->m_Camera.GetCameraVUP_Vector();
	Vector VPN = pDoc->m_Camera.GetCameraVPN_Vector();
	Vector VRP = pDoc->m_Camera.GetCameraVRP_Vector();
	Vector COP = pDoc->m_Camera.GetCameraCOP_Vector();

	// Determine the units of the screen.
	GetUnitVectorPixels(rect, unit_u_pixels, unit_v_pixels);


	// Set up the Modeling, Shear, and Projection matrix, which
	// will be the same for each object.
	ModelingMatrix.SetModelingMatrix(VRP, VUP, VPN);
	ShearMatrix.SetCOPShearMatrix(COP);
	ProjectionMatrix.SetProjectionMatrix(COP, pDoc->m_ProjectionMethod);


	if(objects_size < 1)
	{
		not_done = false;
	}// end if

	// Get the coordinates of the lights in the scene.
	SetPointLightUVNCoordinates(PointLightUVN, ModelingMatrix);

	// Set an array of indices into the m_FacetDistances data structure to 
	// determine which facet is to be drawn next.
	int FacetIndexArray[15] = {0};


	// Loop through all the facets from all the objects and draw them.
	while(not_done)
	{
		double FarthestDistance     = DBL_MIN;
		double NextFarthestDistance = DBL_MIN;
	    int    next_object          = 0;

		// Find the object with the farthest facet.
		for(int i=0; i<objects_size; ++i)
		{
			if(pDoc->m_Objects[i].m_FacetDistances[FacetIndexArray[i]].m_Distance > FarthestDistance)
			{
				FarthestDistance = pDoc->m_Objects[i].m_FacetDistances[FacetIndexArray[i]].m_Distance;
				next_object = i;
			}// end if

		}// end for

		int FacetIndex  = FacetIndexArray[next_object];
		int FacetNumber = pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_FacetNumber - 1;
		int corner1     = pDoc->m_Objects[next_object].m_Facets[FacetNumber]._corner1 - 1;	// index into the m_Points array
		int corner2     = pDoc->m_Objects[next_object].m_Facets[FacetNumber]._corner2 - 1;	// index into the m_Points array
		int corner3     = pDoc->m_Objects[next_object].m_Facets[FacetNumber]._corner3 - 1;	// index into the m_Points array

		// Put the matrices together for a final matrix.
		WM_Matrix.Multiply(ModelingMatrix, WorldMatrix[next_object]);
		WMS_Matrix.Multiply(ShearMatrix, WM_Matrix);
		WMSP_Matrix.Multiply(ProjectionMatrix, WMS_Matrix);

		// Put the corner points into the u,v,n coordinate system, and call them
		// points PointA, PointB, and PointC, respectively.
		point PointA = WMSP_Matrix.ApplyMatrixToPoint(pDoc->m_Objects[next_object].m_Points[corner1]);
		point PointB = WMSP_Matrix.ApplyMatrixToPoint(pDoc->m_Objects[next_object].m_Points[corner2]);
		point PointC = WMSP_Matrix.ApplyMatrixToPoint(pDoc->m_Objects[next_object].m_Points[corner3]);


		// Draw the facet depending on the
		// drawing mode selected by the user.
		switch(m_DisplayType)
		{
		case WIREFRAME:
			DrawWireFrameFacet(MemDC, PointA, PointB, PointC, 
							   next_object, rect, unit_u_pixels, unit_v_pixels,
							   pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Distance);
			break;

		case WIREFRAME_DEPTHCUE:
		case WIREFRAME_BACKFACE:
			// Use backface elimination with the wireframe 
			// depthcue and general backface elimination routines.
			if(pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal.GetVectorZ() <= 0.0)
			{
				DrawWireFrameFacet(MemDC, PointA, PointB, PointC, 
								   next_object, rect, unit_u_pixels, unit_v_pixels,
								   pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Distance);
			}// end if
			break;

		case PAINTERS:
		case PAINTERS_TRACED:
			// Use backface elimination with the painters algorithm.
			if(pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal.GetVectorZ() <= 0.0)
			{
				DrawSolidFacet(MemDC, PointA, PointB, PointC, next_object,
							   rect, unit_u_pixels, unit_v_pixels, ModelingMatrix, PointLightUVN, 
							   pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal,
							   pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_CenterPoint);
			}// end if
			break;

		case GOURAUD_SHADING:
			// Use backface elimination with the Gouraud shading algorithm.
			if(pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal.GetVectorZ() <= 0.0)
			{
				DrawGouraudFacet(MemDC, PointA, PointB, PointC, next_object,
							     rect, unit_u_pixels, unit_v_pixels, ModelingMatrix, PointLightUVN, 
							     pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal,
							     pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_CenterPoint,
								 corner1, corner2, corner3);
			}// end if
			break;

		case PHONG_SHADING:
			// Use backface elimination with the Phong shading algorithm.
			if(pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal.GetVectorZ() <= 0.0)
			{
				DrawPhongFacet(MemDC, PointA, PointB, PointC, next_object,
							   rect, unit_u_pixels, unit_v_pixels, ModelingMatrix, PointLightUVN,
							   pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_Normal,
							   pDoc->m_Objects[next_object].m_FacetDistances[FacetIndex].m_CenterPoint,
							   corner1, corner2, corner3);
			}// end if
			break;

		}// end switch

		// Increment the index counter for the object that was just drawn.
		FacetIndexArray[next_object]++;

		// Determine if the drawing cycle is finished.
		int num_objects_done = 0;

		for(int j=0; j<objects_size; ++j)
		{
			if(FacetIndexArray[j] >= pDoc->m_Objects[j].m_FacetDistances.size())
			{
				++num_objects_done;
			}// end if
		}// end for

		if(num_objects_done >= objects_size)
		{
			not_done = false;

		}// end if
	}// end while

	// Draw the coordinate axis if the 
	// m_DrawAxis toggle is set.
	if(m_DrawAxis == true)
	{
		Matrix MSMatrix;
		Matrix MSPMatrix;

		MSMatrix.Multiply(ShearMatrix, ModelingMatrix);
		MSPMatrix.Multiply(ProjectionMatrix, MSMatrix);

		DrawWorldCoordinateAxis(MemDC, rect, MSPMatrix);
	}// end if

}


void CHomework2View::SetPointLightUVNCoordinates(point PointLightUVN[], 
												 const Matrix& ModelingMatrix)
// Convert the point lights into u, v, n coordinates to determine the 
// diffuse and specular contributions of the lights.
{
	for(int i=0; i<MAX_LIGHTS; ++i)
	{
		if(m_PointLightParameters[i].m_Active == true)
		{
			CString EditBoxXString;
			CString EditBoxYString;
			CString EditBoxZString;

			GetLightPosition(i, EditBoxXString, EditBoxYString, EditBoxZString);

			point LightPointXYZ;

			LightPointXYZ._x = atof(EditBoxXString);
			LightPointXYZ._y = atof(EditBoxYString);
			LightPointXYZ._z = atof(EditBoxZString);
			LightPointXYZ._h = 1.0;

			PointLightUVN[i] = ModelingMatrix.ApplyMatrixToPoint(LightPointXYZ);
		}// end if
	}// end for
}


void CHomework2View::DrawWireFrameFacet(CDC* MemDC, const point& PointA, 
		                                const point& PointB, const point& PointC, 
							            const int& object_index, const RECT& rect,
										const int& unit_u, const int& unit_v,
										const double& distance)
// The DrawWireFrameFacet() function draws the polygon defined by the 
// points PointA, PointB, and PointC into a wireframe polygon.  The facet
// is from the object indicated from the index object_index, which is an
// index into the pDoc->m_Objects vector of objects.
{
	CHomework2Doc* pDoc = GetDocument();
	
	CPen pen;
	SetWireframePen(pen, object_index, distance);
	MemDC->SelectObject(&pen);

	// Calculate start and end points for first line segment.
	double start_u = (PointA._x * unit_u) + rect.right/2;
	double start_v = (PointA._y * unit_v * -1) + rect.bottom/2;
	double end_u   = (PointB._x * unit_u) + rect.right/2;
	double end_v   = (PointB._y * unit_v * -1) + rect.bottom/2;

	// Draw the first line segment.
	MemDC->MoveTo(start_u, start_v);
    MemDC->LineTo(end_u, end_v);

	// Calculate start and end points for second line segment.
	start_u = (PointB._x * unit_u) + rect.right/2;
	start_v = (PointB._y * unit_v * -1) + rect.bottom/2;
	end_u   = (PointC._x * unit_u) + rect.right/2;
	end_v   = (PointC._y * unit_v * -1) + rect.bottom/2;

	// Draw the second line segment.
	MemDC->MoveTo(start_u, start_v);
    MemDC->LineTo(end_u, end_v);

	// Calculate start and end points for third line segment.
	start_u = (PointC._x * unit_u) + rect.right/2;
	start_v = (PointC._y * unit_v * -1) + rect.bottom/2;
	end_u   = (PointA._x * unit_u) + rect.right/2;
	end_v   = (PointA._y * unit_v * -1) + rect.bottom/2;

	// Draw the third line segment.
	MemDC->MoveTo(start_u, start_v);
    MemDC->LineTo(end_u, end_v);

	pen.DeleteObject();
}


void CHomework2View::DrawSolidFacet(CDC* MemDC, const point& PointA, const point& PointB,const point& PointC, 
									const int& object_index, const RECT& rect,const int& unit_u, const int& unit_v, 
									const Matrix& ModelingMatrix,const point PointLightUVN[], const Vector& FacetNormal, 
									const point& CenterPoint)
// This function draws a facet on the object as a solid facet.  The color of the 
// facet can be calculated by the material of the object and the light equations
// which are set up from the parameters provided by the LightParamters dialog box.
{
	CHomework2Doc* pDoc = GetDocument();
	
	CPen      pen;
	CBrush    brush;
    CPoint    Triangle[3] = {0};

	GenerateSolidFacetColor(pen, brush, object_index, PointLightUVN, 
		                    FacetNormal, CenterPoint);

	MemDC->SelectObject(&pen);
	MemDC->SelectObject(&brush);

	Triangle[0].x = (PointA._x * unit_u) + rect.right/2;
	Triangle[0].y = (PointA._y * unit_v * -1) + rect.bottom/2;
	Triangle[1].x = (PointB._x * unit_u) + rect.right/2;
	Triangle[1].y = (PointB._y * unit_v * -1) + rect.bottom/2;
	Triangle[2].x = (PointC._x * unit_u) + rect.right/2;
	Triangle[2].y = (PointC._y * unit_v * -1) + rect.bottom/2;

	MemDC->Polygon(Triangle, 3);

	pen.DeleteObject();
	brush.DeleteObject();
}


void CHomework2View::DrawGouraudFacet(CDC* MemDC, const point& PointA, const point& PointB, 
		                 const point& PointC, const int& object_index, const RECT& rect,
						 const int& unit_u, const int& unit_v, const Matrix& ModelingMatrix,
						 const point PointLightUVN[], const Vector& FacetNormal, const point& CenterPoint,
						 const int& corner_a, const int& corner_b, const int& corner_c)
// This function will draw the given facet with the Gouraud shading algorithm.
// The pixels color will be bi-linearly interpolated from each of the four 
// corners of the facet. The averaged normal of all the connecting facets will 
// be used in determining the color of the pixels at the corners, and pixels in
// between will be interpolated from those corners.
{
	CHomework2Doc* pDoc = GetDocument();

	const bool DEBUG = false;

	double IRed_A = 0.0, IGreen_A = 0.0, IBlue_A = 0.0;
	double IRed_B = 0.0, IGreen_B = 0.0, IBlue_B = 0.0;
	double IRed_C = 0.0, IGreen_C = 0.0, IBlue_C = 0.0;
	
	// Reset the edge list for the new facet.
	ResetFacetEdgeList();

	// Get the intensities of the vertex points.     
	CalculatePointIntensity(PointA, object_index, PointLightUVN, 
		                    pDoc->m_Objects[object_index].m_VertexNormals[corner_a+1], 
							IRed_A, IGreen_A, IBlue_A);
                                                     
	CalculatePointIntensity(PointB, object_index, PointLightUVN, 
		                    pDoc->m_Objects[object_index].m_VertexNormals[corner_b+1], 
							IRed_B, IGreen_B, IBlue_B);
                                                        
	CalculatePointIntensity(PointC, object_index, PointLightUVN, 
		                    pDoc->m_Objects[object_index].m_VertexNormals[corner_c+1], 
							IRed_C, IGreen_C, IBlue_C);

	// Create the edge list for this facet.
	GenerateEdgeList(PointA, PointB, PointC, unit_u, unit_v, rect,
		             IRed_A, IGreen_A, IBlue_A, IRed_B, 
					 IGreen_B, IBlue_B, IRed_C, IGreen_C, IBlue_C, 
					 pDoc->m_Objects[object_index].m_VertexNormals[corner_a+1],
					 pDoc->m_Objects[object_index].m_VertexNormals[corner_b+1],
					 pDoc->m_Objects[object_index].m_VertexNormals[corner_c+1],
					 GOURAUD_SHADING); 

	// Draw the facet with a second round of linear interpolation, this 
	// time interpolating from left to right along the scan line.
	int size = pDoc->m_EdgeListVector.size();
	for(int i=0; i<size; ++i)
	{
		int length     = pDoc->m_EdgeListVector[i].m_x2 - pDoc->m_EdgeListVector[i].m_x1 + 1;
		int current_x  = pDoc->m_EdgeListVector[i].m_x1;
		int current_y  = pDoc->m_EdgeListVector[i].m_y;
		int end_x      = pDoc->m_EdgeListVector[i].m_x2;

		double delta_red   = (double)(pDoc->m_EdgeListVector[i].m_IRed_x2 - 
			                          pDoc->m_EdgeListVector[i].m_IRed_x1);
		double delta_green = (double)(pDoc->m_EdgeListVector[i].m_IGreen_x2 - 
			                          pDoc->m_EdgeListVector[i].m_IGreen_x1);
		double delta_blue  = (double)(pDoc->m_EdgeListVector[i].m_IBlue_x2 - 
			                          pDoc->m_EdgeListVector[i].m_IBlue_x1);

		double current_depth = pDoc->m_EdgeListVector[i].m_Depth_x1;

		double delta_depth   = pDoc->m_EdgeListVector[i].m_Depth_x2 - 
			                   pDoc->m_EdgeListVector[i].m_Depth_x1;

		int counter = 0;

		// Iterate across the scan line and draw the pixels.
		for(current_x; current_x < end_x; ++current_x)
		{
			if(false == TestZBuffer(current_x, current_y, current_depth))
			{
				// The pixel tested false for the depth test, which means
				// a pixel has already been drawn that is closer. Do not 
				// display this pixel.
				continue;
			}// end if

			double next_red    = (pDoc->m_EdgeListVector[i].m_IRed_x1 + 
								 (counter)*(delta_red)/(double)length);

			double next_green  = (pDoc->m_EdgeListVector[i].m_IGreen_x1 + 
								 (counter)*(delta_green)/(double)length);

			double next_blue   = (pDoc->m_EdgeListVector[i].m_IBlue_x1 + 
								 (counter)*(delta_blue)/(double)length);


			NormalizeFinalColorValues(next_red, next_green, next_blue);

			int red   = (int)(next_red*255.0);
			int green = (int)(next_green*255.0);
			int blue  = (int)(next_blue*255.0);

			MemDC->SetPixel(current_x, current_y, RGB(red, green, blue));

			m_ZBuffer[current_y][current_x] = current_depth;

			current_depth = current_depth + (delta_depth/(double)(length));

			++counter;
		}// end for
	}// end for
}



void CHomework2View::DrawPhongFacet(CDC* MemDC, const point& PointA, const point& PointB,
		               const point& PointC, const int& object_index, const RECT& rect,
					   const int& unit_u, const int& unit_v, const Matrix& ModelingMatrix,
					   const point PointLightUVN[], const Vector& FacetNormal, const point& CenterPoint,
					   const int& corner_a, const int& corner_b, const int& corner_c)
// The DrawPhongFacet() function renders the given facet with the Phong shading model.
// This shading method is similar to the Gouraud shading method, but interpolates the color
// for each pixel according to that pixel's normal. The edge list is created with the 
// vertex normals, then the normals are bi-linearly interpolated to create the colors 
// for each pixel by applying light equations for every pixel.
{
	CHomework2Doc* pDoc = GetDocument();
	
	// Reset the edge list for the new facet.
	ResetFacetEdgeList();


	// Get the vertex normals for each corner of the facet.
	Vector VertexNormalA = pDoc->m_Objects[object_index].m_VertexNormals[corner_a+1];
	Vector VertexNormalB = pDoc->m_Objects[object_index].m_VertexNormals[corner_b+1];
	Vector VertexNormalC = pDoc->m_Objects[object_index].m_VertexNormals[corner_c+1];

	// Create the edge list for this facet, without calculating 
	// any intensities at the vertecies.  The vertex normals will
	// be interpolated to determine the pixel colors.
	GenerateEdgeList(PointA, PointB, PointC, unit_u, unit_v, rect,
		             0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
					 VertexNormalA, VertexNormalB, VertexNormalC,
					 PHONG_SHADING); 

	// The edge list has been generated and the ends of each scan line
	// have a corresponding normal for that pixel. Go through the edge
	// list from top to bottom and interpolate the normals on that scan
	// line to generate the intensity of color for that pixel and display
	// it to the screen.
	int size = pDoc->m_EdgeListVector.size();

	for(int i=0; i<size; ++i)
	{
		int length     = pDoc->m_EdgeListVector[i].m_x2 - pDoc->m_EdgeListVector[i].m_x1 + 1;

		int current_x  = pDoc->m_EdgeListVector[i].m_x1;
		int current_y  = pDoc->m_EdgeListVector[i].m_y;
		int end_x      = pDoc->m_EdgeListVector[i].m_x2;

		double delta_normal_x  = (double)(pDoc->m_EdgeListVector[i].m_Normal_x2.GetVectorX() -
			                              pDoc->m_EdgeListVector[i].m_Normal_x1.GetVectorX())/(double)(length);

		double delta_normal_y  = (double)(pDoc->m_EdgeListVector[i].m_Normal_x2.GetVectorY() -
			                              pDoc->m_EdgeListVector[i].m_Normal_x1.GetVectorY())/(double)(length);

		double delta_normal_z  = (double)(pDoc->m_EdgeListVector[i].m_Normal_x2.GetVectorZ() -
			                              pDoc->m_EdgeListVector[i].m_Normal_x1.GetVectorZ())/(double)(length);

		Vector CurrentNormal   = pDoc->m_EdgeListVector[i].m_Normal_x1;

		double current_depth   = pDoc->m_EdgeListVector[i].m_Depth_x1;

		double delta_depth     = pDoc->m_EdgeListVector[i].m_Depth_x2 - 
			                     pDoc->m_EdgeListVector[i].m_Depth_x1;

		// Use the light vector and observer vector to the center of this facet 
		// for light calculations. Iterate through the points on the scan line, 
		// calculate the contribution of each light to the color of that point, 
		// and ouput the pixel.
		for(current_x; current_x < end_x; ++current_x)
		{
			if(false == TestZBuffer(current_x, current_y, current_depth))
			{
				// The pixel tested false for the depth test, which means
				// a pixel has already been drawn that is closer. Do not 
				// display this pixel.
				continue;
			}// end if

			Vector LightVector;
			Vector ObserverVector;
			Vector HVector;

			double distance = 0.0;

			// Variables for color contributions from each type of light.
			double AmbientRed  = 0.0, AmbientGreen  = 0.0, AmbientBlue  = 0.0;
			double DiffuseRed  = 0.0, DiffuseGreen  = 0.0, DiffuseBlue  = 0.0;
			double SpecularRed = 0.0, SpecularGreen = 0.0, SpecularBlue = 0.0;

			// Variables for the final intensity for each color.
			double IRed = 0.0, IGreen = 0.0, IBlue = 0.0;

			// Generate the ambient contribution to this facet.
			GenerateAmbientColorValues(AmbientRed, AmbientGreen, AmbientBlue, object_index);

			// Generate the diffuse and specular light values 
			// for this brush for each RGB color.
			for(int j=0; j<MAX_LIGHTS; ++j)
			{
				if(m_PointLightParameters[j].m_Active == true)
				{
					SetLightAndObserverVectors(LightVector, ObserverVector, HVector, 
											   PointLightUVN, CenterPoint, j, distance);

					if(CurrentNormal.DotProduct(LightVector) > 0.0)
					{
						// Generate the diffuse color contribution to the facet.
						GenerateDiffuseColorValues(DiffuseRed, DiffuseGreen, DiffuseBlue, object_index,
												   j, CurrentNormal, LightVector, distance);

						// Generate the specular color contribution to the facet.
						GenerateSpecularColorValues(SpecularRed, SpecularGreen, SpecularBlue, object_index,
													j, CurrentNormal, LightVector, HVector, distance);
					}// end if		
				}// end if
			}// end for

			// Combine the light types for the final color of the pixel.
			IRed    = AmbientRed   + DiffuseRed   + SpecularRed;
			IGreen  = AmbientGreen + DiffuseGreen + SpecularGreen;
			IBlue   = AmbientBlue  + DiffuseBlue  + SpecularBlue;
	
			NormalizeFinalColorValues(IRed, IGreen, IBlue);
			
			// Output the pixel to the screen.
			MemDC->SetPixel(current_x, current_y, RGB(IRed*255.0, IGreen*255.0, IBlue*255.0));

			// Increment the current facet.
			CurrentNormal.SetVectorX(CurrentNormal.GetVectorX() + delta_normal_x);
			CurrentNormal.SetVectorY(CurrentNormal.GetVectorY() + delta_normal_y);
			CurrentNormal.SetVectorZ(CurrentNormal.GetVectorZ() + delta_normal_z);

			CurrentNormal.NormalizeVector();

			m_ZBuffer[current_y][current_x] = current_depth;

			current_depth = current_depth + (delta_depth/(double)(length));

		}// end for

	}// end for
}

bool CHomework2View::TestZBuffer(const int& x, const int& y, const double& test_depth)
// The TestZBuffer() function tests the test_depth value passed into the function against the
// z-buffer to determine of the point at x, y should be drawn to the screen. The function 
// returns true if the test_depth is less than the z-buffer value at x,y and returns false if
// the pixels should not be drawn.
{
	CHomework2Doc* pDoc = GetDocument();

	int sign = 0;
	
	if(m_ZBufferParametersDialog.z_near < 0.0)
	{
		sign = -1;
	}// end if
	else if(m_ZBufferParametersDialog.z_near >= 0.0)
	{
		sign = 1;
	}// end if

	// Check the distance of this point against the 
	// z-buffer.  If this pixel is closer to the COP
	// than the value in the z-buffer at that location 
	// currently, then the pixel should be drawn.
	if(x < 0 || x >= m_ZBufferParametersDialog.screen_cols ||
	   y < 0 || y >= m_ZBufferParametersDialog.screen_rows)
	{
		// If pixel falls outside the window the z-buffer 
		// does not have an index for that pixel. safely
		// continue the loop.
		return false;
	}// end if

	else if(test_depth <= m_ZBuffer[y][x] && 
		    test_depth >= sign * pow(m_ZBufferParametersDialog.z_near, 2.0))
	{
		// The pixel is closer that the last value at this index in 
		// the z-buffer, and farther away than the minium distance.
		// This pixel should be drawn.
		return true;
	}// end else if
	
	return false;
}




void CHomework2View::GenerateSolidFacetColor(CPen &pen, CBrush &brush, const int& object_index,
										     const point PointLightUVN[], const Vector& FacetNormal, 
										     const point& CenterPoint)
// The GenerateFacetColor() function determines what color the solid facet should be
// depending on the object's material and the application of the light equations.  
// The color will therefore depend on the material reflectivity and diffuse color
// constants, as well as the distance from that facet from any one of the 5 available
// light sources in the scene.  The funtion will then return the pen and the brush
// with the approprate colors for that facet.
{
	CHomework2Doc* pDoc = GetDocument();

	// Ensure pen and brush are available for use.
	pen.DeleteObject();
	brush.DeleteObject();

	Vector LightVector;
	Vector ObserverVector;
	Vector HVector;

	double distance = 0.0;

	// Variables for color contributions from each type of light.
	double AmbientRed  = 0.0, AmbientGreen  = 0.0, AmbientBlue  = 0.0;
	double DiffuseRed  = 0.0, DiffuseGreen  = 0.0, DiffuseBlue  = 0.0;
	double SpecularRed = 0.0, SpecularGreen = 0.0, SpecularBlue = 0.0;

	// Variables for the final intensity for each color.
	double IRed = 0.0, IGreen = 0.0, IBlue = 0.0;

	// Generate the ambient contribution to this facet.
	GenerateAmbientColorValues(AmbientRed, AmbientGreen, AmbientBlue, object_index);

	// Generate the diffuse and specular light values 
	// for this brush for each RGB color.
	for(int j=0; j<MAX_LIGHTS; ++j)
	{
		if(m_PointLightParameters[j].m_Active == true)
		{
			SetLightAndObserverVectors(LightVector, ObserverVector, HVector, 
				                       PointLightUVN, CenterPoint, j, distance);

			if(FacetNormal.DotProduct(LightVector) > 0.0)
			{
				// Generate the diffuse color contribution to the facet.
				GenerateDiffuseColorValues(DiffuseRed, DiffuseGreen, DiffuseBlue, object_index,
					                       j, FacetNormal, LightVector, distance);

				// Generate the specular color contribution to the facet.
				GenerateSpecularColorValues(SpecularRed, SpecularGreen, SpecularBlue, object_index,
					                        j, FacetNormal, LightVector, HVector, distance);
			}// end if		
		}// end if
	}// end for

	// Combine the light types for the final color of the facet.
	IRed    = AmbientRed   + DiffuseRed   + SpecularRed;
	IGreen  = AmbientGreen + DiffuseGreen + SpecularGreen;
	IBlue   = AmbientBlue  + DiffuseBlue  + SpecularBlue;

	// Normalize the final intensities.
	NormalizeFinalColorValues(IRed, IGreen, IBlue);

	// Create the brush with the final color.
	brush.CreateSolidBrush(RGB((int)(IRed*255.0), (int)(IGreen*255.0), (int)(IBlue*255.0)));

	// Determine the pen type to use.
	if(m_DisplayType == PAINTERS_TRACED)
	{
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	}// end if
	else
	{
		pen.CreatePen(PS_SOLID, 1, RGB((int)(IRed*255.0), (int)(IGreen*255.0), (int)(IBlue*255.0)));
	}// end else
}





void CHomework2View::GenerateAmbientColorValues(double& AmbientRed,
					 double& AmbientGreen, double& AmbientBlue, const int& object_index)
// This function generates ambient color values for the scene. The values of 
// ambient red, ambient green, and ambient blue are returned to the calling 
// function by reference.
{
	CHomework2Doc* pDoc = GetDocument();

	// Calculate the Ambient contribution to this object.
	AmbientRed   = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKaRed() * 
		           m_AmbientLightPropertiesDialog.m_AmbientRed / 255.0;

	AmbientGreen = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKaGreen() * 
		           m_AmbientLightPropertiesDialog.m_AmbientGreen / 255.0;

	AmbientBlue  = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKaBlue() * 
		           m_AmbientLightPropertiesDialog.m_AmbientBlue / 255.0;
}




void CHomework2View::GenerateDiffuseColorValues(double& DiffuseRed, double& DiffuseGreen, 
					 double& DiffuseBlue, const int& object_index, const int& light_index, 
					 const Vector& FacetNormal, const Vector& LightVector, const double& distance)
// This function generates diffuse color values for the scene. The values of 
// diffuse red, diffuse green, and diffuse blue are returned to the calling 
// function by reference.
{
	CHomework2Doc* pDoc = GetDocument();

	// Add the diffuse contribution to the facet.
	DiffuseRed   += (m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKdRed() *
					 m_PointLightParameters[light_index].m_PointLightRed/255.0 *
					 FacetNormal.DotProduct(LightVector))/(distance*d0);

	DiffuseGreen += (m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKdGreen() * 
					 m_PointLightParameters[light_index].m_PointLightGreen/255.0 *
					 FacetNormal.DotProduct(LightVector))/(distance*d0);

	DiffuseBlue  += (m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKdBlue() * 
					 m_PointLightParameters[light_index].m_PointLightBlue/255.0 *
					 FacetNormal.DotProduct(LightVector))/(distance*d0);
}




void CHomework2View::GenerateSpecularColorValues(double& SpecularRed, double& SpecularGreen, 
				     double& SpecularBlue, const int& object_index, const int& light_index, 
					 const Vector& FacetNormal, const Vector& LightVector, const Vector& HVector, 
					 const double& distance)
// This function calculates the specular color values for the given facet on the 
// object at object_index. The values of SpecularRed, SpecularGreen, and SpecularBlue 
// are set to their respective values and returned to the calling procedure by reference.
{
	CHomework2Doc* pDoc = GetDocument();

	// Add the specular contribution to the facet.
	double ksRed   = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKsRed();
	double ksGreen = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKsGreen();
	double ksBlue  = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialKsBlue();

	double IsRed   = m_PointLightParameters[light_index].m_PointLightRed/255.0;
	double IsGreen = m_PointLightParameters[light_index].m_PointLightGreen/255.0;
	double IsBlue  = m_PointLightParameters[light_index].m_PointLightBlue/255.0;

	double N_Dot_H = FacetNormal.DotProduct(HVector);

	if(N_Dot_H < 0.0)
	{
		// Do not add color if the color is "negative".
		return;
	}

	double SpecularExponent = m_Materials[pDoc->m_Objects[object_index].m_MaterialIndex].GetMaterialSpecularExponent();

	// Increment the Specular values.
	double delta_specular_red   =  (ksRed   * IsRed   * pow(N_Dot_H, SpecularExponent))/(distance*d0);
	double delta_specular_green =  (ksGreen * IsGreen * pow(N_Dot_H, SpecularExponent))/(distance*d0);
	double delta_specular_blue  =  (ksBlue  * IsBlue  * pow(N_Dot_H, SpecularExponent))/(distance*d0);

	SpecularRed   +=  delta_specular_red;
	SpecularGreen +=  delta_specular_green;
	SpecularBlue  +=  delta_specular_blue;
}





void CHomework2View::SetLightAndObserverVectors(Vector& LightVector, Vector& ObserverVector, Vector& HVector, 
												const point PointLightUVN[], const point& FacetPoint, 
												const int& light_index, double& distance)
// The SetLightAndObserverVectors() function sets up the light vector and the observer vector 
// and an h vector (average between observer and light for the specular light contribution for
// a given point on a facet (FacetPoint: this is the center point for flat shading, vertex points 
// for gouraud shading, and every point for phong shading).  The vectors are normalized and returned
// to the calling function by reference.
{
	CHomework2Doc* pDoc = GetDocument();

	// Get the distance from the light to the center of the facet.
	double distance_x = PointLightUVN[light_index]._x - FacetPoint._x;
	double distance_y = PointLightUVN[light_index]._y - FacetPoint._y;
	double distance_z = PointLightUVN[light_index]._z - FacetPoint._z;

	distance = sqrt(pow(distance_x, 2.0) + 
					pow(distance_y, 2.0) + 
					pow(distance_z, 2.0));

	LightVector.SetVector(PointLightUVN[light_index]._x - FacetPoint._x,
						  PointLightUVN[light_index]._y - FacetPoint._y,
						  PointLightUVN[light_index]._z - FacetPoint._z);

	ObserverVector.SetVector(pDoc->m_Camera.GetCameraCOP_U() - FacetPoint._x,  // use COP not VRP!
							 pDoc->m_Camera.GetCameraCOP_V() - FacetPoint._y, 
							 pDoc->m_Camera.GetCameraCOP_N() - FacetPoint._z);

	HVector = LightVector + ObserverVector;

	LightVector.NormalizeVector();
	ObserverVector.NormalizeVector();
	HVector.NormalizeVector();
}





void CHomework2View::NormalizeFinalColorValues(double& IRed, double& IGreen, double& IBlue)
// The NormalizeFinalColorValues() function ensures that the color values for a 
// given pen or brush do not exceed the range of 0.0 to 1.0.  If the color values 
// fall outside that range, the color value is set to its respective closest value.
{
	// Make sure the final values are not greater than 1.0.
	if(IRed > 1.0)
	{
		IRed = 1.0;
	}// end if
	if(IGreen > 1.0)
	{
		IGreen = 1.0;
	}// end if
	if(IBlue > 1.0)
	{
		IBlue = 1.0;
	}// end if

	// Make sure the final values are not less than 0.0.
	if(IRed < 0.0)
	{
		IRed = 0.0;
	}// end if
	if(IGreen < 0.0)
	{
		IGreen = 0.0;
	}// end if
	if(IBlue < 0.0)
	{
		IBlue = 0.0;
	}// end if
}





void CHomework2View::GenerateEdgeList(const point& PointA, const point& PointB, const point& PointC,
		                              const int& unit_u, const int& unit_v, const RECT& rect,
						              const double& IRed_A, const double& IGreen_A, const double& IBlue_A,
						              const double& IRed_B, const double& IGreen_B, const double& IBlue_B,
						              const double& IRed_C, const double& IGreen_C, const double& IBlue_C,
									  const Vector& VertexNormalA, const Vector& VertexNormalB, 
							          const Vector& VertexNormalC, const int& DISPLAY_TYPE)
// Create the edge list by calling LineDDA and have the callback function
// take the points sent to that function and enter them into the global 
// edge list. This edge list will then be used to interpolate the intensities
// for the pixels along those lines, and then linearly interpolated between each
// edge to fill the facet.
{
	CHomework2Doc* pDoc = GetDocument();

	// Find the screen coordinates of each vertex.
	int a_x = (int)(PointA._x * unit_u + rect.right/2);
	int b_x = (int)(PointB._x * unit_u + rect.right/2);
	int c_x = (int)(PointC._x * unit_u + rect.right/2);

	int a_y = (int)(PointA._y * (-1)*unit_v + rect.bottom/2);
	int b_y = (int)(PointB._y * (-1)*unit_v + rect.bottom/2);
	int c_y = (int)(PointC._y * (-1)*unit_v + rect.bottom/2);

	// Find the depth of each vertex.
	double depth_a = pow((pDoc->m_Camera.GetCameraCOP_U() - PointA._x), 2.0) +
		             pow((pDoc->m_Camera.GetCameraCOP_V() - PointA._y), 2.0) + 
					 pow((pDoc->m_Camera.GetCameraCOP_N() - PointA._z), 2.0);

	double depth_b = pow((pDoc->m_Camera.GetCameraCOP_U() - PointB._x), 2.0) +
		             pow((pDoc->m_Camera.GetCameraCOP_V() - PointB._y), 2.0) + 
					 pow((pDoc->m_Camera.GetCameraCOP_N() - PointB._z), 2.0);

	double depth_c = pow((pDoc->m_Camera.GetCameraCOP_U() - PointC._x), 2.0) +
		             pow((pDoc->m_Camera.GetCameraCOP_V() - PointC._y), 2.0) + 
					 pow((pDoc->m_Camera.GetCameraCOP_N() - PointC._z), 2.0);

	// Add the lines to the edge list.  It is important to add the lines
	// so that the starting y coordinate is less than the ending y coordinate.
	// Therefore, test each set of points and send the point with the smallest
	// y coordinate as the starting point.


	// Add the line from A to B.
	if(a_y <= b_y)
	{
		AddLineToEdgeList(a_x, a_y, b_x, b_y, IRed_A, IGreen_A, 
						  IBlue_A, IRed_B, IGreen_B, IBlue_B, 
						  VertexNormalA, VertexNormalB, 
						  depth_a, depth_b, DISPLAY_TYPE); 
	}// end if
	else if(b_y < a_y)
	{
		AddLineToEdgeList(b_x, b_y, a_x, a_y, IRed_B, IGreen_B, 
						  IBlue_B, IRed_A, IGreen_A, IBlue_A, 
						  VertexNormalB, VertexNormalA, 
						  depth_b, depth_a, DISPLAY_TYPE);
	}// end else if

	// Add the line from B to C.
	if(b_y <= c_y)
	{
		AddLineToEdgeList(b_x, b_y, c_x, c_y, IRed_B, IGreen_B, 
						  IBlue_B, IRed_C, IGreen_C, IBlue_C, 
						  VertexNormalB, VertexNormalC, 
						  depth_b, depth_c, DISPLAY_TYPE);
	}// end if
	else if(c_y < b_y)
	{
		AddLineToEdgeList(c_x, c_y, b_x, b_y, IRed_C, IGreen_C, 
						  IBlue_C, IRed_B, IGreen_B, IBlue_B, 
						  VertexNormalC, VertexNormalB, 
						  depth_c, depth_b, DISPLAY_TYPE);
	}// end else if

	// Add the line from C to A.
	if(c_y <= a_y)
	{
		AddLineToEdgeList(c_x, c_y, a_x, a_y, IRed_C, IGreen_C, 
						  IBlue_C, IRed_A, IGreen_A, IBlue_A, 
						  VertexNormalC, VertexNormalA, 
						  depth_c, depth_a, DISPLAY_TYPE);
	}// end if
	else if(a_y < c_y)
	{
		AddLineToEdgeList(a_x, a_y, c_x, c_y, IRed_A, IGreen_A, 
						  IBlue_A, IRed_C, IGreen_C, IBlue_C, 
						  VertexNormalA, VertexNormalC, 
						  depth_a, depth_c, DISPLAY_TYPE);
	}// end else if



	// Sort the edge list.
	std::sort(pDoc->m_EdgeListVector.begin(), pDoc->m_EdgeListVector.end());

	// Adjust the edge list for any entires in which there is no x2 point
	// (which is typically the corner of a facet), or where the x1 and x2 
	// are out of order (x1 should be less than x2).
	for(int i=0; i<pDoc->m_EdgeListVector.size(); ++i)
	{
		// Check for -1 in x2
		if(pDoc->m_EdgeListVector[i].m_x2 == -1)
		{
			pDoc->m_EdgeListVector[i].m_x2         = pDoc->m_EdgeListVector[i].m_x1;
			pDoc->m_EdgeListVector[i].m_Depth_x2   = pDoc->m_EdgeListVector[i].m_Depth_x1;

			if(DISPLAY_TYPE == GOURAUD_SHADING)
			{
				// do you need to do this?
				pDoc->m_EdgeListVector[i].m_IRed_x2    = pDoc->m_EdgeListVector[i].m_IRed_x1;
				pDoc->m_EdgeListVector[i].m_IGreen_x2  = pDoc->m_EdgeListVector[i].m_IGreen_x1;
				pDoc->m_EdgeListVector[i].m_IBlue_x2   = pDoc->m_EdgeListVector[i].m_IBlue_x1;
			}// end if

			else if(DISPLAY_TYPE == PHONG_SHADING)
			{
				pDoc->m_EdgeListVector[i].m_Normal_x2  = pDoc->m_EdgeListVector[i].m_Normal_x1;
			}// end else if

		}// end if
    
		// Check for x1 and x2 swap.
		if(pDoc->m_EdgeListVector[i].m_x1 > pDoc->m_EdgeListVector[i].m_x2)
		{
			// These points must be swapped.
			int temp = pDoc->m_EdgeListVector[i].m_x1;
			pDoc->m_EdgeListVector[i].m_x1 = pDoc->m_EdgeListVector[i].m_x2;
			pDoc->m_EdgeListVector[i].m_x2 = temp;

			// Swap the depths.
			double temp_depth = pDoc->m_EdgeListVector[i].m_Depth_x1;
			pDoc->m_EdgeListVector[i].m_Depth_x1 = pDoc->m_EdgeListVector[i].m_Depth_x2;
			pDoc->m_EdgeListVector[i].m_Depth_x2 = temp_depth;

			if(DISPLAY_TYPE == GOURAUD_SHADING)
			{
				double temp = 0.0;

				// Also need to swap the intensities at those points.
				temp = pDoc->m_EdgeListVector[i].m_IRed_x1;
				pDoc->m_EdgeListVector[i].m_IRed_x1 = pDoc->m_EdgeListVector[i].m_IRed_x2;
				pDoc->m_EdgeListVector[i].m_IRed_x2 = temp;

				temp = pDoc->m_EdgeListVector[i].m_IGreen_x1;
				pDoc->m_EdgeListVector[i].m_IGreen_x1 = pDoc->m_EdgeListVector[i].m_IGreen_x2;
				pDoc->m_EdgeListVector[i].m_IGreen_x2 = temp;

				temp = pDoc->m_EdgeListVector[i].m_IBlue_x1;
				pDoc->m_EdgeListVector[i].m_IBlue_x1 = pDoc->m_EdgeListVector[i].m_IBlue_x2;
				pDoc->m_EdgeListVector[i].m_IBlue_x2 = temp;

			}// end if

			else if(DISPLAY_TYPE == PHONG_SHADING)
			{
				Vector TempVector;

				// Also need to swap the normals at those points.
				TempVector = pDoc->m_EdgeListVector[i].m_Normal_x1;
				pDoc->m_EdgeListVector[i].m_Normal_x1 = pDoc->m_EdgeListVector[i].m_Normal_x2;
				pDoc->m_EdgeListVector[i].m_Normal_x2 = TempVector;
			}// end else if

		}// end if

	}// end for  
}





void CHomework2View::AddLineToEdgeList(const int& start_x, const int& start_y, const int& end_x,   
						      const int& end_y, const double& start_IRed, const double& start_IGreen, 
						      const double& start_IBlue, const double& end_IRed, const double& end_IGreen, 
						      const double& end_IBlue, const Vector& StartNormal, const Vector& EndNormal, 
						      const double& start_depth, const double& end_depth, const int& DISPLAY_TYPE)
// The AddLineToEdgeList() function adds the line between the start point and end point
// to the pDoc->m_EdgeListVector.  The colors between the vertexes will be interpolated 
// from the provided red, green, and blue parameters.
{
	CHomework2Doc* pDoc = GetDocument();

	int num     = end_x - start_x;
	int den     = end_y - start_y;
	int length  = end_y - start_y + 1;
	int sign    = 0;

	// Variables for color of the points (GOURAUD_SHADING).
	double red   = start_IRed;
	double green = start_IGreen;
	double blue  = start_IBlue;
	double delta_red   = (end_IRed - start_IRed)/(double)(length);
	double delta_green = (end_IGreen - start_IGreen)/(double)(length);
	double delta_blue  = (end_IBlue - start_IBlue)/(double)(length);

	// Variables for the interpolation of normals (PHONG_SHADING).
	double normal_delta_x = (EndNormal.GetVectorX() - StartNormal.GetVectorX())/(double)(length-1);
	double normal_delta_y = (EndNormal.GetVectorY() - StartNormal.GetVectorY())/(double)(length-1);
	double normal_delta_z = (EndNormal.GetVectorZ() - StartNormal.GetVectorZ())/(double)(length-1);


	// Variables for the pixel depth.
	double delta_depth    = (end_depth - start_depth)/(double)(length);
	double current_depth  = start_depth;

	// Use the pixel normal to set the normal for a pixel on the edge.
	Vector PixelNormal    = StartNormal;

	if(num < 0)
	{
		sign = -1;
	}// end if
	else if(num >= 0)
	{
		sign = 1;
	}// end else if

	num      = abs(num);
	int x    = start_x;
	int inc  = 0;

	for(int y=start_y; y<end_y; ++y)
	{
		if(DISPLAY_TYPE == GOURAUD_SHADING)
		{
			AddPointToEdgeList(x, y, red, green, blue, PixelNormal, 
				               current_depth, GOURAUD_SHADING);

			red    += delta_red;
			green  += delta_green;
			blue   += delta_blue;

			current_depth += delta_depth;
		}// end if

		else if(DISPLAY_TYPE == PHONG_SHADING)
		{
			AddPointToEdgeList(x, y, red, green, blue, PixelNormal, 
				               current_depth, PHONG_SHADING);

			current_depth += delta_depth;

			PixelNormal.SetVectorX(PixelNormal.GetVectorX() + normal_delta_x);
			PixelNormal.SetVectorY(PixelNormal.GetVectorY() + normal_delta_y);
			PixelNormal.SetVectorZ(PixelNormal.GetVectorZ() + normal_delta_z);

			PixelNormal.NormalizeVector();
		}// end else if

		inc += num;

		while(inc >= den)
		{
			inc -= den;
			x = x + sign;
		}// end while

	}// end for
}




void CHomework2View::AddPointToEdgeList(const int& x, const int& y, const double& IRed, 
		                                  const double& IGreen, const double& IBlue, 
										          const Vector& PixelNormal, const double& depth, const int& DISPLAY_TYPE)
// The AddPointToEdgeList() function adds the point passed into the function as a parameter
// to the edge list with the intensities determined as parameters.  If the point's y value
// already exists in the data structure, then the x value is entered as the x2 value in the
// data structure.  If the point does not exist in the data structure, then the point's x 
// value is added as the x1 value, and the x2 value is set to -1.
{
	// Get a copy of the document and set the
	// lpData pointer to the document pointer.
	CHomework2Doc* pDoc  = GetDocument();
	int            i     = 0;
	bool           found = false;

	// Search the edge list for an entry at this scan line.
	// If the edge list has an entry at this scan line, then 
	// this point is the other end of the facet at that scan 
	// line.  If no edge with this y value exists in the 
	// edge list, then add a new edge list node.
	int size = pDoc->m_EdgeListVector.size();

	for(i=0; i<size; ++i)
	{
		if(y == pDoc->m_EdgeListVector[i].m_y)
		{
			found = true;
			break;
		}// end if
	}// end for

	if(DISPLAY_TYPE == GOURAUD_SHADING)
	{
		if(found == false)
		{
			EdgeListNode NewEdgeListNode;
			NewEdgeListNode.m_x1           = x;
			NewEdgeListNode.m_x2           = -1;
			NewEdgeListNode.m_y            = y;
			NewEdgeListNode.m_IRed_x1      = IRed;
			NewEdgeListNode.m_IGreen_x1    = IGreen;
			NewEdgeListNode.m_IBlue_x1     = IBlue;
			NewEdgeListNode.m_Depth_x1     = depth;

			pDoc->m_EdgeListVector.push_back(NewEdgeListNode);
		}// end if

		else if(found == true)
		{
			pDoc->m_EdgeListVector[i].m_x2 = x;
			pDoc->m_EdgeListVector[i].m_IRed_x2      = IRed;
			pDoc->m_EdgeListVector[i].m_IGreen_x2    = IGreen;
			pDoc->m_EdgeListVector[i].m_IBlue_x2     = IBlue;
			pDoc->m_EdgeListVector[i].m_Depth_x2     = depth;

		}// end else if
	}// end if

	else if(DISPLAY_TYPE == PHONG_SHADING)
	{
		if(found == false)
		{
			EdgeListNode NewEdgeListNode;
			NewEdgeListNode.m_x1           = x;
			NewEdgeListNode.m_x2           = -1;
			NewEdgeListNode.m_y            = y;
			NewEdgeListNode.m_Normal_x1    = PixelNormal;
			NewEdgeListNode.m_Depth_x1     = depth;

			pDoc->m_EdgeListVector.push_back(NewEdgeListNode);
		}// end if
		
		else if(found == true)
		{
			pDoc->m_EdgeListVector[i].m_x2        = x;
			pDoc->m_EdgeListVector[i].m_Normal_x2 = PixelNormal;
			pDoc->m_EdgeListVector[i].m_Depth_x2  = depth;
		}// end else if

	}// end else if
}




void CHomework2View::CalculatePointIntensity(const point& Point, const int& object_index,
											 const point PointLightUVN[],  const Vector& VertexNormal,
											 double& IRed, double& IGreen, double& IBlue)
// The CalculatePointIntensity() function determines the intensity of light on a given 
// point of an object. The PointLightUVN[] array is used to determine what lights affect 
// the color of this point, and the resulting color values are returned by reference in 
// the variables IRed, IGreen, and IBlue.
{
	CHomework2Doc* pDoc = GetDocument();

	Vector LightVector;
	Vector ObserverVector;
	Vector HVector;

	double distance = 0.0;

	double AmbientRed  = 0.0, AmbientGreen  = 0.0, AmbientBlue  = 0.0;
	double DiffuseRed  = 0.0, DiffuseGreen  = 0.0, DiffuseBlue  = 0.0;
	double SpecularRed = 0.0, SpecularGreen = 0.0, SpecularBlue = 0.0;

	// Generate the ambient contribution to this facet.
	GenerateAmbientColorValues(AmbientRed, AmbientGreen, AmbientBlue, object_index);

	// Generate the diffuse and specular light values 
	// for this brush for each RGB color.
	for(int i=0; i<MAX_LIGHTS; ++i)
	{
		if(m_PointLightParameters[i].m_Active == true)
		{
			SetLightAndObserverVectors(LightVector, ObserverVector, HVector, 
				                       PointLightUVN, Point, i, distance);

			if(VertexNormal.DotProduct(LightVector) > 0.0)
			{
				// Generate the diffuse color contribution to the facet.
				GenerateDiffuseColorValues(DiffuseRed, DiffuseGreen, DiffuseBlue, object_index,
					                       i, VertexNormal, LightVector, distance);

				// Generate the specular color contribution to the facet.
				GenerateSpecularColorValues(SpecularRed, SpecularGreen, SpecularBlue, object_index,
					                        i, VertexNormal, LightVector, HVector, distance);
			}// end if		
		}// end if
	}// end for

	// Combine the light types for the final color of the facet.
	IRed    = AmbientRed   + DiffuseRed   + SpecularRed;
	IGreen  = AmbientGreen + DiffuseGreen + SpecularGreen;
	IBlue   = AmbientBlue  + DiffuseBlue  + SpecularBlue;
}




void CHomework2View::OutputEdgeListToFile(int a_x, int a_y, int b_x, int b_y, int c_x, int c_y,
							 const double& IRed_A, const double& IGreen_A, const double& IBlue_A,
							 const double& IRed_B, const double& IGreen_B, const double& IBlue_B,
							 const double& IRed_C, const double& IGreen_C, const double& IBlue_C)
// This function outputs the particulars of the edge list to the file edgelist.txt 
// for debugging purposes.  
{
	CHomework2Doc* pDoc = GetDocument();
	fstream out;
	out.open("edgelist.txt", ios::app | ios::out);

	out.unsetf(ios::right);
	out.setf(ios::left);

	out << "Edgelist\n\n";
	out << "PointA._x = " << a_x << "  PointA._y = " << a_y << "\n"
		<< "PointB._x = " << b_x << "  PointB._y = " << b_y << "\n"
		<< "PointC._x = " << c_x << "  PointC._y = " << c_y << "\n\n";

	out << "IRed_A   = "  << IRed_A   << "\n"
		<< "IGreen_A = "  << IGreen_A << "\n"
		<< "IBlue_A  = "  << IBlue_A  << "\n"

		<< "IRed_B   = "  << IRed_B   << "\n"
		<< "IGreen_B = "  << IGreen_B << "\n"
		<< "IBlue_B  = "  << IBlue_B  << "\n"

		<< "IRed_C   = "  << IRed_C   << "\n"
		<< "IGreen_C = "  << IGreen_C << "\n"
		<< "IBlue_C  = "  << IBlue_C  << "\n";

	out << setw(7) << "y"
		<< setw(8) << "x1"
		<< setw(9) << "x2"
		<< setw(20) << "I_Redx1"
		<< setw(20) << "I_Greenx1"
		<< setw(20) << "I_Bluex1"
		<< setw(20) << "I_Redx2"
		<< setw(20) << "I_Greenx2"
		<< setw(20) << "I_Bluex2\n";

	for(int k=0; k<pDoc->m_EdgeListVector.size(); ++k)
	{
		out << setw(7) << pDoc->m_EdgeListVector[k].m_y
			<< setw(8) << pDoc->m_EdgeListVector[k].m_x1
			<< setw(9) << pDoc->m_EdgeListVector[k].m_x2
			<< setw(20) << pDoc->m_EdgeListVector[k].m_IRed_x1
			<< setw(20) << pDoc->m_EdgeListVector[k].m_IGreen_x1
			<< setw(20) << pDoc->m_EdgeListVector[k].m_IBlue_x1
			<< setw(20) << pDoc->m_EdgeListVector[k].m_IRed_x2
			<< setw(20) << pDoc->m_EdgeListVector[k].m_IGreen_x2
			<< setw(20) << pDoc->m_EdgeListVector[k].m_IBlue_x2 << "\n";
	}
	out.close();
}




void CHomework2View::OnZBufferParameters() 
// This function sets the z-buffer parameters via a modeless dialog box.
{
	CHomework2Doc* pDoc = GetDocument();

	if(IDOK == m_ZBufferParametersDialog.DoModal())
	{
		
	}// end if
}


void CHomework2View::ResetZBuffer()
// This function deletes all the values in the m_ZBuffer and resets the buffer
// to the default distance values.
{
	// Clear the current contents of the z-buffer.
	m_ZBuffer.clear();

	int width  = m_ZBufferParametersDialog.screen_cols;
	int height = m_ZBufferParametersDialog.screen_rows;

	m_ZBuffer.resize(height);

	for(int i=0; i<height; ++i)
	{
		m_ZBuffer[i].resize(width);

		// Initialize the row/column values.
		for(int j=0; j<width; ++j)
		{
			// Each index in the z-buffer should be the z_far value.
			m_ZBuffer[i][j] =  pow(m_ZBufferParametersDialog.z_far, 2.0);
		}// end for

	}// end for
}



void CHomework2View::ResetFacetEdgeList()
// This function deletes the contents of the edge list to make room 
// for the next facet to be drawn.
{
	CHomework2Doc* pDoc = GetDocument();

	pDoc->m_EdgeListVector.clear();
}


void CHomework2View::GetLightPosition(const int& light_num, CString& EditBoxXString, 
		                              CString& EditBoxYString, CString& EditBoxZString)
// This function gets the positions of the point light and returns their positions as
// strings, extracted from the edit boxes, in the CString parameters.
{
	m_PointLightParameters[light_num].GetDlgItemText(IDC_POINT_LIGHT_X_EDIT, EditBoxXString);
	m_PointLightParameters[light_num].GetDlgItemText(IDC_POINT_LIGHT_Y_EDIT, EditBoxYString);
	m_PointLightParameters[light_num].GetDlgItemText(IDC_POINT_LIGHT_Z_EDIT, EditBoxZString);
}


void CHomework2View::SetWireframePen(CPen& pen, const int& object_index, const double& distance)
// This function sets the pen object for the wire frame drawing
// functions.
{
	CHomework2Doc* pDoc = GetDocument();

	COLORREF pen_color = RGB(0,0,0);
	int      thickness = 0;
	double   max_distance  = DBL_MIN;
	double   min_distance  = DBL_MAX;
	
	if(m_DisplayType == WIREFRAME || m_DisplayType == WIREFRAME_BACKFACE)
	{
		// Choose the color of the pen depending on if
		// the object is the current object.
		if(object_index == pDoc->m_CurrentObject)
		{
			pen_color = RGB(0,255,0);
		}// end if
		else
		{
			pen_color = RGB(255,255,255);
		}// end else if


	}// end if

	else if(m_DisplayType == WIREFRAME_DEPTHCUE)
	{
		// Find the maximum and minimum distances in the scene
		// in order to interpolate pen color.
		GetMaxAndMinDistances(max_distance, min_distance);
		InterpolateDepthCueFacetColor(distance, max_distance, min_distance, pen_color);

	}// end else if

	// Set the pen thickness to this object's thickness.
	thickness = pDoc->m_Objects[object_index].GetObjectLineThickness();

	// Make sure pen is available.
	pen.DeleteObject();

	// Assign pen statistics.
	pen.CreatePen(PS_SOLID, thickness, pen_color);
}


void CHomework2View::GetMaxAndMinDistances(double& max, double& min)
// This function will determine the distance of the facet that is the farthest
// from the observer and the facet that is closest to the obsever and return that
// in the parameter by reference.
{
	CHomework2Doc* pDoc = GetDocument();

	int objects_size = pDoc->m_Objects.size();

	for(int i=0; i<objects_size; ++i)
	{
		if(pDoc->m_Objects[i].m_FacetDistances[0].m_Distance > max)
		{
			max = pDoc->m_Objects[i].m_FacetDistances[0].m_Distance;
		}// end if

		if(pDoc->m_Objects[i].m_FacetDistances[pDoc->m_Objects[i].m_FacetDistances.size()-1].m_Distance < min)
		{
			min = pDoc->m_Objects[i].m_FacetDistances[pDoc->m_Objects[i].m_FacetDistances.size()-1].m_Distance;
		}// end if

	}// end for
}

void CHomework2View::InterpolateDepthCueFacetColor(const double& distance,  const double& max, 
		                                           const double& min, COLORREF& pen_color)
// This function will interpolate a pen color for each facet on the object
// when viewing the world scene with the depth-cue algorithm.  The objects 
// will have a color of bright red for closest facets and the background color
// for far away facets.
{
	double range = max - min;
	double val   = max - distance;

	val  = ((val/range) * 255);		

	pen_color = RGB(val, 
		            m_BackgroundColorDialog.m_BackgroundGreenValue, // finish this.
					m_BackgroundColorDialog.m_BackgroundBlueValue);
}

void CHomework2View::GetUnitVectorPixels(const RECT& rect, int& unit_u_pixels, int& unit_v_pixels)
// Assume the coordinate plane goes from +40 to -40 x and from +40 to -40 y.  Thus 
// calculate how many pixels for each tick mark on the axis.  One "unit" in x and 
// y coordinates in the data structure represent the number of pixels in unit_u_pixels 
// and unit_v_pixels.
{
	int standardized_size = 0;

	if(rect.right < rect.bottom)
	{
		standardized_size = rect.right;
	}// end if
	else
	{
		standardized_size = rect.bottom;
	}// end else
	
	// Use the u_min and u_max and v_min and v_max values to 
	// determine how many pixels are in the unit dimension.
	int u_distance = m_ZBufferParametersDialog.u_max - m_ZBufferParametersDialog.u_min;
	int v_distance = m_ZBufferParametersDialog.v_max - m_ZBufferParametersDialog.v_min;

	unit_u_pixels = standardized_size / u_distance;
	unit_v_pixels = standardized_size / v_distance; 
}




/********************************************************/
/*                                                      */
/*   MFC Generated Diagnostics and Debug code           */
/*                                                      */
/********************************************************/

#ifdef _DEBUG
void CHomework2View::AssertValid() const
{
	CView::AssertValid();
}

void CHomework2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHomework2Doc* CHomework2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomework2Doc)));
	return (CHomework2Doc*)m_pDocument;
}
#endif //_DEBUG



/********************************************************/
/*                                                      */
/*   Three Dimensional Transformation Message Handlers  */
/*   And Dialog Box Command Handlers.                   */
/*                                                      */
/********************************************************/

void CHomework2View::OnObjectManager() 
{
	CObjectManager ObjectManDlg;
    CHomework2Doc* pDoc = GetDocument();
	
	ObjectManDlg.pDoc     = pDoc;
	ObjectManDlg.m_Camera = pDoc->m_Camera;

	if(IDOK == ObjectManDlg.DoModal())
	{
		// The object manager is no longer needed.
		Invalidate(false);
		pDoc->m_CurSel          = ObjectManDlg.m_CurSel;
		pDoc->m_ObjectFileNames = ObjectManDlg.m_ObjectFileNames;

	}// end if

	// If the user deleted all of the objects, then set all of the 
	// light objects to inactive.
	if(pDoc->m_Objects.size() == 0)
	{
		for(int deactivate = 0; deactivate<5; ++deactivate)
		{
			m_PointLightParameters[deactivate].m_Active = false;
		}// end for
	}// end if


	// If the Transformation parameters dialog is open, reset the
	// values in that dialog to represent the affine transformations
	// that are applied to that object.
	if(!m_TransformationParametersDialog.GetSafeHwnd())
	{
	  m_TransformationParametersDialog.pDoc = GetDocument();
	  m_TransformationParametersDialog.Create(IDD_TRANSFORMATION_DIALOG, this);
	}// end if

	if(m_TransformationParametersDialog.IsWindowVisible())
	{
		m_TransformationParametersDialog.pDoc = GetDocument();
		m_TransformationParametersDialog.SetSliderDisplayValues();
		m_TransformationParametersDialog.SetSliderPositions();
	}// end if
}

void CHomework2View::OnTransformationParameters()
// This function allows the user to modify the current object's rotation,
// scale, shear, and translation parameters in real time.
{
   CHomework2Doc* pDoc = GetDocument();

   if(pDoc->m_Objects.size() < 1)
   {
		string warning_string;
		warning_string = "You must first create an object through   \n";
		warning_string.append("the Object Manager to create affine   \n");
		warning_string.append("transformations on that object.");

		MessageBox(warning_string.c_str(), "No Current Object", MB_OK|MB_ICONEXCLAMATION);

		return;

   }// end if

   if(!m_TransformationParametersDialog.GetSafeHwnd())
   {
	  m_TransformationParametersDialog.pDoc = GetDocument();
      m_TransformationParametersDialog.Create(IDD_TRANSFORMATION_DIALOG, this);
   }// end if

   if(!m_TransformationParametersDialog.IsWindowVisible())
   {
      m_TransformationParametersDialog.ShowWindow(SW_SHOW);
	  m_TransformationParametersDialog.pDoc = GetDocument();
   }// end if	
	
}

void CHomework2View::OnViewPalette() 
// This function sets up the View Parameters dialog box, which allows the 
// user to modify the location and disposition of the view coordinate system.
// The dialog box is implemented as a modeless dialog box which will allow 
// the user to make changes to his point of view in real time.
{
   CHomework2Doc* pDoc = GetDocument();

   if(!m_ViewParametersDialog.GetSafeHwnd())
   {
      m_ViewParametersDialog.Create(IDD_VIEW_PARAMETERS_DIALOG, this);
	  m_ViewParametersDialog.pDoc = GetDocument();
	  m_ViewParametersDialog.m_Camera = pDoc->m_Camera;
   }// end if

   if(!m_ViewParametersDialog.IsWindowVisible())
   {
      m_ViewParametersDialog.ShowWindow(SW_SHOW);
	  m_ViewParametersDialog.pDoc = GetDocument();
	  m_ViewParametersDialog.m_Camera = pDoc->m_Camera;
   }// end if	
}

void CHomework2View::OnProjectionMethod() 
// This function allows the user to determine what type of projection method
// to use when displaying the three-dimensional objects.
{
   CHomework2Doc* pDoc = GetDocument();
   
   CProjectionMethod ProjectionMethodDialog;

   ProjectionMethodDialog.m_ProjectionMethod = pDoc->m_ProjectionMethod;

	if(IDOK == ProjectionMethodDialog.DoModal())
	{
		// The projection method dialog is no longer needed.
		pDoc->m_ProjectionMethod = ProjectionMethodDialog.m_ProjectionMethod;

	}// end if

	Invalidate(false);
}

void CHomework2View::OnWireFrame()
// This function sets the display type to wireframe only drawing mode.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = WIREFRAME;

	UncheckAllDisplayModes();

	pMenu->CheckMenuItem(IDM_WIRE_FRAME, MF_CHECKED);

	Invalidate(false);
}

void CHomework2View::OnWireFrameDepthCue() 
// This function sets the display type to wireframe with depth cueing.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = WIREFRAME_DEPTHCUE;

	UncheckAllDisplayModes();

	pMenu->CheckMenuItem(IDM_WIRE_FRAME_DEPTH_CUE, MF_CHECKED);

	Invalidate(false);
}

void CHomework2View::OnWireFrameBackfaceElimination() 
// This function sets the display type to wireframe with backface elimination.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = WIREFRAME_BACKFACE;	

	UncheckAllDisplayModes();

	pMenu->CheckMenuItem(IDM_WIRE_FRAME_BACKFACE_ELIMINATION, MF_CHECKED);

	Invalidate(false);
}

void CHomework2View::OnPaintersAlgorithm() 
// This function sets the display type to the Painter's algorithm.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = PAINTERS;

	UncheckAllDisplayModes();
	
	pMenu->CheckMenuItem(IDM_PAINTERS_ALGORITHM, MF_CHECKED);

	Invalidate(false);
}

void CHomework2View::OnPaintersAlgorithmTracedFacets() 
// This function sets the display type to the Painter's algorithm with traced facets.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = PAINTERS_TRACED;

	UncheckAllDisplayModes();
	
	pMenu->CheckMenuItem(IDM_PAINTERS_ALGORITHM_TRACED_FACETS, MF_CHECKED);

	Invalidate(false);	
}


void CHomework2View::OnGouraudShading() 
// This function sets the display type to Gouraud shading.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = GOURAUD_SHADING;

	UncheckAllDisplayModes();
	
	pMenu->CheckMenuItem(IDM_GOURAUD_SHADING, MF_CHECKED);

	Invalidate(false);	
}


void CHomework2View::OnPhongShading() 
// This function sets the display type to Phong shading.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	m_DisplayType = PHONG_SHADING;

	UncheckAllDisplayModes();
	
	pMenu->CheckMenuItem(IDM_PHONG_SHADING, MF_CHECKED);

	Invalidate(false);	
}



bool CHomework2View::UncheckAllDisplayModes()
// This function unchecks all of display methods in the menu bar.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	pMenu->CheckMenuItem(IDM_WIRE_FRAME, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_WIRE_FRAME_DEPTH_CUE, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_WIRE_FRAME_BACKFACE_ELIMINATION, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_PAINTERS_ALGORITHM, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_PAINTERS_ALGORITHM_TRACED_FACETS, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_GOURAUD_SHADING, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_PHONG_SHADING, MF_UNCHECKED);

	return true;
}


void CHomework2View::OnOptionsLinethickness()
// This function will generate a modal dialog box which will modify
// the current object's line thickness while in any of the wire-frame modes.
{
    CHomework2Doc* pDoc = GetDocument();

	CLineThickness	LineThicknessDialog;

	if(pDoc->m_Objects.size() < 1)
	{
		string warning_string;
		warning_string = "You must first create an object through   \n";
		warning_string.append("the Object Manager to set the current   \n");
		warning_string.append("object's line thickness.");

		MessageBox(warning_string.c_str(), "No Current Object", MB_OK|MB_ICONEXCLAMATION);

		return;
	}// end if


	LineThicknessDialog.m_Thickness = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectLineThickness();

	if(IDOK == LineThicknessDialog.DoModal())
	{
		pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectLineThickness(LineThicknessDialog.m_Thickness);

	}// end if

	Invalidate(false); 
}

void CHomework2View::OnOptionsBackgroundcolor() 
// This function will provide a modeless dialog box that will allow the 
// user to change the background color of the renderable area.
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_BackgroundColorDialog.GetSafeHwnd())
	{
	  m_BackgroundColorDialog.Create(IDD_BACKGROUND_COLOR_DIALOG, this);
	  m_BackgroundColorDialog.pDoc = GetDocument();
	}// end if

	if(!m_BackgroundColorDialog.IsWindowVisible())
	{
	  m_BackgroundColorDialog.ShowWindow(SW_SHOW);
	  m_BackgroundColorDialog.pDoc = GetDocument();
	}// end if		
}

void CHomework2View::OnMaterialSelector() 
// This function creates the material selector dialog box for the user.
// It allows the user to change the material for the current object.
{
	CHomework2Doc* pDoc = GetDocument();

	if(pDoc->m_Objects.size() < 1)
	{
	    string warning_string;
	    warning_string = "You must first create an object through   \n";
	    warning_string.append("the Object Manager to set the current   \n");
	    warning_string.append("object's material.");

	    MessageBox(warning_string.c_str(), "No Current Object", MB_OK|MB_ICONEXCLAMATION);

	    return;
	}// end if

	if(!m_MaterialSelectorDialog.GetSafeHwnd())
	{
	  m_MaterialSelectorDialog.m_MaterialNames.clear();
	  m_MaterialSelectorDialog.m_MaterialNames.resize(NUM_MATERIALS);

	  for(int i=0; i<NUM_MATERIALS; ++i)
	  {
		m_MaterialSelectorDialog.m_MaterialNames[i] = m_Materials[i].GetMaterialName();
	  }// end for

	  m_MaterialSelectorDialog.Create(IDD_MATERIAL_SELECTOR_DIALOG, this);
	  m_MaterialSelectorDialog.pDoc = GetDocument();

	}// end if

	if(!m_MaterialSelectorDialog.IsWindowVisible())
	{
	  m_MaterialSelectorDialog.m_MaterialNames.clear();
	  m_MaterialSelectorDialog.m_MaterialNames.resize(NUM_MATERIALS);

	  for(int i=0; i<NUM_MATERIALS; ++i)
	  {
		m_MaterialSelectorDialog.m_MaterialNames[i] = m_Materials[i].GetMaterialName();
	  }// end for
	  m_MaterialSelectorDialog.ShowWindow(SW_SHOW);
	  m_MaterialSelectorDialog.pDoc = GetDocument();

	}// end if	

	Invalidate(false);
}

void CHomework2View::OnMaterialEditor() 
{
	UpdateMaterialPropertyPagesFromMaterials();

	if(IDOK == m_MaterialPropertiesSheets.DoModal())
	{
		UpdateMaterialsFromEditor();
	}// end if
}

void CHomework2View::UpdateMaterialPropertyPagesFromMaterials()
{
	for(int j=0; j<NUM_MATERIALS; ++j)
	{
		string tab_string = m_Materials[j].GetMaterialName();
		m_MaterialPropertyPages[j].m_psp.pszTitle = tab_string.c_str();
		m_MaterialPropertyPages[j].m_psp.dwFlags|=PSP_USETITLE;
		m_MaterialPropertyPages[j].m_Name    = m_Materials[j].GetMaterialName();
		m_MaterialPropertyPages[j].m_KaRed   = m_Materials[j].GetMaterialKaRed();
		m_MaterialPropertyPages[j].m_KaGreen = m_Materials[j].GetMaterialKaGreen();
		m_MaterialPropertyPages[j].m_KaBlue  = m_Materials[j].GetMaterialKaBlue();
		m_MaterialPropertyPages[j].m_KdRed   = m_Materials[j].GetMaterialKdRed();
		m_MaterialPropertyPages[j].m_KdGreen = m_Materials[j].GetMaterialKdGreen();
		m_MaterialPropertyPages[j].m_KdBlue  = m_Materials[j].GetMaterialKdBlue();
		m_MaterialPropertyPages[j].m_KsRed   = m_Materials[j].GetMaterialKsRed();
		m_MaterialPropertyPages[j].m_KsGreen = m_Materials[j].GetMaterialKsGreen();
		m_MaterialPropertyPages[j].m_KsBlue  = m_Materials[j].GetMaterialKsBlue();
		m_MaterialPropertyPages[j].m_SpecularExponent  = m_Materials[j].GetMaterialSpecularExponent();

	}// end for
}

void CHomework2View::UpdateMaterialsFromEditor()
{
	for(int j=0; j<NUM_MATERIALS; ++j)
	{
		m_Materials[j].SetMaterialName(m_MaterialPropertyPages[j].m_Name);
		m_Materials[j].SetMaterialKaRed(m_MaterialPropertyPages[j].m_KaRed);
		m_Materials[j].SetMaterialKaGreen(m_MaterialPropertyPages[j].m_KaGreen);
		m_Materials[j].SetMaterialKaBlue(m_MaterialPropertyPages[j].m_KaBlue);
		m_Materials[j].SetMaterialKdRed(m_MaterialPropertyPages[j].m_KdRed);
		m_Materials[j].SetMaterialKdGreen(m_MaterialPropertyPages[j].m_KdGreen);
		m_Materials[j].SetMaterialKdBlue(m_MaterialPropertyPages[j].m_KdBlue);
		m_Materials[j].SetMaterialKsRed(m_MaterialPropertyPages[j].m_KsRed);
		m_Materials[j].SetMaterialKsGreen(m_MaterialPropertyPages[j].m_KsGreen);
		m_Materials[j].SetMaterialKsBlue(m_MaterialPropertyPages[j].m_KsBlue);
		m_Materials[j].SetMaterialSpecularExponent(m_MaterialPropertyPages[j].m_SpecularExponent);
	}// end for
}



void CHomework2View::OnAmbientLightProperties() 
// This function will display the ambient light properties dialog box so the
// user can modify the ambient light RGB parameters.  The dialog box is modeless,
// which will allow the user to make changes to the light and see the effects at 
// the same time.  The light values are kept in the m_AmbientLightParamtersDialog.
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_AmbientLightPropertiesDialog.GetSafeHwnd())
	{
	  m_AmbientLightPropertiesDialog.Create(IDD_AMBIENT_LIGHT_DIALOG, this);
	  m_AmbientLightPropertiesDialog.pDoc = GetDocument();
	}// end if

	if(!m_AmbientLightPropertiesDialog.IsWindowVisible())
	{
	  m_AmbientLightPropertiesDialog.ShowWindow(SW_SHOW);
	  m_AmbientLightPropertiesDialog.pDoc = GetDocument();
	}// end if		
}

void CHomework2View::OnPointLight1() 
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_PointLightParameters[0].GetSafeHwnd())
	{
	  m_PointLightParameters[0].Create(IDD_POINT_LIGHT_DIALOG, this);
	  m_PointLightParameters[0].pDoc = GetDocument();
	  m_PointLightParameters[0].SetHeaderString(1);
	}// end if

	if(!m_PointLightParameters[0].IsWindowVisible())
	{
	  m_PointLightParameters[0].ShowWindow(SW_SHOW);
	  m_PointLightParameters[0].pDoc = GetDocument();
	}// end if	
}

void CHomework2View::OnPointLight2() 
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_PointLightParameters[1].GetSafeHwnd())
	{
	  m_PointLightParameters[1].Create(IDD_POINT_LIGHT_DIALOG, this);
	  m_PointLightParameters[1].pDoc = GetDocument();
	  m_PointLightParameters[1].SetHeaderString(2);
	}// end if

	if(!m_PointLightParameters[1].IsWindowVisible())
	{
	  m_PointLightParameters[1].ShowWindow(SW_SHOW);
	  m_PointLightParameters[1].pDoc = GetDocument();
	}// end if	
	
}

void CHomework2View::OnPointLight3() 
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_PointLightParameters[2].GetSafeHwnd())
	{
	  m_PointLightParameters[2].Create(IDD_POINT_LIGHT_DIALOG, this);
	  m_PointLightParameters[2].pDoc = GetDocument();
	  m_PointLightParameters[2].SetHeaderString(3);
	}// end if

	if(!m_PointLightParameters[2].IsWindowVisible())
	{
	  m_PointLightParameters[2].ShowWindow(SW_SHOW);
	  m_PointLightParameters[2].pDoc = GetDocument();
	}// end if	
}

void CHomework2View::OnPointLight4() 
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_PointLightParameters[3].GetSafeHwnd())
	{
	  m_PointLightParameters[3].Create(IDD_POINT_LIGHT_DIALOG, this);
	  m_PointLightParameters[3].pDoc = GetDocument();
	  m_PointLightParameters[3].SetHeaderString(4);
	}// end if

	if(!m_PointLightParameters[3].IsWindowVisible())
	{
	  m_PointLightParameters[3].ShowWindow(SW_SHOW);
	  m_PointLightParameters[3].pDoc = GetDocument();
	}// end if		
}

void CHomework2View::OnPointLight5() 
{
	CHomework2Doc* pDoc = GetDocument();

	if(!m_PointLightParameters[4].GetSafeHwnd())
	{
	  m_PointLightParameters[4].Create(IDD_POINT_LIGHT_DIALOG, this);
	  m_PointLightParameters[4].pDoc = GetDocument();
	  m_PointLightParameters[4].SetHeaderString(5);
	}// end if

	if(!m_PointLightParameters[4].IsWindowVisible())
	{
	  m_PointLightParameters[4].ShowWindow(SW_SHOW);
	  m_PointLightParameters[4].pDoc = GetDocument();
	}// end if	
}




void CHomework2View::AddPointLight(int light_num)
{
	CHomework2Doc* pDoc = GetDocument();

	string     object_name;
	ifstream   in_file;
	int        number_of_points = 0;
	int        number_of_facets = 0;
	int        point_number = 0;
	int        facet_number = 0;
	Object3D   NewLightObject; 
	CString    EditBoxXString;
	CString    EditBoxYString;
	CString    EditBoxZString;

	in_file.open("LightObjects/LIGHT.D3", ios::in);

	if(in_file.fail())
	{
		MessageBox("File not found", "Error", MB_OK);
		return;
	}// end if

	// Read in the information in the file and 
	// store in a new Object.
	in_file >> object_name;	

	NewLightObject.SetObjectName(object_name);

	in_file >> number_of_points;

	NewLightObject.SetPointVectorSize(number_of_points);

	for(int i=0; i<number_of_points; ++i)
	{
		in_file >> point_number;

		point NewPoint;

		in_file >> NewPoint._x;
		in_file >> NewPoint._y;
		in_file >> NewPoint._z;
		NewPoint._h = 1.0;

		NewLightObject.SetObjectPoint(i, NewPoint);
	}// end for

	in_file >> number_of_facets;

	for(int j=0; j<number_of_facets; ++j)
	{
		in_file >> facet_number;

		facet NewFacet;

		in_file >> NewFacet._color;
		in_file >> NewFacet._corner1;
		in_file >> NewFacet._corner2;
		in_file >> NewFacet._corner3;

		NewLightObject.SetObjectFacet(NewFacet);
	}// end for


	// Set the material for the object as a light material.
	NewLightObject.SetObjectMaterialIndex(LIGHT);

	// Set the translation values of the light as the values of 
	// the point light x, y, and z coordinates.
	GetLightPosition(light_num, EditBoxXString, EditBoxYString, EditBoxZString);

	NewLightObject.SetObjectTransXVal(atof(EditBoxXString));
	NewLightObject.SetObjectTransYVal(atof(EditBoxYString));
	NewLightObject.SetObjectTransZVal(atof(EditBoxZString));

	// Set the light number of the object.
	NewLightObject.m_LightIndex = light_num;

	// Create the m_FacetDistances data structure from the
	// list of facets in the object being added.
	NewLightObject.GenerateFacetDistanceVector(pDoc->m_Camera, pDoc->m_ProjectionMethod);

	// The data has been read from the file.  Enter this 
	// object in the document variable m_Objects.
	pDoc->m_Objects.push_back(NewLightObject);
}


void CHomework2View::OnDrawAxis() 
// This function toggles the view variable m_DrawAxis.  If the m_DrawAxis 
// boolean is true, the rendered screen will have the world coordinate axis
// drawn on it.
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	if(m_DrawAxis == false)
	{
		m_DrawAxis = true;
		pMenu->CheckMenuItem(IDM_DRAW_AXIS, MF_CHECKED);
	}// end if

	else if(m_DrawAxis == true)
	{
		m_DrawAxis = false;
		pMenu->CheckMenuItem(IDM_DRAW_AXIS, MF_UNCHECKED);

	}// end if

	Invalidate(false);
}

void CHomework2View::OnMouseCameraPan() 
{
	CWnd*  pMainWnd = (CWnd*) AfxGetMainWnd();
    CMenu* pMenu    = pMainWnd->GetMenu();

	if(m_MouseCameraPanEnable == false)
	{
		m_MouseCameraPanEnable = true;
		pMenu->CheckMenuItem(IDM_MOUSE_CAMERA_PAN, MF_CHECKED);
	}// end if

	else if(m_MouseCameraPanEnable == true)
	{
		m_MouseCameraPanEnable = false;
		pMenu->CheckMenuItem(IDM_MOUSE_CAMERA_PAN, MF_UNCHECKED);

	}// end if

	Invalidate(false);
	
}

void CHomework2View::OnMouseMove(UINT nFlags, CPoint point) 
{
	CHomework2Doc* pDoc = GetDocument();

	// If the user has the camera pan setting on, then use the
	// difference in last mouse point and the current mouse point.
	if( nFlags & MK_LBUTTON && m_MouseCameraPanEnable == true)
	{
		int delta_x = point.x - m_LastMousePosition.x;
		int delta_y = point.y - m_LastMousePosition.y;

		if(delta_x < 0) delta_x = -1;
		else if(delta_x > 0) delta_x = 1;

		if(delta_y < 0) delta_y = -1;
		else if(delta_y > 0) delta_y = 1;

		double current_x_pos = pDoc->m_Camera.GetCameraVRP_X();
		double current_y_pos = pDoc->m_Camera.GetCameraVRP_Y();

		pDoc->m_Camera.SetCameraVRP_X(current_x_pos + delta_x);
		pDoc->m_Camera.SetCameraVRP_Y(current_y_pos + delta_y);

		pDoc->m_Camera.SetCameraVPN_X(0.0 - pDoc->m_Camera.GetCameraVRP_X());
		pDoc->m_Camera.SetCameraVPN_Y(0.0 - pDoc->m_Camera.GetCameraVRP_Y());
		pDoc->m_Camera.SetCameraVPN_Z(0.0 - pDoc->m_Camera.GetCameraVRP_Z());

		m_LastMousePosition.x = point.x;
		m_LastMousePosition.y = point.y;

		if(pDoc->m_Objects.size() > 0)
		{
			// The camera's values have been modified, therefore the m_FacetDistances list
			// must be updated to  reflect any changes the transformations have made to 
			// their distances to the observer.
			pDoc->m_Objects[pDoc->m_CurrentObject].GenerateFacetDistanceVector(pDoc->m_Camera, 
																	  pDoc->m_ProjectionMethod);
		}// end if

		Invalidate(false);
	}

	CView::OnMouseMove(nFlags, point);



}








