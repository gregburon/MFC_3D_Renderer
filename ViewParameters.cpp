

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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



const int OFFSET = 100;
const int MAX    = 200;

CViewParameters::CViewParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CViewParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewParameters)
	//}}AFX_DATA_INIT
}


void CViewParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewParameters)
	DDX_Control(pDX, IDC_CAMERA_VIEW_UP_VECTOR_Z_SLIDER, m_ViewUpVectorZSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_UP_VECTOR_Y_SLIDER, m_ViewUpVectorYSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_UP_VECTOR_X_SLIDER, m_ViewUpVectorXSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_REFERENCE_POINT_Z_SLIDER, m_ViewReferencePointZSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_REFERENCE_POINT_Y_SLIDER, m_ViewReferencePointYSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_REFERENCE_POINT_X_SLIDER, m_ViewReferencePointXSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_PLANE_NORMAL_Z_SLIDER, m_ViewPlaneNormalZSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_PLANE_NORMAL_Y_SLIDER, m_ViewPlaneNormalYSlider);
	DDX_Control(pDX, IDC_CAMERA_VIEW_PLANE_NORMAL_X_SLIDER, m_ViewPlaneNormalXSlider);
	DDX_Control(pDX, IDC_CAMERA_CENTER_OF_PROJECTION_V_SLIDER, m_CenterOfProjectionVSlider);
	DDX_Control(pDX, IDC_CAMERA_CENTER_OF_PROJECTION_U_SLIDER, m_CenterOfProjectionUSlider);
	DDX_Control(pDX, IDC_CAMERA_CENTER_OF_PROJECTION_N_SLIDER, m_CenterOfProjectionNSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewParameters, CDialog)
	//{{AFX_MSG_MAP(CViewParameters)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/********************************************************/
/*                                                      */
/*   View Parameters Dialog Box Message Handlers.       */
/*                                                      */
/********************************************************/



BOOL CViewParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set the values of the spinner displays to their default values.
	SetSliderDefaultValues();

	// Set the strings in the dialog box to their current values.
	SetSliderInitialDisplayValues();
	
	return TRUE;
}



void CViewParameters::SetSliderDefaultValues()
{
	CString msg;
	SCROLLINFO info;

	// Set the view reference point scroll bar sizes and info.
	SetScrollInfo(info, IDC_CAMERA_VIEW_REFERENCE_POINT_X_SLIDER, MAX, 0, OFFSET);
	m_ViewReferencePointXSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_VIEW_REFERENCE_POINT_Y_SLIDER, MAX, 0, OFFSET);
	m_ViewReferencePointYSlider.SetScrollInfo(&info);	

	SetScrollInfo(info, IDC_CAMERA_VIEW_REFERENCE_POINT_Z_SLIDER, MAX, 0, OFFSET);
	m_ViewReferencePointZSlider.SetScrollInfo(&info);

	// Set the view plane normal scroll bar sizes and info.
	SetScrollInfo(info, IDC_CAMERA_VIEW_PLANE_NORMAL_X_SLIDER, MAX, 0, OFFSET);
	m_ViewPlaneNormalXSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_VIEW_PLANE_NORMAL_Y_SLIDER, MAX, 0, OFFSET);
	m_ViewPlaneNormalYSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_VIEW_PLANE_NORMAL_Z_SLIDER, MAX, 0, OFFSET);
	m_ViewPlaneNormalZSlider.SetScrollInfo(&info);

	// Set the view up vector scroll bar sizes and info.
	SetScrollInfo(info, IDC_CAMERA_VIEW_UP_VECTOR_X_SLIDER, MAX, 0, OFFSET);
	m_ViewUpVectorXSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_VIEW_UP_VECTOR_Y_SLIDER, MAX, 0, OFFSET);
	m_ViewUpVectorYSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_VIEW_UP_VECTOR_Z_SLIDER, MAX, 0, OFFSET);
	m_ViewUpVectorZSlider.SetScrollInfo(&info);

	// Set the Center of Projection scroll bar sizes and info.
	SetScrollInfo(info, IDC_CAMERA_CENTER_OF_PROJECTION_U_SLIDER, MAX, 0, OFFSET);
	m_CenterOfProjectionUSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_CENTER_OF_PROJECTION_V_SLIDER, MAX, 0, OFFSET);
	m_CenterOfProjectionVSlider.SetScrollInfo(&info);

	SetScrollInfo(info, IDC_CAMERA_CENTER_OF_PROJECTION_N_SLIDER, MAX, 0, OFFSET);
	m_CenterOfProjectionNSlider.SetScrollInfo(&info);


	m_ViewReferencePointXSlider.SetScrollPos(m_Camera.GetCameraVRP_X() + (double)OFFSET);
	m_ViewReferencePointYSlider.SetScrollPos(m_Camera.GetCameraVRP_Y() + (double)OFFSET);
	m_ViewReferencePointZSlider.SetScrollPos(m_Camera.GetCameraVRP_Z() + (double)OFFSET);
	m_ViewPlaneNormalXSlider.SetScrollPos(m_Camera.GetCameraVPN_X() + (double)OFFSET);
	m_ViewPlaneNormalYSlider.SetScrollPos(m_Camera.GetCameraVPN_Y() + (double)OFFSET);
	m_ViewPlaneNormalZSlider.SetScrollPos(m_Camera.GetCameraVPN_Z() + (double)OFFSET);
	m_ViewUpVectorXSlider.SetScrollPos(m_Camera.GetCameraVUP_X() + (double)OFFSET);
	m_ViewUpVectorYSlider.SetScrollPos(m_Camera.GetCameraVUP_Y() + (double)OFFSET);
	m_ViewUpVectorZSlider.SetScrollPos(m_Camera.GetCameraVUP_Z() + (double)OFFSET);
	m_CenterOfProjectionUSlider.SetScrollPos(m_Camera.GetCameraCOP_U() + (double)OFFSET);
	m_CenterOfProjectionVSlider.SetScrollPos(m_Camera.GetCameraCOP_V() + (double)OFFSET);
	m_CenterOfProjectionNSlider.SetScrollPos(m_Camera.GetCameraCOP_N() + (double)OFFSET);

}

