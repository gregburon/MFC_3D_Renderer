



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

#include "stdafx.h"
#include "homework2.h"
#include "BackgroundColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




CBackgroundColor::CBackgroundColor(CWnd* pParent /*=NULL*/)
	: CDialog(CBackgroundColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackgroundColor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

		m_BackgroundRedValue     = 0;
		m_BackgroundGreenValue   = 0;
		m_BackgroundBlueValue    = 0;
}


void CBackgroundColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackgroundColor)
	DDX_Control(pDX, IDC_BACKGROUND_COLOR_RED_SLIDER, m_BackgroundColorRedSlider);
	DDX_Control(pDX, IDC_BACKGROUND_COLOR_GREEN_SLIDER, m_BackgroundColorGreenSlider);
	DDX_Control(pDX, IDC_BACKGROUND_COLOR_BLUE_SLIDER, m_BackgroundColorBlueSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackgroundColor, CDialog)
	//{{AFX_MSG_MAP(CBackgroundColor)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/********************************************************/
/*                                                      */
/*   Background Color Dialog Box Message Handlers.      */
/*                                                      */
/********************************************************/

BOOL CBackgroundColor::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Set the ranges for the sliders.
	m_BackgroundColorRedSlider.SetRange(0, 255);
	m_BackgroundColorGreenSlider.SetRange(0, 255);
	m_BackgroundColorBlueSlider.SetRange(0, 255);

	// Set the tick size.
	m_BackgroundColorRedSlider.SetTic(1);
	m_BackgroundColorGreenSlider.SetTic(1);
	m_BackgroundColorBlueSlider.SetTic(1);

	// Set the initial position.
	m_BackgroundColorRedSlider.SetPos(0);
	m_BackgroundColorGreenSlider.SetPos(0);
	m_BackgroundColorBlueSlider.SetPos(0);

	
	// Set the messages for each slider.
	SetDisplayValues(0, 0, 0);

	return TRUE;  
}

void CBackgroundColor::SetDisplayValues(int red, int green, int blue)
{
	CString msg;

	msg.Format("%d", red);
	SetDlgItemText(IDC_BACKGROUND_COLOR_RED_VALUE_DISPLAY, msg);

	msg.Format("%d", green);
	SetDlgItemText(IDC_BACKGROUND_COLOR_GREEN_VALUE_DISPLAY, msg);

	msg.Format("%d", blue);
	SetDlgItemText(IDC_BACKGROUND_COLOR_BLUE_VALUE_DISPLAY, msg);
}

void CBackgroundColor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Get the Scrollbar ID.
	int ScrollID = pScrollBar->GetDlgCtrlID();

	switch(ScrollID)
	{
	case IDC_BACKGROUND_COLOR_RED_SLIDER:
		m_BackgroundRedValue = m_BackgroundColorRedSlider.GetPos();
		break;
	case IDC_BACKGROUND_COLOR_GREEN_SLIDER:
		m_BackgroundGreenValue = m_BackgroundColorGreenSlider.GetPos();
		break;
	case IDC_BACKGROUND_COLOR_BLUE_SLIDER:
		m_BackgroundBlueValue = m_BackgroundColorBlueSlider.GetPos();
		break;
	}// end switch

	SetDisplayValues(m_BackgroundRedValue, m_BackgroundGreenValue, m_BackgroundBlueValue);

	GetParentFrame()->GetActiveView()->Invalidate(false);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
