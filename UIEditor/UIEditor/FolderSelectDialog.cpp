// FolderSelectDialog.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "FolderSelectDialog.h"

IMPLEMENT_DYNAMIC(CFolderSelectDialog, CDialog)

CFolderSelectDialog::CFolderSelectDialog(CWnd* pParent /*=NULL*/) : CDialog(CFolderSelectDialog::IDD, pParent)
{
}

CFolderSelectDialog::~CFolderSelectDialog()
{
}

void CFolderSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FOLDER_EDIT, m_strFolder);
}

BEGIN_MESSAGE_MAP(CFolderSelectDialog, CDialog)
	ON_BN_CLICKED(IDC_FOLDER_BROWSE, &CFolderSelectDialog::OnBnClickedFolderBrowse)
END_MESSAGE_MAP()

void CFolderSelectDialog::OnOK()
{
	UpdateData(TRUE);

	if (m_strFolder.IsEmpty())
	{
		return;
	}

	if ((m_strFolder.GetLength() > 3) && (m_strFolder.Right(1) == _T("\\")))
	{
		m_strFolder	= m_strFolder.Left(m_strFolder.GetLength() - 1);
	}

	CDialog::OnOK();
}

void CFolderSelectDialog::OnBnClickedFolderBrowse()
{
	BROWSEINFO	bi	= { 0 };
	
	bi.lpszTitle	= _T("폴더 선택");

	LPITEMIDLIST	lpidl	= SHBrowseForFolder(&bi);

	if (lpidl != 0)
	{
		TCHAR	szPath[MAX_PATH];

		if (SHGetPathFromIDList(lpidl, szPath))
		{
			m_strFolder	= szPath;

			UpdateData(FALSE);
		}

		IMalloc*	im	= 0;

		if (SUCCEEDED(SHGetMalloc(&im)))
		{
			im->Free(lpidl);
			im->Release();
		}
	}
}