void CViewParameters::SetSliderDisplayValues()
{
	CString msg;

	// Set the strings for the View Reference Point
	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVRP_X());
	SetDlgItemText(IDC_VIEW_REFERENCE_POINT_X_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVRP_Y());
	SetDlgItemText(IDC_VIEW_REFERENCE_POINT_Y_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVRP_Z());
	SetDlgItemText(IDC_VIEW_REFERENCE_POINT_Z_DISPLAY, msg);


	// Set the strings for the View Plane Normal Point
	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVPN_X());
	SetDlgItemText(IDC_VIEW_PLANE_NORMAL_X_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVPN_Y());
	SetDlgItemText(IDC_VIEW_PLANE_NORMAL_Y_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVPN_Z());
	SetDlgItemText(IDC_VIEW_PLANE_NORMAL_Z_DISPLAY, msg);


	// Set the strings for the View Up Vector
	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVUP_X());
	SetDlgItemText(IDC_VIEW_UP_X_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVUP_Y());
	SetDlgItemText(IDC_VIEW_UP_Y_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraVUP_Z());
	SetDlgItemText(IDC_VIEW_UP_Z_DISPLAY, msg);


	// Set the strings for the View Up Vector
	msg.Format("%4.1f", pDoc->m_Camera.GetCameraCOP_U());
	SetDlgItemText(IDC_CENTER_OF_PROJECTION_U_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraCOP_V());
	SetDlgItemText(IDC_CENTER_OF_PROJECTION_V_DISPLAY, msg);

	msg.Format("%4.1f", pDoc->m_Camera.GetCameraCOP_N());
	SetDlgItemText(IDC_CENTER_OF_PROJECTION_N_DISPLAY, msg);

}

void CViewParameters::SetSliderInitialDisplayValues()
{
	CString msg;

	// Set the strings for the View Reference Point
	msg.Format("%4.1f", m_Camera.GetCameraVRP_X());
	SetDlgItemText(IDC_VIEW_REFERENCE_POINT_X_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraVRP_Y());
	SetDlgItemText(IDC_VIEW_REFERENCE_POINT_Y_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraVRP_Z());
	SetDlgItemText(IDC_VIEW_REFERENCE_POINT_Z_DISPLAY, msg);


	// Set the strings for the View Plane Normal Point
	msg.Format("%4.1f", m_Camera.GetCameraVPN_X());
	SetDlgItemText(IDC_VIEW_PLANE_NORMAL_X_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraVPN_Y());
	SetDlgItemText(IDC_VIEW_PLANE_NORMAL_Y_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraVPN_Z());
	SetDlgItemText(IDC_VIEW_PLANE_NORMAL_Z_DISPLAY, msg);


	// Set the strings for the View Up Vector
	msg.Format("%4.1f", m_Camera.GetCameraVUP_X());
	SetDlgItemText(IDC_VIEW_UP_X_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraVUP_Y());
	SetDlgItemText(IDC_VIEW_UP_Y_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraVUP_Z());
	SetDlgItemText(IDC_VIEW_UP_Z_DISPLAY, msg);


	// Set the strings for the View Up Vector
	msg.Format("%4.1f", m_Camera.GetCameraCOP_U());
	SetDlgItemText(IDC_CENTER_OF_PROJECTION_U_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraCOP_V());
	SetDlgItemText(IDC_CENTER_OF_PROJECTION_V_DISPLAY, msg);

	msg.Format("%4.1f", m_Camera.GetCameraCOP_N());
	SetDlgItemText(IDC_CENTER_OF_PROJECTION_N_DISPLAY, msg);

}

