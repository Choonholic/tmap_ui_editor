// ResolutionDialog.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "ResolutionDialog.h"

IMPLEMENT_DYNAMIC(CResolutionDialog, CDialog)

CResolutionDialog::CResolutionDialog(CWnd* pParent /*=NULL*/) : CDialog(CResolutionDialog::IDD, pParent), m_nWidth(DEF_WIDTH), m_nHeight(DEF_HEIGHT)
{
}

CResolutionDialog::~CResolutionDialog()
{
}

void CResolutionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RES_WIDTH, m_nWidth);
	DDX_Text(pDX, IDC_RES_HEIGHT, m_nHeight);
}

BEGIN_MESSAGE_MAP(CResolutionDialog, CDialog)
END_MESSAGE_MAP()

void CResolutionDialog::OnOK()
{
	CString	strMessage;

	UpdateData(TRUE);

	if ((m_nWidth < MIN_WIDTH) || (m_nWidth > MAX_WIDTH) || (m_nHeight < MIN_HEIGHT) || (m_nHeight > MAX_HEIGHT))
	{
		strMessage.Format(_T("�ػ󵵰� ������ ������ϴ�. (%dx%d)-(%dx%d)"), MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH, MAX_HEIGHT);
		MessageBox(strMessage, _T("����"), MB_OK | MB_ICONERROR);
	}
	else
	{
		CDialog::OnOK();
	}
}