
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
#include "PointLightParameters.h"

#include <io.h>
#include <fstream>
#include <string.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CPointLightParameters::CPointLightParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CPointLightParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointLightParameters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Active                = false;
	m_RenderAsObject        = false;

	m_PointLightRed			= 255;
	m_PointLightGreen		= 255;
	m_PointLightBlue		= 255;
}


void CPointLightParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointLightParameters)
	DDX_Control(pDX, IDC_POINT_LIGHT_Z_EDIT, m_PointLightZEditBox);
	DDX_Control(pDX, IDC_POINT_LIGHT_Y_EDIT, m_PointLightYEditBox);
	DDX_Control(pDX, IDC_POINT_LIGHT_X_EDIT, m_PointLightXEditBox);
	DDX_Control(pDX, IDC_POINT_LIGHT_RED_SLIDER, m_PointLightRedSlider);
	DDX_Control(pDX, IDC_POINT_LIGHT_GREEN_SLIDER, m_PointLightGreenSlider);
	DDX_Control(pDX, IDC_POINT_LIGHT_BLUE_SLIDER, m_PointLightBlueSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointLightParameters, CDialog)
	//{{AFX_MSG_MAP(CPointLightParameters)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_POINT_LIGHT_ACTIVE_BUTTON, OnPointLightActiveButton)
	ON_EN_UPDATE(IDC_POINT_LIGHT_X_EDIT, OnUpdatePointLightXEdit)
	ON_EN_UPDATE(IDC_POINT_LIGHT_Y_EDIT, OnUpdatePointLightYEdit)
	ON_EN_UPDATE(IDC_POINT_LIGHT_Z_EDIT, OnUpdatePointLightZEdit)
	ON_BN_CLICKED(IDC_POINT_LIGHT_AS_OBJECT_BUTTON, OnPointLightAsObjectButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CPointLightParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set the edit boxes with initial values.
	CString EditString;

	EditString.Format("%4.1f", 25.0);
	SetDlgItemText(IDC_POINT_LIGHT_X_EDIT, EditString);
	SetDlgItemText(IDC_POINT_LIGHT_Y_EDIT, EditString);

	EditString.Format("%4.1f", 25.0);
	SetDlgItemText(IDC_POINT_LIGHT_Z_EDIT, EditString);

	CString msg;

	m_PointLightRedSlider.SetRange(0, 255);
	m_PointLightRedSlider.SetTic(25);
	m_PointLightRedSlider.SetTic(50);
	m_PointLightRedSlider.SetTic(75);
	m_PointLightRedSlider.SetTic(100);
	m_PointLightRedSlider.SetTic(125);
	m_PointLightRedSlider.SetTic(150);
	m_PointLightRedSlider.SetTic(175);
	m_PointLightRedSlider.SetTic(200);
	m_PointLightRedSlider.SetTic(225);
	m_PointLightRedSlider.SetPos(m_PointLightRed);
	msg.Format("%d", m_PointLightRed);
	SetDlgItemText(IDC_POINT_LIGHT_RED_DISPLAY, msg);

	m_PointLightGreenSlider.SetRange(0, 255);
	m_PointLightGreenSlider.SetTic(25);
	m_PointLightGreenSlider.SetTic(50);
	m_PointLightGreenSlider.SetTic(75);
	m_PointLightGreenSlider.SetTic(100);
	m_PointLightGreenSlider.SetTic(125);
	m_PointLightGreenSlider.SetTic(150);
	m_PointLightGreenSlider.SetTic(175);
	m_PointLightGreenSlider.SetTic(200);
	m_PointLightGreenSlider.SetTic(225);
	m_PointLightGreenSlider.SetPos(m_PointLightGreen);
	msg.Format("%d", m_PointLightGreen);
	SetDlgItemText(IDC_POINT_LIGHT_GREEN_DISPLAY, msg);

	m_PointLightBlueSlider.SetRange(0, 255);
	m_PointLightBlueSlider.SetTic(25);
	m_PointLightBlueSlider.SetTic(50);
	m_PointLightBlueSlider.SetTic(75);
	m_PointLightBlueSlider.SetTic(100);
	m_PointLightBlueSlider.SetTic(125);
	m_PointLightBlueSlider.SetTic(150);
	m_PointLightBlueSlider.SetTic(175);
	m_PointLightBlueSlider.SetTic(200);
	m_PointLightBlueSlider.SetTic(225);
	m_PointLightBlueSlider.SetPos(m_PointLightBlue);
	msg.Format("%d", m_PointLightBlue);
	SetDlgItemText(IDC_POINT_LIGHT_BLUE_DISPLAY, msg);

	return TRUE;
}

