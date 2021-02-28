

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

#include "homework2Doc.h"
#include <vector>
#include <string>


#if !defined(AFX_AMBIENTLIGHTPROPERTIES_H__9B5CE901_A0E4_4BEE_AE0C_921E9BF3C557__INCLUDED_)
#define AFX_AMBIENTLIGHTPROPERTIES_H__9B5CE901_A0E4_4BEE_AE0C_921E9BF3C557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmbientLightProperties.h : header file
//

class CAmbientLightProperties : public CDialog
{
// Construction
public:
	CAmbientLightProperties(CWnd* pParent = NULL);   // standard constructor


	CHomework2Doc*		pDoc;

	int					m_AmbientRed;
	int					m_AmbientGreen;
	int					m_AmbientBlue;

// Dialog Data
	//{{AFX_DATA(CAmbientLightProperties)
	enum { IDD = IDD_AMBIENT_LIGHT_DIALOG };
	CSliderCtrl	m_AmbientRedSlider;
	CSliderCtrl	m_AmbientGreenSlider;
	CSliderCtrl	m_AmbientBlueSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmbientLightProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAmbientLightProperties)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMBIENTLIGHTPROPERTIES_H__9B5CE901_A0E4_4BEE_AE0C_921E9BF3C557__INCLUDED_)
