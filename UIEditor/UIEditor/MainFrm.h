// MainFrm.h

#pragma once

#include "WorkspaceBar.h"
#include "PropertiesBar.h"
#include "OutputBar.h"

class CMainFrame : public CBCGPFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual	~CMainFrame();

	virtual	BOOL	PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual	void	AssertValid() const;
	virtual	void	Dump(CDumpContext& dc) const;
#endif

	CBCGPStatusBar	m_wndStatusBar;
	CBCGPMenuBar	m_wndMenuBar;
	CBCGPToolBar	m_wndToolBar;
	CWorkspaceBar	m_wndWorkspace;
	CPropertiesBar	m_wndProperties;
	COutputBar		m_wndOutput;

protected:
	afx_msg	int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg	void	OnViewCustomize();
	afx_msg	LRESULT	OnToolbarReset(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};
