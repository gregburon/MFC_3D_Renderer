

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
#include "TransformationParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CTransformationParameters::CTransformationParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CTransformationParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransformationParameters)
	//}}AFX_DATA_INIT
}


void CTransformationParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransformationParameters)
	DDX_Control(pDX, IDC_TRANSLATION_Z_SCROLLBAR, m_TranslationZScrollBar);
	DDX_Control(pDX, IDC_TRANSLATION_Y_SCROLLBAR, m_TranslationYScrollBar);
	DDX_Control(pDX, IDC_TRANSLATION_X_SCROLLBAR, m_TranslationXScrollBar);
	DDX_Control(pDX, IDC_SHEAR_Z_SCROLLBAR, m_ShearZScrollBar);
	DDX_Control(pDX, IDC_SHEAR_Y_SCROLLBAR, m_ShearYScrollBar);
	DDX_Control(pDX, IDC_SHEAR_X_SCROLLBAR, m_ShearXScrollBar);
	DDX_Control(pDX, IDC_SCALE_Z_SCROLLBAR, m_ScaleZScrollBar);
	DDX_Control(pDX, IDC_SCALE_Y_SCROLLBAR, m_ScaleYScrollBar);
	DDX_Control(pDX, IDC_SCALE_X_SCROLLBAR, m_ScaleXScrollBar);
	DDX_Control(pDX, IDC_ROTATION_Y_SCROLLBAR, m_RotationYScrollBar);
	DDX_Control(pDX, IDC_ROTATION_X_SCROLLBAR, m_RotationXScrollBar);
	DDX_Control(pDX, IDC_ROTATION_Z_SCROLLBAR, m_RotationZScrollBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransformationParameters, CDialog)
	//{{AFX_MSG_MAP(CTransformationParameters)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/********************************************************/
/*                                                      */
/*   View Parameters Dialog Box Message Handlers.       */
/*                                                      */
/********************************************************/

BOOL CTransformationParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString msg;
	SCROLLINFO info;

	// Set the rotation scroll bar sizes and info.
	SetScrollInfo(info, IDC_ROTATION_X_SCROLLBAR, 720, 0, 360);
	m_RotationXScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_ROTATION_Y_SCROLLBAR, 720, 0, 360);
	m_RotationYScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_ROTATION_Z_SCROLLBAR, 720, 0, 360);
	m_RotationZScrollBar.SetScrollInfo(&info);

	// Set the scale scroll bar sizes and info.
	SetScrollInfo(info, IDC_SCALE_X_SCROLLBAR, 200, 0, 10);
	m_ScaleXScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_SCALE_Y_SCROLLBAR, 200, 0, 10);
	m_ScaleYScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_SCALE_Z_SCROLLBAR, 200, 0, 10);
	m_ScaleZScrollBar.SetScrollInfo(&info);

	// Set the shear scroll bar sizes and info.
	SetScrollInfo(info, IDC_SHEAR_X_SCROLLBAR, 200, 0, 100);
	m_ShearXScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_SHEAR_Y_SCROLLBAR, 200, 0, 100);
	m_ShearYScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_SHEAR_Z_SCROLLBAR, 200, 0, 100);
	m_ShearZScrollBar.SetScrollInfo(&info);

	// Set the translation scroll bar sizes and info.
	SetScrollInfo(info, IDC_TRANSLATION_X_SCROLLBAR, 1600, 0, 800);
	m_TranslationXScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_TRANSLATION_Y_SCROLLBAR, 1600, 0, 800);
	m_TranslationYScrollBar.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_TRANSLATION_Z_SCROLLBAR, 1600, 0, 800);
	m_TranslationZScrollBar.SetScrollInfo(&info);	


	// Set default positions if there is not a current object
	// in the objects vector.
	if(pDoc->m_Objects.size() < 1)
	{
		SetScrollBarDisplayInformation(IDC_ROTATION_X_DISPLAY, 0.0);
		SetScrollBarDisplayInformation(IDC_ROTATION_Y_DISPLAY, 0.0);
		SetScrollBarDisplayInformation(IDC_ROTATION_Z_DISPLAY, 0.0);

		SetScrollBarDisplayInformation(IDC_SCALE_X_DISPLAY, 10.0);
		SetScrollBarDisplayInformation(IDC_SCALE_Y_DISPLAY, 10.0);
		SetScrollBarDisplayInformation(IDC_SCALE_Z_DISPLAY, 10.0);

		SetScrollBarDisplayInformation(IDC_SHEAR_X_DISPLAY, 0.0);
		SetScrollBarDisplayInformation(IDC_SHEAR_Y_DISPLAY, 0.0);
		SetScrollBarDisplayInformation(IDC_SHEAR_Z_DISPLAY, 0.0);

		SetScrollBarDisplayInformation(IDC_TRANSLATION_X_DISPLAY, 0.0);
		SetScrollBarDisplayInformation(IDC_TRANSLATION_Y_DISPLAY, 0.0);
		SetScrollBarDisplayInformation(IDC_TRANSLATION_Z_DISPLAY, 0.0);

	}// end if
	else if(pDoc->m_Objects.size() > 0)
	{
		SetSliderDisplayValues();
	}// end if
	
	return TRUE;  
}