bool CViewParameters::SetScrollInfo(SCROLLINFO& info, int ScrollID, int max, int min, int pos)
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
  

void CViewParameters::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
		value = -1.0;
		break;

	case SB_PAGERIGHT:
	case SB_LINERIGHT:
		value = 1.0;
		break;

	case SB_THUMBTRACK:
		cur_pos =  (double)nPos - (double)OFFSET;
		last_pos = GetLastPosition(ScrollID);
		value = cur_pos - last_pos;
		break;

	}// end switch

	switch(ScrollID)
	{
	case IDC_CAMERA_VIEW_REFERENCE_POINT_X_SLIDER:
		ModifyCameraViewReferencePointX(value);
		m_ViewReferencePointXSlider.SetScrollPos(pDoc->m_Camera.GetCameraVRP_X() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_REFERENCE_POINT_Y_SLIDER:
		ModifyCameraViewReferencePointY(value);
		m_ViewReferencePointYSlider.SetScrollPos(pDoc->m_Camera.GetCameraVRP_Y() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_REFERENCE_POINT_Z_SLIDER:
		ModifyCameraViewReferencePointZ(value);
		m_ViewReferencePointZSlider.SetScrollPos(pDoc->m_Camera.GetCameraVRP_Z() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_PLANE_NORMAL_X_SLIDER:
		ModifyCameraViewPlaneNormalX(value);
		m_ViewPlaneNormalXSlider.SetScrollPos(pDoc->m_Camera.GetCameraVPN_X() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_PLANE_NORMAL_Y_SLIDER:
		ModifyCameraViewPlaneNormalY(value);
		m_ViewPlaneNormalYSlider.SetScrollPos(pDoc->m_Camera.GetCameraVPN_Y() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_PLANE_NORMAL_Z_SLIDER:
		ModifyCameraViewPlaneNormalZ(value);
		m_ViewPlaneNormalZSlider.SetScrollPos(pDoc->m_Camera.GetCameraVPN_Z() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_UP_VECTOR_X_SLIDER:
		ModifyCameraViewUpVectorX(value);
		m_ViewUpVectorXSlider.SetScrollPos(pDoc->m_Camera.GetCameraVUP_X() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_UP_VECTOR_Y_SLIDER:
		ModifyCameraViewUpVectorY(value);
		m_ViewUpVectorYSlider.SetScrollPos(pDoc->m_Camera.GetCameraVUP_Y() + (double)OFFSET);
		break;

	case IDC_CAMERA_VIEW_UP_VECTOR_Z_SLIDER:
		ModifyCameraViewUpVectorZ(value);
		m_ViewUpVectorZSlider.SetScrollPos(pDoc->m_Camera.GetCameraVUP_Z() + (double)OFFSET);
		break;

	case IDC_CAMERA_CENTER_OF_PROJECTION_U_SLIDER:
		ModifyCameraCenterOfProjectionU(value);
		m_CenterOfProjectionUSlider.SetScrollPos(pDoc->m_Camera.GetCameraCOP_U() + (double)OFFSET);
		break;

	case IDC_CAMERA_CENTER_OF_PROJECTION_V_SLIDER:
		ModifyCameraCenterOfProjectionV(value);
		m_CenterOfProjectionVSlider.SetScrollPos(pDoc->m_Camera.GetCameraCOP_V() + (double)OFFSET);
		break;

	case IDC_CAMERA_CENTER_OF_PROJECTION_N_SLIDER:
		ModifyCameraCenterOfProjectionN(value);
		m_CenterOfProjectionNSlider.SetScrollPos(pDoc->m_Camera.GetCameraCOP_N() + (double)OFFSET);
		break;
	}// end switch

	if(pDoc->m_Objects.size() > 0)
	{
		// The camera's values have been modified, therefore the m_FacetDistances list
		// must be updated to  reflect any changes the transformations have made to 
		// their distances to the observer.
		pDoc->m_Objects[pDoc->m_CurrentObject].GenerateFacetDistanceVector(pDoc->m_Camera, 
			                                                      pDoc->m_ProjectionMethod);
	}// end if

	// Set the strings in the dialog box to their current values.
	SetSliderDisplayValues();

	GetParentFrame()->GetActiveView()->Invalidate(false);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CViewParameters::ModifyCameraViewReferencePointX(double value)
{
	double current = pDoc->m_Camera.GetCameraVRP_X();
	pDoc->m_Camera.SetCameraVRP_X(current+value);
}

void CViewParameters::ModifyCameraViewReferencePointY(double value)
{
	double current = pDoc->m_Camera.GetCameraVRP_Y();
	pDoc->m_Camera.SetCameraVRP_Y(current+value);
}

void CViewParameters::ModifyCameraViewReferencePointZ(double value)
{
	double current = pDoc->m_Camera.GetCameraVRP_Z();
	pDoc->m_Camera.SetCameraVRP_Z(current+value);
}

void CViewParameters::ModifyCameraViewPlaneNormalX(double value)
{
	double current = pDoc->m_Camera.GetCameraVPN_X();
	pDoc->m_Camera.SetCameraVPN_X(current+value);
}

void CViewParameters::ModifyCameraViewPlaneNormalY(double value)
{
	double current = pDoc->m_Camera.GetCameraVPN_Y();
	pDoc->m_Camera.SetCameraVPN_Y(current+value);
}

void CViewParameters::ModifyCameraViewPlaneNormalZ(double value)
{
	double current = pDoc->m_Camera.GetCameraVPN_Z();
	pDoc->m_Camera.SetCameraVPN_Z(current+value);
}

void CViewParameters::ModifyCameraViewUpVectorX(double value)
{
	double current = pDoc->m_Camera.GetCameraVUP_X();
	pDoc->m_Camera.SetCameraVUP_X(current+value);
}

void CViewParameters::ModifyCameraViewUpVectorY(double value)
{
	double current = pDoc->m_Camera.GetCameraVUP_Y();
	pDoc->m_Camera.SetCameraVUP_Y(current+value);
}

void CViewParameters::ModifyCameraViewUpVectorZ(double value)
{
	double current = pDoc->m_Camera.GetCameraVUP_Z();
	pDoc->m_Camera.SetCameraVUP_Z(current+value);
}

void CViewParameters::ModifyCameraCenterOfProjectionU(double value)
{
	double current = pDoc->m_Camera.GetCameraCOP_U();
	pDoc->m_Camera.SetCameraCOP_U(current+value);
}

void CViewParameters::ModifyCameraCenterOfProjectionV(double value)
{
	double current = pDoc->m_Camera.GetCameraCOP_V();
	pDoc->m_Camera.SetCameraCOP_V(current+value);
}

void CViewParameters::ModifyCameraCenterOfProjectionN(double value)
{
	double current = pDoc->m_Camera.GetCameraCOP_N();
	pDoc->m_Camera.SetCameraCOP_N(current+value);
}

double CViewParameters::GetLastPosition(int ScrollID)
{
	if(IDC_CAMERA_VIEW_REFERENCE_POINT_X_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVRP_X();

	else if(IDC_CAMERA_VIEW_REFERENCE_POINT_Y_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVRP_Y();

	else if(IDC_CAMERA_VIEW_REFERENCE_POINT_Z_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVRP_Z();

	else if(IDC_CAMERA_VIEW_PLANE_NORMAL_X_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVPN_X();

	else if(IDC_CAMERA_VIEW_PLANE_NORMAL_Y_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVPN_Y();

	else if(IDC_CAMERA_VIEW_PLANE_NORMAL_Z_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVPN_Z();

	else if(IDC_CAMERA_VIEW_UP_VECTOR_X_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVUP_X();

	else if(IDC_CAMERA_VIEW_UP_VECTOR_Y_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVUP_Y();

	else if(IDC_CAMERA_VIEW_UP_VECTOR_Z_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraVUP_Z();

	else if(IDC_CAMERA_CENTER_OF_PROJECTION_U_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraCOP_U();

	else if(IDC_CAMERA_CENTER_OF_PROJECTION_V_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraCOP_V();

	else if(IDC_CAMERA_CENTER_OF_PROJECTION_N_SLIDER == ScrollID)
		return pDoc->m_Camera.GetCameraCOP_N();

	
	return 0.0;
}

