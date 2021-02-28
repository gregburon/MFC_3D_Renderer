


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


#if !defined(AFX_PROJECTIONMETHOD_H__C9DC0793_118D_4AE5_8C90_BFB498187C4F__INCLUDED_)
#define AFX_PROJECTIONMETHOD_H__C9DC0793_118D_4AE5_8C90_BFB498187C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectionMethod.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectionMethod dialog

class CProjectionMethod : public CDialog
{
// Construction
public:
	CProjectionMethod(CWnd* pParent = NULL);   // standard constructor

	int m_ProjectionMethod;

// Dialog Data
	//{{AFX_DATA(CProjectionMethod)
	enum { IDD = IDD_PROJECTION_METHOD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectionMethod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectionMethod)
	virtual BOOL OnInitDialog();
	afx_msg void OnParallelProjection();
	afx_msg void OnPerspectiveProjection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTIONMETHOD_H__C9DC0793_118D_4AE5_8C90_BFB498187C4F__INCLUDED_)
