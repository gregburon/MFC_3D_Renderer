

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

#if !defined(AFX_ZBUFFERPARAMETERS_H__234E504E_E711_4826_BBA1_25E4E265A0E9__INCLUDED_)
#define AFX_ZBUFFERPARAMETERS_H__234E504E_E711_4826_BBA1_25E4E265A0E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZBufferParameters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZBufferParameters dialog

class CZBufferParameters : public CDialog
{
// Construction
public:
	CZBufferParameters(CWnd* pParent = NULL);   // standard constructor


	int u_min;
	int u_max;
	int v_min;
	int v_max;

	double z_near;
	double z_far;

	int  screen_rows;
	int  screen_cols;

// Dialog Data
	//{{AFX_DATA(CZBufferParameters)
	enum { IDD = IDD_Z_BUFFER_PARAMETERS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZBufferParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZBufferParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeZBufferUMaxEditBox();
	afx_msg void OnChangeZBufferUMinEditBox();
	afx_msg void OnChangeZBufferVMaxEditBox();
	afx_msg void OnChangeZBufferVMinEditBox();
	afx_msg void OnChangeZBufferZFarEditBox();
	afx_msg void OnChangeZBufferZNearEditBox();
	afx_msg void OnChangeZBufferScreenColumnsEditBox();
	afx_msg void OnChangeZBufferScreenRowsEditBox();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZBUFFERPARAMETERS_H__234E504E_E711_4826_BBA1_25E4E265A0E9__INCLUDED_)
