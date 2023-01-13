// UIEditor.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "MainFrm.h"
#include "ShellUtilities.h"
#include "UIEditorDoc.h"
#include "UIEditorView.h"
#include "WizardDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CUIEditorApp, CWinApp)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_TOOLS_OPTIONS, CUIEditorApp::OnToolsOptions)
END_MESSAGE_MAP()

CUIEditorApp::CUIEditorApp() : CBCGPWorkspace (TRUE)
{
	TCHAR	szStartup[MAX_PATH + 1];

	TakePath(__wargv[0], szStartup, MAX_PATH + 1);

	m_strAppFolder	= szStartup;
}

CUIEditorApp theApp;

void CUIEditorApp::PreLoadState()
{
}

BOOL CUIEditorApp::InitInstance()
{
	INITCOMMONCONTROLSEX	InitCtrls;

	InitCtrls.dwSize	= sizeof(InitCtrls);
	InitCtrls.dwICC		= ICC_WIN95_CLASSES;

	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	SetRegistryKey(_T("SK OCBS Telematics Applications"));
	LoadStdProfileSettings(_AFX_MRU_COUNT);
	SetRegistryBase (_T("Settings"));

	InitTooltipManager();

	CBCGPToolTipParams	params;

	params.m_bVislManagerTheme	= TRUE;

	theApp.GetTooltipManager()->SetTooltipParams(BCGP_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CBCGPToolTipCtrl), &params);

	CSingleDocTemplate*	pDocTemplate;

	pDocTemplate	= new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CUIEditorDoc), RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CUIEditorView));

	if (!pDocTemplate)
	{
		return FALSE;
	}

	AddDocTemplate(pDocTemplate);

	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	CCommandLineInfo	cmdInfo;

	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		CWizardDialog	dWizard;

		if (dWizard.DoModal() == IDCANCEL)
		{
			return FALSE;
		}

		switch (dWizard.m_nWizardMode)
		{
		case WIZ_OPEN:
			{
				TCHAR		szFilters[]	= _T("UI ÆÄÀÏ (*.ui)|*.ui||");
				CFileDialog	dOpen(TRUE, _T("ui"), _T("*.ui"), OFN_FILEMUSTEXIST, szFilters, AfxGetApp()->GetMainWnd());

				if (dOpen.DoModal() != IDOK)
				{
					return FALSE;
				}
				
				cmdInfo.m_nShellCommand	= CCommandLineInfo::FileOpen;
				cmdInfo.m_strFileName	= dOpen.GetPathName();
			}
			break;
		case WIZ_NEW:
		default:
			{
				// Do nothing, because all information is already ready
			}
			break;
		}
	}

	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

#if FALSE
	m_pMainWnd->DragAcceptFiles();
#endif

	return TRUE;
}

int CUIEditorApp::ExitInstance() 
{
	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

CString CUIEditorApp::GetAppFolder()
{
	return m_strAppFolder;
}

void CUIEditorApp::OnToolsOptions()
{
}
