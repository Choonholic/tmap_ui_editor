// MultiDialog.h

#pragma once

class CMultiDialog : public CDialog
{
	DECLARE_DYNAMIC(CMultiDialog)

public:
	CMultiDialog(CWnd* pParent = NULL);
	virtual	~CMultiDialog();

	enum { IDD = IDD_MULTIOBJECT };

	CString			m_strTitle;
	CString			m_strDescription;
	CStringArray	m_arrItems;
	CDWordArray		m_arrPos;

	CDWordArray		m_arrSelItems;
	CStatic			m_ctlDescription;
	CListBox		m_ctlList;
	CButton			m_ctlOK;

	virtual	BOOL	OnInitDialog();

protected:
	virtual	void	DoDataExchange(CDataExchange* pDX);
	virtual	void	OnOK();

	DECLARE_MESSAGE_MAP()
};
