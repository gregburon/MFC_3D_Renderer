

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


#if !defined(AFX_POINTLIGHTPARAMETERS_H__43BEFE99_AB52_4AFC_BCF0_111BF71783DC__INCLUDED_)
#define AFX_POINTLIGHTPARAMETERS_H__43BEFE99_AB52_4AFC_BCF0_111BF71783DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointLightParameters.h : header file
//

class CPointLightParameters : public CDialog
{
// Construction
public:
	CPointLightParameters(CWnd* pParent = NULL);   // standard constructor

	void	SetHeaderString(int light_num);

	CHomework2Doc*		pDoc;

	bool				m_Active;
	bool				m_RenderAsObject;

	int					m_PointLightRed;
	int					m_PointLightGreen;
	int					m_PointLightBlue;




// Dialog Data
	//{{AFX_DATA(CPointLightParameters)
	enum { IDD = IDD_POINT_LIGHT_DIALOG };
	CEdit	m_PointLightZEditBox;
	CEdit	m_PointLightYEditBox;
	CEdit	m_PointLightXEditBox;
	CSliderCtrl	m_PointLightRedSlider;
	CSliderCtrl	m_PointLightGreenSlider;
	CSliderCtrl	m_PointLightBlueSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointLightParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointLightParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPointLightActiveButton();
	virtual void OnOK();
	afx_msg void OnUpdatePointLightXEdit();
	afx_msg void OnUpdatePointLightYEdit();
	afx_msg void OnUpdatePointLightZEdit();
	afx_msg void OnPointLightAsObjectButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTLIGHTPARAMETERS_H__43BEFE99_AB52_4AFC_BCF0_111BF71783DC__INCLUDED_)
