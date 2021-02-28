


/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#pragma warning(disable: 4786)

using namespace std;

#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "defines.h"


#include "homework2.h"
#include "LineThickness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




CLineThickness::CLineThickness(CWnd* pParent /*=NULL*/)
	: CDialog(CLineThickness::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineThickness)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Thickness = 1;
}


void CLineThickness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineThickness)
	DDX_Control(pDX, IDC_LINE_THICKNESS_SLIDER, m_LineThicknessSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineThickness, CDialog)
	//{{AFX_MSG_MAP(CLineThickness)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





/********************************************************/
/*                                                      */
/*   Line Thickness Dialog Box Message Handlers.        */
/*                                                      */
/********************************************************/


BOOL CLineThickness::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_LineThicknessSlider.SetRange(1, 10);
	m_LineThicknessSlider.SetTic(1);
	m_LineThicknessSlider.SetPos(m_Thickness);

	CString msg;
	msg.Format("%d", m_Thickness);
	SetDlgItemText(IDC_LINE_THICKNESS_DISPLAY, msg);

	
	return TRUE;
}


void CLineThickness::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Thickness = m_LineThicknessSlider.GetPos();

	CString msg;
	msg.Format("%d", m_Thickness);
	SetDlgItemText(IDC_LINE_THICKNESS_DISPLAY, msg);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
