

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
#include "ZBufferParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




CZBufferParameters::CZBufferParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CZBufferParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZBufferParameters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	u_min       = -40;
	u_max       = 40;
	v_min       = -40;
	v_max       = 40;
	z_near      = -200.0;
	z_far       = 200.0;

	screen_rows = 500;
	screen_cols = 600;
}


void CZBufferParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZBufferParameters)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZBufferParameters, CDialog)
	//{{AFX_MSG_MAP(CZBufferParameters)
	ON_EN_CHANGE(IDC_Z_BUFFER_U_MAX_EDIT_BOX, OnChangeZBufferUMaxEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_U_MIN_EDIT_BOX, OnChangeZBufferUMinEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_V_MAX_EDIT_BOX, OnChangeZBufferVMaxEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_V_MIN_EDIT_BOX, OnChangeZBufferVMinEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_Z_FAR_EDIT_BOX, OnChangeZBufferZFarEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_Z_NEAR_EDIT_BOX, OnChangeZBufferZNearEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_SCREEN_COLUMNS_EDIT_BOX, OnChangeZBufferScreenColumnsEditBox)
	ON_EN_CHANGE(IDC_Z_BUFFER_SCREEN_ROWS_EDIT_BOX, OnChangeZBufferScreenRowsEditBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CZBufferParameters::OnInitDialog() 
{
	CString temp;

	temp.Format("%d", this->u_min);
	SetDlgItemText(IDC_Z_BUFFER_U_MIN_EDIT_BOX, temp);

	temp.Format("%d", this->u_max);
	SetDlgItemText(IDC_Z_BUFFER_U_MAX_EDIT_BOX, temp);

	temp.Format("%d", this->v_min);
	SetDlgItemText(IDC_Z_BUFFER_V_MIN_EDIT_BOX, temp);

	temp.Format("%d", this->v_max);
	SetDlgItemText(IDC_Z_BUFFER_V_MAX_EDIT_BOX, temp);

	temp.Format("%8.2f", this->z_near);
	SetDlgItemText(IDC_Z_BUFFER_Z_NEAR_EDIT_BOX, temp);

	temp.Format("%8.2f", this->z_far);
	SetDlgItemText(IDC_Z_BUFFER_Z_FAR_EDIT_BOX, temp);

	temp.Format("%d", this->screen_rows);
	SetDlgItemText(IDC_Z_BUFFER_SCREEN_ROWS_EDIT_BOX, temp);

	temp.Format("%d", this->screen_cols);
	SetDlgItemText(IDC_Z_BUFFER_SCREEN_COLUMNS_EDIT_BOX, temp);

	CDialog::OnInitDialog();
	
	return TRUE;
}

void CZBufferParameters::OnChangeZBufferUMaxEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_U_MAX_EDIT_BOX, temp);
	this->u_max = atoi(temp);
}

void CZBufferParameters::OnChangeZBufferUMinEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_U_MIN_EDIT_BOX, temp);
	this->u_min = atoi(temp);
}

void CZBufferParameters::OnChangeZBufferVMaxEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_V_MAX_EDIT_BOX, temp);
	this->v_max = atoi(temp);	
}

void CZBufferParameters::OnChangeZBufferVMinEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_V_MIN_EDIT_BOX, temp);
	this->v_min = atoi(temp);	
}

void CZBufferParameters::OnChangeZBufferZFarEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_Z_FAR_EDIT_BOX, temp);
	this->z_far = atof(temp);		
}

void CZBufferParameters::OnChangeZBufferZNearEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_Z_NEAR_EDIT_BOX, temp);
	this->z_near = atof(temp);
}

void CZBufferParameters::OnChangeZBufferScreenColumnsEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_SCREEN_COLUMNS_EDIT_BOX, temp);
	this->screen_cols = atoi(temp);
}

void CZBufferParameters::OnChangeZBufferScreenRowsEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_Z_BUFFER_SCREEN_ROWS_EDIT_BOX, temp);
	this->screen_rows = atoi(temp);	
}

void CZBufferParameters::OnOK() 
{
	CDialog::OnOK();

	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);
}
