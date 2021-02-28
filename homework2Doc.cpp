

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
#include "homework2.h"

#include "homework2Doc.h"
#include "ViewParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CHomework2Doc, CDocument)

BEGIN_MESSAGE_MAP(CHomework2Doc, CDocument)
	//{{AFX_MSG_MAP(CHomework2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CHomework2Doc::CHomework2Doc()
{
	/*
	m_CurrentObject = -1;
	m_ProjectionMethod = PARALLEL;
	*/

	m_CurrentObject = -1;
	m_ProjectionMethod = PERSPECTIVE;
}

CHomework2Doc::~CHomework2Doc()
{
}

BOOL CHomework2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHomework2Doc serialization

void CHomework2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHomework2Doc diagnostics

#ifdef _DEBUG
void CHomework2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHomework2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHomework2Doc commands
