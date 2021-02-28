
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
#include "MaterialSelectorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




CMaterialSelectorDialog::CMaterialSelectorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialSelectorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialSelectorDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMaterialSelectorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialSelectorDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialSelectorDialog, CDialog)
	//{{AFX_MSG_MAP(CMaterialSelectorDialog)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_1, OnMaterialRadio1)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_2, OnMaterialRadio2)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_3, OnMaterialRadio3)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_4, OnMaterialRadio4)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_5, OnMaterialRadio5)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_6, OnMaterialRadio6)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_7, OnMaterialRadio7)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_8, OnMaterialRadio8)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_9, OnMaterialRadio9)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_10, OnMaterialRadio10)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_11, OnMaterialRadio11)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_12, OnMaterialRadio12)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_13, OnMaterialRadio13)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_14, OnMaterialRadio14)
	ON_BN_CLICKED(IDC_MATERIAL_RADIO_15, OnMaterialRadio15)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





/********************************************************/
/*                                                      */
/*   Material Selector Dialog Box Message Handlers.     */
/*                                                      */
/********************************************************/
BOOL CMaterialSelectorDialog::OnInitDialog() 
{
	SetRadioButtonMaterialNames();

	CheckRadioButton(IDC_MATERIAL_RADIO_1, 
				     IDC_MATERIAL_RADIO_15, 
				     IDC_MATERIAL_RADIO_1);

	CDialog::OnInitDialog();

	return TRUE;
}

void CMaterialSelectorDialog::SetRadioButtonMaterialNames()
{
	CString temp;

	temp.Format("%s", this->m_MaterialNames[0].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_1, temp);

	temp.Format("%s", this->m_MaterialNames[1].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_2, temp);

	temp.Format("%s", this->m_MaterialNames[2].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_3, temp);

	temp.Format("%s", this->m_MaterialNames[3].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_4, temp);

	temp.Format("%s", this->m_MaterialNames[4].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_5, temp);

	temp.Format("%s", this->m_MaterialNames[5].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_6, temp);

	temp.Format("%s", this->m_MaterialNames[6].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_7, temp);

	temp.Format("%s", this->m_MaterialNames[7].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_8, temp);

	temp.Format("%s", this->m_MaterialNames[8].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_9, temp);

	temp.Format("%s", this->m_MaterialNames[9].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_10, temp);

	temp.Format("%s", this->m_MaterialNames[10].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_11, temp);

	temp.Format("%s", this->m_MaterialNames[11].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_12, temp);

	temp.Format("%s", this->m_MaterialNames[12].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_13, temp);

	temp.Format("%s", this->m_MaterialNames[13].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_14, temp);

	temp.Format("%s", this->m_MaterialNames[14].c_str());
	SetDlgItemText(IDC_MATERIAL_RADIO_15, temp);
}

void CMaterialSelectorDialog::OnMaterialRadio1() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 0;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio2() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 1;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio3() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 2;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio4() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 3;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio5() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 4;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio6() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 5;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio7() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 6;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio8() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 7;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio9() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 8;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio10() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 9;	
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio11() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 10;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio12() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 11;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio13() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 12;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio14() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 13;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}

void CMaterialSelectorDialog::OnMaterialRadio15() 
{
	pDoc->m_Objects[pDoc->m_CurrentObject].m_MaterialIndex = 14;
	GetParentFrame()->GetActiveView()->Invalidate(false);
}
