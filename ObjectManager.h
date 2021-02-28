#if !defined(AFX_OBJECTMANAGER_H__34095AAD_53A4_49C1_82A7_5A8282E85BAE__INCLUDED_)
#define AFX_OBJECTMANAGER_H__34095AAD_53A4_49C1_82A7_5A8282E85BAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectManager.h : header file
//

#include <typeinfo.h>

using namespace std;

#include <vector>
#include <string>
#include "homework2Doc.h"
#include "Vector.h"

/////////////////////////////////////////////////////////////////////////////
// CObjectManager dialog

class CObjectManager : public CDialog
{
// Construction
public:
	CObjectManager(CWnd* pParent = NULL);   // standard constructor

	vector<string>    m_ObjectFileNames;
    int               m_CurSel;
	CHomework2Doc*    pDoc;
	Camera            m_Camera;

	void UpdateDisplayedObjectsListBox();
	void UpdateCurrentObjectComboBox();


// Dialog Data
	//{{AFX_DATA(CObjectManager)
	enum { IDD = IDD_OBJECT_MANAGER_DIALOG };
	CComboBox	m_CurrentObjectComboBox;
	CListBox	m_DisplayedObjectsListBox;
	CButton	m_DeleteCurrentObjectButton;
	CButton	m_DeleteAllObjectsButton;
	CButton	m_AddObjectButton;
	CComboBox	m_AddObjectComboBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectManager)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectManager)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddObjectButton();
	afx_msg void OnSelchangeAddObjectComboBox();
	afx_msg void OnSelchangeCurrentObjectCombo();
	afx_msg void OnDeleteCurrentObject();
	afx_msg void OnDeleteAllObjects();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTMANAGER_H__34095AAD_53A4_49C1_82A7_5A8282E85BAE__INCLUDED_)
