// MainFrm.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
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
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CBCGPVisualManager::SetDefaultManager(RUNTIME_CLASS(CBCGPVisualManagerVS2008));
	CBCGPDockManager::SetDockMode(BCGP_DT_SMART);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create Menu Bar\n");
		return -1;
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	CClientDC	dc(this);
	BOOL		bIsHighColor	= (dc.GetDeviceCaps(BITSPIXEL) > 8);
	UINT		uiToolbarHotID	= (bIsHighColor ? IDB_TOOLBAR256 : 0);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create Toolbar\n");
		return -1;
	}

	if ((!m_wndStatusBar.Create(this)) || (!m_wndStatusBar.SetIndicators(indicators, (sizeof(indicators) / sizeof(UINT)))))
	{
		TRACE0("Failed to create Status Bar\n");
		return -1;
	}

	CBCGPToolBarImages	imagesWorkspace;

	imagesWorkspace.SetImageSize(CSize (16, 16));
	imagesWorkspace.SetTransparentColor(RGB(255, 0, 255));
	imagesWorkspace.Load(IDB_WORKSPACE);
	
	if ((!m_wndWorkspace.Create(_T("작업 공간"), this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_WORKSPACE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI)))
	{
		TRACE0("Failed to create Workspace\n");

		return -1;
	}

	m_wndWorkspace.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);

	if ((!m_wndProperties.Create(_T("속성"), this, CSize(150, 150), TRUE, ID_VIEW_PROPERTIES, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_FLOAT_MULTI)))
	{
		TRACE0("Failed to create Properties Bar\n");

		return -1;
	}

	if ((!m_wndOutput.Create(_T("출력"), this, CSize(150, 150), TRUE, ID_VIEW_OUTPUT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLOAT_MULTI)))
	{
		TRACE0("Failed to create Output Bar\n");

		return -1;
	}

	CString	strMainToolbarTitle;

	strMainToolbarTitle.LoadString(IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText(strMainToolbarTitle);

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkspace.EnableDocking(CBRS_ALIGN_ANY);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndWorkspace);
	DockControlBar(&m_wndProperties);
	DockControlBar(&m_wndOutput);

	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, _T("사용자 정의..."));
	EnableControlBarMenu(TRUE, ID_VIEW_CUSTOMIZE, _T("사용자 정의..."), ID_VIEW_TOOLBARS);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CBCGPFrameWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}

	cs.style	= WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CMainFrame::OnViewCustomize()
{
	MessageBox(_T("사용자 정의 기능을 지원하지 않도록 설정되어 있습니다"), _T("UI Editor"), MB_OK | MB_ICONINFORMATION);

#if FALSE
	CBCGPToolbarCustomize*	pDlgCust	= new CBCGPToolbarCustomize(this, TRUE);

	pDlgCust->Create();
#endif
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM, LPARAM)
{
	return 0;
}
