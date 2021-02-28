
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
#include "AmbientLightProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




CAmbientLightProperties::CAmbientLightProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CAmbientLightProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAmbientLightProperties)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_AmbientRed		= 128;
	m_AmbientGreen		= 128;
	m_AmbientBlue		= 128;
}


void CAmbientLightProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmbientLightProperties)
	DDX_Control(pDX, IDC_AMBIENT_RED_SLIDER, m_AmbientRedSlider);
	DDX_Control(pDX, IDC_AMBIENT_GREEN_SLIDER, m_AmbientGreenSlider);
	DDX_Control(pDX, IDC_AMBIENT_BLUE_SLIDER, m_AmbientBlueSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmbientLightProperties, CDialog)
	//{{AFX_MSG_MAP(CAmbientLightProperties)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CAmbientLightProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString msg;

	m_AmbientRedSlider.SetRange(0, 255);
	m_AmbientRedSlider.SetTic(25);
	m_AmbientRedSlider.SetTic(50);
	m_AmbientRedSlider.SetTic(75);
	m_AmbientRedSlider.SetTic(100);
	m_AmbientRedSlider.SetTic(125);
	m_AmbientRedSlider.SetTic(150);
	m_AmbientRedSlider.SetTic(175);
	m_AmbientRedSlider.SetTic(200);
	m_AmbientRedSlider.SetTic(225);
	m_AmbientRedSlider.SetPos(m_AmbientRed);
	msg.Format("%d", m_AmbientRed);
	SetDlgItemText(IDC_AMBIENT_RED_DISPLAY, msg);

	m_AmbientGreenSlider.SetRange(0, 255);
	m_AmbientGreenSlider.SetTic(25);
	m_AmbientGreenSlider.SetTic(50);
	m_AmbientGreenSlider.SetTic(75);
	m_AmbientGreenSlider.SetTic(100);
	m_AmbientGreenSlider.SetTic(125);
	m_AmbientGreenSlider.SetTic(150);
	m_AmbientGreenSlider.SetTic(175);
	m_AmbientGreenSlider.SetTic(200);
	m_AmbientGreenSlider.SetTic(225);
	m_AmbientGreenSlider.SetPos(m_AmbientGreen);
	msg.Format("%d", m_AmbientGreen);
	SetDlgItemText(IDC_AMBIENT_GREEN_DISPLAY, msg);

	m_AmbientBlueSlider.SetRange(0, 255);
	m_AmbientBlueSlider.SetTic(25);
	m_AmbientBlueSlider.SetTic(50);
	m_AmbientBlueSlider.SetTic(75);
	m_AmbientBlueSlider.SetTic(100);
	m_AmbientBlueSlider.SetTic(125);
	m_AmbientBlueSlider.SetTic(150);
	m_AmbientBlueSlider.SetTic(175);
	m_AmbientBlueSlider.SetTic(200);
	m_AmbientBlueSlider.SetTic(225);
	m_AmbientBlueSlider.SetPos(m_AmbientBlue);
	msg.Format("%d", m_AmbientBlue);
	SetDlgItemText(IDC_AMBIENT_BLUE_DISPLAY, msg);
	
	return TRUE;
}

void CAmbientLightProperties::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	int ScrollID    = pScrollBar->GetDlgCtrlID();
	CString msg;

	switch(ScrollID)
	{
	case IDC_AMBIENT_RED_SLIDER:
		m_AmbientRed = m_AmbientRedSlider.GetPos();
		msg.Format("%d", m_AmbientRed);
		SetDlgItemText(IDC_AMBIENT_RED_DISPLAY, msg);
		break;

	case IDC_AMBIENT_GREEN_SLIDER:
		m_AmbientGreen = m_AmbientGreenSlider.GetPos();
		msg.Format("%d", m_AmbientGreen);
		SetDlgItemText(IDC_AMBIENT_GREEN_DISPLAY, msg);
		break;

	case IDC_AMBIENT_BLUE_SLIDER:
		m_AmbientBlue  = m_AmbientBlueSlider.GetPos();
		msg.Format("%d", m_AmbientBlue);
		SetDlgItemText(IDC_AMBIENT_BLUE_DISPLAY, msg);
		break;
	}// end switch

	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);

}

void CAmbientLightProperties::OnOK() 
{
	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);
	
	CDialog::OnOK();
}
