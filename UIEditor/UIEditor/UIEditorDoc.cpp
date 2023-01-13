// UIEditorDoc.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "MainFrm.h"
#include "UIEditorDoc.h"
#include "ImageHandle.h"
#include "UIBin.h"
#include "ShellUtilities.h"
#include "FolderSelectDialog.h"
#include "ResolutionDialog.h"
#include "SelectDialog.h"
#include "MultiDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CUIEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CUIEditorDoc, CDocument)
	ON_COMMAND(ID_FILE_MERGE, CUIEditorDoc::OnFileMerge)
	ON_COMMAND(ID_FILE_DB_EXPORT, CUIEditorDoc::OnFileDBExport)
	ON_COMMAND(ID_FILE_IMAGE_EXPORT, CUIEditorDoc::OnFileImageExport)
	ON_COMMAND(ID_FILE_IMAGE_IMPORT, CUIEditorDoc::OnFileImageImport)
	ON_COMMAND(ID_EDIT_COPY, CUIEditorDoc::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CUIEditorDoc::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, CUIEditorDoc::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CUIEditorDoc::OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, CUIEditorDoc::OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, &CUIEditorDoc::OnUpdateEditClear)
	ON_COMMAND(ID_ACTION_GROUP_ADD, &CUIEditorDoc::OnActionGroupAdd)
	ON_COMMAND(ID_ACTION_GROUP_DELETE, &CUIEditorDoc::OnActionGroupDelete)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP_DELETE, &CUIEditorDoc::OnUpdateActionGroupDelete)
	ON_COMMAND(ID_ACTION_GROUP_ACTIVE, &CUIEditorDoc::OnActionGroupActive)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP_ACTIVE, &CUIEditorDoc::OnUpdateActionGroupActive)
	ON_COMMAND(ID_ACTION_PAGE_ADD, &CUIEditorDoc::OnActionPageAdd)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_ADD, &CUIEditorDoc::OnUpdateActionPageAdd)
	ON_COMMAND(ID_ACTION_PAGE_DELETE, &CUIEditorDoc::OnActionPageDelete)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_DELETE, &CUIEditorDoc::OnUpdateActionPageDelete)
	ON_COMMAND(ID_ACTION_PAGE_MOVE_TOP, &CUIEditorDoc::OnActionPageMoveTop)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_MOVE_TOP, &CUIEditorDoc::OnUpdateActionPageMoveTop)
	ON_COMMAND(ID_ACTION_PAGE_MOVE_UP, &CUIEditorDoc::OnActionPageMoveUp)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_MOVE_UP, &CUIEditorDoc::OnUpdateActionPageMoveUp)
	ON_COMMAND(ID_ACTION_PAGE_MOVE_DOWN, &CUIEditorDoc::OnActionPageMoveDown)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_MOVE_DOWN, &CUIEditorDoc::OnUpdateActionPageMoveDown)
	ON_COMMAND(ID_ACTION_PAGE_MOVE_BOTTOM, &CUIEditorDoc::OnActionPageMoveBottom)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_MOVE_BOTTOM, &CUIEditorDoc::OnUpdateActionPageMoveBottom)
	ON_COMMAND(ID_ACTION_PAGE_GENERATE, &CUIEditorDoc::OnActionPageGenerate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_PAGE_GENERATE, &CUIEditorDoc::OnUpdateActionPageGenerate)
	ON_COMMAND(ID_ACTION_CTRL_ADD, &CUIEditorDoc::OnActionCtrlAdd)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CTRL_ADD, &CUIEditorDoc::OnUpdateActionCtrlAdd)
	ON_COMMAND(ID_ACTION_CTRL_DELETE, &CUIEditorDoc::OnActionCtrlDelete)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CTRL_DELETE, &CUIEditorDoc::OnUpdateActionCtrlDelete)
	ON_COMMAND(ID_ACTION_CTRL_MOVE_TOP, &CUIEditorDoc::OnActionCtrlMoveTop)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CTRL_MOVE_TOP, &CUIEditorDoc::OnUpdateActionCtrlMoveTop)
	ON_COMMAND(ID_ACTION_CTRL_MOVE_UP, &CUIEditorDoc::OnActionCtrlMoveUp)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CTRL_MOVE_UP, &CUIEditorDoc::OnUpdateActionCtrlMoveUp)
	ON_COMMAND(ID_ACTION_CTRL_MOVE_DOWN, &CUIEditorDoc::OnActionCtrlMoveDown)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CTRL_MOVE_DOWN, &CUIEditorDoc::OnUpdateActionCtrlMoveDown)
	ON_COMMAND(ID_ACTION_CTRL_MOVE_BOTTOM, &CUIEditorDoc::OnActionCtrlMoveBottom)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CTRL_MOVE_BOTTOM, &CUIEditorDoc::OnUpdateActionCtrlMoveBottom)
	ON_COMMAND(ID_ACTION_IMAGE_ADD, &CUIEditorDoc::OnActionImageAdd)
	ON_UPDATE_COMMAND_UI(ID_ACTION_IMAGE_ADD, &CUIEditorDoc::OnUpdateActionImageAdd)
	ON_COMMAND(ID_ACTION_IMAGE_DELETE, &CUIEditorDoc::OnActionImageDelete)
	ON_UPDATE_COMMAND_UI(ID_ACTION_IMAGE_DELETE, &CUIEditorDoc::OnUpdateActionImageDelete)
	ON_COMMAND(ID_ACTION_IMAGE_MOVE_TOP, &CUIEditorDoc::OnActionImageMoveTop)
	ON_UPDATE_COMMAND_UI(ID_ACTION_IMAGE_MOVE_TOP, &CUIEditorDoc::OnUpdateActionImageMoveTop)
	ON_COMMAND(ID_ACTION_IMAGE_MOVE_UP, &CUIEditorDoc::OnActionImageMoveUp)
	ON_UPDATE_COMMAND_UI(ID_ACTION_IMAGE_MOVE_UP, &CUIEditorDoc::OnUpdateActionImageMoveUp)
	ON_COMMAND(ID_ACTION_IMAGE_MOVE_DOWN, &CUIEditorDoc::OnActionImageMoveDown)
	ON_UPDATE_COMMAND_UI(ID_ACTION_IMAGE_MOVE_DOWN, &CUIEditorDoc::OnUpdateActionImageMoveDown)
	ON_COMMAND(ID_ACTION_IMAGE_MOVE_BOTTOM, &CUIEditorDoc::OnActionImageMoveBottom)
	ON_UPDATE_COMMAND_UI(ID_ACTION_IMAGE_MOVE_BOTTOM, &CUIEditorDoc::OnUpdateActionImageMoveBottom)
	ON_COMMAND(ID_TOOLS_LOG_SAVE, &CUIEditorDoc::OnToolsLogSave)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_LOG_SAVE, &CUIEditorDoc::OnUpdateToolsLogSave)
	ON_COMMAND(ID_TOOLS_LOG_CLEAN, &CUIEditorDoc::OnToolsLogClean)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_LOG_CLEAN, &CUIEditorDoc::OnUpdateToolsLogClean)
	ON_COMMAND(ID_TOOLS_CHECK, &CUIEditorDoc::OnToolsCheck)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CHECK, &CUIEditorDoc::OnUpdateToolsCheck)
END_MESSAGE_MAP()

CUIEditorDoc::CUIEditorDoc()
{
}

CUIEditorDoc::~CUIEditorDoc()
{
}

CUIEditorDoc* CUIEditorDoc::GetUIDocument()
{
	CFrameWnd*	pFrame	= (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	return (CUIEditorDoc*)pFrame->GetActiveDocument();
}

BOOL CUIEditorDoc::OnNewDocument()
{
	DECLARE_FRAME()

	CFolderSelectDialog	dFolder;
	CResolutionDialog	dResolution;
	CString				strUIFolder;
	TCHAR				szCurrentFolder[MAX_PATH + 1];

	if (!CDocument::OnNewDocument())
	{
		OUTPUT_STR0(_T("Failed to create new document"));

		return FALSE;
	}

	GetCurrentDirectory(MAX_PATH + 1, szCurrentFolder);

	strUIFolder	= AfxGetApp()->GetProfileString(_T("Settings"), _T("UI Folder"), szCurrentFolder);

	dFolder.m_strFolder	= strUIFolder;

	if (dFolder.DoModal() != IDOK)
	{
		OUTPUT_STR0(_T("Creating new document was cancelled by user"));

		return FALSE;
	}
	
	m_strFolder	= dFolder.m_strFolder;

	AfxGetApp()->WriteProfileString(_T("Settings"), _T("UI Folder"), m_strFolder);

	if (!ShellCreate(m_strFolder))
	{
		OUTPUT_STR1(_T("Failed to create working directory %s"), m_strFolder);

		return FALSE;
	}

	if (dResolution.DoModal() != IDOK)
	{
		OUTPUT_STR0(_T("Creating new document was cancelled by user"));

		return FALSE;
	}

	AddGroup(dResolution.m_nWidth, dResolution.m_nHeight, UI_INVALIDID);
	AddPage();

	SetModifiedFlag();

	OUTPUT_STR0(_T("New document has been created"));

	return TRUE;
}

BOOL CUIEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	DECLARE_FRAME()

	CString	strPath	= lpszPathName;
	int		nPos	= strPath.ReverseFind(_T('.'));
	BOOL	bRetCode;

	m_strFileName	= lpszPathName;
	m_strFolder		= strPath.Left(nPos);

	if (!ShellCreate(m_strFolder))
	{
		OUTPUT_STR1(_T("Failed to create working directory %s"), m_strFolder);

		return FALSE;
	}

	bRetCode	= CDocument::OnOpenDocument(lpszPathName);

	if (bRetCode)
	{
		OUTPUT_STR1(_T("Document %s has been opened"), lpszPathName);
	}
	else
	{
		OUTPUT_STR1(_T("Failed to open document %s"), lpszPathName);
	}

	return bRetCode;
}

BOOL CUIEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	DECLARE_FRAME()

	CString	strFolder;
	CString	strPath;
	int		nPos;
	CString	strSource;
	CString	strTarget;
	int		lp;
	BOOL	bRetCode;

	if (_tcscmp(lpszPathName, m_strFileName))
	{
		strPath		= lpszPathName;
		nPos		= strPath.ReverseFind(_T('.'));
		strFolder	= strPath.Left(nPos);

		if (!ShellCreate(strFolder))
		{
			OUTPUT_STR1(_T("Failed to create working directory %s"), strFolder);

			return FALSE;
		}

		for (lp = 0; lp < static_cast<int>(m_arrUIGroup.GetCount()); lp++)
		{
			strSource.Format(_T("%s\\%08X"), strFolder, m_arrUIGroup.GetAt(lp).dwGroupID);

			if (!ShellCreate(strSource))
			{
				OUTPUT_STR1(_T("Failed to create working directory %s"), strSource);

				return FALSE;
			}

			strSource.Format(_T("%s\\%08X\\*.*"), m_strFolder, m_arrUIGroup.GetAt(lp).dwGroupID);
			strTarget.Format(_T("%s\\%08X"), strFolder, m_arrUIGroup.GetAt(lp).dwGroupID);

			if (ShellCopy(strSource, strTarget))
			{
				OUTPUT_STR0(_T("All item files have been copied"));
			}
			else
			{
				OUTPUT_STR0(_T("Failed to copy item files"));
			}

			strSource.Format(_T("%s\\%08X"), m_strFolder, m_arrUIGroup.GetAt(lp).dwGroupID);

			ShellDelete(strSource);
		}

		m_strFolder		= strFolder;
		m_strFileName	= lpszPathName;
	}
	else
	{
		strPath		= lpszPathName;
		nPos		= strPath.ReverseFind(_T('.'));
		strTarget	= strPath.Left(nPos + 1);
		strTarget	+= _T("bak");

		ShellCopy(lpszPathName, strTarget);
	}

	bRetCode	= CDocument::OnSaveDocument(lpszPathName);

	if (bRetCode)
	{
		OUTPUT_STR1(_T("Document %s has been saved"), lpszPathName);
	}
	else
	{
		OUTPUT_STR1(_T("Failed to save document %s"), lpszPathName);
	}

	return bRetCode;
}

void CUIEditorDoc::Serialize(CArchive& ar)
{
	DECLARE_FRAME()

	int		lp1;
	int		lp2;
	CString	strImageName;

	WND_OUTPUT.SetMultipleAdd(TRUE);

	if (ar.IsStoring())
	{
		m_tUIHeader.dwSaveCount++;
		m_tUIHeader.dwGroups	= static_cast<DWORD>(m_arrUIGroup.GetCount());
		m_tUIHeader.dwPages		= static_cast<DWORD>(m_arrUIPageC.GetCount());
		m_tUIHeader.dwCtrls		= static_cast<DWORD>(m_arrUICtrlC.GetCount());
		m_tUIHeader.dwImages	= static_cast<DWORD>(m_arrUIImageC.GetCount());
		m_tUIHeader.nCType		= m_nCType;
		m_tUIHeader.dwCGroupID	= m_dwCGroupID;
		m_tUIHeader.dwCPageID	= m_dwCPageID;
		m_tUIHeader.dwCCtrlID	= m_dwCCtrlID;
		m_tUIHeader.dwCImageID	= m_dwCImageID;

		ar.Write(&m_tUIHeader, sizeof(UI_HEADER));

		OUTPUT_STR0(_T("UI Header has been saved"));

		for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
		{
			ar.Write(&m_arrUIGroup.GetAt(lp1), sizeof(UI_GROUP));

			OUTPUT_STR3(_T("Group [%d] %08X [%s] has been saved"), lp1, m_arrUIGroup.GetAt(lp1).dwGroupID, m_arrUIGroup.GetAt(lp1).szName);
		}

		for (lp1 = 0; lp1 < m_arrUIPageC.GetCount(); lp1++)
		{
			ar.Write(&m_arrUIPageC.GetAt(lp1), sizeof(UI_PAGEC));

			OUTPUT_STR3(_T("PageC [%d] %08X [%s] has been saved"), lp1, m_arrUIPageC.GetAt(lp1).dwPageID, m_arrUIPageC.GetAt(lp1).szName);
		}

		for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
		{
			ar.Write(&m_arrUICtrlC.GetAt(lp1), sizeof(UI_CTRLC));

			OUTPUT_STR3(_T("CtrlC [%d] %08X [%s] has been saved"), lp1, m_arrUICtrlC.GetAt(lp1).dwCtrlID, m_arrUICtrlC.GetAt(lp1).szName);
		}

		for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
		{
			ar.Write(&m_arrUIImageC.GetAt(lp1), sizeof(UI_IMAGEC));

			OUTPUT_STR3(_T("ImageC [%d] %08X [%s] has been saved"), lp1, m_arrUIImageC.GetAt(lp1).dwImageID, m_arrUIImageC.GetAt(lp1).szName);
		}

		for (lp1 = 0; lp1 < m_arrUIPageS.GetCount(); lp1++)
		{
			ar.Write(&m_arrUIPageS.GetAt(lp1), sizeof(UI_PAGES));

			OUTPUT_STR3(_T("PageS [%d: %08X/%08X] has been saved"), lp1, m_arrUIPageS.GetAt(lp1).dwPageID, m_arrUIPageS.GetAt(lp1).dwGroupID);
		}

		for (lp1 = 0; lp1 < m_arrUICtrlS.GetCount(); lp1++)
		{
			ar.Write(&m_arrUICtrlS.GetAt(lp1), sizeof(UI_CTRLS));

			OUTPUT_STR3(_T("CtrlS [%d: %08X/%08X] has been saved"), lp1, m_arrUICtrlS.GetAt(lp1).dwCtrlID, m_arrUICtrlS.GetAt(lp1).dwGroupID);
		}

		for (lp1 = 0; lp1 < m_arrUIImageS.GetCount(); lp1++)
		{
			ar.Write(&m_arrUIImageS.GetAt(lp1), sizeof(UI_IMAGES));

			OUTPUT_STR3(_T("ImageS [%d: %08X/%08X] has been saved"), lp1, m_arrUIImageS.GetAt(lp1).dwImageID, m_arrUIImageS.GetAt(lp1).dwGroupID);

			for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
			{
				if (m_arrUIImageC.GetAt(lp2).dwImageID == m_arrUIImageS.GetAt(lp1).dwImageID)
				{
					if (GetImageFullPath(strImageName, m_arrUIImageC.GetAt(lp2), m_arrUIImageS.GetAt(lp1), TRUE))
					{
						SaveImageBuffer(ar, strImageName, m_arrUIImageS.GetAt(lp1).nType, m_arrUIImageS.GetAt(lp1).dwSize);

						OUTPUT_STR2(_T("Image %s [%08X] has been saved"), strImageName, m_arrUIImageC.GetAt(lp2).dwImageID);
					}
					else
					{
						OUTPUT_STR2(_T("Failed to save Image %s [%08X]"), strImageName, m_arrUIImageC.GetAt(lp2).dwImageID);
					}

					break;
				}
			}
		}

		OUTPUT_STR0(_T("All items has been saved"));
	}
	else
	{
		UI_GROUP	UIGroup;
		UI_PAGEC	UIPageC;
		UI_PAGES	UIPageS;
		UI_CTRLC	UICtrlC;
		UI_CTRLS	UICtrlS;
		UI_IMAGEC	UIImageC;
		UI_IMAGES	UIImageS;
		CString		strFolder;

		ar.Read(&m_tUIHeader, sizeof(UI_HEADER));

		OUTPUT_STR0(_T("UI Header has been loaded"));

		m_nCType		= m_tUIHeader.nCType;
		m_dwCGroupID	= m_tUIHeader.dwCGroupID;
		m_dwCPageID		= m_tUIHeader.dwCPageID;
		m_dwCCtrlID		= m_tUIHeader.dwCCtrlID;
		m_dwCImageID	= m_tUIHeader.dwCImageID;

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwGroups); lp1++)
		{
			ar.Read(&UIGroup, sizeof(UI_GROUP));
			m_arrUIGroup.Add(UIGroup);

			OUTPUT_STR3(_T("Group [%d] %08X [%s] has been loaded"), lp1, UIGroup.dwGroupID, UIGroup.szName);

			strFolder.Format(_T("%s\\%08X"), m_strFolder, UIGroup.dwGroupID);
			ShellCreate(strFolder);
		}

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwPages); lp1++)
		{
			ar.Read(&UIPageC, sizeof(UI_PAGEC));
			m_arrUIPageC.Add(UIPageC);

			OUTPUT_STR3(_T("PageC [%d] %08X [%s] has been loaded"), lp1, UIPageC.dwPageID, UIPageC.szName);

			for (lp2 = 0; lp2 < static_cast<int>(m_tUIHeader.dwGroups); lp2++)
			{
				strFolder.Format(_T("%s\\%08X\\%08X"), m_strFolder, m_arrUIGroup.GetAt(lp2).dwGroupID, UIPageC.dwPageID);
				ShellCreate(strFolder);
			}
		}

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwCtrls); lp1++)
		{
			ar.Read(&UICtrlC, sizeof(UI_CTRLC));
			m_arrUICtrlC.Add(UICtrlC);

			OUTPUT_STR3(_T("CtrlC [%d] %08X [%s] has been loaded"), lp1, UICtrlC.dwCtrlID, UICtrlC.szName);

			for (lp2 = 0; lp2 < static_cast<int>(m_tUIHeader.dwGroups); lp2++)
			{
				strFolder.Format(_T("%s\\%08X\\%08X\\%08X"), m_strFolder, m_arrUIGroup.GetAt(lp2).dwGroupID, UICtrlC.dwPageID, UICtrlC.dwCtrlID);
				ShellCreate(strFolder);
			}
		}

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwImages); lp1++)
		{
			ar.Read(&UIImageC, sizeof(UI_IMAGEC));
			m_arrUIImageC.Add(UIImageC);

			OUTPUT_STR3(_T("ImageC [%d] %08X [%s] has been loaded"), lp1, UIImageC.dwImageID, UIImageC.szName);
		}

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwGroups * m_tUIHeader.dwPages); lp1++)
		{
			ar.Read(&UIPageS, sizeof(UI_PAGES));
			m_arrUIPageS.Add(UIPageS);

			OUTPUT_STR3(_T("PageS [%d: %08X/%08X] has been loaded"), lp1, UIPageS.dwPageID, UIPageS.dwGroupID);
		}

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwGroups * m_tUIHeader.dwCtrls); lp1++)
		{
			ar.Read(&UICtrlS, sizeof(UI_CTRLS));
			m_arrUICtrlS.Add(UICtrlS);

			OUTPUT_STR3(_T("CtrlS [%d: %08X/%08X] has been loaded"), lp1, UICtrlS.dwCtrlID, UICtrlS.dwGroupID);
		}

		for (lp1 = 0; lp1 < static_cast<int>(m_tUIHeader.dwGroups * m_tUIHeader.dwImages); lp1++)
		{
			ar.Read(&UIImageS, sizeof(UI_IMAGES));
			m_arrUIImageS.Add(UIImageS);

			OUTPUT_STR3(_T("ImageS [%d: %08X/%08X] has been loaded"), lp1, UIImageS.dwImageID, UIImageS.dwGroupID);

			for (lp2 = 0; lp2 < static_cast<int>(m_tUIHeader.dwImages); lp2++)
			{
				if (m_arrUIImageC.GetAt(lp2).dwImageID == UIImageS.dwImageID)
				{
					if (GetImageFullPath(strImageName, m_arrUIImageC.GetAt(lp2), UIImageS, FALSE))
					{
						LoadImageBuffer(ar, strImageName, UIImageS.nType, UIImageS.dwSize);

						OUTPUT_STR2(_T("Image %s [%08X] has been loaded"), strImageName, m_arrUIImageC.GetAt(lp2).dwImageID);
						break;
					}
				}
			}
		}

		OUTPUT_STR0(_T("All items has been loaded"));
	}

	WND_OUTPUT.SetMultipleAdd(FALSE);
}

