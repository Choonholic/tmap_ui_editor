// MultiDialog.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "MultiDialog.h"

IMPLEMENT_DYNAMIC(CMultiDialog, CDialog)

CMultiDialog::CMultiDialog(CWnd* pParent /*=NULL*/) : CDialog(CMultiDialog::IDD, pParent)
{
}

CMultiDialog::~CMultiDialog()
{
}

void CMultiDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MULTI_DESCRIPTION, m_ctlDescription);
	DDX_Control(pDX, IDC_MULTI_LIST, m_ctlList);
	DDX_Control(pDX, IDOK, m_ctlOK);
}

BEGIN_MESSAGE_MAP(CMultiDialog, CDialog)
END_MESSAGE_MAP()

BOOL CMultiDialog::OnInitDialog()
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
		m_ctlList.SetCurSel(0);
	}

	return TRUE;
}

void CMultiDialog::OnOK()
{
	if (m_ctlList.GetSelCount() > 0)
	{
		m_arrSelItems.SetSize(m_ctlList.GetSelCount());
		m_ctlList.GetSelItems(m_ctlList.GetSelCount(), (LPINT)m_arrSelItems.GetData());

		CDialog::OnOK();
	}
}