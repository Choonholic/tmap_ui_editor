// WizardDialog.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "WizardDialog.h"

IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

CWizardDialog::CWizardDialog(CWnd* pParent /*=NULL*/) : CDialog(CWizardDialog::IDD, pParent), m_nWizardMode(WIZ_CANCEL)
{
}

CWizardDialog::~CWizardDialog()
{
}

void CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDC_WIZ_NEW, &CWizardDialog::OnBnClickedWizNew)
	ON_BN_CLICKED(IDC_WIZ_OPEN, &CWizardDialog::OnBnClickedWizOpen)
END_MESSAGE_MAP()

void CWizardDialog::OnBnClickedWizNew()
{
	m_nWizardMode	= WIZ_NEW;

	CDialog::OnOK();
}

void CWizardDialog::OnBnClickedWizOpen()
{
	m_nWizardMode	= WIZ_OPEN;

	CDialog::OnOK();
}
