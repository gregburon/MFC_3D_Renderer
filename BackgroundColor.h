



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

#if !defined(AFX_BACKGROUNDCOLOR_H__BCE9D4DD_610C_4177_A6DF_75244B838AEC__INCLUDED_)
#define AFX_BACKGROUNDCOLOR_H__BCE9D4DD_610C_4177_A6DF_75244B838AEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackgroundColor.h : header file
//


class CBackgroundColor : public CDialog
{
// Construction
public:

	CHomework2Doc* pDoc;

	void SetDisplayValues(int red, int green, int blue);

	CBackgroundColor(CWnd* pParent = NULL);   // standard constructor


	int               m_BackgroundRedValue;
	int               m_BackgroundGreenValue;
	int               m_BackgroundBlueValue;

// Dialog Data
	//{{AFX_DATA(CBackgroundColor)
	enum { IDD = IDD_BACKGROUND_COLOR_DIALOG };
	CSliderCtrl	m_BackgroundColorRedSlider;
	CSliderCtrl	m_BackgroundColorGreenSlider;
	CSliderCtrl	m_BackgroundColorBlueSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackgroundColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackgroundColor)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKGROUNDCOLOR_H__BCE9D4DD_610C_4177_A6DF_75244B838AEC__INCLUDED_)
