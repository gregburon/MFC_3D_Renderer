

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

#include "defines.h"
#include "Matrix.h"
#include "ViewParameters.h"
#include "TransformationParameters.h"
#include "LineThickness.h"
#include "BackgroundColor.h"
#include "AmbientLightProperties.h"
#include "PointLightParameters.h"
#include "Material.h"
#include "MaterialSelectorDialog.h"
#include "MaterialPropertyPage.h"
#include "ZBufferParameters.h"

#if !defined(AFX_HOMEWORK2VIEW_H__3FE73463_E226_42D6_86D2_6CD683E7E9DD__INCLUDED_)
#define AFX_HOMEWORK2VIEW_H__3FE73463_E226_42D6_86D2_6CD683E7E9DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHomework2View : public CView
{
protected: // create from serialization only
	CHomework2View();
	DECLARE_DYNCREATE(CHomework2View)

// Attributes
public:

	// Document pointer.
	CHomework2Doc*      GetDocument();


	// Drawing functions for the view object.
	void    DrawWorldCoordinateAxis(CDC* MemDC, const RECT& rect, 
									const Matrix& CoordMatrix);

	void    DrawAxisLine(CDC* MemDC, const RECT& rect, const int& axis, 
						 const Matrix& CoordMatrix, const CPen& pen, const int& direction, 
						 const int& unit_u_pixels, const int& unit_v_pixels);

	void    DrawObjects(CDC* MemDC, const RECT& rect);

	void    DrawWireFrameFacet(CDC* MemDC, const point& PointA, 
		                       const point& PointB, const point& PointC, 
							   const int& object_index, const RECT& rect,
							   const int& unit_u, const int& unit_v,
							   const double& distance);

	void    DrawSolidFacet(CDC* MemDC, const point& PointA, const point& PointB,
		                   const point& PointC, const int& object_index, const RECT& rect,
						   const int& unit_u, const int& unit_v, const Matrix& ModelingMatrix,
						   const point PointLightUVN[], 
						   const Vector& FacetNormal, const point& CenterPoint);

	void    DrawGouraudFacet(CDC* MemDC, const point& PointA, const point& PointB, 
		                     const point& PointC, const int& object_index, const RECT& rect,
						     const int& unit_u, const int& unit_v, const Matrix& ModelingMatrix,
							 const point PointLightUVN[], const Vector& FacetNormal, 
							 const point& CenterPoint, const int& corner_a, const int& corner_b, 
							 const int& corner_c);

	void    DrawPhongFacet(CDC* MemDC, const point& PointA, const point& PointB,
		                   const point& PointC, const int& object_index, const RECT& rect,
						   const int& unit_u, const int& unit_v, const Matrix& ModelingMatrix,
						   const point PointLightUVN[], const Vector& FacetNormal, const point& CenterPoint, 
						   const int& corner_a, const int& corner_b, const int& corner_c);

	void    SetWireframePen(CPen& pen, const int& object_index, const double& distance);

	void	GenerateSolidFacetColor(CPen& pen, CBrush& brush, const int& object_index,
		                            const point PointLightUVN[],
							        const Vector& FacetNormal, const point& CenterPoint);

	void    GenerateAmbientColorValues(double& AmbientRed, double& AmbientGreen,
		                               double& AmbientBlue, const int& object_index);

    void    GenerateDiffuseColorValues(double& DiffuseRed, double& DiffuseGreen, double& DiffuseBlue, 
									   const int& object_index, const int& light_index, 
									   const Vector& FacetNormal, const Vector& LightVector, 
									   const double& distance);

    void    GenerateSpecularColorValues(double& SpecularRed, double& SpecularGreen, double& SpecularBlue, 
									    const int& object_index, const int& light_index, 
									    const Vector& FacetNormal, const Vector& LightVector, 
									    const Vector& HVector, const double& distance);

	void    SetLightAndObserverVectors(Vector& LightVector, Vector& ObserverVector, 
		                               Vector& HVector, const point PointLightUVN[], 
									   const point& FacetPoint, const int& light_index,
									   double& distance);

	void    GetUnitVectorPixels(const RECT& rect, int& unit_u_pixels, int& unit_v_pixels);

	void    GetMaxAndMinDistances(double& max, double& min);

	void    NormalizeFinalColorValues(double& IRed, double& IGreen, double& IBlue);

	void    InterpolateDepthCueFacetColor(const double& distance, const double& max, 
		                                  const double& min, COLORREF& pen_color);

	void    GetLightPosition(const int& light_num, CString& EditBoxXString, 
		                              CString& EditBoxYString, CString& EditBoxZString);

	void    AddPointLight(int light_num);

	void    UpdateMaterialsFromEditor();

	void    UpdateMaterialPropertyPagesFromMaterials();

	void    ResetZBuffer();

	void    ResetFacetEdgeList();

	void    GenerateEdgeList(const point& PointA, const point& PointB, const point& PointC,
		                     const int& unit_u, const int& unit_v, const RECT& rect,
							 const double& IRed_A, const double& IGreen_A, const double& IBlue_A,
							 const double& IRed_B, const double& IGreen_B, const double& IBlue_B,
							 const double& IRed_C, const double& IGreen_C, const double& IBlue_C,
							 const Vector& VertexNormalA, const Vector& VertexNormalB, 
							 const Vector& VertexNormalC, const int& DISPLAY_TYPE);

	void    AddLineToEdgeList(const int& start_x, const int& start_y, const int& end_x,   
						const int& end_y, const double& start_IRed, const double& start_IGreen, 
						const double& start_IBlue, const double& end_IRed, const double& end_IGreen, 
						const double& end_IBlue, const Vector& StartNormal, const Vector& EndNormal, 
						const double& start_depth, const double& end_depth, const int& DISPLAY_TYPE);

	void    AddPointToEdgeList(const int& x, const int& y, const double& IRed, 
		                       const double& IGreen, const double& IBlue, 
							   const Vector& PixelNormal, const double& depth, const int& DISPLAY_TYPE);

	void    CalculatePointIntensity(const point& Point, const int& object_index, 
		                            const point PointLightUVN[], const Vector& VertexNormal,
		                            double& IRed, double& IGreen, double& IBlue);

	void    SetPointLightUVNCoordinates(point PointLightUVN[], const Matrix& ModelingMatrix);

	bool    TestZBuffer(const int& x, const int& y, const double& test_depth);

	void    OutputEdgeListToFile(int a_x, int a_y, int b_x, int b_y, int c_x, int c_y,
							     const double& IRed_A, const double& IGreen_A, const double& IBlue_A,
							     const double& IRed_B, const double& IGreen_B, const double& IBlue_B,
							     const double& IRed_C, const double& IGreen_C, const double& IBlue_C);




	// dialog boxes 
	CViewParameters              m_ViewParametersDialog;
	CTransformationParameters    m_TransformationParametersDialog;
	CLineThickness               m_LineThicknessDialog;
	CBackgroundColor             m_BackgroundColorDialog;
	CAmbientLightProperties      m_AmbientLightPropertiesDialog;
	CPointLightParameters        m_PointLightParameters[5];
	CMaterialSelectorDialog      m_MaterialSelectorDialog;
	CZBufferParameters           m_ZBufferParametersDialog;

	CPropertySheet               m_MaterialPropertiesSheets;
	CMaterialPropertyPage        m_MaterialPropertyPages[NUM_MATERIALS];

	// View variables
	int                          m_DisplayType;
	bool                         m_DrawAxis;
	bool                         m_MouseCameraPanEnable;
	CPoint                       m_LastMousePosition;

	std::vector<Material>        m_Materials;

	std::vector<vector<double> > m_ZBuffer;
	



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	
	bool UncheckAllDisplayModes();

	virtual ~CHomework2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHomework2View)
	afx_msg void OnObjectManager();
	afx_msg void OnTransformationParameters();
	afx_msg void OnViewPalette();
	afx_msg void OnProjectionMethod();
	afx_msg void OnWireFrame();
	afx_msg void OnWireFrameDepthCue();
	afx_msg void OnWireFrameBackfaceElimination();
	afx_msg void OnPaintersAlgorithm();
	afx_msg void OnOptionsLinethickness();
	afx_msg void OnOptionsBackgroundcolor();
	afx_msg void OnMaterialSelector();
	afx_msg void OnPaintersAlgorithmTracedFacets();
	afx_msg void OnAmbientLightProperties();
	afx_msg void OnPointLight1();
	afx_msg void OnPointLight2();
	afx_msg void OnPointLight3();
	afx_msg void OnPointLight4();
	afx_msg void OnPointLight5();
	afx_msg void OnDrawAxis();
	afx_msg void OnGouraudShading();
	afx_msg void OnPhongShading();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseCameraPan();
	afx_msg void OnMaterialEditor();
	afx_msg void OnZBufferParameters();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in homework2View.cpp
inline CHomework2Doc* CHomework2View::GetDocument()
   { return (CHomework2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK2VIEW_H__3FE73463_E226_42D6_86D2_6CD683E7E9DD__INCLUDED_)
