// FolderSelectDialog.h

#pragma once

class CFolderSelectDialog : public CDialog
{
	DECLARE_DYNAMIC(CFolderSelectDialog)

public:
	CFolderSelectDialog(CWnd* pParent = NULL);
	virtual	~CFolderSelectDialog();

	enum	{ IDD = IDD_FOLDERSELECT };

	CString	m_strFolder;

	afx_msg	void	OnBnClickedFolderBrowse();

protected:
	virtual	void	DoDataExchange(CDataExchange* pDX);
	virtual	void	OnOK();

	DECLARE_MESSAGE_MAP()
};
