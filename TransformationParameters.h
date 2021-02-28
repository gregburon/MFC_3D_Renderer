

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
#include "Camera.h"



#if !defined(AFX_TRANSFORMATIONPARAMETERS_H__FAD3A4AF_10F3_42E5_A807_468F255A902B__INCLUDED_)
#define AFX_TRANSFORMATIONPARAMETERS_H__FAD3A4AF_10F3_42E5_A807_468F255A902B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransformationParameters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransformationParameters dialog

class CTransformationParameters : public CDialog
{
// Construction
public:
	void SetSliderPositions();
	void SetScrollBarDisplayInformation(int DisplayID, double pos);
	bool SetScrollInfo(SCROLLINFO& info, int ScrollID, int max, int min, int pos);
	CTransformationParameters(CWnd* pParent = NULL);   // standard constructor
	void SetSliderDisplayValues();
	CHomework2Doc* pDoc;

	void ModifyObjectRotationX(double value);
	void ModifyObjectRotationY(double value);
	void ModifyObjectRotationZ(double value);
	void ModifyObjectScaleX(double value);
	void ModifyObjectScaleY(double value);
	void ModifyObjectScaleZ(double value);
	void ModifyObjectShearX(double value);
	void ModifyObjectShearY(double value);
	void ModifyObjectShearZ(double value);
	void ModifyObjectTranslationX(double value);
	void ModifyObjectTranslationY(double value);
	void ModifyObjectTranslationZ(double value);

	double GetLastPosition(int ScrollID);

// Dialog Data
	//{{AFX_DATA(CTransformationParameters)
	enum { IDD = IDD_TRANSFORMATION_DIALOG };
	CScrollBar	m_TranslationZScrollBar;
	CScrollBar	m_TranslationYScrollBar;
	CScrollBar	m_TranslationXScrollBar;
	CScrollBar	m_ShearZScrollBar;
	CScrollBar	m_ShearYScrollBar;
	CScrollBar	m_ShearXScrollBar;
	CScrollBar	m_ScaleZScrollBar;
	CScrollBar	m_ScaleYScrollBar;
	CScrollBar	m_ScaleXScrollBar;
	CScrollBar	m_RotationYScrollBar;
	CScrollBar	m_RotationXScrollBar;
	CScrollBar	m_RotationZScrollBar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformationParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransformationParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMATIONPARAMETERS_H__FAD3A4AF_10F3_42E5_A807_468F255A902B__INCLUDED_)
