

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

#include <string>
#include <vector>

#if !defined(AFX_MATERIALPROPERTYPAGE_H__21CC1E7B_D281_48ED_BB66_9DA1FA0FF18D__INCLUDED_)
#define AFX_MATERIALPROPERTYPAGE_H__21CC1E7B_D281_48ED_BB66_9DA1FA0FF18D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialPropertyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterialPropertyPage dialog

class CMaterialPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMaterialPropertyPage)

// Construction
public:
	CMaterialPropertyPage();
	~CMaterialPropertyPage();


	string m_Name;

	double  m_KaRed;
	double  m_KaGreen;
	double  m_KaBlue;

	double  m_KdRed;
	double  m_KdGreen;
	double  m_KdBlue;

	double  m_KsRed;
	double  m_KsGreen;
	double  m_KsBlue;

	double  m_SpecularExponent;

// Dialog Data
	//{{AFX_DATA(CMaterialPropertyPage)
	enum { IDD = IDD_MATERIAL_PROPERTY_PAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMaterialPropertyPage)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMaterialPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeMaterialAmbientRedEditBox();
	afx_msg void OnChangeMaterialAmbientGreenEditBox();
	afx_msg void OnChangeMaterialAmbientBlueEditBox();
	afx_msg void OnChangeMaterialDiffuseBlueEditBox();
	afx_msg void OnChangeMaterialDiffuseGreenEditBox();
	afx_msg void OnChangeMaterialDiffuseRedEditBox();
	afx_msg void OnChangeMaterialNameEditBox();
	afx_msg void OnChangeMaterialSpecularBlueEditBox();
	afx_msg void OnChangeMaterialSpecularExponentEditBox();
	afx_msg void OnChangeMaterialSpecularGreenEditBox();
	afx_msg void OnChangeMaterialSpecularRedEditBox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALPROPERTYPAGE_H__21CC1E7B_D281_48ED_BB66_9DA1FA0FF18D__INCLUDED_)