bool CTransformationParameters::SetScrollInfo(SCROLLINFO& info, int ScrollID, int max, int min, int pos)
// This function sets the scrollbar info structure for a specific scroll bar
// in the tranformations palette depending on the ScrollID parameter
// sent into the function.
{
	info.cbSize     = sizeof(SCROLLINFO);
	info.fMask      = SIF_ALL;
	info.nMin       = min;
	info.nMax       = max;
	info.nPage      = 1;
	info.nPos       = pos;
	info.nTrackPos  = 2;
	
	return true;
}

void CTransformationParameters::SetScrollBarDisplayInformation(int DisplayID, double pos)
{
	CString msg;

	msg.Format("%3.1f", pos);
	SetDlgItemText(DisplayID, msg);
}

void CTransformationParameters::SetSliderDisplayValues()
{
	SetScrollBarDisplayInformation(IDC_ROTATION_X_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValX());
	SetScrollBarDisplayInformation(IDC_ROTATION_Y_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValY());
	SetScrollBarDisplayInformation(IDC_ROTATION_Z_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValZ());

	SetScrollBarDisplayInformation(IDC_SHEAR_X_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearXVal());
	SetScrollBarDisplayInformation(IDC_SHEAR_Y_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearYVal());
	SetScrollBarDisplayInformation(IDC_SHEAR_Z_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearZVal());

	SetScrollBarDisplayInformation(IDC_SCALE_X_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleXVal());
	SetScrollBarDisplayInformation(IDC_SCALE_Y_DISPLAY,
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleYVal());
	SetScrollBarDisplayInformation(IDC_SCALE_Z_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleZVal());

	SetScrollBarDisplayInformation(IDC_TRANSLATION_X_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransXVal());
	SetScrollBarDisplayInformation(IDC_TRANSLATION_Y_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransYVal());
	SetScrollBarDisplayInformation(IDC_TRANSLATION_Z_DISPLAY, 
			 pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransZVal());
}

void CTransformationParameters::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Get the Scrollbar ID.
	int ScrollID    = pScrollBar->GetDlgCtrlID();
	double value    = 0.0;
	double last_pos = 0.0;
	double cur_pos  = 0.0;

	switch(nSBCode)
	{
	case SB_PAGELEFT:
	case SB_LINELEFT:
		if(ScrollID == IDC_ROTATION_X_SCROLLBAR ||
		   ScrollID == IDC_ROTATION_Y_SCROLLBAR || 
		   ScrollID == IDC_ROTATION_Z_SCROLLBAR )
		{
			value = -1.0;
		}// end if
		else
		{
			value = -0.1;
		}// end else if
		break;

	case SB_PAGERIGHT:
	case SB_LINERIGHT:
		if(ScrollID == IDC_ROTATION_X_SCROLLBAR ||
		   ScrollID == IDC_ROTATION_Y_SCROLLBAR || 
		   ScrollID == IDC_ROTATION_Z_SCROLLBAR )
		{
			value = 1.0;
		}// end if
		else
		{
			value = 0.1;
		}// end else if
		break;

	case SB_THUMBTRACK:
		if(ScrollID == IDC_ROTATION_X_SCROLLBAR ||
		   ScrollID == IDC_ROTATION_Y_SCROLLBAR ||
		   ScrollID == IDC_ROTATION_Z_SCROLLBAR)
		{
			cur_pos =  nPos - 360;
		}// end if
		else if(ScrollID == IDC_SCALE_X_SCROLLBAR ||
			    ScrollID == IDC_SCALE_Y_SCROLLBAR ||
				ScrollID == IDC_SCALE_Z_SCROLLBAR)
		{
			cur_pos = (double)nPos;
		}// end else if
		else if(ScrollID == IDC_TRANSLATION_X_SCROLLBAR ||
			    ScrollID == IDC_TRANSLATION_Y_SCROLLBAR ||
				ScrollID == IDC_TRANSLATION_Z_SCROLLBAR)
		{
			cur_pos = (double)nPos - 800.0;
		}// end else if
		else if(ScrollID == IDC_SHEAR_X_SCROLLBAR ||
			    ScrollID == IDC_SHEAR_Y_SCROLLBAR ||
				ScrollID == IDC_SHEAR_Z_SCROLLBAR)
		{
			cur_pos = (double)nPos - 100.0;
		}// end else if

		last_pos = GetLastPosition(ScrollID);
		value = cur_pos - last_pos;
		break;

	}// end switch

	int current = pDoc->m_CurrentObject;
	
	switch(ScrollID)
	{
	case IDC_ROTATION_X_SCROLLBAR:
		ModifyObjectRotationX(value);
		m_RotationXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectRotationValX() + 360.0);
		break;

	case IDC_ROTATION_Y_SCROLLBAR:
		ModifyObjectRotationY(value);
		m_RotationYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectRotationValY() + 360.0);
		break;

	case IDC_ROTATION_Z_SCROLLBAR:
		ModifyObjectRotationZ(value);
		m_RotationZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectRotationValZ() + 360.0);
		break;

	case IDC_SHEAR_X_SCROLLBAR:
		ModifyObjectShearX(value);
		m_ShearXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectShearXVal() + 100.0);
		break;

	case IDC_SHEAR_Y_SCROLLBAR:
		ModifyObjectShearY(value);
		m_ShearYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectShearYVal() + 100.0);
		break;

	case IDC_SHEAR_Z_SCROLLBAR:
		ModifyObjectShearZ(value);
		m_ShearZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectShearZVal() + 100.0);
		break;

	case IDC_SCALE_X_SCROLLBAR:
		ModifyObjectScaleX(value);
		m_ScaleXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectScaleXVal());
		break;
		
	case IDC_SCALE_Y_SCROLLBAR:
		ModifyObjectScaleY(value);
		m_ScaleYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectScaleYVal());
		break;

	case IDC_SCALE_Z_SCROLLBAR:
		ModifyObjectScaleZ(value);
		m_ScaleZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectScaleZVal());
		break;

	case IDC_TRANSLATION_X_SCROLLBAR:
		ModifyObjectTranslationX(value);
		m_TranslationXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectTransXVal() + 800.0);
		break;

	case IDC_TRANSLATION_Y_SCROLLBAR:
		ModifyObjectTranslationY(value);
		m_TranslationYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectTransYVal() + 800.0);
		break;

	case IDC_TRANSLATION_Z_SCROLLBAR:
		ModifyObjectTranslationZ(value);
		m_TranslationZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectTransZVal() + 800.0);
		break;
	}// end switch

	if(pDoc->m_Objects.size() > 0)
	{
		// The object's values have been modified, therefore the m_FacetDistances list
		// must be updated to  reflect any changes the transformations have made to 
		// their distances to the observer.
		pDoc->m_Objects[pDoc->m_CurrentObject].GenerateFacetDistanceVector(pDoc->m_Camera,
			                                                      pDoc->m_ProjectionMethod);
	}// end if

	// Set the strings in the dialog box to their current values.
	SetSliderDisplayValues();

	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CTransformationParameters::ModifyObjectRotationX(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValX();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectRotationXVal(current + value);
}