void CUIEditorDoc::DeleteContents()
{
	Initialize();

	CDocument::DeleteContents();
}

#ifdef _DEBUG
void CUIEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUIEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CUIEditorDoc::Initialize()
{
	// Initialize Summarized Information

	m_tUIHeader.dwHeaderID		= UI_HEADER_ID;
	m_tUIHeader.dwUIVersion		= UI_VERSION;
	m_tUIHeader.dwSaveCount		= 0;
	m_tUIHeader.dwExportCount	= 0;
	m_tUIHeader.dwGroups		= 0;
	m_tUIHeader.dwPages			= 0;
	m_tUIHeader.dwCtrls			= 0;
	m_tUIHeader.dwImages		= 0;
	m_tUIHeader.nCType			= UI_ITEM_NONE;
	m_tUIHeader.dwCGroupID		= UI_INVALIDID;
	m_tUIHeader.dwCPageID		= UI_INVALIDID;
	m_tUIHeader.dwCCtrlID		= UI_INVALIDID;
	m_tUIHeader.dwCImageID		= UI_INVALIDID;

	memset(m_tUIHeader.cReserved, 0, sizeof(BYTE) * 76);

	m_nCType					= UI_ITEM_NONE;
	m_dwCGroupID				= UI_INVALIDID;
	m_dwCPageID					= UI_INVALIDID;
	m_dwCCtrlID					= UI_INVALIDID;
	m_dwCImageID				= UI_INVALIDID;

	m_arrUIGroup.RemoveAll();
	m_arrUIPageC.RemoveAll();
	m_arrUIPageS.RemoveAll();
	m_arrUICtrlC.RemoveAll();
	m_arrUICtrlS.RemoveAll();
	m_arrUIImageC.RemoveAll();
	m_arrUIImageS.RemoveAll();

	ClearSelection();
	ClearClipboard();
	ClearMergeData();
};

DWORD CUIEditorDoc::GetNewGroupID()
{
	CDWordArray	arrID;
	CByteArray	arrFlags;
	int			lp1;
	int			lp2;
	BOOL		bFound;
	DWORD		dwID	= UI_INVALIDID;

	if (m_arrUIGroup.GetCount() == 0)
	{
		return 0;
	}

	// Build ID List

	for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
	{
		bFound	= FALSE;

		for (lp2 = 0; lp2 < arrID.GetCount(); lp2++)
		{
			if (arrID.GetAt(lp2) > m_arrUIGroup.GetAt(lp1).dwGroupID)
			{
				bFound	= TRUE;

				arrID.InsertAt(lp2, m_arrUIGroup.GetAt(lp1).dwGroupID);
				break;
			}
		}

		if (bFound == FALSE)
		{
			arrID.Add(m_arrUIGroup.GetAt(lp1).dwGroupID);
		}
	}

	// Build Flag List

	arrFlags.SetSize(arrID.GetAt(arrID.GetUpperBound()) + 1);

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		arrFlags.SetAt(lp1, 0);
	}

	for (lp1 = 0; lp1 < arrID.GetCount(); lp1++)
	{
		arrFlags.SetAt(arrID.GetAt(lp1), 1);
	}
	
	// Search available ID

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		if (arrFlags.GetAt(lp1) == 0)
		{
			dwID	= lp1;
			break;
		}
	}

	if (dwID == UI_INVALIDID)
	{
		dwID	= static_cast<DWORD>(arrFlags.GetCount());
	}

	return (dwID > UI_MAX_ID ? UI_NOMOREID : dwID);
}

DWORD CUIEditorDoc::GetNewPageID()
{
	CDWordArray	arrID;
	CByteArray	arrFlags;
	int			lp1;
	int			lp2;
	BOOL		bFound;
	DWORD		dwID	= UI_INVALIDID;

	if (m_arrUIPageC.GetCount() == 0)
	{
		return 0;
	}

	// Build ID List

	for (lp1 = 0; lp1 < m_arrUIPageC.GetCount(); lp1++)
	{
		bFound	= FALSE;

		for (lp2 = 0; lp2 < arrID.GetCount(); lp2++)
		{
			if (arrID.GetAt(lp2) > m_arrUIPageC.GetAt(lp1).dwPageID)
			{
				bFound	= TRUE;

				arrID.InsertAt(lp2, m_arrUIPageC.GetAt(lp1).dwPageID);
				break;
			}
		}

		if (bFound == FALSE)
		{
			arrID.Add(m_arrUIPageC.GetAt(lp1).dwPageID);
		}
	}

	// Build Flag List

	arrFlags.SetSize(arrID.GetAt(arrID.GetUpperBound()) + 1);

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		arrFlags.SetAt(lp1, 0);
	}

	for (lp1 = 0; lp1 < arrID.GetCount(); lp1++)
	{
		arrFlags.SetAt(arrID.GetAt(lp1), 1);
	}
	
	// Search available ID

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		if (arrFlags.GetAt(lp1) == 0)
		{
			dwID	= lp1;
			break;
		}
	}

	if (dwID == UI_INVALIDID)
	{
		dwID	= static_cast<DWORD>(arrFlags.GetCount());
	}

	return (dwID > UI_MAX_ID ? UI_NOMOREID : dwID);
}

DWORD CUIEditorDoc::GetNewCtrlID()
{
	CDWordArray	arrID;
	CByteArray	arrFlags;
	int			lp1;
	int			lp2;
	BOOL		bFound;
	DWORD		dwID	= UI_INVALIDID;

	if (m_arrUICtrlC.GetCount() == 0)
	{
		return 0;
	}

	// Build ID List

	for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
	{
		bFound	= FALSE;

		for (lp2 = 0; lp2 < arrID.GetCount(); lp2++)
		{
			if (arrID.GetAt(lp2) > m_arrUICtrlC.GetAt(lp1).dwCtrlID)
			{
				bFound	= TRUE;

				arrID.InsertAt(lp2, m_arrUICtrlC.GetAt(lp1).dwCtrlID);
				break;
			}
		}

		if (bFound == FALSE)
		{
			arrID.Add(m_arrUICtrlC.GetAt(lp1).dwCtrlID);
		}
	}

	// Build Flag List

	arrFlags.SetSize(arrID.GetAt(arrID.GetUpperBound()) + 1);

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		arrFlags.SetAt(lp1, 0);
	}

	for (lp1 = 0; lp1 < arrID.GetCount(); lp1++)
	{
		arrFlags.SetAt(arrID.GetAt(lp1), 1);
	}
	
	// Search available ID

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		if (arrFlags.GetAt(lp1) == 0)
		{
			dwID	= lp1;
			break;
		}
	}

	if (dwID == UI_INVALIDID)
	{
		dwID	= static_cast<DWORD>(arrFlags.GetCount());
	}

	return (dwID > UI_MAX_ID ? UI_NOMOREID : dwID);
}

DWORD CUIEditorDoc::GetNewImageID()
{
	CDWordArray	arrID;
	CByteArray	arrFlags;
	int			lp1;
	int			lp2;
	BOOL		bFound;
	DWORD		dwID	= UI_INVALIDID;

	if (m_arrUIImageC.GetCount() == 0)
	{
		return 0;
	}

	// Build ID List

	for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
	{
		bFound	= FALSE;

		for (lp2 = 0; lp2 < arrID.GetCount(); lp2++)
		{
			if (arrID.GetAt(lp2) > m_arrUIImageC.GetAt(lp1).dwImageID)
			{
				bFound	= TRUE;

				arrID.InsertAt(lp2, m_arrUIImageC.GetAt(lp1).dwImageID);
				break;
			}
		}

		if (bFound == FALSE)
		{
			arrID.Add(m_arrUIImageC.GetAt(lp1).dwImageID);
		}
	}

	// Build Flag List

	arrFlags.SetSize(arrID.GetAt(arrID.GetUpperBound()) + 1);

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		arrFlags.SetAt(lp1, 0);
	}

	for (lp1 = 0; lp1 < arrID.GetCount(); lp1++)
	{
		arrFlags.SetAt(arrID.GetAt(lp1), 1);
	}
	
	// Search available ID

	for (lp1 = 0; lp1 < arrFlags.GetCount(); lp1++)
	{
		if (arrFlags.GetAt(lp1) == 0)
		{
			dwID	= lp1;
			break;
		}
	}

	if (dwID == UI_INVALIDID)
	{
		dwID	= static_cast<DWORD>(arrFlags.GetCount());
	}

	return (dwID > UI_MAX_ID ? UI_NOMOREID : dwID);
}