void CPointLightParameters::SetHeaderString(int light_num)
{
	CString HeaderString;
	HeaderString.Format("Point light %d:\nSet the location and light intensities for this point light.", light_num);
	SetDlgItemText(IDC_POINT_LIGHT_HEADER_DISPLAY, HeaderString);

}

void CPointLightParameters::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	int ScrollID    = pScrollBar->GetDlgCtrlID();
	CString msg;

	switch(ScrollID)
	{
	case IDC_POINT_LIGHT_RED_SLIDER:
		m_PointLightRed = m_PointLightRedSlider.GetPos();
		msg.Format("%d", m_PointLightRed);
		SetDlgItemText(IDC_POINT_LIGHT_RED_DISPLAY, msg);
		break;

	case IDC_POINT_LIGHT_GREEN_SLIDER:
		m_PointLightGreen = m_PointLightGreenSlider.GetPos();
		msg.Format("%d", m_PointLightGreen);
		SetDlgItemText(IDC_POINT_LIGHT_GREEN_DISPLAY, msg);
		break;

	case IDC_POINT_LIGHT_BLUE_SLIDER:
		m_PointLightBlue  = m_PointLightBlueSlider.GetPos();
		msg.Format("%d", m_PointLightBlue);
		SetDlgItemText(IDC_POINT_LIGHT_BLUE_DISPLAY, msg);
		break;
	}// end switch

	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CPointLightParameters::OnPointLightActiveButton() 
{
	if(m_Active == false)
	{
		CheckRadioButton(IDC_POINT_LIGHT_ACTIVE_BUTTON, 
						 IDC_POINT_LIGHT_ACTIVE_BUTTON, 
						 IDC_POINT_LIGHT_ACTIVE_BUTTON);
		m_Active = true;

	}// end if
	else if(m_Active == true)
	{
		CheckRadioButton(IDC_POINT_LIGHT_ACTIVE_BUTTON, 
						 IDC_POINT_LIGHT_ACTIVE_BUTTON, 
						 -1);
		m_Active = false;
	}// end else if

	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);	
}

void CPointLightParameters::OnPointLightAsObjectButton() 
{
	if(m_RenderAsObject == false)
	{
		CheckRadioButton(IDC_POINT_LIGHT_AS_OBJECT_BUTTON, 
						 IDC_POINT_LIGHT_AS_OBJECT_BUTTON, 
						 IDC_POINT_LIGHT_AS_OBJECT_BUTTON);
		m_RenderAsObject = true;
	}// end if
	else if(m_RenderAsObject == true)
	{
		CheckRadioButton(IDC_POINT_LIGHT_AS_OBJECT_BUTTON, 
						 IDC_POINT_LIGHT_AS_OBJECT_BUTTON, 
						 -1);
		m_RenderAsObject = false;
	}// end else if

	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);	
}


void CPointLightParameters::OnOK() 
{
	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);
	
	CDialog::OnOK();
}

void CPointLightParameters::OnUpdatePointLightXEdit() 
{
	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);	
}

void CPointLightParameters::OnUpdatePointLightYEdit() 
{
	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);	
}

void CPointLightParameters::OnUpdatePointLightZEdit() 
{
	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);
}



