

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

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};



CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CMenu* pMenu   = GetMenu();

	pMenu->CheckMenuItem(IDM_WIRE_FRAME, MF_CHECKED);
	pMenu->CheckMenuItem(IDM_WIRE_FRAME_DEPTH_CUE, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_WIRE_FRAME_BACKFACE_ELIMINATION, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_PAINTERS_ALGORITHM, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_PAINTERS_ALGORITHM_TRACED_FACETS, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_GOURAUD_SHADING, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_PHONG_SHADING, MF_UNCHECKED);

	pMenu->CheckMenuItem(ID_LIGHTSOURCES_DISPLAYLIGHTSASOBJECTS, MF_UNCHECKED);
	pMenu->CheckMenuItem(ID_LIGHTSOURCES_SHOWLIGHTCOLORRINGS, MF_UNCHECKED);

	pMenu->CheckMenuItem(IDM_DRAW_AXIS, MF_UNCHECKED);
	pMenu->CheckMenuItem(IDM_MOUSE_CAMERA_PAN, MF_UNCHECKED);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 600;
	cs.cy = 500;
	cs.x  = 100;
	cs.y  = 100;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG




