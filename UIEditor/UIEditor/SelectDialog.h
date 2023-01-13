// SelectDialog.h

#pragma once

class CSelectDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectDialog)

public:
	CSelectDialog(CWnd* pParent = NULL);
	virtual	~CSelectDialog();

	enum { IDD = IDD_SELECTOBJECT };

	CString			m_strTitle;
	CString			m_strDescription;
	CStringArray	m_arrItems;
	CDWordArray		m_arrPos;

	int				m_nSelect;
	CStatic			m_ctlDescription;
	CListBox		m_ctlList;
	CButton			m_ctlOK;

	virtual	BOOL	OnInitDialog();

protected:
	virtual	void	DoDataExchange(CDataExchange* pDX);
	virtual	void	OnOK();

	DECLARE_MESSAGE_MAP()
};
