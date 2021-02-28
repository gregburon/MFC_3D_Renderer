

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

#include <vector>
#include <string>
#include "defines.h"
#include "Object3D.h"
#include "Camera.h"
#include "EdgeListNode.h"


#if !defined(AFX_HOMEWORK2DOC_H__28934C24_4EAC_4623_A8F0_1CB0732A77B4__INCLUDED_)
#define AFX_HOMEWORK2DOC_H__28934C24_4EAC_4623_A8F0_1CB0732A77B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHomework2Doc : public CDocument
{
protected: // create from serialization only
	CHomework2Doc();
	DECLARE_DYNCREATE(CHomework2Doc)

// Attributes
public:
	vector<string>    m_ObjectFileNames;
	vector<Object3D>  m_Objects;
	Camera            m_Camera;

	int               m_CurrentObject;	// index into m_Objects vector
	int               m_CurSel;
	int               m_ProjectionMethod;

	std::vector<EdgeListNode > m_EdgeListVector;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHomework2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHomework2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK2DOC_H__28934C24_4EAC_4623_A8F0_1CB0732A77B4__INCLUDED_)
