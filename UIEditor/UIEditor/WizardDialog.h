// WizardDialog.h

#pragma once

#ifndef WIZ_MODES
#define	WIZ_MODES
#define	WIZ_CANCEL		0x00
#define	WIZ_NEW			0x01
#define	WIZ_OPEN		0x02
#endif

class CWizardDialog : public CDialog
{
	DECLARE_DYNAMIC(CWizardDialog)

public:
	CWizardDialog(CWnd* pParent = NULL);
	virtual	~CWizardDialog();

	enum { IDD = IDD_WIZARD };

	afx_msg void OnBnClickedWizNew();
	afx_msg void OnBnClickedWizOpen();

	int		m_nWizardMode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
