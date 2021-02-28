

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
#include "defines.h"
#include "homework2.h"
#include "ObjectManager.h"
#include "homework2.h"
#include "homework2Doc.h"
#include "Object3D.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include <io.h>
#include <fstream>
#include <string.h>
//#include "Vector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CObjectManager::CObjectManager(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectManager)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CObjectManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectManager)
	DDX_Control(pDX, IDC_CURRENT_OBJECT_COMBO, m_CurrentObjectComboBox);
	DDX_Control(pDX, IDC_DISPLAYED_OBJECTS_LIST, m_DisplayedObjectsListBox);
	DDX_Control(pDX, IDC_DELETE_CURRENT_OBJECT, m_DeleteCurrentObjectButton);
	DDX_Control(pDX, IDC_DELETE_ALL_OBJECTS, m_DeleteAllObjectsButton);
	DDX_Control(pDX, IDC_ADD_OBJECT_BUTTON, m_AddObjectButton);
	DDX_Control(pDX, IDC_ADD_OBJECT_COMBO_BOX, m_AddObjectComboBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjectManager, CDialog)
	//{{AFX_MSG_MAP(CObjectManager)
	ON_BN_CLICKED(IDC_ADD_OBJECT_BUTTON, OnAddObjectButton)
	ON_CBN_SELCHANGE(IDC_ADD_OBJECT_COMBO_BOX, OnSelchangeAddObjectComboBox)
	ON_CBN_SELCHANGE(IDC_CURRENT_OBJECT_COMBO, OnSelchangeCurrentObjectCombo)
	ON_BN_CLICKED(IDC_DELETE_CURRENT_OBJECT, OnDeleteCurrentObject)
	ON_BN_CLICKED(IDC_DELETE_ALL_OBJECTS, OnDeleteAllObjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/********************************************************/
/*                                                      */
/*   Object Manager Dialog Box Message Handlers.        */
/*                                                      */
/********************************************************/

BOOL CObjectManager::OnInitDialog() 
{
	// Init the basic dialog features.
	CDialog::OnInitDialog();
	
	m_ObjectFileNames.clear();

	struct _finddata_t c_file;
    long   hFile;
    int    trunc = 0;
    string next_name;

	// Populate the m_AddObjectComboBox
    if( (hFile = _findfirst( "NewObjects/*.D3", &c_file )) == -1L )
       return FALSE;

 	else
    {
       next_name = c_file.name;
       m_ObjectFileNames.push_back(next_name);
       trunc = next_name.find_first_of(".");
       next_name.resize(trunc);

       m_AddObjectComboBox.AddString(next_name.c_str());
    } // end else     
    while( _findnext( hFile, &c_file ) == 0 )
    {
       next_name = c_file.name;
       m_ObjectFileNames.push_back(next_name);
       trunc = next_name.find_first_of(".");
       next_name.resize(trunc);

       m_AddObjectComboBox.AddString(next_name.c_str());
    }// end while

	m_CurSel = 0;
	m_AddObjectComboBox.SetCurSel(m_CurSel);

	// if there are currently objects in the pDoc->m_Objects
	// vector, add those to the dialog box.
	UpdateDisplayedObjectsListBox();
	UpdateCurrentObjectComboBox();

	return TRUE;
}

void CObjectManager::OnAddObjectButton() 
// This function will add an object to the view variable
// vector<Object> m_Objects.
{
	string     file_name;
	string     object_name;
	ifstream   in_file;
	int        number_of_points = 0;
	int        number_of_facets = 0;
	int        point_number = 0;
	int        facet_number = 0;
	Object3D   NewObject;

	// Only allow the user to add 10 objects.
	if(pDoc->m_Objects.size() > 9)
	{
		MessageBox("Cannot display more than 10 objects",
			       "Object buffer full", MB_OK);
		return;
	}// end if

	// Get the name of the selection in the combo box.
	if(m_CurSel < 0 || m_CurSel > m_ObjectFileNames.size())
	{
		MessageBox("Invalid object name", "Error", MB_OK);
		return;
	}// end if

	if(m_ObjectFileNames[m_CurSel] == "LIGHT.D3")
	{
		string warning;

		warning="You cannot add light objects through the object\n";
		warning.append("manager.  Use the Light Parameters Dialog\n");
		warning.append("boxes to activate light sources.\n");

		MessageBox(warning.c_str(), "Not a valid object", MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	file_name = "NewObjects/";
	file_name.append(m_ObjectFileNames[m_CurSel]);

	in_file.open(file_name.c_str(), ios::in);

	if(in_file.fail())
	{
		MessageBox("File not found", "Error", MB_OK);
		return;
	}// end if

	// Read in the information in the file and 
	// store in a new Object.
	in_file >> object_name;	

	NewObject.SetObjectName(object_name);

	in_file >> number_of_points;

	NewObject.SetPointVectorSize(number_of_points);

	for(int i=0; i<number_of_points; ++i)
	{
		in_file >> point_number;

		point NewPoint;

		in_file >> NewPoint._x;
		in_file >> NewPoint._y;
		in_file >> NewPoint._z;
		NewPoint._h = 1.0;

		NewObject.SetObjectPoint(i, NewPoint);
	}// end for

	in_file >> number_of_facets;

	for(int j=0; j<number_of_facets; ++j)
	{
		in_file >> facet_number;

		facet NewFacet;

		in_file >> NewFacet._color;
		in_file >> NewFacet._corner1;
		in_file >> NewFacet._corner2;
		in_file >> NewFacet._corner3;

		NewObject.SetObjectFacet(NewFacet);
	}// end for

	// Create the m_FacetDistances data structure from the
	// list of facets in the object being added.
	NewObject.GenerateFacetDistanceVector(m_Camera, pDoc->m_ProjectionMethod);

	// The data has been read from the file.  Enter this 
	// object in the document variable m_Objects.
	pDoc->m_Objects.push_back(NewObject);

	// if only one object, set the current object to the
	// first object in the vector;
	if(pDoc->m_Objects.size() == 1)
	{
		pDoc->m_CurrentObject = 0;
	}// end if

	// Update the list of displayed objects.
	UpdateDisplayedObjectsListBox();
	
	// Update the list of current objects.
	UpdateCurrentObjectComboBox();
}



void CObjectManager::OnSelchangeAddObjectComboBox() 
// This function changes the current selection of the 
// combo box to what the user has selected.
{
	m_CurSel = m_AddObjectComboBox.GetCurSel();		
}


void CObjectManager::UpdateDisplayedObjectsListBox()
// This function updates the list of current objects displayed
// in the displayed items list box of the object manager.
{
	// Clear the list box.
	m_DisplayedObjectsListBox.ResetContent();
	
	// Repopulate the list box with the contents of the
	// pDoc->m_Objects vector names.
	for(int i=0; i<pDoc->m_Objects.size(); ++i)
	{
		string next_object;

		next_object = pDoc->m_Objects[i].GetObjectName();

		// mark the current object.
		if(pDoc->m_CurrentObject == i)
		{
			next_object.append("*");
		}// end if

		m_DisplayedObjectsListBox.AddString(next_object.c_str());
	}// end for
}


void CObjectManager::UpdateCurrentObjectComboBox()
// This function populates the current object combo box to
// reflect which object is the current object and allows the 
// user to select which object is the current object.
{
	// erase the current contents of the combo box.
	m_CurrentObjectComboBox.ResetContent();

	// populate the current object combo box.
	for(int i=0; i<pDoc->m_Objects.size(); ++i)
	{
		string next_object;
		
		next_object = pDoc->m_Objects[i].GetObjectName();

		// mark the current object.
		if(pDoc->m_CurrentObject == i)
		{
			next_object.append("*");
		}// end if

		m_CurrentObjectComboBox.AddString(next_object.c_str());
	}// end for

	m_CurrentObjectComboBox.SetCurSel(pDoc->m_CurrentObject);	
}


void CObjectManager::OnSelchangeCurrentObjectCombo() 
// This function changes the current object and resets the combo and 
// list box object to reflect the current object selected.
{
	int selection = m_CurrentObjectComboBox.GetCurSel();

	if(pDoc->m_Objects[selection].GetObjectName() == "Light")
	{
		string warning;

		warning="You cannot select a light objects as the current object.\n";
		warning.append("To modify a light, use the Light Parameters Dialog\n");
		warning.append("box to activate light sources.\n");

		MessageBox(warning.c_str(), "Not a valid object", MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	pDoc->m_CurrentObject = m_CurrentObjectComboBox.GetCurSel();
	
	// Update the combo/list boxes to reflect changes
	// made to the current object.
	UpdateDisplayedObjectsListBox();
	UpdateCurrentObjectComboBox();	
	
}


void CObjectManager::OnDeleteCurrentObject()
// Clicking this button will delete the current object.  Prompt 
// user for confirmation.  If true, then delete the object and set
// the first object in the list the active object. 
{
	if(pDoc->m_Objects.size() < 1)
	{
		MessageBox("No current object selected.", "Error", MB_OK);
		return;
	}
	else if(IDYES == MessageBox("Delete the current object?",
		       "Warning", MB_YESNO))
	{
		vector<Object3D>::iterator pos;

		pos = pDoc->m_Objects.begin();

		for(int i=0; i<pDoc->m_Objects.size(); ++i)
		{
			if(i == pDoc->m_CurrentObject)
			{
				break;
			}// end if

			++pos;

		}// end for

		// erase the current object.
		pDoc->m_Objects.erase(pos);
			
		// set the current object to 0 if the objects vector has 
		// members, -1 if it is empty.
		if(pDoc->m_Objects.size() > 0)
		{
			pDoc->m_CurrentObject = 0;
		}// end if
		else
		{
			pDoc->m_CurrentObject = -1;
		}// end else if

		UpdateDisplayedObjectsListBox();
		UpdateCurrentObjectComboBox();

	}// end if
}


void CObjectManager::OnDeleteAllObjects() 
// Clicking on this button will delete all the objects 
// within the pDoc->m_Objects vector.  Prompt the user 
// for confirmation.  If true, then delete all the objects
// and set the current object to -1.
{
	if(IDYES == MessageBox("Deleting all objects will destroy all transformations.  Continue?",
		       "Warning", MB_YESNO))
	{
		pDoc->m_Objects.clear();

		UpdateDisplayedObjectsListBox();
		UpdateCurrentObjectComboBox();

		pDoc->m_CurrentObject = -1;

	}// end if
}








