// UIEditor.h

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#ifndef	DEF_RESOLUTION
#define	DEF_RESOLUTION
#define	MIN_WIDTH		120
#define	MIN_HEIGHT		120
#define	DEF_WIDTH		800
#define	DEF_HEIGHT		480
#define	MAX_WIDTH		2048
#define	MAX_HEIGHT		2048
#endif

#include "Resource.h"
#include "BasicDef.h"

class CUIEditorApp : public CWinApp, public CBCGPWorkspace
{
public:
	CUIEditorApp();

	virtual	void	PreLoadState();
	virtual	BOOL	InitInstance();
	virtual	int		ExitInstance();

	CString	GetAppFolder();

	afx_msg	void	OnToolsOptions();

protected:
	CString	m_strAppFolder;

	DECLARE_MESSAGE_MAP()
};

extern CUIEditorApp theApp;
