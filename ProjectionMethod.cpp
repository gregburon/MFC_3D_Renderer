

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
#include "homework2View.h"
#include "ViewParameters.h"
#include "Camera.h"
#include "ProjectionMethod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




CProjectionMethod::CProjectionMethod(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectionMethod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectionMethod)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProjectionMethod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectionMethod)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectionMethod, CDialog)
	//{{AFX_MSG_MAP(CProjectionMethod)
	ON_BN_CLICKED(IDC_PARALLEL_PROJECTION, OnParallelProjection)
	ON_BN_CLICKED(IDC_PERSPECTIVE_PROJECTION, OnPerspectiveProjection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/********************************************************/
/*                                                      */
/*   Projection Method Dialog Box Message Handlers.     */
/*                                                      */
/********************************************************/

BOOL CProjectionMethod::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int value = 0;

	if(m_ProjectionMethod == PARALLEL)
	{
		value = IDC_PARALLEL_PROJECTION;
	}// end if
	else if(m_ProjectionMethod == PERSPECTIVE)
	{
		value = IDC_PERSPECTIVE_PROJECTION;
	}// end else

	// Set the current selection to the m_ProjectionMethod value.
	CheckRadioButton(IDC_PARALLEL_PROJECTION, 
		             IDC_PERSPECTIVE_PROJECTION, 
					 value);
	return TRUE;  
}


void CProjectionMethod::OnParallelProjection() 
{
	m_ProjectionMethod = PARALLEL;	
}

void CProjectionMethod::OnPerspectiveProjection() 
{
	m_ProjectionMethod = PERSPECTIVE;
}
