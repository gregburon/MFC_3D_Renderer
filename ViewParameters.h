


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
#include "homework2Doc.h"
#include <vector>
#include <string>
#include "defines.h"
#include "Vector.h"
#include "Camera.h"

#if !defined(AFX_VIEWPARAMETERS_H__431C1283_BC30_48D1_91F5_88FCAEB3CDF4__INCLUDED_)
#define AFX_VIEWPARAMETERS_H__431C1283_BC30_48D1_91F5_88FCAEB3CDF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewParameters.h : header file
//





class CViewParameters : public CDialog
{
// Construction
public:

	CHomework2Doc* GetDocument();

	CViewParameters(CWnd* pParent = NULL);   // standard constructor
	CHomework2Doc* pDoc;
	Camera   m_Camera;
	
	void SetSliderDefaultValues();
	void SetSliderDisplayValues();
	void SetSliderInitialDisplayValues();
	bool SetScrollInfo(SCROLLINFO& info, int ScrollID, int max, int min, int pos);

	void ModifyCameraViewReferencePointX(double value);
	void ModifyCameraViewReferencePointY(double value);
	void ModifyCameraViewReferencePointZ(double value);
	void ModifyCameraViewPlaneNormalX(double value);
	void ModifyCameraViewPlaneNormalY(double value);
	void ModifyCameraViewPlaneNormalZ(double value);
	void ModifyCameraViewUpVectorX(double value);
	void ModifyCameraViewUpVectorY(double value);
	void ModifyCameraViewUpVectorZ(double value);
	void ModifyCameraCenterOfProjectionU(double value);
	void ModifyCameraCenterOfProjectionV(double value);
	void ModifyCameraCenterOfProjectionN(double value);

	double GetLastPosition(int ScrollID);

// Dialog Data
	//{{AFX_DATA(CViewParameters)
	enum { IDD = IDD_VIEW_PARAMETERS_DIALOG };
	CScrollBar	m_ViewUpVectorZSlider;
	CScrollBar	m_ViewUpVectorYSlider;
	CScrollBar	m_ViewUpVectorXSlider;
	CScrollBar	m_ViewReferencePointZSlider;
	CScrollBar	m_ViewReferencePointYSlider;
	CScrollBar	m_ViewReferencePointXSlider;
	CScrollBar	m_ViewPlaneNormalZSlider;
	CScrollBar	m_ViewPlaneNormalYSlider;
	CScrollBar	m_ViewPlaneNormalXSlider;
	CScrollBar	m_CenterOfProjectionVSlider;
	CScrollBar	m_CenterOfProjectionUSlider;
	CScrollBar	m_CenterOfProjectionNSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPARAMETERS_H__431C1283_BC30_48D1_91F5_88FCAEB3CDF4__INCLUDED_)
