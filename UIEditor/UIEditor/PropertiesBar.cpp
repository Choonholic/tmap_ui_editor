// PropertiesBar.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "UIEditorDoc.h"
#include "PropertiesBar.h"
#include "ShellUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const	int	nBorderSize	= 1;

BEGIN_MESSAGE_MAP(CPropertiesBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

CPropertiesBar::CPropertiesBar()
{
}

CPropertiesBar::~CPropertiesBar()
{
}

int CPropertiesBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CRect	rectDummy;

	rectDummy.SetRectEmpty();

	const	DWORD	dwViewStyle	= WS_CHILD | WS_VISIBLE;
	
	if (!m_wndPropList.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properties View\n");
		return -1;
	}

	ResetPropList();

	return 0;
}

void CPropertiesBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_wndPropList.SetWindowPos(NULL, nBorderSize, nBorderSize, cx - 2 * nBorderSize, cy - 2 * nBorderSize, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPropertiesBar::OnPaint() 
{
	CPaintDC	dc(this);
	CRect		rectList;

	m_wndPropList.GetWindowRect(rectList);
	ScreenToClient(rectList);
	rectList.InflateRect(nBorderSize, nBorderSize);
	dc.Draw3dRect(rectList, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

LRESULT CPropertiesBar::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CBCGPProp*		pProp	= (CBCGPProp*)lParam;
	CUIEditorDoc*	pDoc	= CUIEditorDoc::GetUIDocument();
	CString			strText;
	CString			strNewText;
	int				nValue;
	int				lp;
	CDWordArray		arrItems;
	SYSTEMTIME		st;
	DWORD			dwGroup;
	DWORD			dwPage;
	DWORD			dwCtrl;
	DWORD			dwImage;

	GetLocalTime(&st);

	switch (pProp->GetData())
	{
	case PROP_GROUP_ID:
		{
			// Read Only
		}
		break;
	case PROP_GROUP_NAME:
		{
			dwGroup		= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
			strText		= (LPCTSTR)(_bstr_t)pProp->GetValue();
			strNewText	= strText;

			if (strText.GetLength())
			{
				for (lp = 0; lp < pDoc->m_arrUIGroup.GetCount(); lp++)
				{
					if ((!strText.Compare(pDoc->m_arrUIGroup.GetAt(lp).szName)) && (pDoc->m_arrUIGroup.GetAt(lp).dwGroupID != pDoc->m_dwCGroupID))
					{
						strNewText.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), strText, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
						pProp->SetValue((_variant_t)strNewText);
						break;
					}
				}
						
				pDoc->RenameGroup(strNewText);
			}
			else
			{
				pProp->SetValue((_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).szName);
			}
		}
		break;
	case PROP_GROUP_NOTE:
		{
			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			_tcscpy_s(pDoc->m_arrUIGroup.GetAt(dwGroup).szNote, UI_MAX_NOTELEN, strText);
		}
		break;
	case PROP_GROUP_WIDTH:
		{
			// Read Only
		}
		break;
	case PROP_GROUP_HEIGHT:
		{
			// Read Only
		}
		break;
	case PROP_PAGE_ID:
		{
			// Read Only
		}
		break;
	case PROP_PAGE_NAME:
		{
			dwPage		= pDoc->GetPageByID(pDoc->m_dwCPageID);
			strText		= (LPCTSTR)(_bstr_t)pProp->GetValue();
			strNewText	= strText;

			if (strText.GetLength())
			{
				for (lp = 0; lp < pDoc->m_arrUIPageC.GetCount(); lp++)
				{
					if ((!strText.Compare(pDoc->m_arrUIPageC.GetAt(lp).szName)) && (pDoc->m_arrUIPageC.GetAt(lp).dwPageID != pDoc->m_dwCPageID))
					{
						strNewText.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), strText, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
						pProp->SetValue((_variant_t)strNewText);
						break;
					}
				}
						
				pDoc->RenamePage(strNewText);
			}
			else
			{
				pProp->SetValue((_variant_t)pDoc->m_arrUIPageC.GetAt(dwPage).szName);
			}
		}
		break;
	case PROP_PAGE_NOTE:
		{
			dwPage	= pDoc->GetPageByID(pDoc->m_dwCPageID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			_tcscpy_s(pDoc->m_arrUIPageC.GetAt(dwPage).szNote, UI_MAX_NOTELEN, strText);
		}
		break;
	case PROP_PAGE_ENABLE:
		{
			dwPage	= pDoc->GetPageByID(pDoc->m_dwCPageID);

			for (lp = 0; lp < pDoc->m_arrUIPageS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUIPageS.GetAt(lp).dwPageID == pDoc->m_dwCPageID) && (pDoc->m_arrUIPageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUIPageS.GetAt(lp).bEnable	= (BOOL)((bool)pProp->GetValue() == true);
					break;
				}
			}
		}
		break;
	case PROP_CTRL_ID:
		{
			// Read Only
		}
		break;
	case PROP_CTRL_NAME:
		{
			dwCtrl		= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText		= (LPCTSTR)(_bstr_t)pProp->GetValue();
			strNewText	= strText;

			if (strText.GetLength())
			{
				for (lp = 0; lp < pDoc->m_arrUICtrlC.GetCount(); lp++)
				{
					if ((!strText.Compare(pDoc->m_arrUICtrlC.GetAt(lp).szName)) && (pDoc->m_arrUICtrlC.GetAt(lp).dwCtrlID != pDoc->m_dwCCtrlID))
					{
						strNewText.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), strText, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
						pProp->SetValue((_variant_t)strNewText);
						break;
					}
				}
						
				pDoc->RenameCtrl(strNewText);
			}
			else
			{
				pProp->SetValue((_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szName);
			}
		}
		break;
	case PROP_CTRL_NOTE:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			_tcscpy_s(pDoc->m_arrUICtrlC.GetAt(dwCtrl).szNote, UI_MAX_NOTELEN, strText);
		}
		break;
	case PROP_CTRL_TEXT:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			_tcscpy_s(pDoc->m_arrUICtrlC.GetAt(dwCtrl).szText, UI_MAX_TEXTLEN, strText);
		}
		break;
	case PROP_CTRL_ENABLE:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).bEnable	= (BOOL)((bool)pProp->GetValue() == true);
					break;
				}
			}
		}
		break;
	case PROP_CTRL_TYPE:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (!strText.Compare(_T("�̹���")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_IMAGE;
					}

					if (!strText.Compare(_T("��ư")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_BUTTON;
					}

					if (!strText.Compare(_T("����Ʈ �ڽ�")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_LISTBOX;
					}

					if (!strText.Compare(_T("����Ʈ �ڽ�")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_EDITBOX;
					}

					if (!strText.Compare(_T("�޺� �ڽ�")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_COMBOBOX;
					}

					if (!strText.Compare(_T("����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_REGION;
					}

					break;
				}
			}
		}
		break;
	case PROP_CTRL_COMMON:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).bCommon	= (BOOL)((bool)pProp->GetValue() == true);
					break;
				}
			}
		}
		break;
	case PROP_CTRL_BG:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).bBackground	= (BOOL)((bool)pProp->GetValue() == true);
					break;
				}
			}
		}
		break;
	case PROP_CTRL_LEFT:
		{
			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			nValue	= (LONG)pProp->GetValue();

			if (nValue < 0)
			{
				nValue	= 0;
			}

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left	= nValue;

					if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + pDoc->m_arrUICtrlS.GetAt(lp).uWidth > pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth)
					{
						pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left	= pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth - pDoc->m_arrUICtrlS.GetAt(lp).uWidth;
					}

					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + pDoc->m_arrUICtrlS.GetAt(lp).uWidth;
					break;
				}
			}
		}
		break;
	case PROP_CTRL_TOP:
		{
			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			nValue	= (LONG)pProp->GetValue();

			if (nValue < 0)
			{
				nValue	= 0;
			}

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top	= nValue;

					if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + pDoc->m_arrUICtrlS.GetAt(lp).uHeight > pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight)
					{
						pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top	= pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight - pDoc->m_arrUICtrlS.GetAt(lp).uHeight;
					}

					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + pDoc->m_arrUICtrlS.GetAt(lp).uHeight;
					break;
				}
			}
		}
		break;
	case PROP_CTRL_WIDTH:
		{
			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			nValue	= (LONG)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + nValue > pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth)
					{
						nValue	= pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth - pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left;
					}

					pDoc->m_arrUICtrlS.GetAt(lp).uWidth			= nValue;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + pDoc->m_arrUICtrlS.GetAt(lp).uWidth;
					break;
				}
			}
		}
		break;
	case PROP_CTRL_HEIGHT:
		{
			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			nValue	= (LONG)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + nValue > pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight)
					{
						nValue	= pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight - pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top;
					}

					pDoc->m_arrUICtrlS.GetAt(lp).uHeight			= nValue;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + pDoc->m_arrUICtrlS.GetAt(lp).uHeight;
					break;
				}
			}
		}
		break;
	case PROP_CTRL_PINLEFT:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (!strText.Compare(_T("���� ��ǥ ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft	= UI_PIN_LEFT;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft	= UI_PIN_RIGHT;
					}

					break;
				}
			}
		}
		break;
	case PROP_CTRL_PINTOP:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (!strText.Compare(_T("���� ��ǥ ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinTop	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinTop	= UI_PIN_TOP;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinTop	= UI_PIN_BOTTOM;
					}

					break;
				}
			}
		}
		break;
	case PROP_CTRL_PINRIGHT:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (!strText.Compare(_T("���� ��ǥ ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinRight	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinRight	= UI_PIN_LEFT;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinRight	= UI_PIN_RIGHT;
					}

					break;
				}
			}
		}
		break;
	case PROP_CTRL_PINBOTTOM:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (!strText.Compare(_T("���� ��ǥ ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom	= UI_PIN_TOP;
					}

					if (!strText.Compare(_T("���� �Ÿ� ����")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom	= UI_PIN_BOTTOM;
					}

					break;
				}
			}
		}
		break;
	case PROP_CTRL_IDLEFT:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).uIDLeft	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	case PROP_CTRL_IDUP:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).uIDUp	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	case PROP_CTRL_IDRIGHT:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).uIDRight	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	case PROP_CTRL_IDDOWN:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).uIDDown	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	case PROP_CTRL_IDENTER:
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUICtrlS.GetAt(lp).uIDEnter	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	case PROP_IMAGE_ID:
		{
			// Read Only
		}
		break;
	case PROP_IMAGE_NAME:
		{
			dwImage		= pDoc->GetImageByID(pDoc->m_dwCImageID);
			strText		= (LPCTSTR)(_bstr_t)pProp->GetValue();
			strNewText	= strText;

			if (strText.GetLength())
			{
				for (lp = 0; lp < pDoc->m_arrUIImageC.GetCount(); lp++)
				{
					if ((!strText.Compare(pDoc->m_arrUIImageC.GetAt(lp).szName)) && (pDoc->m_arrUIImageC.GetAt(lp).dwImageID != pDoc->m_dwCImageID))
					{
						strNewText.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d"), strText, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
						pProp->SetValue((_variant_t)strNewText);
						break;
					}
				}
						
				pDoc->RenameImage(strNewText);
			}
			else
			{
				pProp->SetValue((_variant_t)pDoc->m_arrUIImageC.GetAt(dwImage).szName);
			}
		}
		break;
	case PROP_IMAGE_TYPE:
		{
			// Read Only
		}
		break;
	case PROP_IMAGE_WIDTH:
		{
			// Read Only
		}
		break;
	case PROP_IMAGE_HEIGHT:
		{
			// Read Only
		}
		break;
	case PROP_IMAGE_SIZE:
		{
			// Read Only
		}
		break;
	case PROP_IMAGE_MASKSIZE:
		{
			// Read Only
		}
		break;
	case PROP_IMAGE_ALPHA:
		{
			dwImage	= pDoc->GetImageByID(pDoc->m_dwCImageID);
			strText	= (LPCTSTR)(_bstr_t)pProp->GetValue();

			for (lp = 0; lp < pDoc->m_arrUIImageS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUIImageS.GetAt(lp).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					if (!strText.Compare(_T("����")))
					{
						pDoc->m_arrUIImageS.GetAt(lp).nAlphaType	= UI_ABG_NONE;
					}

					if (!strText.Compare(_T("���� ����")))
					{
						pDoc->m_arrUIImageS.GetAt(lp).nAlphaType	= UI_ABG_UPDOWN;
					}

					if (!strText.Compare(_T("�¿� ����")))
					{
						pDoc->m_arrUIImageS.GetAt(lp).nAlphaType	= UI_ABG_LEFTRIGHT;
					}

					break;
				}
			}
		}
		break;
	case PROP_IMAGE_FOPACITY:
		{
			dwImage	= pDoc->GetImageByID(pDoc->m_dwCImageID);

			for (lp = 0; lp < pDoc->m_arrUIImageS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUIImageS.GetAt(lp).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUIImageS.GetAt(lp).uFirstOpacity	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	case PROP_IMAGE_LOPACITY:
		{
			dwImage	= pDoc->GetImageByID(pDoc->m_dwCImageID);

			for (lp = 0; lp < pDoc->m_arrUIImageS.GetCount(); lp++)
			{
				if ((pDoc->m_arrUIImageS.GetAt(lp).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
				{
					pDoc->m_arrUIImageS.GetAt(lp).uLastOpacity	= (USHORT)pProp->GetValue();
					break;
				}
			}
		}
		break;
	}
	
	pProp->CommitModifiedValue();
	m_wndPropList.RedrawWindow();

	pDoc->UpdateAllViews(NULL);
	pDoc->UpdateWorkspace(WSU_STATE);
	pDoc->SetModifiedFlag();

	m_wndPropList.SetFocus();

	return 1;
}

void CPropertiesBar::InitPropList()
{
	CUIEditorDoc*	pDoc	= CUIEditorDoc::GetUIDocument();
	int				lp;
	DWORD			dwGroup;
	DWORD			dwPage;
	DWORD			dwCtrl;
	DWORD			dwImage;
	CString			strID;

	ResetPropList();

	switch (pDoc->m_nCType)
	{
	case UI_ITEM_GROUP:
		{
			CBCGPProp*	pGroup	= new CBCGPProp(_T("�⺻ ����"));

			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);

			if (dwGroup != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUIGroup.GetAt(dwGroup).dwGroupID);

				CBCGPProp*	pID		= new CBCGPProp(_T("���� ID"), (_variant_t)strID, _T("�������� ���� ID�Դϴ�."), PROP_GROUP_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("�׷� ID"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).szName, _T("�׷��� ID�� �����մϴ�."), PROP_GROUP_NAME));
				pGroup->AddSubItem(new CBCGPProp(_T("�׷� ����"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).szNote, _T("�׷��� ������ �����մϴ�."), PROP_GROUP_NOTE));

				CBCGPProp*	pWidth	= new CBCGPProp(_T("���� ũ��"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth, _T("�׷��� ���� ũ�⸦ �����մϴ�."), PROP_GROUP_WIDTH);
				CBCGPProp*	pHeight	= new CBCGPProp(_T("���� ũ��"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight, _T("�׷��� ���� ũ�⸦ �����մϴ�."), PROP_GROUP_HEIGHT);

				pWidth->AllowEdit(FALSE);
				pHeight->AllowEdit(FALSE);
				pGroup->AddSubItem(pWidth);
				pGroup->AddSubItem(pHeight);

				m_wndPropList.AddProperty(pGroup);
			}
		}
		break;
	case UI_ITEM_PAGE:
		{
			CBCGPProp*	pGroup	= new CBCGPProp(_T("�⺻ ����"));

			dwPage	= pDoc->GetPageByID(pDoc->m_dwCPageID);

			if (dwPage != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUIPageC.GetAt(dwPage).dwPageID);

				CBCGPProp*	pID		= new CBCGPProp(_T("���� ID"), (_variant_t)strID, _T("�������� ���� ID�Դϴ�."), PROP_PAGE_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("������ ID"), (_variant_t)pDoc->m_arrUIPageC.GetAt(dwPage).szName, _T("�������� ID�� �����մϴ�."), PROP_PAGE_NAME));
				pGroup->AddSubItem(new CBCGPProp(_T("������ ����"), (_variant_t)pDoc->m_arrUIPageC.GetAt(dwPage).szNote, _T("�������� ������ �����մϴ�."), PROP_PAGE_NOTE));

				for (lp = 0; lp < pDoc->m_arrUIPageS.GetCount(); lp++)
				{
					if ((pDoc->m_arrUIPageS.GetAt(lp).dwPageID == pDoc->m_dwCPageID) && (pDoc->m_arrUIPageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
					{
						pGroup->AddSubItem(new CBCGPProp(_T("������ ���"), (_variant_t)(bool)(pDoc->m_arrUIPageS.GetAt(lp).bEnable == TRUE)));
						break;
					}
				}

				m_wndPropList.AddProperty(pGroup);
			}
		}
		break;
	case UI_ITEM_CTRL:
		{
			CBCGPProp*	pGroup	= new CBCGPProp(_T("�⺻ ����"));

			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			if (dwCtrl != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUICtrlC.GetAt(dwCtrl).dwCtrlID);

				CBCGPProp*	pID		= new CBCGPProp(_T("���� ID"), (_variant_t)strID, _T("�������� ���� ID�Դϴ�."), PROP_CTRL_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("��Ʈ�� ID"), (_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szName, _T("��Ʈ���� ID�� �����մϴ�."), PROP_CTRL_NAME));
				pGroup->AddSubItem(new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szNote, _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_NOTE));
				pGroup->AddSubItem(new CBCGPProp(_T("�߰� �ؽ�Ʈ"), (_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szText, _T("��Ʈ�ѿ� �̹����� �������� �ʾ��� ��쿡 ������ �ؽ�Ʈ�� �����մϴ�."), PROP_CTRL_TEXT));

				for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
				{
					if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
					{
						pGroup->AddSubItem(new CBCGPProp(_T("��Ʈ�� ���"), (_variant_t)(bool)(pDoc->m_arrUICtrlS.GetAt(lp).bEnable == TRUE), _T("���� ��Ʈ���� ��������� ���θ� �����մϴ�."), PROP_CTRL_ENABLE));

						CBCGPProp*	pType;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).nType)
						{
						case UI_CTRL_IMAGE:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("�̹���"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_BUTTON:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("��ư"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_LISTBOX:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("����Ʈ �ڽ�"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_EDITBOX:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("����Ʈ �ڽ�"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_COMBOBOX:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("�޺� �ڽ�"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_REGION:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("����"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						default:
							{
								pType	= new CBCGPProp(_T("��Ʈ�� ����"), (_variant_t)_T("�� �� ����"), _T("��Ʈ���� ������ �����մϴ�."), PROP_CTRL_TYPE);
							}
							break;
						}

						pType->AddOption(_T("�̹���"));
						pType->AddOption(_T("��ư"));
						pType->AddOption(_T("����Ʈ �ڽ�"));
						pType->AddOption(_T("����Ʈ �ڽ�"));
						pType->AddOption(_T("�޺� �ڽ�"));
						pType->AddOption(_T("����"));
						pType->AddOption(_T("�� �� ����"));
						pType->AllowEdit(FALSE);
						pGroup->AddSubItem(pType);

						pGroup->AddSubItem(new CBCGPProp(_T("���� ��Ʈ��"), (_variant_t)(bool)(pDoc->m_arrUICtrlS.GetAt(lp).bCommon == TRUE), _T("���� ��Ʈ�ѷ� ��������� ���θ� �����մϴ�."), PROP_CTRL_COMMON));
						pGroup->AddSubItem(new CBCGPProp(_T("��� ��Ʈ��"), (_variant_t)(bool)(pDoc->m_arrUICtrlS.GetAt(lp).bBackground == TRUE), _T("��� ��Ʈ�ѷ� ��������� ���θ� �����մϴ�."), PROP_CTRL_BG));

						m_wndPropList.AddProperty(pGroup);

						CBCGPProp*	pSize	= new CBCGPProp(_T("��Ʈ�� ��ġ/ũ��"));

						pSize->AddSubItem(new CBCGPProp(_T("���� ��ġ"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left, _T("��Ʈ���� ��ġ�� �����մϴ�."), PROP_CTRL_LEFT));
						pSize->AddSubItem(new CBCGPProp(_T("���� ��ġ"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top, _T("��Ʈ���� ��ġ�� �����մϴ�."), PROP_CTRL_TOP));
						pSize->AddSubItem(new CBCGPProp(_T("���� ����"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uWidth, _T("��Ʈ���� ũ�⸦ �����մϴ�."), PROP_CTRL_WIDTH));
						pSize->AddSubItem(new CBCGPProp(_T("���� ����"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uHeight, _T("��Ʈ���� ũ�⸦ �����մϴ�."), PROP_CTRL_HEIGHT));

						m_wndPropList.AddProperty(pSize);

						CBCGPProp*	pPin		= new CBCGPProp(_T("��Ʈ�� ��ġ ����"));

						CBCGPProp*	pPinLeft;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft)
						{
						case UI_PIN_LEFT:
							{
								pPinLeft	= new CBCGPProp(_T("����"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� ���� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINLEFT);
							}
							break;
						case UI_PIN_RIGHT:
							{
								pPinLeft	= new CBCGPProp(_T("����"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� ���� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINLEFT);
							}
							break;
						default:
							{
								pPinLeft	= new CBCGPProp(_T("����"), (_variant_t)_T("���� ��ǥ ����"), _T("��Ʈ���� ���� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINLEFT);
							}
							break;
						}

						pPinLeft->AddOption(_T("���� ��ǥ ����"));
						pPinLeft->AddOption(_T("���� �Ÿ� ����"));
						pPinLeft->AddOption(_T("���� �Ÿ� ����"));
						pPin->AddSubItem(pPinLeft);

						CBCGPProp*	pPinTop;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinTop)
						{
						case UI_PIN_TOP:
							{
								pPinTop	= new CBCGPProp(_T("���"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� ��� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINTOP);
							}
							break;
						case UI_PIN_BOTTOM:
							{
								pPinTop	= new CBCGPProp(_T("���"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� ��� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINTOP);
							}
							break;
						default:
							{
								pPinTop	= new CBCGPProp(_T("���"), (_variant_t)_T("���� ��ǥ ����"), _T("��Ʈ���� ��� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINTOP);
							}
							break;
						}

						pPinTop->AddOption(_T("���� ��ǥ ����"));
						pPinTop->AddOption(_T("���� �Ÿ� ����"));
						pPinTop->AddOption(_T("���� �Ÿ� ����"));
						pPin->AddSubItem(pPinTop);

						CBCGPProp*	pPinRight;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinRight)
						{
						case UI_PIN_LEFT:
							{
								pPinRight	= new CBCGPProp(_T("����"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� ���� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINRIGHT);
							}
							break;
						case UI_PIN_RIGHT:
							{
								pPinRight	= new CBCGPProp(_T("����"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� ���� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINRIGHT);
							}
							break;
						default:
							{
								pPinRight	= new CBCGPProp(_T("����"), (_variant_t)_T("���� ��ǥ ����"), _T("��Ʈ���� ���� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINRIGHT);
							}
							break;
						}

						pPinRight->AddOption(_T("���� ��ǥ ����"));
						pPinRight->AddOption(_T("���� �Ÿ� ����"));
						pPinRight->AddOption(_T("���� �Ÿ� ����"));
						pPin->AddSubItem(pPinRight);

						CBCGPProp*	pPinBottom;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom)
						{
						case UI_PIN_TOP:
							{
								pPinBottom	= new CBCGPProp(_T("�ϴ�"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� �ϴ� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINBOTTOM);
							}
							break;
						case UI_PIN_BOTTOM:
							{
								pPinBottom	= new CBCGPProp(_T("�ϴ�"), (_variant_t)_T("���� �Ÿ� ����"), _T("��Ʈ���� �ϴ� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINBOTTOM);
							}
							break;
						default:
							{
								pPinBottom	= new CBCGPProp(_T("�ϴ�"), (_variant_t)_T("���� ��ǥ ����"), _T("��Ʈ���� �ϴ� �𼭸� ���� ����� �����մϴ�."), PROP_CTRL_PINBOTTOM);
							}
							break;
						}

						pPinBottom->AddOption(_T("���� ��ǥ ����"));
						pPinBottom->AddOption(_T("���� �Ÿ� ����"));
						pPinBottom->AddOption(_T("���� �Ÿ� ����"));
						pPin->AddSubItem(pPinBottom);

						m_wndPropList.AddProperty(pPin);

						CBCGPProp*	pRemote	= new CBCGPProp(_T("������ Ű"));

						pRemote->AddSubItem(new CBCGPProp(_T("���� ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDLeft, _T("���� ������ Ű�� ID�� �����մϴ�."), PROP_CTRL_IDLEFT));
						pRemote->AddSubItem(new CBCGPProp(_T("���� ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDUp, _T("���� ������ Ű�� ID�� �����մϴ�."), PROP_CTRL_IDUP));
						pRemote->AddSubItem(new CBCGPProp(_T("���� ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDRight, _T("������ ������ Ű�� ID�� �����մϴ�."), PROP_CTRL_IDRIGHT));
						pRemote->AddSubItem(new CBCGPProp(_T("���� ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDDown, _T("�Ʒ��� ������ Ű�� ID�� �����մϴ�."), PROP_CTRL_IDDOWN));
						pRemote->AddSubItem(new CBCGPProp(_T("���� ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDEnter, _T("���� ������ Ű�� ID�� �����մϴ�."), PROP_CTRL_IDENTER));

						m_wndPropList.AddProperty(pRemote);
						break;
					}
				}
			}
		}
		break;
	case UI_ITEM_IMAGE:
		{
			CBCGPProp*	pGroup	= new CBCGPProp(_T("�⺻ ����"));

			dwImage	= pDoc->GetImageByID(pDoc->m_dwCImageID);

			if (dwImage != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUIImageC.GetAt(dwImage).dwImageID);

				CBCGPProp*	pID		= new CBCGPProp(_T("���� ID"), (_variant_t)strID, _T("�������� ���� ID�Դϴ�."), PROP_IMAGE_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("�̹��� ID"), (_variant_t)pDoc->m_arrUIImageC.GetAt(dwImage).szName, _T("�̹����� ID�� �����մϴ�. �̹����� ID�� ���� �̸��� �����մϴ�."), PROP_IMAGE_NAME));

				for (lp = 0; lp < pDoc->m_arrUIImageS.GetCount(); lp++)
				{
					if ((pDoc->m_arrUIImageS.GetAt(lp).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
					{
						CBCGPProp*	pType;

						switch (pDoc->m_arrUIImageS.GetAt(lp).nType)
						{
						case UI_IMAGE_BMP32:
							{
								pType	= new CBCGPProp(_T("����"), (_variant_t)_T("32��Ʈ BMP"), _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_BMP24:
							{
								pType	= new CBCGPProp(_T("����"), (_variant_t)_T("24��Ʈ BMP"), _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_BMP16:
							{
								pType	= new CBCGPProp(_T("����"), (_variant_t)_T("16��Ʈ BMP"), _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_PNG32:
							{
								pType	= new CBCGPProp(_T("����"), (_variant_t)_T("32��Ʈ PNG"), _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_PNG24:
							{
								pType	= new CBCGPProp(_T("����"), (_variant_t)_T("24��Ʈ PNG"), _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_TYPE);
							}
							break;
						default:
							{
								pType	= new CBCGPProp(_T("����"), (_variant_t)_T("�� �� ����"), _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_TYPE);
							}
							break;
						}

						CBCGPProp*	pWidth		= new CBCGPProp(_T("��"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uWidth, _T("�̹����� ���Դϴ�. (�б� ����)"), PROP_IMAGE_WIDTH);
						CBCGPProp*	pHeight		= new CBCGPProp(_T("����"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uHeight, _T("�̹����� �����Դϴ�. (�б� ����)"), PROP_IMAGE_HEIGHT);
						CBCGPProp*	pSize		= new CBCGPProp(_T("���� ũ��"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).dwSize, _T("�̹����� ���� ũ���Դϴ�. (�б� ����)"), PROP_IMAGE_SIZE);
						CBCGPProp*	pMaskSize	= new CBCGPProp(_T("����ũ ũ��"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).dwMaskSize, _T("�̹����� ����ũ ũ���Դϴ�. (�б� ����)"), PROP_IMAGE_MASKSIZE);

						pType->AllowEdit(FALSE);
						pWidth->AllowEdit(FALSE);
						pHeight->AllowEdit(FALSE);
						pSize->AllowEdit(FALSE);
						pMaskSize->AllowEdit(FALSE);

						pGroup->AddSubItem(pType);
						pGroup->AddSubItem(pWidth);
						pGroup->AddSubItem(pHeight);
						pGroup->AddSubItem(pSize);
						pGroup->AddSubItem(pMaskSize);

						m_wndPropList.AddProperty(pGroup);

						CBCGPProp*	pAG		= new CBCGPProp(_T("���ĺ��� �׶���Ʈ"));
						CBCGPProp*	pAGType;

						switch (pDoc->m_arrUIImageS.GetAt(lp).nAlphaType)
						{
						case UI_ABG_NONE:
							{
								pAGType	= new CBCGPProp(_T("����"), (_variant_t)_T("����"), _T("�̹����� ������ ���ĺ��� �׶���Ʈ�� ������ �����մϴ�."), PROP_IMAGE_ALPHA);
							}
							break;
						case UI_ABG_UPDOWN:
							{
								pAGType	= new CBCGPProp(_T("����"), (_variant_t)_T("���� ����"), _T("�̹����� ������ ���ĺ��� �׶���Ʈ�� ������ �����մϴ�."), PROP_IMAGE_ALPHA);
							}
							break;
						case UI_ABG_LEFTRIGHT:
							{
								pAGType	= new CBCGPProp(_T("����"), (_variant_t)_T("�¿� ����"), _T("�̹����� ������ ���ĺ��� �׶���Ʈ�� ������ �����մϴ�."), PROP_IMAGE_ALPHA);
							}
							break;
						}

						pAGType->AddOption(_T("����"));
						pAGType->AddOption(_T("���� ����"));
						pAGType->AddOption(_T("�¿� ����"));
						pAGType->AllowEdit(FALSE);

						pAG->AddSubItem(pAGType);
						pAG->AddSubItem(new CBCGPProp(_T("���� ����"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uFirstOpacity, _T("���ĺ��� �׶���Ʈ�� ������ ���� ������ �����մϴ�."), PROP_IMAGE_FOPACITY));
						pAG->AddSubItem(new CBCGPProp(_T("���� ����"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uLastOpacity, _T("���ĺ��� �׶���Ʈ�� ������ ���� ������ �����մϴ�."), PROP_IMAGE_LOPACITY));

						m_wndPropList.AddProperty(pAG);
						break;
					}
				}
			}
		}
		break;
	}

	m_wndPropList.RedrawWindow();
}

void CPropertiesBar::ResetPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDesciptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties(FALSE);
	m_wndPropList.RemoveAll();
}

void CPropertiesBar::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

#ifndef _DEBUG
	NONCLIENTMETRICS	info;
#endif

	LOGFONT				lf;

	globalData.fontRegular.GetLogFont(&lf);

#ifndef _DEBUG
	info.cbSize	= sizeof(NONCLIENTMETRICS);

	globalData.GetNonClientMetrics(info);

	lf.lfHeight	= info.lfMenuFont.lfHeight;
	lf.lfWeight	= info.lfMenuFont.lfWeight;
	lf.lfItalic	= info.lfMenuFont.lfItalic;
#endif

	m_fntPropList.CreateFontIndirect(&lf);
	m_wndPropList.SetFont(&m_fntPropList);
}
