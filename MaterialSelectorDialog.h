
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



#if !defined(AFX_MATERIALSELECTORDIALOG_H__C6F8D729_0370_4208_8C3F_A4CA95BD9B9C__INCLUDED_)
#define AFX_MATERIALSELECTORDIALOG_H__C6F8D729_0370_4208_8C3F_A4CA95BD9B9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialSelectorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterialSelectorDialog dialog

class CMaterialSelectorDialog : public CDialog
{
// Construction
public:
	CMaterialSelectorDialog(CWnd* pParent = NULL);   // standard constructor

	CHomework2Doc* pDoc;

	vector<string>   m_MaterialNames;

	void SetRadioButtonMaterialNames();

// Dialog Data
	//{{AFX_DATA(CMaterialSelectorDialog)
	enum { IDD = IDD_MATERIAL_SELECTOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialSelectorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialSelectorDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnMaterialRadio1();
	afx_msg void OnMaterialRadio2();
	afx_msg void OnMaterialRadio3();
	afx_msg void OnMaterialRadio4();
	afx_msg void OnMaterialRadio5();
	afx_msg void OnMaterialRadio6();
	afx_msg void OnMaterialRadio7();
	afx_msg void OnMaterialRadio8();
	afx_msg void OnMaterialRadio9();
	afx_msg void OnMaterialRadio10();
	afx_msg void OnMaterialRadio11();
	afx_msg void OnMaterialRadio12();
	afx_msg void OnMaterialRadio13();
	afx_msg void OnMaterialRadio14();
	afx_msg void OnMaterialRadio15();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALSELECTORDIALOG_H__C6F8D729_0370_4208_8C3F_A4CA95BD9B9C__INCLUDED_)