void CTransformationParameters::ModifyObjectRotationY(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValY();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectRotationYVal(current + value);
}

void CTransformationParameters::ModifyObjectRotationZ(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValZ();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectRotationZVal(current + value);
}

void CTransformationParameters::ModifyObjectScaleX(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleXVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectScaleXVal(current + value);
}

void CTransformationParameters::ModifyObjectScaleY(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleYVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectScaleYVal(current + value);
}

void CTransformationParameters::ModifyObjectScaleZ(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleZVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectScaleZVal(current + value);
}

void CTransformationParameters::ModifyObjectShearX(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearXVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectShearXVal(current + value);
}

void CTransformationParameters::ModifyObjectShearY(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearYVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectShearYVal(current + value);
}

void CTransformationParameters::ModifyObjectShearZ(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearZVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectShearZVal(current + value);
}

void CTransformationParameters::ModifyObjectTranslationX(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransXVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectTransXVal(current + value);
}

void CTransformationParameters::ModifyObjectTranslationY(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransYVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectTransYVal(current + value);
}

void CTransformationParameters::ModifyObjectTranslationZ(double value)
{
	double current = pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransZVal();
	pDoc->m_Objects[pDoc->m_CurrentObject].SetObjectTransZVal(current + value);
}


double CTransformationParameters::GetLastPosition(int ScrollID)
{
	if(IDC_ROTATION_X_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValX();

	else if(IDC_ROTATION_Y_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValY();

	else if(IDC_ROTATION_Z_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectRotationValZ();

	else if(IDC_SHEAR_X_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearXVal();

	else if(IDC_SHEAR_Y_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearYVal();

	else if(IDC_SHEAR_Z_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectShearZVal();

	else if(IDC_SCALE_X_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleXVal();
		
	else if(IDC_SCALE_Y_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleYVal();

	else if(IDC_SCALE_Z_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectScaleZVal();

	else if(IDC_TRANSLATION_X_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransXVal();

	else if(IDC_TRANSLATION_Y_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransYVal();

	else if(IDC_TRANSLATION_Z_SCROLLBAR == ScrollID)
		return pDoc->m_Objects[pDoc->m_CurrentObject].GetObjectTransZVal();

	return 0.0;
}

void CTransformationParameters::SetSliderPositions()
{
	int    current  = pDoc->m_CurrentObject;

	if(current < 0)
	{
		return;
	}// end if

	m_RotationXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectRotationValX());
	m_RotationYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectRotationValY());
	m_RotationZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectRotationValZ());
	m_ShearXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectShearXVal());
	m_ShearYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectShearYVal());
	m_ShearZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectShearZVal());
	m_ScaleXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectScaleXVal());
	m_ScaleYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectScaleYVal());
	m_ScaleZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectScaleZVal());
	m_TranslationXScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectTransXVal());
	m_TranslationYScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectTransYVal());
	m_TranslationZScrollBar.SetScrollPos(pDoc->m_Objects[current].GetObjectTransZVal());
}