DWORD CUIEditorDoc::GetGroupByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
	{
		if (dwID == m_arrUIGroup.GetAt(lp).dwGroupID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

DWORD CUIEditorDoc::GetPageByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrUIPageC.GetCount(); lp++)
	{
		if (dwID == m_arrUIPageC.GetAt(lp).dwPageID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

DWORD CUIEditorDoc::GetCtrlByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrUICtrlC.GetCount(); lp++)
	{
		if (dwID == m_arrUICtrlC.GetAt(lp).dwCtrlID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

DWORD CUIEditorDoc::GetImageByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrUIImageC.GetCount(); lp++)
	{
		if (dwID == m_arrUIImageC.GetAt(lp).dwImageID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

BOOL CUIEditorDoc::GetImageFullPath(CString& strImageName, UI_IMAGEC& UIImageC, UI_IMAGES& UIImageS, BOOL bMustExist)
{
	CString		strBuffer;
	CString		strPath;
	int			lp;
	BOOL		bFound;
	CFileStatus	fs;

	strImageName	= _T("");
	strPath			= m_strFolder + _T("\\");
	bFound			= FALSE;

	for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
	{
		if (m_arrUIGroup.GetAt(lp).dwGroupID == UIImageS.dwGroupID)
		{
			strBuffer.Format(_T("%08X"), m_arrUIGroup.GetAt(lp).dwGroupID);

			strPath	+= strBuffer;
			strPath	+= _T("\\");
			bFound	= TRUE;
			break;
		}
	}

	if (bFound == FALSE)
	{
		return FALSE;
	}

	bFound	= FALSE;

	for (lp = 0; lp < m_arrUIPageC.GetCount(); lp++)
	{
		if (m_arrUIPageC.GetAt(lp).dwPageID == UIImageC.dwPageID)
		{
			strBuffer.Format(_T("%08X"), m_arrUIPageC.GetAt(lp).dwPageID);

			strPath	+= strBuffer;
			strPath	+= _T("\\");
			bFound	= TRUE;
			break;
		}
	}

	if (bFound == FALSE)
	{
		return FALSE;
	}

	bFound	= FALSE;

	for (lp = 0; lp < m_arrUICtrlC.GetCount(); lp++)
	{
		if (m_arrUICtrlC.GetAt(lp).dwCtrlID == UIImageC.dwCtrlID)
		{
			strBuffer.Format(_T("%08X"), m_arrUICtrlC.GetAt(lp).dwCtrlID);

			strPath	+= strBuffer;
			strPath	+= _T("\\");
			bFound	= TRUE;
			break;
		}
	}

	if (bFound == FALSE)
	{
		return FALSE;
	}

	strPath	+= UIImageC.szName;

	switch (UIImageS.nType)
	{
	case UI_IMAGE_BMP32:
	case UI_IMAGE_BMP24:
	case UI_IMAGE_BMP16:
		{
			strPath	+= _T(".bmp");
		}
		break;
	case UI_IMAGE_PNG32:
	case UI_IMAGE_PNG24:
		{
			strPath	+= _T(".png");
		}
		break;
	case UI_IMAGE_JPG24:
		{
			strPath	+= _T(".jpg");
		}
		break;
	case UI_IMAGE_GIF08:
		{
			strPath	+= _T(".gif");
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	strImageName	= strPath;

	if (bMustExist)
	{
		return (CFile::GetStatus(strImageName, fs));
	}

	return TRUE;
}

BOOL CUIEditorDoc::GetImageFileName(CString& strImageName, UI_IMAGEC& UIImageC, UI_IMAGES& UIImageS)
{
	strImageName	= UIImageC.szName;

	switch (UIImageS.nType)
	{
	case UI_IMAGE_BMP32:
	case UI_IMAGE_BMP24:
	case UI_IMAGE_BMP16:
		{
			strImageName	+= _T(".bmp");
		}
		break;
	case UI_IMAGE_PNG32:
	case UI_IMAGE_PNG24:
		{
			strImageName	+= _T(".png");
		}
		break;
	case UI_IMAGE_JPG24:
		{
			strImageName	+= _T(".jpg");
		}
		break;
	case UI_IMAGE_GIF08:
		{
			strImageName	+= _T(".gif");
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

DWORD CUIEditorDoc::GetMGroupByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrMUIGroup.GetCount(); lp++)
	{
		if (dwID == m_arrMUIGroup.GetAt(lp).dwGroupID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

DWORD CUIEditorDoc::GetMPageByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrMUIPageC.GetCount(); lp++)
	{
		if (dwID == m_arrMUIPageC.GetAt(lp).dwPageID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

DWORD CUIEditorDoc::GetMCtrlByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrMUICtrlC.GetCount(); lp++)
	{
		if (dwID == m_arrMUICtrlC.GetAt(lp).dwCtrlID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

DWORD CUIEditorDoc::GetMImageByID(DWORD dwID)
{
	int	lp;

	for (lp = 0; lp < m_arrMUIImageC.GetCount(); lp++)
	{
		if (dwID == m_arrMUIImageC.GetAt(lp).dwImageID)
		{
			return lp;
		}
	}

	return UI_INVALIDID;
}

BOOL CUIEditorDoc::GetMImageFullPath(CString& strImageName, UI_IMAGEC& UIImageC, UI_IMAGES& UIImageS, BOOL bMustExist)
{
	CString		strBuffer;
	CString		strPath;
	int			lp;
	BOOL		bFound;
	CFileStatus	fs;

	strImageName	= _T("");
	strPath			= m_strMFolder + _T("\\");
	bFound			= FALSE;

	for (lp = 0; lp < m_arrMUIGroup.GetCount(); lp++)
	{
		if (m_arrMUIGroup.GetAt(lp).dwGroupID == UIImageS.dwGroupID)
		{
			strBuffer.Format(_T("%08X"), m_arrMUIGroup.GetAt(lp).dwGroupID);

			strPath	+= strBuffer;
			strPath	+= _T("\\");
			bFound	= TRUE;
			break;
		}
	}

	if (bFound == FALSE)
	{
		return FALSE;
	}

	bFound	= FALSE;

	for (lp = 0; lp < m_arrMUIPageC.GetCount(); lp++)
	{
		if (m_arrMUIPageC.GetAt(lp).dwPageID == UIImageC.dwPageID)
		{
			strBuffer.Format(_T("%08X"), m_arrMUIPageC.GetAt(lp).dwPageID);

			strPath	+= strBuffer;
			strPath	+= _T("\\");
			bFound	= TRUE;
			break;
		}
	}

	if (bFound == FALSE)
	{
		return FALSE;
	}

	bFound	= FALSE;

	for (lp = 0; lp < m_arrMUICtrlC.GetCount(); lp++)
	{
		if (m_arrMUICtrlC.GetAt(lp).dwCtrlID == UIImageC.dwCtrlID)
		{
			strBuffer.Format(_T("%08X"), m_arrMUICtrlC.GetAt(lp).dwCtrlID);

			strPath	+= strBuffer;
			strPath	+= _T("\\");
			bFound	= TRUE;
			break;
		}
	}

	if (bFound == FALSE)
	{
		return FALSE;
	}

	strPath	+= UIImageC.szName;

	switch (UIImageS.nType)
	{
	case UI_IMAGE_BMP32:
	case UI_IMAGE_BMP24:
	case UI_IMAGE_BMP16:
		{
			strPath += _T(".bmp");
		}
		break;
	case UI_IMAGE_PNG32:
	case UI_IMAGE_PNG24:
		{
			strPath	+= _T(".png");
		}
		break;
	case UI_IMAGE_JPG24:
		{
			strPath	+= _T(".jpg");
		}
		break;
	case UI_IMAGE_GIF08:
		{
			strPath	+= _T(".gif");
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	strImageName	= strPath;

	if (bMustExist)
	{
		return (CFile::GetStatus(strImageName, fs));
	}

	return TRUE;
}

BOOL CUIEditorDoc::AddGroup(USHORT uWidth, USHORT uHeight, DWORD dwBaseID)
{
	DECLARE_FRAME()

	UI_GROUP	UIGroup;
	UI_PAGES	UIPageS;
	UI_CTRLS	UICtrlS;
	UI_IMAGES	UIImageS;
	DWORD		dwID;
	DWORD		dwGroup;
	double		dbXFactor	= 1.0f;
	double		dbYFactor	= 1.0f;
	BOOL		bResize		= FALSE;
	SYSTEMTIME	st;
	int			lp1;
	int			lp2;
	CString		strDirectory;
	CString		strNewDirectory;

	GetLocalTime(&st);

	memset(&UIGroup, 0, sizeof(UI_GROUP));

	dwID	= GetNewGroupID();

	if (dwID != UI_NOMOREID)
	{
		UIGroup.dwGroupID	= dwID;
		UIGroup.uWidth		= uWidth;
		UIGroup.uHeight		= uHeight;

#ifdef	_UNICODE
		swprintf_s(UIGroup.szName, UI_MAX_NAMELEN, _T("IDG_GROUP_%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
		sprintf_s(UIGroup.szName, UI_MAX_NAMELEN, "IDG_GROUP_%04d%02d%02d%02d%02d%02d%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif

		m_arrUIGroup.Add(UIGroup);
		
		m_dwCGroupID	= dwID;

		strDirectory.Format(_T("%s\\%08X"), m_strFolder, UIGroup.dwGroupID);
		ShellCreate(strDirectory);

		if (dwBaseID != UI_INVALIDID)
		{
			dwGroup	= GetGroupByID(dwBaseID);
			lp2		= UI_INVALIDID;

			for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
			{
				if (m_arrUIGroup.GetAt(lp1).dwGroupID == dwBaseID)
				{
					lp2	= lp1;
					break;
				}
			}

			if (lp2 != UI_INVALIDID)
			{
				strDirectory.Format(_T("%s\\%08X\\*.*"), m_strFolder, m_arrUIGroup.GetAt(lp2).dwGroupID); 
				strNewDirectory.Format(_T("%s\\%08X"), m_strFolder, UIGroup.dwGroupID);

				if (ShellCopy(strDirectory, strNewDirectory))
				{
					OUTPUT_STR0(_T("All item files have been copied"));
				}
				else
				{
					OUTPUT_STR0(_T("Failed to copy item files"));
				}

				if ((UIGroup.uWidth != m_arrUIGroup.GetAt(lp2).uWidth) || (UIGroup.uHeight != m_arrUIGroup.GetAt(lp2).uHeight))
				{
					dbXFactor	= (double)((double)(UIGroup.uWidth) / (double)(m_arrUIGroup.GetAt(lp2).uWidth));
					dbYFactor	= (double)((double)(UIGroup.uHeight) / (double)(m_arrUIGroup.GetAt(lp2).uHeight));
					bResize		= TRUE;
				}
			}

			for (lp1 = 0; lp1 < m_arrUIPageC.GetCount(); lp1++)
			{
				for (lp2 = 0; lp2 < m_arrUIPageS.GetCount(); lp2++)
				{
					if ((m_arrUIPageS.GetAt(lp2).dwPageID == m_arrUIPageC.GetAt(lp1).dwPageID) && (m_arrUIPageS.GetAt(lp2).dwGroupID == dwBaseID))
					{
						memcpy_s(&UIPageS, sizeof(UI_PAGES), &m_arrUIPageS.GetAt(lp2), sizeof(UI_PAGES));

						UIPageS.dwGroupID	= dwID;

						m_arrUIPageS.Add(UIPageS);
						break;
					}
				}
			}

			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
				{
					if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == dwBaseID))
					{
						memcpy_s(&UICtrlS, sizeof(UI_CTRLS), &m_arrUICtrlS.GetAt(lp2), sizeof(UI_CTRLS));

						UICtrlS.dwGroupID	= dwID;

						if (bResize)
						{
							UICtrlS.rcWindow.left	= (LONG)(dbXFactor * UICtrlS.rcWindow.left);
							UICtrlS.rcWindow.top	= (LONG)(dbYFactor * UICtrlS.rcWindow.top);
							UICtrlS.rcWindow.right	= (LONG)(dbXFactor * UICtrlS.rcWindow.right);
							UICtrlS.rcWindow.bottom	= (LONG)(dbYFactor * UICtrlS.rcWindow.bottom);

							UICtrlS.uWidth			= (USHORT)(UICtrlS.rcWindow.right - UICtrlS.rcWindow.left);
							UICtrlS.uHeight			= (USHORT)(UICtrlS.rcWindow.bottom - UICtrlS.rcWindow.top);

							if (UICtrlS.uWidth < 1)
							{
								UICtrlS.uWidth			= 1;
								UICtrlS.rcWindow.right	= UICtrlS.rcWindow.left + UICtrlS.uWidth;
							}

							if (UICtrlS.uHeight < 1)
							{
								UICtrlS.uHeight			= 1;
								UICtrlS.rcWindow.bottom	= UICtrlS.rcWindow.top + UICtrlS.uHeight;
							}
						}
						
						m_arrUICtrlS.Add(UICtrlS);
						break;
					}
				}
			}

			for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
			{
				for (lp2 = 0; lp2 < m_arrUIImageS.GetCount(); lp2++)
				{
					if ((m_arrUIImageS.GetAt(lp2).dwImageID == m_arrUIImageC.GetAt(lp1).dwImageID) && (m_arrUIImageS.GetAt(lp2).dwGroupID == dwBaseID))
					{
						memcpy_s(&UIImageS, sizeof(UI_IMAGES), &m_arrUIImageS.GetAt(lp2), sizeof(UI_IMAGES));

						UIImageS.dwGroupID	= dwID;

						if (bResize)
						{
							CString	strOldName;
							CString	strNewName;

							UIImageS.uWidth		= (USHORT)(dbXFactor * m_arrUIImageS.GetAt(lp2).uWidth);
							UIImageS.uHeight	= (USHORT)(dbYFactor * m_arrUIImageS.GetAt(lp2).uHeight);

							if (UIImageS.uWidth < 1)
							{
								UIImageS.uWidth		= 1;
							}

							if (UIImageS.uHeight < 1)
							{
								UIImageS.uHeight	= 1;
							}

							if (GetImageFullPath(strOldName, m_arrUIImageC.GetAt(lp1), m_arrUIImageS.GetAt(lp2), TRUE))
							{
								GetImageFullPath(strNewName, m_arrUIImageC.GetAt(lp1), UIImageS, FALSE);
								ResizeImage(strNewName, strOldName, UIImageS.nType, UIImageS.uWidth, UIImageS.uHeight, UIImageS.dwSize, UIImageS.dwMaskSize);
							}								
						}

						m_arrUIImageS.Add(UIImageS);
						break;
					}
				}
			}
		}

		OUTPUT_STR2(_T("New group %08X [%s] is added"), UIGroup.dwGroupID, UIGroup.szName);

		return TRUE;
	}

	OUTPUT_STR0(_T("Failed to add new group"));

	return FALSE;
}

BOOL CUIEditorDoc::DeleteGroup()
{
	DECLARE_FRAME()

	DWORD	dwGroup	= GetGroupByID(m_dwCGroupID);
	int		lp;
	int		ct;
	CString	strDirectory;

	if (dwGroup == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if (m_arrUIGroup.GetCount() < 2)
	{
		OUTPUT_STR0(_T("The last group cannot be deleted"));

		return FALSE;
	}

	ct	= static_cast<int>(m_arrUIImageS.GetCount());

	for (lp = ct - 1; lp >= 0; lp--)
	{
		if (m_arrUIImageS.GetAt(lp).dwGroupID == m_dwCGroupID)
		{
			m_arrUIImageS.RemoveAt(lp);
		}
	}

	ct	= static_cast<int>(m_arrUICtrlS.GetCount());

	for (lp = ct - 1; lp >= 0; lp--)
	{
		if (m_arrUICtrlS.GetAt(lp).dwGroupID == m_dwCGroupID)
		{
			m_arrUICtrlS.RemoveAt(lp);
		}
	}

	ct	= static_cast<int>(m_arrUIPageS.GetCount());

	for (lp = ct - 1; lp >= 0; lp--)
	{
		if (m_arrUIPageS.GetAt(lp).dwGroupID == m_dwCGroupID)
		{
			m_arrUIPageS.RemoveAt(lp);
		}
	}

	strDirectory.Format(_T("%s\\%08X"), m_strFolder, m_arrUIGroup.GetAt(dwGroup).dwGroupID);
	ShellDelete(strDirectory);

	OUTPUT_STR2(_T("Group %08X [%s] has been removed"), m_arrUIGroup.GetAt(dwGroup).dwGroupID, m_arrUIGroup.GetAt(dwGroup).szName);

	m_arrUIGroup.RemoveAt(dwGroup);

	m_dwCGroupID	= (m_arrUIGroup.GetCount() ? m_arrUIGroup.GetAt(0).dwGroupID : UI_INVALIDID);

	return TRUE;
}

BOOL CUIEditorDoc::RenameGroup(LPCTSTR lpszNewName)
{
	DECLARE_FRAME()

	DWORD	dwGroup	= GetGroupByID(m_dwCGroupID);
	CString	strDirectory;
	CString	strNewDirectory;

	if (dwGroup == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}
	
	_tcscpy_s(m_arrUIGroup.GetAt(dwGroup).szName, UI_MAX_NAMELEN, lpszNewName);

	OUTPUT_STR2(_T("Group %08X was renamed to %s"), m_dwCGroupID, lpszNewName);

	return TRUE;
}

BOOL CUIEditorDoc::AddPage()
{
	DECLARE_FRAME()

	UI_PAGEC	UIPageC;
	UI_PAGES	UIPageS;
	DWORD		dwID;	
	SYSTEMTIME	st;
	int			lp;
	CString		strDirectory;

	GetLocalTime(&st);

	memset(&UIPageC, 0, sizeof(UI_PAGEC));

	dwID	= GetNewPageID();

	if (dwID != UI_NOMOREID)
	{
		UIPageC.dwPageID	= dwID;

#ifdef	_UNICODE
		swprintf_s(UIPageC.szName, UI_MAX_NAMELEN, _T("IDP_PAGE_%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
		sprintf_s(UIPageC.szName, UI_MAX_NAMELEN, "IDP_PAGE_%04d%02d%02d%02d%02d%02d%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif

		m_arrUIPageC.Add(UIPageC);

		m_dwCPageID	= dwID;
		
		for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
		{
			memset(&UIPageS, 0, sizeof(UI_PAGES));

			UIPageS.dwPageID	= dwID;
			UIPageS.dwGroupID	= m_arrUIGroup.GetAt(lp).dwGroupID;
			UIPageS.bEnable		= ((m_arrUIGroup.GetAt(lp).dwGroupID == m_dwCGroupID) ? TRUE : FALSE);

			m_arrUIPageS.Add(UIPageS);

			strDirectory.Format(_T("%s\\%08X\\%08X"), m_strFolder, m_arrUIGroup.GetAt(lp).dwGroupID, UIPageC.dwPageID);
			ShellCreate(strDirectory);
		}
		
		OUTPUT_STR2(_T("New page %08X [%s] is added"), UIPageC.dwPageID, UIPageC.szName);

		return TRUE;
	}

	OUTPUT_STR0(_T("Failed to add new page"));

	return FALSE;
}

BOOL CUIEditorDoc::DeletePage()
{
	DECLARE_FRAME()

	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	int		lp1;
	int		lp2;
	int		ct1;
	int		ct2;
	DWORD	dwGroup;
	CString	strDirectory;

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	ct1	= static_cast<int>(m_arrUIImageC.GetCount());

	for (lp1 = ct1 - 1; lp1 >= 0; lp1--)
	{
		if (m_arrUIImageC.GetAt(lp1).dwPageID == m_dwCPageID)
		{
			ct2	= static_cast<int>(m_arrUIImageS.GetCount());

			for (lp2 = ct2 - 1; lp2 >= 0; lp2--)
			{
				if (m_arrUIImageS.GetAt(lp2).dwImageID == m_arrUIImageC.GetAt(lp1).dwImageID)
				{
					m_arrUIImageS.RemoveAt(lp2);
				}
			}

			m_arrUIImageC.RemoveAt(lp1);
		}
	}

	ct1	= static_cast<int>(m_arrUICtrlC.GetCount());

	for (lp1 = ct1 - 1; lp1 >= 0; lp1--)
	{
		if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
		{
			ct2	= static_cast<int>(m_arrUICtrlS.GetCount());

			for (lp2 = ct2 - 1; lp2 >= 0; lp2--)
			{
				if (m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID)
				{
					m_arrUICtrlS.RemoveAt(lp2);
				}
			}

			m_arrUICtrlC.RemoveAt(lp1);
		}
	}

	ct1	= static_cast<int>(m_arrUIPageS.GetCount());

	for (lp1 = ct1 - 1; lp1 >= 0 ; lp1--)
	{
		if (m_arrUIPageS.GetAt(lp1).dwPageID == m_dwCPageID)
		{
			dwGroup	= GetGroupByID(m_arrUIPageS.GetAt(lp1).dwGroupID);

			strDirectory.Format(_T("%s\\%08X\\%08X"), m_strFolder, m_arrUIGroup.GetAt(dwGroup).dwGroupID, m_arrUIPageC.GetAt(dwPage).dwPageID);
			ShellDelete(strDirectory);
			m_arrUIPageS.RemoveAt(lp1);
		}
	}

	OUTPUT_STR2(_T("Page %08X [%s] has been removed"), m_arrUIPageC.GetAt(dwPage).dwPageID, m_arrUIPageC.GetAt(dwPage).szName);

	m_arrUIPageC.RemoveAt(dwPage);

	m_dwCPageID	= UI_INVALIDID;

	return TRUE;
}

BOOL CUIEditorDoc::RenamePage(LPCTSTR lpszNewName)
{
	DECLARE_FRAME()

	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	CString	strDirectory;
	CString	strNewDirectory;

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}
	
	_tcscpy_s(m_arrUIPageC.GetAt(dwPage).szName, UI_MAX_NAMELEN, lpszNewName);

	OUTPUT_STR2(_T("Page %08X was renamed to %s"), m_dwCPageID, lpszNewName);

	return TRUE;
}

BOOL CUIEditorDoc::MovePageToTop()
{
	DECLARE_FRAME()

	DWORD		dwPage	= GetPageByID(m_dwCPageID);
	int			lp;

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid page ID is assigned"));

		return FALSE;
	}

	if ((dwPage < 1) || (dwPage > static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwPage - 1); lp >= 0; lp--)
	{
		MovePageUp();
	}

	return TRUE;
}

BOOL CUIEditorDoc::MovePageUp()
{
	DECLARE_FRAME()

	DWORD		dwPage	= GetPageByID(m_dwCPageID);
	UI_PAGEC	UIPageC;

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwPage < 1) || (dwPage > static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("Page ID is out of range"));

		return FALSE;
	}

	memcpy_s(&UIPageC, sizeof(UI_PAGEC), &m_arrUIPageC.GetAt(dwPage), sizeof(UI_PAGEC));
	memcpy_s(&m_arrUIPageC.GetAt(dwPage), sizeof(UI_PAGEC), &m_arrUIPageC.GetAt(dwPage - 1), sizeof(UI_PAGEC));
	memcpy_s(&m_arrUIPageC.GetAt(dwPage - 1), sizeof(UI_PAGEC), &UIPageC, sizeof(UI_PAGEC));

	OUTPUT_STR2(_T("Page %08X [%s] has been moved up"), UIPageC.dwPageID, UIPageC.szName);

	return TRUE;
}

BOOL CUIEditorDoc::MovePageDown()
{
	DECLARE_FRAME()

	DWORD		dwPage	= GetPageByID(m_dwCPageID);
	UI_PAGEC	UIPageC;

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwPage < 0) || (dwPage >= static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	memcpy_s(&UIPageC, sizeof(UI_PAGEC), &m_arrUIPageC.GetAt(dwPage), sizeof(UI_PAGEC));
	memcpy_s(&m_arrUIPageC.GetAt(dwPage), sizeof(UI_PAGEC), &m_arrUIPageC.GetAt(dwPage + 1), sizeof(UI_PAGEC));
	memcpy_s(&m_arrUIPageC.GetAt(dwPage + 1), sizeof(UI_PAGEC), &UIPageC, sizeof(UI_PAGEC));

	OUTPUT_STR2(_T("Page %08X [%s] has been moved down"), UIPageC.dwPageID, UIPageC.szName);

	return TRUE;
}

BOOL CUIEditorDoc::MovePageToBottom()
{
	DECLARE_FRAME()

	DWORD		dwPage	= GetPageByID(m_dwCPageID);
	int			lp;

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid page ID is assigned"));

		return FALSE;
	}

	if ((dwPage < 0) || (dwPage >= static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwPage + 1); lp < static_cast<int>(m_arrUIPageC.GetCount()); lp++)
	{
		MovePageDown();
	}

	return TRUE;
}

#define	PAGE_H_NAME		_T("\\UIPage_h.tpl")
#define	PAGE_CPP_NAME	_T("\\UIPage_cpp.tpl")

BOOL CUIEditorDoc::GeneratePage()
{
	DECLARE_FRAME()

	DWORD	dwPage		= GetPageByID(m_dwCPageID);
	CString	strPage;
	CString	strPageU;
	CString	strPageC;
	CString	strCtrl;
	CString	strCtrlC;
	CString	strImage;
	CString	strTemplate;
	CString	strHandler;
	HANDLE	hTemplate;
	HANDLE	hHandler;
	DWORD	dwWritten;
	int		lp1;
	int		lp2;
	int		lp3;
	char	cReadBuffer[496];
	char	cWriteBuffer[512];

	if (dwPage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid page ID is assigned"));

		return FALSE;
	}

	strPage	= m_arrUIPageC.GetAt(dwPage).szName;
	
	if (strPage.Left(4) == _T("IDP_"))
	{
		strPage	= strPage.Mid(4);
	}

	strPageU	= strPage;

	strPageU.MakeUpper();

	MakeCapitalized(strPageC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strPage);
	strPageC.ReleaseBuffer();

	strTemplate.Format(_T("%s%s"), ((CUIEditorApp*)AfxGetApp())->GetAppFolder(), PAGE_H_NAME);

	hTemplate	= CreateFile(strTemplate, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hTemplate == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("Failed to open template file %s"), strTemplate);
		return FALSE;
	}

	strHandler.Format(_T("%s\\Handler%s.h"), m_strFolder, strPageC);

	hHandler	= CreateFile(strHandler, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hHandler == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hTemplate);

		OUTPUT_STR1(_T("Failed to create file %s"), strHandler);
		return FALSE;
	}

	while (ReadFileString(hTemplate, cReadBuffer, 496))
	{
		if (!strcmp(cReadBuffer, "$[HANDLER_HEADER]"))
		{
			sprintf_s(cWriteBuffer, 512, "// Handler%S.h\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_IFNDEF]"))
		{
			sprintf_s(cWriteBuffer, 512, "#ifndef\t__HANDLER_%S_H__\r\n", strPageU);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_DEFINE]"))
		{
			sprintf_s(cWriteBuffer, 512, "#define\t__HANDLER_%S_H__\r\n", strPageU);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ENDIF]"))
		{
			sprintf_s(cWriteBuffer, 512, "#endif\t// __HANDLER_%S_H__\r\n", strPageU);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_CLASS]"))
		{
			sprintf_s(cWriteBuffer, 512, "class CHandler%S : public CHandler\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_CONSTRUCTOR]"))
		{
			sprintf_s(cWriteBuffer, 512, "\tCHandler%S(CNaviContainer* pContainer, Int32 nHandlerID);\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_DESTRUCTOR]"))
		{
			sprintf_s(cWriteBuffer, 512, "\tvirtual\t~CHandler%S();\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[BUTTON_LIST]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType == UI_CTRL_BUTTON)
							{
								strCtrl		= m_arrUICtrlC.GetAt(lp1).szName;

								if (strCtrl.Left(4) == _T("IDC_"))
								{
									strCtrl	= strCtrl.Mid(4);
								}

								MakeCapitalized(strCtrlC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strCtrl);
								strCtrlC.ReleaseBuffer();

								sprintf_s(cWriteBuffer, 512, "\tCUIButton\tm_ctl%S;\r\n", strCtrlC);
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			sprintf_s(cWriteBuffer, 512, "%s\r\n", cReadBuffer);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
	}

	FlushFileBuffers(hHandler);
	CloseHandle(hHandler);
	CloseHandle(hTemplate);

	OUTPUT_STR1(_T("%s has been created"), strHandler);

	strTemplate.Format(_T("%s%s"), ((CUIEditorApp*)AfxGetApp())->GetAppFolder(), PAGE_CPP_NAME);

	hTemplate	= CreateFile(strTemplate, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hTemplate == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("Failed to open template file %s"), strTemplate);
		return FALSE;
	}

	strHandler.Format(_T("%s\\Handler%s.cpp"), m_strFolder, strPageC);

	hHandler	= CreateFile(strHandler, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hHandler == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hTemplate);

		OUTPUT_STR1(_T("Failed to create file %s"), strHandler);
		return FALSE;
	}

	while (ReadFileString(hTemplate, cReadBuffer, 496))
	{
		if (!strcmp(cReadBuffer, "$[HANDLER_CPP]"))
		{
			sprintf_s(cWriteBuffer, 512, "// Handler%S.cpp\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_INCLUDE]"))
		{
			sprintf_s(cWriteBuffer, 512, "#include \"Handler%S.h\"\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_CONSTRUCTOR_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "CHandler%S::CHandler%S(CNaviContainer* pContainer, Int32 nHandlerID) : CHandler(pContainer, nHandlerID)\r\n", strPageC, strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_DESTRUCTOR_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "CHandler%S::~CHandler%S()\r\n", strPageC, strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_INITDRAW_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "void CHandler%S::InitDraw()\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONACTIVATE_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "Bool CHandler%S::OnActivate()\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONDEACTIVATE_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "Bool CHandler%S::OnDeactivate()\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONINITHANDLER_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "void CHandler%S::OnInitHandler(SDL_Surface* psfContainer, void* pParam1, void* pParam2)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONERASEBKGND_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "void CHandler%S::OnEraseBkgnd()\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONDRAW_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "void CHandler%S::OnDraw()\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONSIZE_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "Int32 CHandler%S::OnSize(Int32 cx, Int32 cy)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONLBUTTONDOWN_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "UInt32 CHandler%S::OnLButtonDown(Int32 x, Int32 y, UInt32 uFlag)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONMOUSEMOVE_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "UInt32 CHandler%S::OnMouseMove(Int32 x, Int32 y, UInt32 uFlag)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONLBUTTONUP_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "UInt32 CHandler%S::OnLButtonUp(Int32 x, Int32 y, UInt32 uFlag)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONKEYINPUT_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "UInt32 CHandler%S::OnKeyInput(Int32 nKey, UInt32 uKeyModify)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONNAVIUPDATE_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "UInt32 CHandler%S::OnNaviUpdate(UInt32 msg, Long lParam1, Long lParam2, Long lParam3)\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[HANDLER_ONTIMERPROC_IMP]"))
		{
			sprintf_s(cWriteBuffer, 512, "UInt32 CHandler%S::OnTimerProc()\r\n", strPageC);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
		else if (!strcmp(cReadBuffer, "$[BUTTON_INITIALIZE]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType == UI_CTRL_BUTTON)
							{
								strCtrl		= m_arrUICtrlC.GetAt(lp1).szName;

								if (strCtrl.Left(4) == _T("IDC_"))
								{
									strCtrl	= strCtrl.Mid(4);
								}

								MakeCapitalized(strCtrlC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strCtrl);
								strCtrlC.ReleaseBuffer();

								sprintf_s(cWriteBuffer, 512, "\tm_ctl%S.Init(m_pSurface, NULL, %S, %S);\r\n", strCtrlC, m_arrUIPageC.GetAt(dwPage).szName, m_arrUICtrlC.GetAt(lp1).szName);
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);

								for (lp3 = 0; lp3 < m_arrUIImageC.GetCount(); lp3++)
								{
									if (m_arrUIImageC.GetAt(lp3).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID)
									{
										strImage	= m_arrUIImageC.GetAt(lp3).szName;
	
										if (strImage.Left(4) != _T("IDI_"))
										{
											strImage.Format(_T("IDI_%s"), m_arrUIImageC.GetAt(lp3).szName);
										}

										sprintf_s(cWriteBuffer, 512, "\tm_ctl%S.SetImages(%S, %S);\r\n", strCtrlC, strImage, strImage);
										WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		else if (!strcmp(cReadBuffer, "$[CONTROL_DRAW]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType != UI_CTRL_BUTTON)
							{
								for (lp3 = 0; lp3 < m_arrUIImageC.GetCount(); lp3++)
								{
									if (m_arrUIImageC.GetAt(lp3).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID)
									{
										strImage	= m_arrUIImageC.GetAt(lp3).szName;
	
										if (strImage.Left(4) != _T("IDI_"))
										{
											strImage.Format(_T("IDI_%s"), m_arrUIImageC.GetAt(lp3).szName);
										}

										sprintf_s(cWriteBuffer, 512, "\tCNonMapDraw::DrawCtrl(m_pSurface, %S, %S, %S);\r\n", m_arrUIPageC.GetAt(dwPage).szName, m_arrUICtrlC.GetAt(lp1).szName, strImage); 
										WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		else if (!strcmp(cReadBuffer, "$[BUTTON_DRAW]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType == UI_CTRL_BUTTON)
							{
								strCtrl		= m_arrUICtrlC.GetAt(lp1).szName;

								if (strCtrl.Left(4) == _T("IDC_"))
								{
									strCtrl	= strCtrl.Mid(4);
								}

								MakeCapitalized(strCtrlC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strCtrl);
								strCtrlC.ReleaseBuffer();

								sprintf_s(cWriteBuffer, 512, "\tm_ctl%S.OnDraw();\r\n", strCtrlC);
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								break;
							}
						}
					}
				}
			}
		}
		else if (!strcmp(cReadBuffer, "$[BUTTON_LBUTTONDOWN]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType == UI_CTRL_BUTTON)
							{
								strCtrl		= m_arrUICtrlC.GetAt(lp1).szName;

								if (strCtrl.Left(4) == _T("IDC_"))
								{
									strCtrl	= strCtrl.Mid(4);
								}

								MakeCapitalized(strCtrlC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strCtrl);
								strCtrlC.ReleaseBuffer();

								sprintf_s(cWriteBuffer, 512, "\tif (m_ctl%S.OnLButtonDown(x, y, uFlag))\r\n", strCtrlC);
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t{\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t\tdocument.m_bControlActivated\t= true;\r\n\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t\tOnDraw();\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t\treturn CHANGEPAGE_UPDATE;\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t}\r\n\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								break;
							}
						}
					}
				}
			}
		}
		else if (!strcmp(cReadBuffer, "$[BUTTON_MOUSEMOVE]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType == UI_CTRL_BUTTON)
							{
								strCtrl		= m_arrUICtrlC.GetAt(lp1).szName;

								if (strCtrl.Left(4) == _T("IDC_"))
								{
									strCtrl	= strCtrl.Mid(4);
								}

								MakeCapitalized(strCtrlC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strCtrl);
								strCtrlC.ReleaseBuffer();

								sprintf_s(cWriteBuffer, 512, "\tif (m_ctl%S.OnMouseMove(x, y, uFlag))\r\n", strCtrlC);
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t{\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t\tOnDraw();\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t}\r\n\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								break;
							}
						}
					}
				}
			}
		}
		else if (!strcmp(cReadBuffer, "$[BUTTON_LBUTTONUP]"))
		{
			for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
			{
				if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwCPageID)
				{
					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if ((m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (m_arrUICtrlS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							if (m_arrUICtrlS.GetAt(lp2).nType == UI_CTRL_BUTTON)
							{
								strCtrl		= m_arrUICtrlC.GetAt(lp1).szName;

								if (strCtrl.Left(4) == _T("IDC_"))
								{
									strCtrl	= strCtrl.Mid(4);
								}

								MakeCapitalized(strCtrlC.GetBufferSetLength(UI_MAX_NAMELEN), UI_MAX_NAMELEN, strCtrl);
								strCtrlC.ReleaseBuffer();

								sprintf_s(cWriteBuffer, 512, "\tif (m_ctl%S.OnLButtonUp(x, y, uFlag))\r\n", strCtrlC);
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t{\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t\tOnDraw();\r\n\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t\treturn CHANGEPAGE_UPDATE;\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								sprintf_s(cWriteBuffer, 512, "\t}\r\n\r\n");
								WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			sprintf_s(cWriteBuffer, 512, "%s\r\n", cReadBuffer);
			WriteFile(hHandler, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
		}
	}

	FlushFileBuffers(hHandler);
	CloseHandle(hHandler);
	CloseHandle(hTemplate);

	OUTPUT_STR1(_T("%s has been created"), strHandler);

	return TRUE;
}

BOOL CUIEditorDoc::AddCtrl()
{
	DECLARE_FRAME()

	UI_CTRLC	UICtrlC;
	UI_CTRLS	UICtrlS;
	DWORD		dwID;	
	SYSTEMTIME	st;
	int			lp;
	CString		strDirectory;

	GetLocalTime(&st);

	memset(&UICtrlC, 0, sizeof(UI_CTRLC));

	dwID	= GetNewCtrlID();

	if (dwID != UI_NOMOREID)
	{
		UICtrlC.dwCtrlID	= dwID;
		UICtrlC.dwPageID	= m_dwCPageID;

#ifdef	_UNICODE
		swprintf_s(UICtrlC.szName, UI_MAX_NAMELEN, _T("IDC_CTRL_%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
		sprintf_s(UICtrlC.szName, UI_MAX_NAMELEN, "IDC_CTRL_%04d%02d%02d%02d%02d%02d%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif

		m_arrUICtrlC.Add(UICtrlC);

		m_dwCCtrlID	= dwID;
		
		for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
		{
			memset(&UICtrlS, 0, sizeof(UI_CTRLS));

			UICtrlS.dwCtrlID	= dwID;
			UICtrlS.dwGroupID	= m_arrUIGroup.GetAt(lp).dwGroupID;
			UICtrlS.bEnable		= ((m_arrUIGroup.GetAt(lp).dwGroupID == m_dwCGroupID) ? TRUE : FALSE);
			UICtrlS.nType		= UI_CTRL_IMAGE;
			UICtrlS.bCommon		= FALSE;
			UICtrlS.bBackground	= FALSE;
			UICtrlS.uWidth		= 100;
			UICtrlS.uHeight		= 100;
			UICtrlS.uPinLeft	= UI_PIN_ALL;
			UICtrlS.uPinTop		= UI_PIN_ALL;
			UICtrlS.uPinRight	= UI_PIN_ALL;
			UICtrlS.uPinBottom	= UI_PIN_ALL;
			UICtrlS.uIDRight	= 0xFFFF;
			UICtrlS.uIDLeft		= 0xFFFF;
			UICtrlS.uIDUp		= 0xFFFF;
			UICtrlS.uIDDown		= 0xFFFF;
			UICtrlS.uIDEnter	= 0xFFFF;

			SetRect(&UICtrlS.rcWindow, 0, 0, 100, 100);
			m_arrUICtrlS.Add(UICtrlS);

			strDirectory.Format(_T("%s\\%08X\\%08X\\%08X"), m_strFolder, m_arrUIGroup.GetAt(lp).dwGroupID, m_arrUIPageC.GetAt(GetPageByID(m_dwCPageID)).dwPageID, UICtrlC.dwCtrlID);
			ShellCreate(strDirectory);
		}
		
		OUTPUT_STR2(_T("New ctrl %08X [%s] is added"), UICtrlC.dwCtrlID, UICtrlC.szName);

		return TRUE;
	}

	OUTPUT_STR0(_T("Failed to add new ctrl"));

	return FALSE;
}

BOOL CUIEditorDoc::DeleteCtrl()
{
	DECLARE_FRAME()

	DWORD	dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	int		lp1;
	int		lp2;
	int		ct1;
	int		ct2;
	DWORD	dwGroup;
	DWORD	dwPage;
	CString	strDirectory;

	if (dwCtrl == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	ct1	= static_cast<int>(m_arrUIImageC.GetCount());

	for (lp1 = ct1 - 1; lp1 >= 0; lp1--)
	{
		if (m_arrUIImageC.GetAt(lp1).dwCtrlID == m_dwCCtrlID)
		{
			ct2	= static_cast<int>(m_arrUIImageS.GetCount());

			for (lp2 = ct2 - 1; lp2 >= 0; lp2--)
			{
				if (m_arrUIImageS.GetAt(lp2).dwImageID == m_arrUIImageC.GetAt(lp1).dwImageID)
				{
					m_arrUIImageS.RemoveAt(lp2);
				}
			}

			m_arrUIImageC.RemoveAt(lp1);
		}
	}

	dwPage	= GetPageByID(m_arrUICtrlC.GetAt(dwCtrl).dwPageID);
	ct1		= static_cast<int>(m_arrUICtrlS.GetCount());

	for (lp1 = ct1 - 1; lp1 >= 0 ; lp1--)
	{
		if (m_arrUICtrlS.GetAt(lp1).dwCtrlID == m_dwCCtrlID)
		{
			dwGroup	= GetGroupByID(m_arrUICtrlS.GetAt(lp1).dwGroupID);

			strDirectory.Format(_T("%s\\%08X\\%08X\\%08X"), m_strFolder, m_arrUIGroup.GetAt(dwGroup).dwGroupID, m_arrUIPageC.GetAt(dwPage).dwPageID, m_arrUICtrlC.GetAt(dwCtrl).dwCtrlID);
			ShellDelete(strDirectory);
			m_arrUICtrlS.RemoveAt(lp1);
		}
	}

	OUTPUT_STR2(_T("Ctrl %08X [%s] has been removed"), m_arrUICtrlC.GetAt(dwCtrl).dwCtrlID, m_arrUICtrlC.GetAt(dwCtrl).szName);

	m_arrUICtrlC.RemoveAt(dwCtrl);

	m_dwCCtrlID	= UI_INVALIDID;

	return TRUE;
}

BOOL CUIEditorDoc::RenameCtrl(LPCTSTR lpszNewName)
{
	DECLARE_FRAME()

	DWORD	dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	CString	strDirectory;
	CString	strNewDirectory;

	if (dwCtrl == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	_tcscpy_s(m_arrUICtrlC.GetAt(dwCtrl).szName, UI_MAX_NAMELEN, lpszNewName);

	OUTPUT_STR2(_T("Ctrl %08X was renamed to %s"), m_dwCCtrlID, lpszNewName);

	return TRUE;
}

BOOL CUIEditorDoc::MoveCtrlToTop()
{
	DECLARE_FRAME()

	DWORD		dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	int			lp;
	int			ct		= 0;

	if (dwCtrl == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwCtrl < 1) || (dwCtrl > static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwCtrl - 1); lp >= 0; lp--)
	{
		if (m_arrUICtrlC.GetAt(lp).dwPageID == m_arrUICtrlC.GetAt(dwCtrl).dwPageID)
		{
			ct++;
		}
	}

	if (ct > 0)
	{
		for (lp = 0; lp < ct; lp++)
		{
			MoveCtrlUp();
		}
	}

	return TRUE;
}

BOOL CUIEditorDoc::MoveCtrlUp()
{
	DECLARE_FRAME()

	DWORD		dwCtrl		= GetCtrlByID(m_dwCCtrlID);
	UI_CTRLC	UICtrlC;
	int			lp;
	DWORD		dwTarget	= UI_INVALIDID;

	if (dwCtrl == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwCtrl < 1) || (dwCtrl > static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwCtrl - 1); lp >= 0; lp--)
	{
		if (m_arrUICtrlC.GetAt(lp).dwPageID == m_arrUICtrlC.GetAt(dwCtrl).dwPageID)
		{
			dwTarget	= lp;
			break;
		}
	}

	if (dwTarget != UI_INVALIDID)
	{
		memcpy_s(&UICtrlC, sizeof(UI_CTRLC), &m_arrUICtrlC.GetAt(dwCtrl), sizeof(UI_CTRLC));
		memcpy_s(&m_arrUICtrlC.GetAt(dwCtrl), sizeof(UI_CTRLC), &m_arrUICtrlC.GetAt(dwTarget), sizeof(UI_CTRLC));
		memcpy_s(&m_arrUICtrlC.GetAt(dwTarget), sizeof(UI_CTRLC), &UICtrlC, sizeof(UI_CTRLC));

		OUTPUT_STR2(_T("Ctrl %08X [%s] has been moved up"), UICtrlC.dwCtrlID, UICtrlC.szName);
	}
	else
	{
		OUTPUT_STR2(_T("Ctrl %08X [%s] does not need to move up"), UICtrlC.dwCtrlID, UICtrlC.szName);
	}

	return TRUE;
}

BOOL CUIEditorDoc::MoveCtrlDown()
{
	DECLARE_FRAME()

	DWORD		dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	UI_CTRLC	UICtrlC;
	int			lp;
	int			ct;
	DWORD		dwTarget	= UI_INVALIDID;

	if (dwCtrl == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwCtrl < 0) || (dwCtrl >= static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	ct	= static_cast<int>(m_arrUICtrlC.GetCount());

	for (lp = (dwCtrl + 1); lp < ct; lp++)
	{
		if (m_arrUICtrlC.GetAt(lp).dwPageID == m_arrUICtrlC.GetAt(dwCtrl).dwPageID)
		{
			dwTarget	= lp;
			break;
		}
	}

	if (dwTarget != UI_INVALIDID)
	{
		memcpy_s(&UICtrlC, sizeof(UI_CTRLC), &m_arrUICtrlC.GetAt(dwCtrl), sizeof(UI_CTRLC));
		memcpy_s(&m_arrUICtrlC.GetAt(dwCtrl), sizeof(UI_CTRLC), &m_arrUICtrlC.GetAt(dwTarget), sizeof(UI_CTRLC));
		memcpy_s(&m_arrUICtrlC.GetAt(dwTarget), sizeof(UI_CTRLC), &UICtrlC, sizeof(UI_CTRLC));

		OUTPUT_STR2(_T("Ctrl %08X [%s] has been moved down"), UICtrlC.dwCtrlID, UICtrlC.szName);
	}
	else
	{
		OUTPUT_STR2(_T("Ctrl %08X [%s] does not need to move down"), UICtrlC.dwCtrlID, UICtrlC.szName);
	}

	return TRUE;
}

BOOL CUIEditorDoc::MoveCtrlToBottom()
{
	DECLARE_FRAME()

	DWORD		dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	int			lp;
	int			ct		= 0;

	if (dwCtrl == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwCtrl < 0) || (dwCtrl >= static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwCtrl + 1); lp < static_cast<int>(m_arrUICtrlC.GetCount()); lp++)
	{
		if (m_arrUICtrlC.GetAt(lp).dwPageID == m_arrUICtrlC.GetAt(dwCtrl).dwPageID)
		{
			ct++;
		}
	}

	if (ct > 0)
	{
		for (lp = 0; lp < ct; lp++)
		{
			MoveCtrlDown();
		}
	}

	return TRUE;
}

BOOL CUIEditorDoc::AddImage(LPCTSTR lpszImageFile)
{
	DECLARE_FRAME()

	UI_IMAGEC	UIImageC;
	UI_IMAGES	UIImageS;
	DWORD		dwID;	
	int			lp;
	CString		strImage;
	DWORD		dwSize;
	int			nType;
	USHORT		uWidth;
	USHORT		uHeight;
	BOOL		bMask;

	if (!GetImageType(lpszImageFile, nType, dwSize, uWidth, uHeight, bMask))
	{
		OUTPUT_STR1(_T("Image %s is not available"), lpszImageFile);

		return FALSE;
	}

	memset(&UIImageC, 0, sizeof(UI_IMAGEC));

	dwID	= GetNewImageID();

	if (dwID != UI_NOMOREID)
	{
		UIImageC.dwImageID	= dwID;
		UIImageC.dwPageID	= m_dwCPageID;
		UIImageC.dwCtrlID	= m_dwCCtrlID;

		TakeTitle(lpszImageFile, UIImageC.szName, UI_MAX_NAMELEN);

		m_arrUIImageC.Add(UIImageC);

		m_dwCImageID	= dwID;
		
		for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
		{
			memset(&UIImageS, 0, sizeof(UI_IMAGES));

			UIImageS.dwImageID		= dwID;
			UIImageS.dwGroupID		= m_arrUIGroup.GetAt(lp).dwGroupID;
			UIImageS.nType			= nType;
			UIImageS.uWidth			= uWidth;
			UIImageS.uHeight		= uHeight;
			UIImageS.dwSize			= dwSize;
			UIImageS.dwMaskSize		= (bMask ? (uWidth * uHeight) : 0);
			UIImageS.nAlphaType		= UI_ABG_NONE;
			UIImageS.uFirstOpacity	= 255;
			UIImageS.uLastOpacity	= 255;

			m_arrUIImageS.Add(UIImageS);

			GetImageFullPath(strImage, UIImageC, UIImageS, FALSE);
			ShellCopy(lpszImageFile, strImage);
		}
		
		OUTPUT_STR2(_T("New image %08X [%s] is added"), UIImageC.dwImageID, UIImageC.szName);

		return TRUE;
	}

	OUTPUT_STR0(_T("Failed to add new image"));

	return FALSE;
}

BOOL CUIEditorDoc::DeleteImage()
{
	DECLARE_FRAME()

	DWORD	dwImage	= GetImageByID(m_dwCImageID);
	int		lp1;
	int		lp2;
	CString	strImage;

	if (dwImage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
	{
		for (lp2 = 0; lp2 < m_arrUIImageS.GetCount(); lp2++)
		{
			if ((m_arrUIImageS.GetAt(lp2).dwImageID == m_dwCImageID) && (m_arrUIImageS.GetAt(lp2).dwGroupID == lp1))
			{
				if (GetImageFullPath(strImage, m_arrUIImageC.GetAt(dwImage), m_arrUIImageS.GetAt(lp2), TRUE))
				{
					ShellDelete(strImage);
				}

				m_arrUIImageS.RemoveAt(lp2);
				break;
			}
		}
	}

	OUTPUT_STR2(_T("Image %08X [%s] has been removed"), m_arrUIImageC.GetAt(dwImage).dwImageID, m_arrUIImageC.GetAt(dwImage).szName);

	m_arrUIImageC.RemoveAt(dwImage);

	m_dwCImageID	= UI_INVALIDID;

	return TRUE;
}

BOOL CUIEditorDoc::RenameImage(LPCTSTR lpszNewName)
{
	DECLARE_FRAME()

	DWORD		dwImage	= GetImageByID(m_dwCImageID);
	int			lp1;
	int			lp2;
	CString		strImage;
	CString		strNewImage;
	UI_IMAGEC	UIImageC;

	if (dwImage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
	{
		for (lp2 = 0; lp2 < m_arrUIImageS.GetCount(); lp2++)
		{
			if ((m_arrUIImageS.GetAt(lp2).dwImageID == m_dwCImageID) && (m_arrUIImageS.GetAt(lp2).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
			{
				if (GetImageFullPath(strImage, m_arrUIImageC.GetAt(dwImage), m_arrUIImageS.GetAt(lp2), TRUE))
				{
					memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &m_arrUIImageC.GetAt(dwImage), sizeof(UI_IMAGEC));
					_tcscpy_s(UIImageC.szName, UI_MAX_NAMELEN, lpszNewName);
					GetImageFullPath(strNewImage, UIImageC, m_arrUIImageS.GetAt(lp2), FALSE);

					if (!ShellMove(strImage, strNewImage))
					{
						OUTPUT_STR0(_T("Failed to move item files"));

						return FALSE;
					}
				}
			}
		}
	}

	OUTPUT_STR0(_T("All item files have been moved"));
	
	_tcscpy_s(m_arrUIImageC.GetAt(dwImage).szName, UI_MAX_NAMELEN, lpszNewName);

	OUTPUT_STR2(_T("Image %08X was renamed to %s"), m_dwCImageID, lpszNewName);

	return TRUE;
}

BOOL CUIEditorDoc::MoveImageToTop()
{
	DECLARE_FRAME()

	DWORD		dwImage	= GetImageByID(m_dwCImageID);
	int			lp;
	int			ct		= 0;

	if (dwImage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwImage < 1) || (dwImage > static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwImage - 1); lp >= 0; lp--)
	{
		if (m_arrUIImageC.GetAt(lp).dwCtrlID == m_arrUIImageC.GetAt(dwImage).dwCtrlID)
		{
			ct++;
		}
	}

	if (ct > 0)
	{
		for (lp = 0; lp < ct; lp++)
		{
			MoveImageUp();
		}
	}

	return TRUE;
}

BOOL CUIEditorDoc::MoveImageUp()
{
	DECLARE_FRAME()

	DWORD		dwTarget	= UI_INVALIDID;
	DWORD		dwImage		= GetImageByID(m_dwCImageID);
	UI_IMAGEC	UIImageC;
	int			lp;

	if (dwImage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwImage < 1) || (dwImage > static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwImage - 1); lp >= 0; lp--)
	{
		if (m_arrUIImageC.GetAt(lp).dwCtrlID == m_arrUIImageC.GetAt(dwImage).dwCtrlID)
		{
			dwTarget	= lp;
			break;
		}
	}

	if (dwTarget != UI_INVALIDID)
	{
		memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &m_arrUIImageC.GetAt(dwImage), sizeof(UI_IMAGEC));
		memcpy_s(&m_arrUIImageC.GetAt(dwImage), sizeof(UI_IMAGEC), &m_arrUIImageC.GetAt(dwTarget), sizeof(UI_IMAGEC));
		memcpy_s(&m_arrUIImageC.GetAt(dwTarget), sizeof(UI_IMAGEC), &UIImageC, sizeof(UI_IMAGEC));

		OUTPUT_STR2(_T("Image %08X [%s] has been moved up"), UIImageC.dwImageID, UIImageC.szName);
	}
	else
	{
		OUTPUT_STR2(_T("Image %08X [%s] does not need to move up"), UIImageC.dwImageID, UIImageC.szName);
	}

	return TRUE;
}

BOOL CUIEditorDoc::MoveImageDown()
{
	DECLARE_FRAME()

	DWORD		dwTarget	= UI_INVALIDID;
	DWORD		dwImage		= GetImageByID(m_dwCImageID);
	UI_IMAGEC	UIImageC;
	int			lp;
	int			ct;

	if (dwImage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwImage < 0) || (dwImage >= static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	ct	= static_cast<int>(m_arrUIImageC.GetCount());

	for (lp = (dwImage + 1); lp < ct; lp++)
	{
		if (m_arrUIImageC.GetAt(lp).dwCtrlID == m_arrUIImageC.GetAt(dwImage).dwCtrlID)
		{
			dwTarget	= lp;
			break;
		}
	}

	if (dwTarget != UI_INVALIDID)
	{
		memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &m_arrUIImageC.GetAt(dwImage), sizeof(UI_IMAGEC));
		memcpy_s(&m_arrUIImageC.GetAt(dwImage), sizeof(UI_IMAGEC), &m_arrUIImageC.GetAt(dwTarget), sizeof(UI_IMAGEC));
		memcpy_s(&m_arrUIImageC.GetAt(dwTarget), sizeof(UI_IMAGEC), &UIImageC, sizeof(UI_IMAGEC));

		OUTPUT_STR2(_T("Image %08X [%s] has been moved down"), UIImageC.dwImageID, UIImageC.szName);
	}
	else
	{
		OUTPUT_STR2(_T("Image %08X [%s] does not need to move down"), UIImageC.dwImageID, UIImageC.szName);
	}

	return TRUE;
}

BOOL CUIEditorDoc::MoveImageToBottom()
{
	DECLARE_FRAME()

	DWORD		dwImage	= GetImageByID(m_dwCImageID);
	int			lp;
	int			ct		= 0;

	if (dwImage == UI_INVALIDID)
	{
		OUTPUT_STR0(_T("Invalid ID is assigned"));

		return FALSE;
	}

	if ((dwImage < 0) || (dwImage >= static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		OUTPUT_STR0(_T("ID is out of range"));

		return FALSE;
	}

	for (lp = (dwImage + 1); lp < static_cast<int>(m_arrUIImageC.GetCount()); lp++)
	{
		if (m_arrUIImageC.GetAt(lp).dwCtrlID == m_arrUIImageC.GetAt(dwImage).dwCtrlID)
		{
			ct++;
		}
	}

	if (ct > 0)
	{
		for (lp = 0; lp < ct; lp++)
		{
			MoveImageDown();
		}
	}

	return TRUE;
}

void CUIEditorDoc::UpdateWorkspace(int nUpdateType)
{
	DECLARE_FRAME()

	CString	strItem;
	DWORD	dwItem;
	int		nImage	= WSI_INVALID;
	int		lp;

	switch (nUpdateType)
	{
	case WSU_FULL:
		{
			pFrame->m_wndWorkspace.BuildTree();
		}
		break;
	case WSU_SELECT:
		{
			pFrame->m_wndWorkspace.SelectItem();
		}
		break;
	case WSU_STATE:
		{
			switch (m_nCType)
			{
			case UI_ITEM_GROUP:
				{
					dwItem	= GetGroupByID(m_dwCGroupID);

					strItem.Format(_T("%s [%dx%d]"), m_arrUIGroup.GetAt(dwItem).szName, m_arrUIGroup.GetAt(dwItem).uWidth, m_arrUIGroup.GetAt(dwItem).uHeight);
					pFrame->m_wndWorkspace.UpdateItem(strItem, nImage);
				}
				break;
			case UI_ITEM_PAGE:
				{
					dwItem	= GetPageByID(m_dwCPageID);
					strItem	= m_arrUIPageC.GetAt(dwItem).szName;

					pFrame->m_wndWorkspace.UpdateItem(strItem, nImage);
				}
				break;
			case UI_ITEM_CTRL:
				{
					dwItem	= GetCtrlByID(m_dwCCtrlID);
					strItem	= m_arrUICtrlC.GetAt(dwItem).szName;

					for (lp = 0; lp < m_arrUICtrlS.GetCount(); lp++)
					{
						if ((m_arrUICtrlS.GetAt(lp).dwCtrlID == m_dwCCtrlID) && (m_arrUICtrlS.GetAt(lp).dwGroupID == m_dwCGroupID))
						{
							nImage	= (m_arrUICtrlS.GetAt(lp).bEnable ? WSI_CTRL_ENABLE : WSI_CTRL_DISABLE);
							break;
						}
					}

					pFrame->m_wndWorkspace.UpdateItem(strItem, nImage);
				}
				break;
			case UI_ITEM_IMAGE:
				{
					dwItem	= GetImageByID(m_dwCImageID);
					strItem	= m_arrUIImageC.GetAt(dwItem).szName;

					pFrame->m_wndWorkspace.UpdateItem(strItem, nImage);
				}
				break;
			}
		}
		break;
	case WSU_DELETE:
		{
			pFrame->m_wndWorkspace.DeleteItem();
		}
		break;
	}
}

void CUIEditorDoc::UpdateProperties()
{
	DECLARE_FRAME()

	WND_PROPERTIES.InitPropList();
}

BOOL CUIEditorDoc::SaveImageBuffer(CArchive &ar, LPCTSTR lpszFileName, int nType, DWORD dwSize)
{
	if (nType & UI_IMAGE_BMP)
	{
		return (SaveBufferBMP(ar, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		return (SaveBufferPNG(ar, lpszFileName, dwSize));
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		return (SaveBufferJPG(ar, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		return (SaveBufferGIF(ar, lpszFileName, dwSize));
	}
#endif

	return FALSE;
}

BOOL CUIEditorDoc::LoadImageBuffer(CArchive &ar, LPCTSTR lpszFileName, int nType, DWORD dwSize)
{
	if (nType & UI_IMAGE_BMP)
	{
		return (LoadBufferBMP(ar, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		return (LoadBufferPNG(ar, lpszFileName, dwSize));
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		return (LoadBufferJPG(ar, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		return (LoadBufferGIF(ar, lpszFileName, dwSize));
	}
#endif

	return FALSE;
}

BOOL CUIEditorDoc::SaveImageBuffer(CFile &file, LPCTSTR lpszFileName, int nType, DWORD dwSize)
{
	if (nType & UI_IMAGE_BMP)
	{
		return (SaveBufferBMP(file, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		return (SaveBufferPNG(file, lpszFileName, dwSize));
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		return (SaveBufferJPG(file, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		return (SaveBufferGIF(file, lpszFileName, dwSize));
	}
#endif

	return FALSE;
}

BOOL CUIEditorDoc::LoadImageBuffer(CFile &file, LPCTSTR lpszFileName, int nType, DWORD dwSize)
{
	if (nType & UI_IMAGE_BMP)
	{
		return (LoadBufferBMP(file, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		return (LoadBufferPNG(file, lpszFileName, dwSize));
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		return (LoadBufferJPG(file, lpszFileName, dwSize));
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		return (LoadBufferGIF(file, lpszFileName, dwSize));
	}
#endif

	return FALSE;
}

BOOL CUIEditorDoc::ResizeImage(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nType, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize)
{
	if (nType & UI_IMAGE_BMP)
	{
		return (ResizeBMP(lpszNewFileName, lpszOldFileName, nNewWidth, nNewHeight, dwSize, dwMaskSize));
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		return (ResizePNG(lpszNewFileName, lpszOldFileName, nNewWidth, nNewHeight, dwSize, dwMaskSize));
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		return (ResizeJPG(lpszNewFileName, lpszOldFileName, nNewWidth, nNewHeight, dwSize, dwMaskSize));
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		return (ResizeGIF(lpszNewFileName, lpszOldFileName, nNewWidth, nNewHeight, dwSize, dwMaskSize));
	}
#endif

	return FALSE;
}

BOOL CUIEditorDoc::SaveDatabaseImage(HANDLE hStream, LPCTSTR lpszFileName, int nType, UINT &uSize, UINT &uMaskSize, BOOL bCompress)
{
	if (nType & UI_IMAGE_BMP)
	{
		return (SaveDatabaseBMP(hStream, lpszFileName, uSize, uMaskSize, bCompress));
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		return (SaveDatabasePNG(hStream, lpszFileName, uSize, uMaskSize, bCompress));
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		return (SaveDatabaseJPG(hStream, lpszFileName, uSize, uMaskSize, bCompress));
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		return (SaveDatabaseGIF(hStream, lpszFileName, uSize, uMaskSize, bCompress));
	}
#endif

	return FALSE;
}

void CUIEditorDoc::ClearSelection()
{
	m_nSLType		= UI_ITEM_NONE;
	m_dwSLPageID	= UI_INVALIDID;
	
	m_arrSLCtrlID.RemoveAll();
}

void CUIEditorDoc::ClearClipboard()
{
	m_nCBType	= UI_ITEM_NONE;

	memset(&m_tCBPageC, 0, sizeof(UI_PAGEC));

	m_arrCBPageS.RemoveAll();
	m_arrCBCtrlC.RemoveAll();
	m_arrCBCtrlS.RemoveAll();
	m_arrCBImageC.RemoveAll();
	m_arrCBImageS.RemoveAll();
}

void CUIEditorDoc::ClearMergeData()
{
	m_strMFolder.Empty();
	m_strMFileName.Empty();

	memset(&m_tMUIHeader, 0, sizeof(UI_HEADER));

	m_arrMUIGroup.RemoveAll();
	m_arrMUIPageC.RemoveAll();
	m_arrMUIPageS.RemoveAll();
	m_arrMUICtrlC.RemoveAll();
	m_arrMUICtrlS.RemoveAll();
	m_arrMUIImageC.RemoveAll();
	m_arrMUIImageS.RemoveAll();
}

void CUIEditorDoc::OnFileMerge()
{
	DECLARE_FRAME()

	TCHAR		szFilters[]	= _T("UI 파일 (*.ui)|*.ui||");
	CFileDialog	dOpen(TRUE, _T("ui"), _T("*.ui"), OFN_FILEMUSTEXIST, szFilters, AfxGetApp()->GetMainWnd());
	CFile		file;

	if (m_arrUIGroup.GetCount() != 1)
	{
		OUTPUT_STR0(_T("UI has too many groups, merging will be cancelled"));
		return;
	}

	OnFileSave();

	if (dOpen.DoModal() != IDOK)
	{
		OUTPUT_STR0(_T("Merging was cancelled by user"));
		return;
	}
				
	BeginWaitCursor();
	ClearMergeData();

	m_strMFileName	= dOpen.GetPathName();
	m_strMFolder	= m_strMFileName.Left(m_strMFileName.ReverseFind(_T('.')));

	CString	strFolder;
	CString	strImageName;
	int		lp;
	int		lp0;
	int		lp1;
	int		lp2;
	int		lp3;

	if (!ShellCreate(m_strMFolder))
	{
		EndWaitCursor();

		OUTPUT_STR1(_T("Failed to create working directory %s"), m_strMFolder);
		return;
	}

	UI_GROUP	UIGroup;
	UI_PAGEC	UIPageC;
	UI_PAGES	UIPageS;
	UI_CTRLC	UICtrlC;
	UI_CTRLS	UICtrlS;
	UI_IMAGEC	UIImageC;
	UI_IMAGES	UIImageS;

	if (!file.Open(m_strMFileName, CFile::modeRead))
	{
		EndWaitCursor();

		OUTPUT_STR1(_T("Failed to open UI file, %s"), m_strMFileName);
		return;
	}

	file.Read(&m_tMUIHeader, sizeof(UI_HEADER));

	OUTPUT_STR0(_T("UI Header has been loaded"));

	if (m_tMUIHeader.dwGroups != 1)
	{
		EndWaitCursor();
		file.Close();
		ClearMergeData();

		OUTPUT_STR0(_T("UI has too many groups, merging will be cancelled"));
		return;
	}

	WND_OUTPUT.SetMultipleAdd(TRUE);

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwGroups); lp1++)
	{
		file.Read(&UIGroup, sizeof(UI_GROUP));
		m_arrMUIGroup.Add(UIGroup);

		OUTPUT_STR2(_T("Group %08X [%s] has been loaded"), UIGroup.dwGroupID, UIGroup.szName);

		strFolder.Format(_T("%s\\%08X"), m_strMFolder, UIGroup.dwGroupID);
		ShellCreate(strFolder);
	}

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwPages); lp1++)
	{
		file.Read(&UIPageC, sizeof(UI_PAGEC));
		m_arrMUIPageC.Add(UIPageC);

		OUTPUT_STR2(_T("PageC %08X [%s] has been loaded"), UIPageC.dwPageID, UIPageC.szName);

		for (lp2 = 0; lp2 < static_cast<int>(m_tMUIHeader.dwGroups); lp2++)
		{
			strFolder.Format(_T("%s\\%08X\\%08X"), m_strMFolder, m_arrMUIGroup.GetAt(lp2).dwGroupID, UIPageC.dwPageID);
			ShellCreate(strFolder);
		}
	}

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwCtrls); lp1++)
	{
		file.Read(&UICtrlC, sizeof(UI_CTRLC));
		m_arrMUICtrlC.Add(UICtrlC);

		OUTPUT_STR2(_T("CtrlC %08X [%s] has been loaded"), UICtrlC.dwCtrlID, UICtrlC.szName);

		for (lp2 = 0; lp2 < static_cast<int>(m_tMUIHeader.dwGroups); lp2++)
		{
			strFolder.Format(_T("%s\\%08X\\%08X\\%08X"), m_strMFolder, m_arrMUIGroup.GetAt(lp2).dwGroupID, UICtrlC.dwPageID, UICtrlC.dwCtrlID);
			ShellCreate(strFolder);
		}
	}

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwImages); lp1++)
	{
		file.Read(&UIImageC, sizeof(UI_IMAGEC));
		m_arrMUIImageC.Add(UIImageC);

		OUTPUT_STR2(_T("ImageC %08X [%s] has been loaded"), UIImageC.dwImageID, UIImageC.szName);
	}

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwGroups * m_tMUIHeader.dwPages); lp1++)
	{
		file.Read(&UIPageS, sizeof(UI_PAGES));
		m_arrMUIPageS.Add(UIPageS);

		OUTPUT_STR2(_T("PageS [%08X/%08X] has been loaded"), UIPageS.dwPageID, UIPageS.dwGroupID);
	}

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwGroups * m_tMUIHeader.dwCtrls); lp1++)
	{
		file.Read(&UICtrlS, sizeof(UI_CTRLS));
		m_arrMUICtrlS.Add(UICtrlS);

		OUTPUT_STR2(_T("CtrlS [%08X/%08X] has been loaded"), UICtrlS.dwCtrlID, UICtrlS.dwGroupID);
	}

	for (lp1 = 0; lp1 < static_cast<int>(m_tMUIHeader.dwGroups * m_tMUIHeader.dwImages); lp1++)
	{
		file.Read(&UIImageS, sizeof(UI_IMAGES));
		m_arrMUIImageS.Add(UIImageS);

		OUTPUT_STR2(_T("ImageS [%08X/%08X] has been loaded"), UIImageS.dwImageID, UIImageS.dwGroupID);

		for (lp2 = 0; lp2 < static_cast<int>(m_tMUIHeader.dwImages); lp2++)
		{
			if (m_arrMUIImageC.GetAt(lp2).dwImageID == m_arrMUIImageS.GetAt(lp1).dwImageID)
			{
				if (GetMImageFullPath(strImageName, m_arrMUIImageC.GetAt(lp2), m_arrMUIImageS.GetAt(lp1), FALSE))
				{
					LoadImageBuffer(file, strImageName, m_arrMUIImageS.GetAt(lp1).nType, m_arrMUIImageS.GetAt(lp1).dwSize);

					OUTPUT_STR2(_T("Image %s [%08X] has been loaded"), strImageName, m_arrMUIImageC.GetAt(lp2).dwImageID);
					break;
				}
			}
		}
	}

	file.Close();

	EndWaitCursor();

	OUTPUT_STR0(_T("All items has been loaded"));

	WND_OUTPUT.SetMultipleAdd(FALSE);

	CMultiDialog	dSelect;

	dSelect.m_strTitle			= _T("페이지 선택");
	dSelect.m_strDescription	= _T("병합할 페이지를 선택하세요.");

	for (lp1 = 0; lp1 < m_arrMUIPageC.GetCount(); lp1++)
	{
		strImageName.Format(_T("%s"), m_arrMUIPageC.GetAt(lp1).szName);
		dSelect.m_arrItems.Add(strImageName);
		dSelect.m_arrPos.Add(m_arrMUIPageC.GetAt(lp1).dwPageID);
	}

	if (dSelect.DoModal() != IDOK)
	{
		ClearMergeData();

		OUTPUT_STR0(_T("Merging was cancelled by user"));
		return;	
	}

	WND_OUTPUT.SetMultipleAdd(TRUE);

	CString		strName;
	CString		strTarget;
	SYSTEMTIME	st;
	DWORD		dwOldPageID;
	DWORD		dwOldPage;
	DWORD		dwPageID;
	DWORD		dwCtrlID;
	DWORD		dwImageID;

	for (lp0 = 0; lp0 < dSelect.m_arrSelItems.GetCount(); lp0++)
	{
		dwOldPageID	= dSelect.m_arrPos.GetAt(dSelect.m_arrSelItems.GetAt(lp0));
		dwOldPage	= GetMPageByID(dwOldPageID);
		dwPageID	= GetNewPageID();

		if (dwPageID != UI_INVALIDID)
		{
			GetLocalTime(&st);
			memcpy_s(&UIPageC, sizeof(UI_PAGEC), &m_arrMUIPageC.GetAt(dwOldPage), sizeof(UI_PAGEC));

			UIPageC.dwPageID	= dwPageID;
			strName				= UIPageC.szName;

			for (lp = 0; lp < m_arrUIPageC.GetCount(); lp++)
			{
				if (!_tcscmp(UIPageC.szName, m_arrUIPageC.GetAt(lp).szName))
				{
					strName.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), UIPageC.szName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
					break;
				}
			}

			_tcscpy_s(UIPageC.szName, UI_MAX_NAMELEN, strName);

			m_arrUIPageC.Add(UIPageC);

			for (lp1 = 0; lp1 < m_arrMUIPageS.GetCount(); lp1++)
			{
				if (m_arrMUIPageS.GetAt(lp1).dwPageID == m_arrMUIPageC.GetAt(dwOldPage).dwPageID)
				{
					memcpy_s(&UIPageS, sizeof(UI_PAGES), &m_arrMUIPageS.GetAt(lp1), sizeof(UI_PAGES));

					UIPageS.dwPageID	= dwPageID;
					UIPageS.dwGroupID	= m_dwCGroupID;

					m_arrUIPageS.Add(UIPageS);

					strName.Format(_T("%s\\%08X\\%08X"), m_strFolder, UIPageS.dwGroupID, UIPageC.dwPageID);
					ShellCreate(strName);
				}
			}

			for (lp1 = 0; lp1 < m_arrMUICtrlC.GetCount(); lp1++)
			{
				if (m_arrMUICtrlC.GetAt(lp1).dwPageID == dwOldPageID)
				{
					dwCtrlID	= GetNewCtrlID();

					memcpy_s(&UICtrlC, sizeof(UI_CTRLC), &m_arrMUICtrlC.GetAt(lp1), sizeof(UI_CTRLC));

					UICtrlC.dwCtrlID	= dwCtrlID;
					UICtrlC.dwPageID	= dwPageID;
					strName				= UICtrlC.szName;

					for (lp = 0; lp < m_arrUICtrlC.GetCount(); lp++)
					{
						if (!_tcscmp(UICtrlC.szName, m_arrUICtrlC.GetAt(lp).szName))
						{
							strName.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), UICtrlC.szName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
							break;
						}
					}

					_tcscpy_s(UICtrlC.szName, UI_MAX_NAMELEN, strName);

					m_arrUICtrlC.Add(UICtrlC);

					for (lp2 = 0; lp2 < m_arrMUICtrlS.GetCount(); lp2++)
					{
						if (m_arrMUICtrlS.GetAt(lp2).dwCtrlID == m_arrMUICtrlC.GetAt(lp1).dwCtrlID)
						{
							memcpy_s(&UICtrlS, sizeof(UI_CTRLS), &m_arrMUICtrlS.GetAt(lp2), sizeof(UI_CTRLS));

							UICtrlS.dwCtrlID	= dwCtrlID;
							UICtrlS.dwGroupID	= m_dwCGroupID;

							m_arrUICtrlS.Add(UICtrlS);

							strName.Format(_T("%s\\%08X\\%08X\\%08X"), m_strFolder, UICtrlS.dwGroupID, UICtrlC.dwPageID, UICtrlC.dwCtrlID);
							ShellCreate(strName);
						}
					}

					for (lp2 = 0; lp2 < m_arrMUIImageC.GetCount(); lp2++)
					{
						if (m_arrMUIImageC.GetAt(lp2).dwCtrlID == m_arrMUICtrlC.GetAt(lp1).dwCtrlID)
						{
							dwImageID	= GetNewImageID();

							memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &m_arrMUIImageC.GetAt(lp2), sizeof(UI_IMAGEC));

							UIImageC.dwImageID	= dwImageID;
							UIImageC.dwPageID	= dwPageID;
							UIImageC.dwCtrlID	= dwCtrlID;

							m_arrUIImageC.Add(UIImageC);

							for (lp3 = 0; lp3 < m_arrMUIImageS.GetCount(); lp3++)
							{
								if (m_arrMUIImageS.GetAt(lp3).dwImageID == m_arrMUIImageC.GetAt(lp2).dwImageID)
								{
									memcpy_s(&UIImageS, sizeof(UI_IMAGES), &m_arrMUIImageS.GetAt(lp3), sizeof(UI_IMAGES));

									UIImageS.dwImageID	= dwImageID;
									UIImageS.dwGroupID	= m_dwCGroupID;
									
									m_arrUIImageS.Add(UIImageS);

									if (GetMImageFullPath(strName, m_arrMUIImageC.GetAt(lp2), m_arrMUIImageS.GetAt(lp3), TRUE))
									{
										GetImageFullPath(strTarget, UIImageC, UIImageS, FALSE);
										ShellCopy(strName, strTarget);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	ClearMergeData();

	OUTPUT_STR0(_T("Merge has been finished successfully"));

	WND_OUTPUT.SetMultipleAdd(FALSE);

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateWorkspace(WSU_SELECT);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnFileImageExport()
{
	DECLARE_FRAME()

	int		lp1;
	int		lp2;
	int		lp3;
	CString	strImage;
	CString	strFile;
	CString	strSource;
	CString	strTarget;

	WND_OUTPUT.SetMultipleAdd(TRUE);

	BeginWaitCursor();

	for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
	{
		strImage.Format(_T("%s\\Image_%08d_%dx%d"), m_strFolder, m_arrUIGroup.GetAt(lp1).dwGroupID, m_arrUIGroup.GetAt(lp1).uWidth, m_arrUIGroup.GetAt(lp1).uHeight);
		ShellCreate(strImage);

		for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
		{
			for (lp3 = 0; lp3 < m_arrUIImageS.GetCount(); lp3++)
			{
				if ((m_arrUIImageS.GetAt(lp3).dwImageID == m_arrUIImageC.GetAt(lp2).dwImageID) && (m_arrUIImageS.GetAt(lp3).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
				{
					if (!GetImageFullPath(strSource, m_arrUIImageC.GetAt(lp2), m_arrUIImageS.GetAt(lp3), TRUE))
					{
						OUTPUT_STR1(_T("Image file %s does not exist"), strSource);
						continue;
					}

					GetImageFileName(strFile, m_arrUIImageC.GetAt(lp2), m_arrUIImageS.GetAt(lp3));
					strTarget.Format(_T("%s\\%s"), strImage, strFile);
					ShellCopy(strSource, strTarget);
				}
			}
		}

		OUTPUT_STR0(_T("All images have been exported"));
	}

	EndWaitCursor();

	WND_OUTPUT.SetMultipleAdd(TRUE);
}

void CUIEditorDoc::OnFileImageImport()
{
	DECLARE_FRAME()

	int			lp1;
	int			lp2;
	int			lp3;
	int			lp4;
	CString		strImage;
	CString		strFile;
	CString		strSource;
	CString		strTarget;
	int			nType;
	DWORD		dwSize;
	USHORT		uWidth;
	USHORT		uHeight;
	BOOL		bMask;
	BOOL		bIdentical;
	USHORT		uCtrlWidth;
	USHORT		uCtrlHeight;

	WND_OUTPUT.SetMultipleAdd(TRUE);

	BeginWaitCursor();

	for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
	{
		strImage.Format(_T("%s\\Image_%08d_%dx%d"), m_strFolder, m_arrUIGroup.GetAt(lp1).dwGroupID, m_arrUIGroup.GetAt(lp1).uWidth, m_arrUIGroup.GetAt(lp1).uHeight);

		for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
		{
			for (lp3 = 0; lp3 < m_arrUIImageS.GetCount(); lp3++)
			{
				if ((m_arrUIImageS.GetAt(lp3).dwImageID == m_arrUIImageC.GetAt(lp2).dwImageID) && (m_arrUIImageS.GetAt(lp3).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
				{
					GetImageFullPath(strTarget, m_arrUIImageC.GetAt(lp2), m_arrUIImageS.GetAt(lp3), FALSE);
					GetImageFileName(strFile, m_arrUIImageC.GetAt(lp2), m_arrUIImageS.GetAt(lp3));
					strSource.Format(_T("%s\\%s"), strImage, strFile);

					if (!GetImageType(strSource, nType, dwSize, uWidth, uHeight, bMask))
					{
						continue;
					}

					bIdentical	= (((m_arrUIImageS.GetAt(lp3).uWidth != uWidth) || (m_arrUIImageS.GetAt(lp3).uHeight != uHeight)) ? FALSE : TRUE);

					ShellCopy(strSource, strTarget);

					m_arrUIImageS.GetAt(lp3).uWidth		= uWidth;
					m_arrUIImageS.GetAt(lp3).uHeight	= uHeight;
					m_arrUIImageS.GetAt(lp3).dwSize		= dwSize;
					m_arrUIImageS.GetAt(lp3).dwMaskSize	= ((bMask == TRUE) ? uWidth * uHeight : 0);

					if (bIdentical == FALSE)
					{
						for (lp4 = 0; lp4 < m_arrUICtrlS.GetCount(); lp4++)
						{
							if ((m_arrUICtrlS.GetAt(lp4).dwCtrlID == m_arrUIImageC.GetAt(lp2).dwCtrlID) && (m_arrUICtrlS.GetAt(lp4).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
							{
								uCtrlWidth	= m_arrUICtrlS.GetAt(lp4).uWidth;
								uCtrlHeight	= m_arrUICtrlS.GetAt(lp4).uHeight;

								if (uCtrlWidth < uWidth)
								{
									m_arrUICtrlS.GetAt(lp4).uWidth	= uWidth;
								}

								if (uCtrlHeight < uHeight)
								{
									m_arrUICtrlS.GetAt(lp4).uHeight	= uHeight;
								}

								m_arrUICtrlS.GetAt(lp4).rcWindow.right	= m_arrUICtrlS.GetAt(lp4).rcWindow.left + m_arrUICtrlS.GetAt(lp4).uWidth;
								m_arrUICtrlS.GetAt(lp4).rcWindow.bottom	= m_arrUICtrlS.GetAt(lp4).rcWindow.top + m_arrUICtrlS.GetAt(lp4).uHeight;

								if (m_arrUICtrlS.GetAt(lp4).rcWindow.right > m_arrUIGroup.GetAt(lp1).uWidth)
								{
									m_arrUICtrlS.GetAt(lp4).rcWindow.right	= m_arrUIGroup.GetAt(lp1).uWidth;
									m_arrUICtrlS.GetAt(lp4).rcWindow.left	= m_arrUICtrlS.GetAt(lp4).rcWindow.right - m_arrUICtrlS.GetAt(lp4).uWidth;
								}

								if (m_arrUICtrlS.GetAt(lp4).rcWindow.bottom > m_arrUIGroup.GetAt(lp1).uHeight)
								{
									m_arrUICtrlS.GetAt(lp4).rcWindow.bottom	= m_arrUIGroup.GetAt(lp1).uHeight;
									m_arrUICtrlS.GetAt(lp4).rcWindow.top	= m_arrUICtrlS.GetAt(lp4).rcWindow.bottom - m_arrUICtrlS.GetAt(lp4).uHeight;
								}

								OUTPUT_STR5(_T("Size of Ctrl %08X has been changed from %dx%d to %dx%d and position also may be changed"), m_arrUICtrlS.GetAt(lp4).dwCtrlID, uCtrlWidth, uCtrlHeight, m_arrUICtrlS.GetAt(lp4).uWidth, m_arrUICtrlS.GetAt(lp4).uHeight);
							}
						}
					}
				}
			}
		}

		OUTPUT_STR0(_T("All valid images have been imported"));
	}

	EndWaitCursor();

	WND_OUTPUT.SetMultipleAdd(TRUE);

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateWorkspace(WSU_SELECT);
	UpdateProperties();
	SetModifiedFlag();
}

#define	TEMPLATE_NAME	_T("\\UIExport.tpl")

void CUIEditorDoc::OnFileDBExport()
{
	DECLARE_FRAME()

	int				lp1;
	int				lp2;
	int				lp3;
	int				lp4;
	int				lp5;
	int				ct;
	int				nDefault;
	int				nPos;
	BOOL			bInserted;
	CString			strUDBName;
	HANDLE			hFile;
	DWORD			dwWritten;
	RESOURCE_INFO	ResourceInfo;
	PAGE_INFO		PageInfo;
	CONTROL_INFO	CtrlInfo;
	IMAGE_INFO		ImageInfo;
	BITMAP_INFO		BitmapInfo;
	CStringArray	arrImageName;
	CDWordArray		arrImageID;
	CString			strTemplate;
	HANDLE			hTemplate;
	DWORD			dwImage;
	char			cReadBuffer[496];
	char			cConvertBuffer[496];
	char			cWriteBuffer[512];
	DWORD			dwImagePos;
	DWORD			dwOffset;
	DWORD			dwCurrentPos;
	DWORD			dwMaxImageSize;
	DWORD			dwMaxCompressedImageSize;
	DWORD			dwMaxMaskSize;
	DWORD			dwMaxCompressedMaskSize;
	SYSTEMTIME		st;

	m_tUIHeader.dwExportCount++;

	SetModifiedFlag();
	OnFileSave();

	WND_OUTPUT.SetMultipleAdd(TRUE);

	BeginWaitCursor();

	for (lp1 = 0; lp1 < m_arrUIGroup.GetCount(); lp1++)
	{
		// 압축 버전
		arrImageName.RemoveAll();
		arrImageID.RemoveAll();

		strUDBName.Format(_T("%s\\%08d_%dx%d.udb"), m_strFolder, m_arrUIGroup.GetAt(lp1).dwGroupID, m_arrUIGroup.GetAt(lp1).uWidth, m_arrUIGroup.GetAt(lp1).uHeight);

		hFile	= CreateFile(strUDBName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			OUTPUT_STR1(_T("Failed to create file %s"), strUDBName);
			continue;
		}

		nPos	= 0;

		SetFilePointer(hFile, sizeof(RESOURCE_INFO), NULL, FILE_BEGIN);

		for (lp2 = 0; lp2 < m_arrUIPageC.GetCount(); lp2++)
		{
			for (lp3 = 0; lp3 < m_arrUIPageS.GetCount(); lp3++)
			{
				if ((m_arrUIPageS.GetAt(lp3).dwPageID == m_arrUIPageC.GetAt(lp2).dwPageID) && (m_arrUIPageS.GetAt(lp3).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
				{
					ct			= 0;
					nDefault	= 0;

					for (lp4 = 0; lp4 < m_arrUICtrlC.GetCount(); lp4++)
					{
						if (m_arrUICtrlC.GetAt(lp4).dwPageID == m_arrUIPageC.GetAt(lp2).dwPageID)
						{
							ct++;
						}
					}

					memset(&PageInfo, 0, sizeof(PAGE_INFO));

					PageInfo.bEnable		= ((m_arrUIPageS.GetAt(lp3).bEnable == TRUE) ? 1 : 0);
					PageInfo.uStartIDC		= nPos;
					PageInfo.uControlCount	= ct;
					PageInfo.uDefaultIDC	= nPos;
					nPos					+= ct;

					WriteFile(hFile, &PageInfo, sizeof(PAGE_INFO), &dwWritten, NULL);

					OUTPUT_STR2(_T("PAGE_INFO [%d/%d] has been written"), lp2, m_arrUIPageC.GetCount());
					break;
				}
			}
		}

		for (lp2 = 0; lp2 < m_arrUIPageC.GetCount(); lp2++)
		{
			for (lp3 = 0; lp3 < m_arrUICtrlC.GetCount(); lp3++)
			{
				if (m_arrUICtrlC.GetAt(lp3).dwPageID == m_arrUIPageC.GetAt(lp2).dwPageID)
				{
					for (lp4 = 0; lp4 < m_arrUICtrlS.GetCount(); lp4++)
					{
						if ((m_arrUICtrlS.GetAt(lp4).dwCtrlID == m_arrUICtrlC.GetAt(lp3).dwCtrlID) && (m_arrUICtrlS.GetAt(lp4).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
						{
							ct	= 0;

							for (lp5 = 0; lp5 < m_arrUIImageC.GetCount(); lp5++)
							{
								if (m_arrUIImageC.GetAt(lp5).dwCtrlID == m_arrUICtrlC.GetAt(lp3).dwCtrlID)
								{
									ct++;
								}
							}

							memset(&CtrlInfo, 0, sizeof(CONTROL_INFO));

							CtrlInfo.bEnable		= ((m_arrUICtrlS.GetAt(lp4).bEnable == TRUE) ? 1 : 0);
							CtrlInfo.bBackground	= ((m_arrUICtrlS.GetAt(lp4).bBackground == TRUE) ? 1 : 0);
							CtrlInfo.bCommon		= ((m_arrUICtrlS.GetAt(lp4).bCommon == TRUE) ? 1 : 0);
							CtrlInfo.uControlType	= m_arrUICtrlS.GetAt(lp4).nType;
							CtrlInfo.uImageCount	= ct;
							CtrlInfo.nLeft			= m_arrUICtrlS.GetAt(lp4).rcWindow.left;
							CtrlInfo.nTop			= m_arrUICtrlS.GetAt(lp4).rcWindow.top;
							CtrlInfo.nRight			= m_arrUICtrlS.GetAt(lp4).rcWindow.right;
							CtrlInfo.nBottom		= m_arrUICtrlS.GetAt(lp4).rcWindow.bottom;
							CtrlInfo.uWidth			= m_arrUICtrlS.GetAt(lp4).uWidth;
							CtrlInfo.uHeight		= m_arrUICtrlS.GetAt(lp4).uHeight;
							CtrlInfo.uPinLeft		= m_arrUICtrlS.GetAt(lp4).uPinLeft;
							CtrlInfo.uPinTop		= m_arrUICtrlS.GetAt(lp4).uPinTop;
							CtrlInfo.uPinRight		= m_arrUICtrlS.GetAt(lp4).uPinRight;
							CtrlInfo.uPinBottom		= m_arrUICtrlS.GetAt(lp4).uPinBottom;
							CtrlInfo.uLKeyIDC		= m_arrUICtrlS.GetAt(lp4).uIDLeft;
							CtrlInfo.uUKeyIDC		= m_arrUICtrlS.GetAt(lp4).uIDUp;
							CtrlInfo.uRKeyIDC		= m_arrUICtrlS.GetAt(lp4).uIDRight;
							CtrlInfo.uDKeyIDC		= m_arrUICtrlS.GetAt(lp4).uIDDown;
							CtrlInfo.uEKeyIDC		= m_arrUICtrlS.GetAt(lp4).uIDEnter;

							WideCharToMultiByte(CP_ACP, 0, m_arrUICtrlC.GetAt(lp3).szText, UI_MAX_TEXTLEN, CtrlInfo.szText, 32, NULL, NULL);

							WriteFile(hFile, &CtrlInfo, sizeof(CONTROL_INFO), &dwWritten, NULL);

							OUTPUT_STR2(_T("CONTROL_INFO [%d/%d] has been written"), lp3, m_arrUICtrlC.GetCount());
							break;
						}
					}
				}
			}
		}

		for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
		{
			bInserted	= FALSE;

			for (lp3 = 0; lp3 < arrImageName.GetCount(); lp3++)
			{
				int	nCompare	= _tcsicmp(arrImageName.GetAt(lp3), m_arrUIImageC.GetAt(lp2).szName);
				
				if (nCompare == 0)
				{
					bInserted	= TRUE;
					break;
				}
				else if (nCompare > 0)
				{
					arrImageName.InsertAt(lp3, m_arrUIImageC.GetAt(lp2).szName);
					arrImageID.InsertAt(lp3, m_arrUIImageC.GetAt(lp2).dwImageID);

					bInserted	= TRUE;
					break;
				}
			}

			if (bInserted == FALSE)
			{
				arrImageName.Add(m_arrUIImageC.GetAt(lp2).szName);
				arrImageID.Add(m_arrUIImageC.GetAt(lp2).dwImageID);
			}
		}

		arrImageName.RemoveAll();

		dwImagePos	= SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		dwOffset	= dwImagePos + (sizeof(IMAGE_INFO) * arrImageID.GetCount());

		memset(&ImageInfo, 0, sizeof(IMAGE_INFO));

		for (lp2 = 0; lp2 < arrImageID.GetCount(); lp2++)
		{
			WriteFile(hFile, &ImageInfo, sizeof(IMAGE_INFO), &dwWritten, NULL);

			OUTPUT_STR2(_T("IMAGE_INFO for dummy [%d/%d] has been written"), lp2, arrImageID.GetCount());
		}

		dwMaxImageSize				= 0;
		dwMaxCompressedImageSize	= 0;
		dwMaxMaskSize				= 0;
		dwMaxCompressedMaskSize		= 0;

		for (lp2 = 0; lp2 < arrImageID.GetCount(); lp2++)
		{
			for (lp3 = 0; lp3 < m_arrUIImageS.GetCount(); lp3++)
			{
				if ((m_arrUIImageS.GetAt(lp3).dwImageID == arrImageID.GetAt(lp2)) && (m_arrUIImageS.GetAt(lp3).dwGroupID == m_arrUIGroup.GetAt(lp1).dwGroupID))
				{
					memset(&BitmapInfo, 0, sizeof(BITMAP_INFO));

					BitmapInfo.uWidth			= m_arrUIImageS.GetAt(lp3).uWidth;
					BitmapInfo.uHeight			= m_arrUIImageS.GetAt(lp3).uHeight;
					BitmapInfo.uType			= m_arrUIImageS.GetAt(lp3).nType;
					BitmapInfo.uMask			= ((m_arrUIImageS.GetAt(lp3).dwMaskSize != 0) ? 1 : 0);
					BitmapInfo.uAlphaGradient	= m_arrUIImageS.GetAt(lp3).nAlphaType;
					BitmapInfo.uFirstOpacity	= m_arrUIImageS.GetAt(lp3).uFirstOpacity;
					BitmapInfo.uLastOpacity		= m_arrUIImageS.GetAt(lp3).uLastOpacity;

					WriteFile(hFile, &BitmapInfo, sizeof(BITMAP_INFO), &dwWritten, NULL);

					OUTPUT_STR2(_T("BITMAP_INFO [%d/%d] has been written"), lp2, arrImageID.GetCount());
					
					dwImage	= GetImageByID(arrImageID.GetAt(lp2));
					
					CString	strImageName;
					UINT	uSize;
					UINT	uMaskSize;
					UINT	uLine;

					memset(&ImageInfo, 0, sizeof(IMAGE_INFO));

					ImageInfo.uOffset		= dwOffset;
					ImageInfo.bCompress		= 1;

					if (dwImage != UI_INVALIDID)
					{
						if (GetImageFullPath(strImageName, m_arrUIImageC.GetAt(dwImage), m_arrUIImageS.GetAt(lp3), TRUE))
						{
							uLine		= (UINT)((((m_arrUIImageS.GetAt(lp3).uWidth * UDB_DEST_BPP) / CHAR_BIT) % sizeof(DWORD)) ? (((((m_arrUIImageS.GetAt(lp3).uWidth * UDB_DEST_BPP) / CHAR_BIT) / sizeof(DWORD)) + 1) * sizeof(DWORD)) : ((m_arrUIImageS.GetAt(lp3).uWidth * UDB_DEST_BPP) / CHAR_BIT));
							uSize		= ((m_arrUIImageS.GetAt(lp3).uHeight * uLine) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)) + BMP_EXTRA_BYTES;
							uMaskSize	= m_arrUIImageS.GetAt(lp3).dwMaskSize;

							ImageInfo.uSizeOriginal	= uSize;
							ImageInfo.uMaskOriginal	= uMaskSize;

							DWORD	dwImagePos	= SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

							if (dwOffset != (dwImagePos - sizeof(BITMAP_INFO)))
							{
								OUTPUT_STR3(_T("Offset for Image %s is not matched [C: %d / D: %d]"), strImageName, (dwImagePos - sizeof(BITMAP_INFO)), dwOffset);
							}

							SaveDatabaseImage(hFile, strImageName, m_arrUIImageS.GetAt(lp3).nType, uSize, uMaskSize, TRUE);

							OUTPUT_STR4(_T("Image %s has been written [%d/%d] at %d"), strImageName, uSize, uMaskSize, dwOffset);
						}
					}
					
					ImageInfo.uSize	= uSize;
					ImageInfo.uMask	= uMaskSize;
					dwCurrentPos	= SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

					SetFilePointer(hFile, dwImagePos + sizeof(IMAGE_INFO) * lp2, NULL, FILE_BEGIN);
					WriteFile(hFile, &ImageInfo, sizeof(IMAGE_INFO), &dwWritten, NULL);

					dwOffset	+= sizeof(BITMAP_INFO) + ImageInfo.uSize + ImageInfo.uMask;

					OUTPUT_STR2(_T("IMAGE_INFO [%d/%d] has been written"), lp2, arrImageID.GetCount());

					if (dwMaxImageSize < ImageInfo.uSizeOriginal)
					{
						dwMaxImageSize	= ImageInfo.uSizeOriginal;
					}

					if (dwMaxMaskSize < ImageInfo.uMaskOriginal)
					{
						dwMaxMaskSize	= ImageInfo.uMaskOriginal;
					}

					if (dwMaxCompressedImageSize < ImageInfo.uSize)
					{
						dwMaxCompressedImageSize	= ImageInfo.uSize;
					}

					if (dwMaxCompressedMaskSize < ImageInfo.uMask)
					{
						dwMaxCompressedMaskSize		= ImageInfo.uMask;
					}

					SetFilePointer(hFile, dwCurrentPos, NULL, FILE_BEGIN);
					break;
				}
			}
		}

		dwCurrentPos	= SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

		SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		memset(&ResourceInfo, 0, sizeof(RESOURCE_INFO));

		GetLocalTime(&st);

		ResourceInfo.uKey						= dwCurrentPos * 5 + 1234;
		ResourceInfo.uUIVersion					= UDB_VERSION;
		ResourceInfo.uUpdateVersion				= m_tUIHeader.dwSaveCount;
		ResourceInfo.uExportVersion				= m_tUIHeader.dwExportCount;
		ResourceInfo.uWidth						= m_arrUIGroup.GetAt(lp1).uWidth;
		ResourceInfo.uHeight					= m_arrUIGroup.GetAt(lp1).uHeight;
		ResourceInfo.uPageCount					= static_cast<unsigned int>(m_arrUIPageC.GetCount());
		ResourceInfo.uControlCount				= static_cast<unsigned int>(m_arrUICtrlC.GetCount());
		ResourceInfo.uImageCount				= static_cast<unsigned int>(arrImageID.GetCount());
		ResourceInfo.uImageMaxSize				= dwMaxImageSize;
		ResourceInfo.uImageCompressionMaxSize	= dwMaxCompressedImageSize;
		ResourceInfo.uMaskMaxSize				= dwMaxMaskSize;
		ResourceInfo.uMaskCompressionMaxSize	= dwMaxCompressedMaskSize;
		ResourceInfo.uResourceInfoSize			= sizeof(RESOURCE_INFO);
		ResourceInfo.uPageInfoSize				= sizeof(PAGE_INFO);
		ResourceInfo.uControlInfoSize			= sizeof(CONTROL_INFO);
		ResourceInfo.uImageInfoSize				= sizeof(IMAGE_INFO);

		sprintf_s(ResourceInfo.szDate, 16, "%04d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);

		WriteFile(hFile, &ResourceInfo, sizeof(RESOURCE_INFO), &dwWritten, NULL);

		OUTPUT_STR0(_T("RESOURCE_INFO has been written"));

		FlushFileBuffers(hFile);
		CloseHandle(hFile);

		OUTPUT_STR2(_T("%s has been created [%d Bytes]"), strUDBName, dwCurrentPos);

		// 헤더 파일
		strTemplate.Format(_T("%s%s"), ((CUIEditorApp*)AfxGetApp())->GetAppFolder(), TEMPLATE_NAME);

		hTemplate	= CreateFile(strTemplate, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hTemplate == INVALID_HANDLE_VALUE)
		{
			OUTPUT_STR1(_T("Failed to open template file %s"), strTemplate);
			continue;
		}

		strUDBName.Format(_T("%s\\%08d_%dx%d.h"), m_strFolder, m_arrUIGroup.GetAt(lp1).dwGroupID, m_arrUIGroup.GetAt(lp1).uWidth, m_arrUIGroup.GetAt(lp1).uHeight);

		hFile	= CreateFile(strUDBName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hTemplate);

			OUTPUT_STR1(_T("Failed to create file %s"), strUDBName);
			continue;
		}

		while (ReadFileString(hTemplate, cReadBuffer, 496))
		{
			if (!strcmp(cReadBuffer, "// $[RELEASE_DATE]"))
			{
				sprintf_s(cWriteBuffer, 512, "// %04d/%02d/%02d\r\n", st.wYear, st.wMonth, st.wDay);
				WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
			}
			else if (!strcmp(cReadBuffer, "#define UI_UPD_VERSION     $[UPDATE_VERSION]"))
			{
				sprintf_s(cWriteBuffer, 512, "#define UI_UPD_VERSION     0x%08X\r\n", m_tUIHeader.dwSaveCount);
				WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
			}
			else if (!strcmp(cReadBuffer, "#define UI_EXP_VERSION     $[EXPORT_VERSION]"))
			{
				sprintf_s(cWriteBuffer, 512, "#define UI_EXP_VERSION     0x%08X\r\n", m_tUIHeader.dwExportCount);
				WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
			}
			else if (!strcmp(cReadBuffer, "    $[PAGE_ID]"))
			{
				for (lp2 = 0; lp2 < m_arrUIPageC.GetCount(); lp2++)
				{
					memset(cConvertBuffer, 0, sizeof(BYTE) * 496);
					WideCharToMultiByte(CP_ACP, 0, m_arrUIPageC.GetAt(lp2).szName, UI_MAX_NAMELEN, reinterpret_cast<LPSTR>(cConvertBuffer), 496, NULL, NULL);
					sprintf_s(cWriteBuffer, 512, "    %s,\r\n", cConvertBuffer);
					WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
				}
			}
			else if (!strcmp(cReadBuffer, "    $[CTRL_ID]"))
			{
				for (lp2 = 0; lp2 < m_arrUIPageC.GetCount(); lp2++)
				{
					for (lp3 = 0; lp3 < m_arrUICtrlC.GetCount(); lp3++)
					{
						if (m_arrUICtrlC.GetAt(lp3).dwPageID == m_arrUIPageC.GetAt(lp2).dwPageID)
						{
							memset(cConvertBuffer, 0, sizeof(BYTE) * 496);
							WideCharToMultiByte(CP_ACP, 0, m_arrUICtrlC.GetAt(lp3).szName, UI_MAX_NAMELEN, reinterpret_cast<LPSTR>(cConvertBuffer), 496, NULL, NULL);
							sprintf_s(cWriteBuffer, 512, "    %s,\r\n", cConvertBuffer);
							WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
						}
					}
				}
			}
			else if (!strcmp(cReadBuffer, "    $[IMAGE_ID]"))
			{
				for (lp2 = 0; lp2 < arrImageID.GetCount(); lp2++)
				{
					dwImage	= GetImageByID(arrImageID.GetAt(lp2));

					memset(cConvertBuffer, 0, sizeof(BYTE) * 496);
					WideCharToMultiByte(CP_ACP, 0, m_arrUIImageC.GetAt(dwImage).szName, UI_MAX_NAMELEN, reinterpret_cast<LPSTR>(cConvertBuffer), 496, NULL, NULL);
					sprintf_s(cWriteBuffer, 512, "    IDI_%s,\r\n", cConvertBuffer);
					WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
				}
			}
			else
			{
				sprintf_s(cWriteBuffer, 512, "%s\r\n", cReadBuffer);
				WriteFile(hFile, cWriteBuffer, static_cast<DWORD>(strlen(cWriteBuffer) * sizeof(BYTE)), &dwWritten, NULL);
			}
		}

		arrImageID.RemoveAll();

		FlushFileBuffers(hFile);
		CloseHandle(hFile);

		CloseHandle(hTemplate);

		OUTPUT_STR1(_T("%s has been created"), strUDBName);
	}

	EndWaitCursor();

	WND_OUTPUT.SetMultipleAdd(TRUE);
}

void CUIEditorDoc::OnEditCopy()
{
	int	lp1;
	int	lp2;
	int	lp3;

	ClearClipboard();

	switch (m_nCType)
	{
	case UI_ITEM_NONE:
	case UI_ITEM_GROUP:
	case UI_ITEM_IMAGE:
		{
			m_nCBType	= UI_ITEM_NONE;
			return;
		}
		break;
	case UI_ITEM_PAGE:
		{
			DWORD	dwPage;

			m_nCBType	= UI_ITEM_PAGE;

			if (m_nSLType != UI_ITEM_PAGE)
			{
				ClearSelection();

				m_dwSLPageID	= m_dwCPageID;
			}

			dwPage	= GetPageByID(m_dwSLPageID);

			if (dwPage != UI_INVALIDID)
			{
				memcpy_s(&m_tCBPageC, sizeof(UI_PAGEC), &m_arrUIPageC.GetAt(dwPage), sizeof(UI_PAGEC));

				for (lp1 = 0; lp1 < m_arrUIPageS.GetCount(); lp1++)
				{
					if (m_arrUIPageS.GetAt(lp1).dwPageID == m_dwSLPageID)
					{
						m_arrCBPageS.Add(m_arrUIPageS.GetAt(lp1));
					}
				}

				for (lp1 = 0; lp1 < m_arrUICtrlC.GetCount(); lp1++)
				{
					if (m_arrUICtrlC.GetAt(lp1).dwPageID == m_dwSLPageID)
					{
						m_arrCBCtrlC.Add(m_arrUICtrlC.GetAt(lp1));

						for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
						{
							if (m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID)
							{
								m_arrCBCtrlS.Add(m_arrUICtrlS.GetAt(lp2));
							}
						}

						for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
						{
							if (m_arrUIImageC.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(lp1).dwCtrlID)
							{
								m_arrCBImageC.Add(m_arrUIImageC.GetAt(lp2));

								for (lp3 = 0; lp3 < m_arrUIImageS.GetCount(); lp3++)
								{
									if (m_arrUIImageS.GetAt(lp3).dwImageID == m_arrUIImageC.GetAt(lp2).dwImageID)
									{
										m_arrCBImageS.Add(m_arrUIImageS.GetAt(lp3));
									}
								}
							}
						}
					}
				}
			}
		}
		break;
	case UI_ITEM_CTRL:
		{
			DWORD	dwCtrl;

			m_nCBType	= UI_ITEM_CTRL;

			if (m_nSLType != UI_ITEM_CTRL)
			{
				ClearSelection();

				m_arrSLCtrlID.Add(m_dwCCtrlID);
			}

			for (lp1 = 0; lp1 < m_arrSLCtrlID.GetCount(); lp1++)
			{
				dwCtrl	= GetCtrlByID(m_arrSLCtrlID.GetAt(lp1));

				if (dwCtrl != UI_INVALIDID)
				{
					m_arrCBCtrlC.Add(m_arrUICtrlC.GetAt(dwCtrl));

					for (lp2 = 0; lp2 < m_arrUICtrlS.GetCount(); lp2++)
					{
						if (m_arrUICtrlS.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(dwCtrl).dwCtrlID)
						{
							m_arrCBCtrlS.Add(m_arrUICtrlS.GetAt(lp2));
						}
					}

					for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
					{
						if (m_arrUIImageC.GetAt(lp2).dwCtrlID == m_arrUICtrlC.GetAt(dwCtrl).dwCtrlID)
						{
							m_arrCBImageC.Add(m_arrUIImageC.GetAt(lp2));

							for (lp3 = 0; lp3 < m_arrUIImageS.GetCount(); lp3++)
							{
								if (m_arrUIImageS.GetAt(lp3).dwImageID == m_arrUIImageC.GetAt(lp2).dwImageID)
								{
									m_arrCBImageS.Add(m_arrUIImageS.GetAt(lp3));
								}
							}
						}
					}
				}
			}
		}
		break;
	}
}

void CUIEditorDoc::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	BOOL	bEnable	= TRUE;

	switch (m_nCType)
	{
	case UI_ITEM_PAGE:
	case UI_ITEM_CTRL:
		{
			bEnable	= TRUE;
		}
		break;
	default:
		{
			bEnable	= FALSE;
		}
		break;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnEditPaste()
{
	DECLARE_FRAME()

	DWORD		dwPageID;
	DWORD		dwCtrlID;
	DWORD		dwImageID;
	UI_PAGEC	UIPageC;
	UI_PAGES	UIPageS;
	UI_CTRLC	UICtrlC;
	UI_CTRLS	UICtrlS;
	UI_IMAGEC	UIImageC;
	UI_IMAGES	UIImageS;
	CString		strName;
	CString		strTarget;
	SYSTEMTIME	st;
	int			lp1;
	int			lp2;
	int			lp3;

	GetLocalTime(&st);

	switch (m_nCBType)
	{
	case UI_ITEM_PAGE:
		{
			dwPageID	= GetNewPageID();

			if (dwPageID != UI_INVALIDID)
			{
				memcpy_s(&UIPageC, sizeof(UI_PAGEC), &m_tCBPageC, sizeof(UI_PAGEC));

				UIPageC.dwPageID	= dwPageID;

				strName.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), UIPageC.szName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				_tcscpy_s(UIPageC.szName, UI_MAX_NAMELEN, strName);

				m_arrUIPageC.Add(UIPageC);

				for (lp1 = 0; lp1 < m_arrCBPageS.GetCount(); lp1++)
				{
					memcpy_s(&UIPageS, sizeof(UI_PAGES), &m_arrCBPageS.GetAt(lp1), sizeof(UI_PAGES));

					UIPageS.dwPageID	= dwPageID;

					m_arrUIPageS.Add(UIPageS);

					strName.Format(_T("%s\\%08X\\%08X"), m_strFolder, UIPageS.dwGroupID, UIPageC.dwPageID);
					ShellCreate(strName);
				}

				for (lp1 = 0; lp1 < m_arrCBCtrlC.GetCount(); lp1++)
				{
					dwCtrlID	= GetNewCtrlID();

					memcpy_s(&UICtrlC, sizeof(UI_CTRLC), &m_arrCBCtrlC.GetAt(lp1), sizeof(UI_CTRLC));

					UICtrlC.dwCtrlID	= dwCtrlID;
					UICtrlC.dwPageID	= dwPageID;

					strName.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), UICtrlC.szName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
					_tcscpy_s(UICtrlC.szName, UI_MAX_NAMELEN, strName);

					m_arrUICtrlC.Add(UICtrlC);

					for (lp2 = 0; lp2 < m_arrCBCtrlS.GetCount(); lp2++)
					{
						if (m_arrCBCtrlS.GetAt(lp2).dwCtrlID == m_arrCBCtrlC.GetAt(lp1).dwCtrlID)
						{
							memcpy_s(&UICtrlS, sizeof(UI_CTRLS), &m_arrCBCtrlS.GetAt(lp2), sizeof(UI_CTRLS));

							UICtrlS.dwCtrlID	= dwCtrlID;
							
							m_arrUICtrlS.Add(UICtrlS);

							strName.Format(_T("%s\\%08X\\%08X\\%08X"), m_strFolder, UICtrlS.dwGroupID, UICtrlC.dwPageID, UICtrlC.dwCtrlID);
							ShellCreate(strName);
						}
					}

					for (lp2 = 0; lp2 < m_arrCBImageC.GetCount(); lp2++)
					{
						if (m_arrCBImageC.GetAt(lp2).dwCtrlID == m_arrCBCtrlC.GetAt(lp1).dwCtrlID)
						{
							dwImageID	= GetNewImageID();

							memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &m_arrCBImageC.GetAt(lp2), sizeof(UI_IMAGEC));

							UIImageC.dwImageID	= dwImageID;
							UIImageC.dwPageID	= dwPageID;
							UIImageC.dwCtrlID	= dwCtrlID;

							m_arrUIImageC.Add(UIImageC);

							for (lp3 = 0; lp3 < m_arrCBImageS.GetCount(); lp3++)
							{
								if (m_arrCBImageS.GetAt(lp3).dwImageID == m_arrCBImageC.GetAt(lp2).dwImageID)
								{
									memcpy_s(&UIImageS, sizeof(UI_IMAGES), &m_arrCBImageS.GetAt(lp3), sizeof(UI_IMAGES));

									UIImageS.dwImageID	= dwImageID;
									
									m_arrUIImageS.Add(UIImageS);

									if (GetImageFullPath(strName, m_arrCBImageC.GetAt(lp2), m_arrCBImageS.GetAt(lp3), TRUE))
									{
										GetImageFullPath(strTarget, UIImageC, UIImageS, FALSE);
										ShellCopy(strName, strTarget);
									}
								}
							}
						}
					}
				}
			}
		}
		break;
	case UI_ITEM_CTRL:
		{
			for (lp1 = 0; lp1 < m_arrCBCtrlC.GetCount(); lp1++)
			{
				dwCtrlID	= GetNewCtrlID();

				memcpy_s(&UICtrlC, sizeof(UI_CTRLC), &m_arrCBCtrlC.GetAt(lp1), sizeof(UI_CTRLC));

				UICtrlC.dwCtrlID	= dwCtrlID;
				UICtrlC.dwPageID	= m_dwCPageID;

				strName.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), UICtrlC.szName, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				_tcscpy_s(UICtrlC.szName, UI_MAX_NAMELEN, strName);

				m_arrUICtrlC.Add(UICtrlC);

				for (lp2 = 0; lp2 < m_arrCBCtrlS.GetCount(); lp2++)
				{
					if (m_arrCBCtrlS.GetAt(lp2).dwCtrlID == m_arrCBCtrlC.GetAt(lp1).dwCtrlID)
					{
						memcpy_s(&UICtrlS, sizeof(UI_CTRLS), &m_arrCBCtrlS.GetAt(lp2), sizeof(UI_CTRLS));

						UICtrlS.dwCtrlID	= dwCtrlID;
						
						m_arrUICtrlS.Add(UICtrlS);

						strName.Format(_T("%s\\%08X\\%08X\\%08X"), m_strFolder, UICtrlS.dwGroupID, UICtrlC.dwPageID, UICtrlC.dwCtrlID);
						ShellCreate(strName);
					}
				}

				for (lp2 = 0; lp2 < m_arrCBImageC.GetCount(); lp2++)
				{
					if (m_arrCBImageC.GetAt(lp2).dwCtrlID == m_arrCBCtrlC.GetAt(lp1).dwCtrlID)
					{
						dwImageID	= GetNewImageID();

						memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &m_arrCBImageC.GetAt(lp2), sizeof(UI_IMAGEC));

						UIImageC.dwImageID	= dwImageID;
						UIImageC.dwPageID	= m_dwCPageID;
						UIImageC.dwCtrlID	= dwCtrlID;

						m_arrUIImageC.Add(UIImageC);

						for (lp3 = 0; lp3 < m_arrCBImageS.GetCount(); lp3++)
						{
							if (m_arrCBImageS.GetAt(lp3).dwImageID == m_arrCBImageC.GetAt(lp2).dwImageID)
							{
								memcpy_s(&UIImageS, sizeof(UI_IMAGES), &m_arrCBImageS.GetAt(lp3), sizeof(UI_IMAGES));

								UIImageS.dwImageID	= dwImageID;
								
								m_arrUIImageS.Add(UIImageS);

								if (GetImageFullPath(strName, m_arrCBImageC.GetAt(lp2), m_arrCBImageS.GetAt(lp3), TRUE))
								{
									GetImageFullPath(strTarget, UIImageC, UIImageS, FALSE);
									ShellCopy(strName, strTarget);
								}
							}
						}
					}
				}
			}
		}
		break;
	}

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateWorkspace(WSU_SELECT);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_nCBType != UI_ITEM_NONE));
}

void CUIEditorDoc::OnEditClear()
{
	UpdateWorkspace(WSU_SELECT);

	switch (m_nCType)
	{
	case UI_ITEM_GROUP:
		{
			DeleteGroup();
		}
		break;
	case UI_ITEM_PAGE:
		{
			DeletePage();
		}
		break;
	case UI_ITEM_CTRL:
		{
			DeleteCtrl();
		}
		break;
	case UI_ITEM_IMAGE:
		{
			DeleteImage();
		}
		break;
	}

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_DELETE);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateEditClear(CCmdUI* pCmdUI)
{
	BOOL	bEnable	= FALSE;

	switch (m_nCType)
	{
	case UI_ITEM_GROUP:
		{
			if ((m_arrUIGroup.GetCount() > 1) && (GetGroupByID(m_dwCGroupID) != UI_INVALIDID))
			{
				bEnable	= TRUE;
			}
		}
		break;
	case UI_ITEM_PAGE:
		{
			if (GetPageByID(m_dwCPageID) != UI_INVALIDID)
			{
				bEnable	= TRUE;
			}
		}
		break;
	case UI_ITEM_CTRL:
		{
			if (GetCtrlByID(m_dwCCtrlID) != UI_INVALIDID)
			{
				bEnable	= TRUE;
			}
		}
		break;
	case UI_ITEM_IMAGE:
		{
			if (GetImageByID(m_dwCImageID) != UI_INVALIDID)
			{
				bEnable	= TRUE;
			}
		}
		break;
	}
	
	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionGroupAdd()
{
	DECLARE_FRAME()

	CResolutionDialog	dResolution;
	CSelectDialog		dSelect;
	CString				strItem;
	int					lp;
	DWORD				dwBaseGroup	= UI_INVALIDID;

	if (dResolution.DoModal() != IDOK)
	{
		OUTPUT_STR0(_T("Adding new group was cancelled"));
		return;
	}

	dSelect.m_strTitle			= _T("그룹 선택");
	dSelect.m_strDescription	= _T("정보를 복사해 올 그룹을 선택하세요.");

	for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
	{
		strItem.Format(_T("%s [%dx%d]"), m_arrUIGroup.GetAt(lp).szName, m_arrUIGroup.GetAt(lp).uWidth, m_arrUIGroup.GetAt(lp).uHeight);
		dSelect.m_arrItems.Add(strItem);
		dSelect.m_arrPos.Add(m_arrUIGroup.GetAt(lp).dwGroupID);
	}

	if (dSelect.DoModal() != IDOK)
	{
		OUTPUT_STR0(_T("Adding new group was cancelled"));
		return;
	}

	dwBaseGroup	= dSelect.m_arrPos.GetAt(dSelect.m_nSelect);

	AddGroup(dResolution.m_nWidth, dResolution.m_nHeight, dwBaseGroup);

	m_nCType	= UI_ITEM_GROUP;

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateWorkspace(WSU_SELECT);
	UpdateProperties();
	SetModifiedFlag();

	pFrame->m_wndProperties.SetFocus();
}

void CUIEditorDoc::OnActionGroupDelete()
{
	m_nCType	= UI_ITEM_GROUP;

	DeleteGroup();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionGroupDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_arrUIGroup.GetCount() > 1));
}

void CUIEditorDoc::OnActionGroupActive()
{
	DECLARE_FRAME()

	CSelectDialog	dSelect;
	CString			strItem;
	int				lp;

	dSelect.m_strTitle			= _T("그룹 선택");
	dSelect.m_strDescription	= _T("작업할 그룹을 선택하세요.");

	for (lp = 0; lp < m_arrUIGroup.GetCount(); lp++)
	{
		strItem.Format(_T("%s [%dx%d]"), m_arrUIGroup.GetAt(lp).szName, m_arrUIGroup.GetAt(lp).uWidth, m_arrUIGroup.GetAt(lp).uHeight);
		dSelect.m_arrItems.Add(strItem);
		dSelect.m_arrPos.Add(m_arrUIGroup.GetAt(lp).dwGroupID);

		if (m_arrUIGroup.GetAt(lp).dwGroupID == m_dwCGroupID)
		{
			dSelect.m_nSelect	= lp;
		}
	}

	if (dSelect.DoModal() != IDOK)
	{
		OUTPUT_STR0(_T("Activating group was cancelled"));
		return;
	}

	m_dwCGroupID	= dSelect.m_arrPos.GetAt(dSelect.m_nSelect);
	m_nCType		= UI_ITEM_GROUP;
	lp				= GetGroupByID(m_dwCGroupID);

	OUTPUT_STR2(_T("Group %08X [%s] has been activated"), m_dwCGroupID, m_arrUIGroup.GetAt(lp).szName);

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
}

void CUIEditorDoc::OnUpdateActionGroupActive(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_arrUIGroup.GetCount() > 1));
}

void CUIEditorDoc::OnActionPageAdd()
{
	DECLARE_FRAME()

	AddPage();

	m_nCType	= UI_ITEM_PAGE;

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateWorkspace(WSU_SELECT);
	UpdateProperties();
	SetModifiedFlag();

	pFrame->m_wndProperties.SetFocus();
}

void CUIEditorDoc::OnUpdateActionPageAdd(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_dwCGroupID != UI_INVALIDID));
}

void CUIEditorDoc::OnActionPageDelete()
{
	m_nCType	= UI_ITEM_PAGE;

	UpdateWorkspace(WSU_SELECT);
	DeletePage();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_DELETE);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionPageDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_dwCPageID != UI_INVALIDID));
}

void CUIEditorDoc::OnActionPageMoveTop()
{
	MovePageToTop();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionPageMoveTop(CCmdUI* pCmdUI)
{
	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	BOOL	bEnable	= TRUE;

	if (dwPage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwPage < 1) || (dwPage > static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionPageMoveUp()
{
	MovePageUp();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionPageMoveUp(CCmdUI* pCmdUI)
{
	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	BOOL	bEnable	= TRUE;

	if (dwPage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwPage < 1) || (dwPage > static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionPageMoveDown()
{
	MovePageDown();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionPageMoveDown(CCmdUI* pCmdUI)
{
	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	BOOL	bEnable	= TRUE;

	if (dwPage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwPage < 0) || (dwPage >= static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionPageMoveBottom()
{
	MovePageToBottom();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionPageMoveBottom(CCmdUI* pCmdUI)
{
	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	BOOL	bEnable	= TRUE;

	if (dwPage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwPage < 0) || (dwPage >= static_cast<DWORD>(m_arrUIPageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionPageGenerate()
{
	DECLARE_FRAME()

	GeneratePage();
}

void CUIEditorDoc::OnUpdateActionPageGenerate(CCmdUI* pCmdUI)
{
	DWORD	dwPage	= GetPageByID(m_dwCPageID);
	BOOL	bEnable	= TRUE;

	if (dwPage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionCtrlAdd()
{
	DECLARE_FRAME()

	AddCtrl();

	m_nCType	= UI_ITEM_CTRL;

	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateWorkspace(WSU_SELECT);
	UpdateProperties();
	SetModifiedFlag();

	pFrame->m_wndProperties.SetFocus();
}

void CUIEditorDoc::OnUpdateActionCtrlAdd(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_dwCPageID != UI_INVALIDID));
}

void CUIEditorDoc::OnActionCtrlDelete()
{
	m_nCType	= UI_ITEM_CTRL;

	UpdateWorkspace(WSU_SELECT);
	DeleteCtrl();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_DELETE);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionCtrlDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_dwCCtrlID != UI_INVALIDID));
}

void CUIEditorDoc::OnActionCtrlMoveTop()
{
	MoveCtrlToTop();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionCtrlMoveTop(CCmdUI* pCmdUI)
{
	DWORD	dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	BOOL	bEnable	= TRUE;

	if (dwCtrl == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwCtrl < 1) || (dwCtrl > static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionCtrlMoveUp()
{
	MoveCtrlUp();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionCtrlMoveUp(CCmdUI* pCmdUI)
{
	DWORD	dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	BOOL	bEnable	= TRUE;

	if (dwCtrl == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwCtrl < 1) || (dwCtrl > static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionCtrlMoveDown()
{
	MoveCtrlDown();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionCtrlMoveDown(CCmdUI* pCmdUI)
{
	DWORD	dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	BOOL	bEnable	= TRUE;

	if (dwCtrl == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwCtrl < 0) || (dwCtrl >= static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionCtrlMoveBottom()
{
	MoveCtrlToBottom();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionCtrlMoveBottom(CCmdUI* pCmdUI)
{
	DWORD	dwCtrl	= GetCtrlByID(m_dwCCtrlID);
	BOOL	bEnable	= TRUE;

	if (dwCtrl == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwCtrl < 0) || (dwCtrl >= static_cast<DWORD>(m_arrUICtrlC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

#define	MAX_IMAGEFILES	1024

void CUIEditorDoc::OnActionImageAdd()
{
	DECLARE_FRAME()

	TCHAR		szFilters[]	= _T("지원하는 이미지 파일|*.bmp;*.png|모든 파일|*.*||");
	CFileDialog	dOpen(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, szFilters, AfxGetApp()->GetMainWnd());
	TCHAR		szCurrentFolder[MAX_PATH + 1];
	POSITION	pos;
	CString		strImageFolder;
	CString		strFileName;
	CString		strFullPath;
	CString		strPath;
	CString		strTitle;
	CString		strExt;
	int			nPos;
	int			lp1;
	int			lp2;
	BOOL		bFound;
	DWORD		dwFound	= UI_INVALIDID;
	SYSTEMTIME	st;

	GetCurrentDirectory(MAX_PATH + 1, szCurrentFolder);

	strImageFolder	= AfxGetApp()->GetProfileString(_T("Settings"), _T("Image Folder"), szCurrentFolder);

	dOpen.GetOFN().lpstrFile		= strFileName.GetBuffer((MAX_PATH + 1) * MAX_IMAGEFILES);
	dOpen.GetOFN().nMaxFile			= (MAX_PATH + 1) * MAX_IMAGEFILES;
	dOpen.GetOFN().lpstrInitialDir	= strImageFolder.GetBuffer();

	if (dOpen.DoModal() == IDOK)
	{
		BeginWaitCursor();

		strImageFolder.ReleaseBuffer();

		if ((m_nCType != UI_ITEM_CTRL) || (m_dwCCtrlID == UI_INVALIDID))
		{
			AddCtrl();
		}

		pos		= dOpen.GetStartPosition();
		bFound	= TRUE;

		while (pos)
		{
			strFullPath		= dOpen.GetNextPathName(pos);
			nPos			= strFullPath.ReverseFind(_T('\\'));
			strImageFolder	= strFullPath.Left(nPos + 1);

			if (bFound)
			{
				AfxGetApp()->WriteProfileString(_T("Settings"), _T("Image Folder"), strImageFolder);

				bFound	= FALSE;
			}

			strPath			= strFullPath.Mid(nPos + 1);
			nPos			= strPath.ReverseFind(_T('.'));
			strTitle		= strPath.Left(nPos);
			strExt			= strPath.Mid(nPos + 1);
			dwFound			= UI_INVALIDID;

			for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
			{
				if (!strTitle.CompareNoCase(m_arrUIImageC.GetAt(lp1).szName))
				{
					for (lp2 = 0; lp2 < m_arrUIImageS.GetCount(); lp2++)
					{
						if ((m_arrUIImageS.GetAt(lp2).dwImageID == m_arrUIImageC.GetAt(lp1).dwImageID) && (m_arrUIImageS.GetAt(lp2).dwGroupID == m_dwCGroupID))
						{
							dwFound	= lp2;
							break;
						}
					}

					if (dwFound != UI_INVALIDID)
					{
						bFound	= FALSE;

						if (!strExt.CompareNoCase(_T("bmp")))
						{
							if ((m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_BMP) != UI_IMAGE_BMP)
							{
								bFound	= TRUE;
							}
						}
						else if (!strExt.CompareNoCase(_T("png")))
						{
							if ((m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_PNG) != UI_IMAGE_PNG)
							{
								bFound	= TRUE;
							}
						}
#if FALSE
						else if ((!strExt.CompareNoCase(_T("jpg"))) || (!strExt.CompareNoCase(_T("jpeg"))))
						{
							if ((m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_JPG) != UI_IMAGE_JPG)
							{
								bFound	= TRUE;
							}
						}
						else if (!strExt.CompareNoCase(_T("gif")))
						{
							if ((m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_GIF) != UI_IMAGE_GIF)
							{
								bFound	= TRUE;
							}
						}
#endif
						if (bFound)
						{
							bFound	= FALSE;

							GetLocalTime(&st);
							strImageFolder.Format(_T("%s%s_%04d%02d%02d%02d%02d%02d%03d.%s"), strImageFolder, strTitle, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, strExt);
							MoveFile(strFullPath, strImageFolder);
							
							strFullPath	= strImageFolder;

							OUTPUT_STR2(_T("Image %s was renamed to %s due to name confliction"), strFullPath, strImageFolder);
							break;
						}
					}
				}
			}

			if (!AddImage(strFullPath))
			{
				continue;
			}

			bFound	= FALSE;

			for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
			{
				if ((m_arrUIImageC.GetAt(lp1).dwCtrlID == m_dwCCtrlID) && (m_arrUIImageC.GetAt(lp1).dwImageID != m_dwCImageID))
				{
					bFound	= TRUE;
					break;
				}
			}

			dwFound	= UI_INVALIDID;

			for (lp1 = 0; lp1 < m_arrUIImageS.GetCount(); lp1++)
			{
				if ((m_arrUIImageS.GetAt(lp1).dwImageID == m_dwCImageID) && (m_arrUIImageS.GetAt(lp1).dwGroupID == m_dwCGroupID))
				{
					dwFound	= lp1;
					break;
				}
			}

			if (bFound == FALSE)
			{
				for (lp1 = 0; lp1 < m_arrUICtrlS.GetCount(); lp1++)
				{
					if (m_arrUICtrlS.GetAt(lp1).dwCtrlID == m_dwCCtrlID)
					{
						m_arrUICtrlS.GetAt(lp1).uWidth			= m_arrUIImageS.GetAt(dwFound).uWidth;
						m_arrUICtrlS.GetAt(lp1).uHeight			= m_arrUIImageS.GetAt(dwFound).uHeight;
						m_arrUICtrlS.GetAt(lp1).rcWindow.right	= m_arrUICtrlS.GetAt(lp1).rcWindow.left + m_arrUICtrlS.GetAt(lp1).uWidth;
						m_arrUICtrlS.GetAt(lp1).rcWindow.bottom	= m_arrUICtrlS.GetAt(lp1).rcWindow.top + m_arrUICtrlS.GetAt(lp1).uHeight;
					}
				}
			}

			for (lp1 = 0; lp1 < m_arrUICtrlS.GetCount(); lp1++)
			{
				if (m_arrUICtrlS.GetAt(lp1).dwCtrlID == m_dwCCtrlID)
				{
					if (m_arrUICtrlS.GetAt(lp1).uWidth < m_arrUIImageS.GetAt(dwFound).uWidth)
					{
						m_arrUICtrlS.GetAt(lp1).uWidth			= m_arrUIImageS.GetAt(dwFound).uWidth;
						m_arrUICtrlS.GetAt(lp1).rcWindow.right	= m_arrUICtrlS.GetAt(lp1).rcWindow.left + m_arrUICtrlS.GetAt(lp1).uWidth;
					}

					if (m_arrUICtrlS.GetAt(lp1).uHeight < m_arrUIImageS.GetAt(dwFound).uHeight)
					{
						m_arrUICtrlS.GetAt(lp1).uHeight			= m_arrUIImageS.GetAt(dwFound).uHeight;
						m_arrUICtrlS.GetAt(lp1).rcWindow.bottom	= m_arrUICtrlS.GetAt(lp1).rcWindow.top + m_arrUICtrlS.GetAt(lp1).uHeight;
					}
				}
			}
		}

		EndWaitCursor();

		m_nCType	= UI_ITEM_IMAGE;

		UpdateAllViews(NULL);
		UpdateWorkspace(WSU_FULL);
		UpdateWorkspace(WSU_SELECT);
		UpdateProperties();
		SetModifiedFlag();

		pFrame->m_wndProperties.SetFocus();
	}
	else
	{
		strImageFolder.ReleaseBuffer();
		
		OUTPUT_STR0(_T("Adding image was cancelled by user"));
	}

	strFileName.ReleaseBuffer();
}

void CUIEditorDoc::OnUpdateActionImageAdd(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_dwCPageID != UI_INVALIDID));
}

void CUIEditorDoc::OnActionImageDelete()
{
	m_nCType	= UI_ITEM_IMAGE;

	UpdateWorkspace(WSU_SELECT);
	DeleteImage();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_DELETE);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionImageDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((BOOL)(m_dwCImageID != UI_INVALIDID));
}

void CUIEditorDoc::OnActionImageMoveTop()
{
	MoveImageToTop();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionImageMoveTop(CCmdUI* pCmdUI)
{
	DWORD	dwImage	= GetImageByID(m_dwCImageID);
	BOOL	bEnable	= TRUE;

	if (dwImage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwImage < 1) || (dwImage > static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionImageMoveUp()
{
	MoveImageUp();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionImageMoveUp(CCmdUI* pCmdUI)
{
	DWORD	dwImage	= GetImageByID(m_dwCImageID);
	BOOL	bEnable	= TRUE;

	if (dwImage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwImage < 1) || (dwImage > static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionImageMoveDown()
{
	MoveImageDown();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionImageMoveDown(CCmdUI* pCmdUI)
{
	DWORD	dwImage	= GetImageByID(m_dwCImageID);
	BOOL	bEnable	= TRUE;

	if (dwImage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwImage < 0) || (dwImage >= static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnActionImageMoveBottom()
{
	MoveImageToBottom();
	UpdateAllViews(NULL);
	UpdateWorkspace(WSU_FULL);
	UpdateProperties();
	SetModifiedFlag();
}

void CUIEditorDoc::OnUpdateActionImageMoveBottom(CCmdUI* pCmdUI)
{
	DWORD	dwImage	= GetImageByID(m_dwCImageID);
	BOOL	bEnable	= TRUE;

	if (dwImage == UI_INVALIDID)
	{
		bEnable	= FALSE;
	}

	if ((dwImage < 0) || (dwImage >= static_cast<DWORD>(m_arrUIImageC.GetUpperBound())))
	{
		bEnable	= FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CUIEditorDoc::OnToolsLogSave()
{
	DECLARE_FRAME()

	SYSTEMTIME	st;
	CString		strFileName;

	GetLocalTime(&st);
	strFileName.Format(_T("UI_%04d%02d%02d%02d%02d%02d.log"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	TCHAR		szFilters[]	= _T("로그 파일 (*.log)|*.log|모든 파일|*.*||");
	CFileDialog	dSave(FALSE, _T("log"), strFileName, OFN_OVERWRITEPROMPT, szFilters, WND_MAIN);

	if (dSave.DoModal() == IDOK)
	{
		WND_OUTPUT.Save(dSave.GetPathName());
	}
}

void CUIEditorDoc::OnUpdateToolsLogSave(CCmdUI* pCmdUI)
{
	DECLARE_FRAME()

	pCmdUI->Enable((BOOL)(!WND_OUTPUT.IsEmpty()));
}

void CUIEditorDoc::OnToolsLogClean()
{
	DECLARE_FRAME()

	WND_OUTPUT.Clean();
}

void CUIEditorDoc::OnUpdateToolsLogClean(CCmdUI* pCmdUI)
{
	DECLARE_FRAME()

	pCmdUI->Enable((BOOL)(!WND_OUTPUT.IsEmpty()));
}


void CUIEditorDoc::OnToolsCheck()
{
	DECLARE_FRAME()

	BOOL	bFound;
	int		nCount;
	int		lp1;
	int		lp2;

	OUTPUT_STR0(_T("Checking Image Integrity..."));

	// Phase 1

	OUTPUT_STR0(_T("Phase 1: Checking image duplication of Common Information..."));

	do
	{
		bFound	= FALSE;

		for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
		{
			for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
			{
				if (lp2 == lp1)
				{
					continue;
				}

				if (m_arrUIImageC.GetAt(lp1).dwImageID == m_arrUIImageC.GetAt(lp2).dwImageID)
				{
					OUTPUT_STR4(_T("ImageC [%08X:%s] and [%08X:%s] are conflicted."), lp1, m_arrUIImageC.GetAt(lp1).szName, lp2, m_arrUIImageC.GetAt(lp2).szName);

					bFound	= TRUE;
					
					m_arrUIImageC.RemoveAt(lp2);
					SetModifiedFlag();
					break;
				}
			}

			break;
		}
	} while (bFound == TRUE);

	// Phase 2

	OUTPUT_STR0(_T("Phase 2: Checking image duplication of Specified Information..."));

	do
	{
		bFound	= FALSE;

		for (lp1 = 0; lp1 < m_arrUIImageS.GetCount(); lp1++)
		{
			for (lp2 = 0; lp2 < m_arrUIImageS.GetCount(); lp2++)
			{
				if (lp2 == lp1)
				{
					continue;
				}

				if ((m_arrUIImageS.GetAt(lp1).dwImageID == m_arrUIImageS.GetAt(lp2).dwImageID) && (m_arrUIImageS.GetAt(lp1).dwGroupID == m_arrUIImageS.GetAt(lp2).dwGroupID))
				{
					OUTPUT_STR2(_T("ImageS [%08X] and [%08X] are conflicted."), lp1, lp2);

					bFound	= TRUE;
					
					m_arrUIImageS.RemoveAt(lp2);
					SetModifiedFlag();
					break;
				}
			}

			break;
		}
	} while (bFound == TRUE);

	// Phase 3

	OUTPUT_STR0(_T("Phase 3: Checking image matching for Common Information..."));

	do
	{
		bFound	= FALSE;

		for (lp1 = 0; lp1 < m_arrUIImageC.GetCount(); lp1++)
		{
			nCount	= 0;

			for (lp2 = 0; lp2 < m_arrUIImageS.GetCount(); lp2++)
			{
				if (m_arrUIImageC.GetAt(lp1).dwImageID == m_arrUIImageS.GetAt(lp2).dwImageID)
				{
					nCount++;
				}
			}

			if (nCount == 0)
			{
				OUTPUT_STR2(_T("ImageC [%08X:%s] is orphan information."), lp1, m_arrUIImageC.GetAt(lp1).szName);

				bFound	= TRUE;

				m_arrUIImageC.RemoveAt(lp1);
				SetModifiedFlag();
				break;
			}
		}
	} while (bFound == TRUE);

	// Phase 4

	OUTPUT_STR0(_T("Phase 4: Checking image matching for Specified Information..."));

	do
	{
		bFound	= FALSE;

		for (lp1 = 0; lp1 < m_arrUIImageS.GetCount(); lp1++)
		{
			nCount	= 0;

			for (lp2 = 0; lp2 < m_arrUIImageC.GetCount(); lp2++)
			{
				if (m_arrUIImageS.GetAt(lp1).dwImageID == m_arrUIImageC.GetAt(lp2).dwImageID)
				{
					nCount++;
				}
			}

			if (nCount == 0)
			{
				OUTPUT_STR1(_T("ImageS [%08X] is orphan information."), lp1);

				bFound	= TRUE;

				m_arrUIImageS.RemoveAt(lp1);
				SetModifiedFlag();
				break;
			}
		}
	} while (bFound == TRUE);

	// Phase 5

	OUTPUT_STR0(_T("Phase 5: Checking count of images for Common Information..."));

	nCount	= static_cast<int>(m_arrUIImageC.GetCount() - (m_arrUIImageS.GetCount() * m_arrUIGroup.GetCount()));

	if (nCount > 0)
	{
		OUTPUT_STR1(_T("Image Common Information is too big. %d items will be truncated."), nCount);

		for (lp1 = 0; lp1 < nCount; lp1++)
		{
			lp2	= static_cast<int>(m_arrUIImageC.GetCount() - 1);

			m_arrUIImageC.RemoveAt(lp2);
		}
	}

	// Phase 6

	OUTPUT_STR0(_T("Phase 6: Checking count of images for Specified Information..."));

	nCount	= static_cast<int>((m_arrUIImageS.GetCount() * m_arrUIGroup.GetCount()) - m_arrUIImageC.GetCount());

	if (nCount > 0)
	{
		OUTPUT_STR1(_T("Image Specified Information is too big. %d items will be truncated."), nCount);

		for (lp1 = 0; lp1 < nCount; lp1++)
		{
			lp2	= static_cast<int>(m_arrUIImageS.GetCount() - 1);

			m_arrUIImageS.RemoveAt(lp2);
		}
	}

	OUTPUT_STR0(_T("Checking Image Integrity has been completed. Please save the document."));
}

void CUIEditorDoc::OnUpdateToolsCheck(CCmdUI* pCmdUI)
{
	DECLARE_FRAME()

	pCmdUI->Enable((BOOL)(m_arrUIGroup.GetCount()));
}
