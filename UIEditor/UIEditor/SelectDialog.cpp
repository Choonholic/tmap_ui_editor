// SelectDialog.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "SelectDialog.h"

IMPLEMENT_DYNAMIC(CSelectDialog, CDialog)

CSelectDialog::CSelectDialog(CWnd* pParent /*=NULL*/) : CDialog(CSelectDialog::IDD, pParent)
{
	m_nSelect	= 0;
}

CSelectDialog::~CSelectDialog()
{
}

void CSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SELECT_DESCRIPTION, m_ctlDescription);
	DDX_Control(pDX, IDC_SELECT_LIST, m_ctlList);
	DDX_LBIndex(pDX, IDC_SELECT_LIST, m_nSelect);
	DDX_Control(pDX, IDOK, m_ctlOK);
}

BEGIN_MESSAGE_MAP(CSelectDialog, CDialog)
END_MESSAGE_MAP()

BOOL CSelectDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_strTitle);
	m_ctlDescription.SetWindowText(m_strDescription);

	for (int lp = 0; lp < m_arrItems.GetCount(); lp++)
	{
		m_ctlList.AddString(m_arrItems.GetAt(lp));
	}

	if (m_ctlList.GetCount() < 1)
	{
		m_ctlOK.EnableWindow(FALSE);
	}
	else
	{
		m_ctlList.SetCurSel(m_nSelect);
	}

	return TRUE;
}

void CSelectDialog::OnOK()
{
	if (m_ctlList.GetCurSel() != -1)
	{
		CDialog::OnOK();
	}
}
