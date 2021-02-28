
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
#include "MaterialPropertyPage.h"
#include "homework2Doc.h"
#include "homework2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMaterialPropertyPage, CPropertyPage)

CMaterialPropertyPage::CMaterialPropertyPage() : CPropertyPage(CMaterialPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CMaterialPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMaterialPropertyPage::~CMaterialPropertyPage()
{
}

void CMaterialPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialPropertyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMaterialPropertyPage)
	ON_EN_CHANGE(IDC_MATERIAL_AMBIENT_RED_EDIT_BOX, OnChangeMaterialAmbientRedEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_AMBIENT_GREEN_EDIT_BOX, OnChangeMaterialAmbientGreenEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_AMBIENT_BLUE_EDIT_BOX, OnChangeMaterialAmbientBlueEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_DIFFUSE_BLUE_EDIT_BOX, OnChangeMaterialDiffuseBlueEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_DIFFUSE_GREEN_EDIT_BOX, OnChangeMaterialDiffuseGreenEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_DIFFUSE_RED_EDIT_BOX, OnChangeMaterialDiffuseRedEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_NAME_EDIT_BOX, OnChangeMaterialNameEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_SPECULAR_BLUE_EDIT_BOX, OnChangeMaterialSpecularBlueEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_SPECULAR_EXPONENT_EDIT_BOX, OnChangeMaterialSpecularExponentEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_SPECULAR_GREEN_EDIT_BOX, OnChangeMaterialSpecularGreenEditBox)
	ON_EN_CHANGE(IDC_MATERIAL_SPECULAR_RED_EDIT_BOX, OnChangeMaterialSpecularRedEditBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





/********************************************************/
/*                                                      */
/*   Material Property Page Dialog Box Message Handlers */
/*                                                      */
/********************************************************/

BOOL CMaterialPropertyPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Set the values of the edit boxes to the material values.
	SetDlgItemText(IDC_MATERIAL_NAME_EDIT_BOX, this->m_Name.c_str());

	CString temp;

	temp.Format("%6.5f", this->m_KaRed);
	SetDlgItemText(IDC_MATERIAL_AMBIENT_RED_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KaGreen);
	SetDlgItemText(IDC_MATERIAL_AMBIENT_GREEN_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KaBlue);
	SetDlgItemText(IDC_MATERIAL_AMBIENT_BLUE_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KdRed);
	SetDlgItemText(IDC_MATERIAL_DIFFUSE_RED_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KdGreen);
	SetDlgItemText(IDC_MATERIAL_DIFFUSE_GREEN_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KdBlue);
	SetDlgItemText(IDC_MATERIAL_DIFFUSE_BLUE_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KsRed);
	SetDlgItemText(IDC_MATERIAL_SPECULAR_RED_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KsGreen);
	SetDlgItemText(IDC_MATERIAL_SPECULAR_GREEN_EDIT_BOX, temp);

	temp.Format("%6.5f", this->m_KsBlue);
	SetDlgItemText(IDC_MATERIAL_SPECULAR_BLUE_EDIT_BOX, temp);

	temp.Format("%4.2f", this->m_SpecularExponent);
	SetDlgItemText(IDC_MATERIAL_SPECULAR_EXPONENT_EDIT_BOX, temp);

	this->SetModified(true);
	
	return TRUE; 
}

BOOL CMaterialPropertyPage::OnApply() 
{
	// Update the view window.
	GetParentFrame()->GetActiveView()->Invalidate(false);

	return CPropertyPage::OnApply();
}

BOOL CMaterialPropertyPage::OnSetActive() 
{
	
	return CPropertyPage::OnSetActive();
}


void CMaterialPropertyPage::OnChangeMaterialAmbientRedEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_AMBIENT_RED_EDIT_BOX, temp);
	this->m_KaRed = atof(temp);

	this->SetModified(true);
}

void CMaterialPropertyPage::OnChangeMaterialAmbientGreenEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_AMBIENT_GREEN_EDIT_BOX, temp);
	this->m_KaGreen = atof(temp);

	this->SetModified(true);	
}

void CMaterialPropertyPage::OnChangeMaterialAmbientBlueEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_AMBIENT_BLUE_EDIT_BOX, temp);
	this->m_KaBlue = atof(temp);

	this->SetModified(true);
}

void CMaterialPropertyPage::OnChangeMaterialDiffuseBlueEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_DIFFUSE_BLUE_EDIT_BOX, temp);
	this->m_KdBlue = atof(temp);

	this->SetModified(true);	
}

void CMaterialPropertyPage::OnChangeMaterialDiffuseGreenEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_DIFFUSE_GREEN_EDIT_BOX, temp);
	this->m_KdGreen = atof(temp);

	this->SetModified(true);
}

void CMaterialPropertyPage::OnChangeMaterialDiffuseRedEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_DIFFUSE_RED_EDIT_BOX, temp);
	this->m_KdRed = atof(temp);

	this->SetModified(true);	
}

void CMaterialPropertyPage::OnChangeMaterialNameEditBox() 
{
	CString name;
	this->GetDlgItemText(IDC_MATERIAL_NAME_EDIT_BOX, name);
	this->m_Name = name;
	this->SetModified(true);	
}

void CMaterialPropertyPage::OnChangeMaterialSpecularBlueEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_SPECULAR_BLUE_EDIT_BOX, temp);
	this->m_KsBlue = atof(temp);

	this->SetModified(true);	
}

void CMaterialPropertyPage::OnChangeMaterialSpecularExponentEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_SPECULAR_EXPONENT_EDIT_BOX, temp);
	this->m_SpecularExponent = atof(temp);

	this->SetModified(true);	
}

void CMaterialPropertyPage::OnChangeMaterialSpecularGreenEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_SPECULAR_GREEN_EDIT_BOX, temp);
	this->m_KsGreen = atof(temp);

	this->SetModified(true);
}

void CMaterialPropertyPage::OnChangeMaterialSpecularRedEditBox() 
{
	CString temp;
	GetDlgItemText(IDC_MATERIAL_SPECULAR_RED_EDIT_BOX, temp);
	this->m_KsRed = atof(temp);

	this->SetModified(true);
}
