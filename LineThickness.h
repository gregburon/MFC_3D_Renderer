



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



#if !defined(AFX_LINETHICKNESS_H__CFF23F94_3CB6_470A_B557_942DD6E13F79__INCLUDED_)
#define AFX_LINETHICKNESS_H__CFF23F94_3CB6_470A_B557_942DD6E13F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineThickness.h : header file
//


class CLineThickness : public CDialog
{
// Construction
public:
	CLineThickness(CWnd* pParent = NULL);   // standard constructor

	CHomework2Doc* pDoc;

	int       m_Thickness;


// Dialog Data
	//{{AFX_DATA(CLineThickness)
	enum { IDD = IDD_LINE_THICKNESS_DIALOG };
	CSliderCtrl	m_LineThicknessSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineThickness)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineThickness)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINETHICKNESS_H__CFF23F94_3CB6_470A_B557_942DD6E13F79__INCLUDED_)
