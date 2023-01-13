// ResolutionDialog.h

#pragma once

class CResolutionDialog : public CDialog
{
	DECLARE_DYNAMIC(CResolutionDialog)

public:
	CResolutionDialog(CWnd* pParent = NULL);
	virtual ~CResolutionDialog();

	enum	{ IDD = IDD_RESOLUTION };

	int		m_nWidth;
	int		m_nHeight;

protected:
	virtual	void	DoDataExchange(CDataExchange* pDX);
	virtual	void	OnOK();

	DECLARE_MESSAGE_MAP()
};
