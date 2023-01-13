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
					if (!strText.Compare(_T("이미지")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_IMAGE;
					}

					if (!strText.Compare(_T("버튼")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_BUTTON;
					}

					if (!strText.Compare(_T("리스트 박스")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_LISTBOX;
					}

					if (!strText.Compare(_T("에디트 박스")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_EDITBOX;
					}

					if (!strText.Compare(_T("콤보 박스")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).nType	= UI_CTRL_COMBOBOX;
					}

					if (!strText.Compare(_T("영역")))
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
					if (!strText.Compare(_T("절대 좌표 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("좌측 거리 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft	= UI_PIN_LEFT;
					}

					if (!strText.Compare(_T("우측 거리 고정")))
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
					if (!strText.Compare(_T("절대 좌표 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinTop	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("상측 거리 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinTop	= UI_PIN_TOP;
					}

					if (!strText.Compare(_T("하측 거리 고정")))
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
					if (!strText.Compare(_T("절대 좌표 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinRight	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("좌측 거리 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinRight	= UI_PIN_LEFT;
					}

					if (!strText.Compare(_T("우측 거리 고정")))
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
					if (!strText.Compare(_T("절대 좌표 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom	= UI_PIN_ALL;
					}

					if (!strText.Compare(_T("상측 거리 고정")))
					{
						pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom	= UI_PIN_TOP;
					}

					if (!strText.Compare(_T("하측 거리 고정")))
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
					if (!strText.Compare(_T("없음")))
					{
						pDoc->m_arrUIImageS.GetAt(lp).nAlphaType	= UI_ABG_NONE;
					}

					if (!strText.Compare(_T("상하 방향")))
					{
						pDoc->m_arrUIImageS.GetAt(lp).nAlphaType	= UI_ABG_UPDOWN;
					}

					if (!strText.Compare(_T("좌우 방향")))
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
			CBCGPProp*	pGroup	= new CBCGPProp(_T("기본 설정"));

			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);

			if (dwGroup != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUIGroup.GetAt(dwGroup).dwGroupID);

				CBCGPProp*	pID		= new CBCGPProp(_T("내부 ID"), (_variant_t)strID, _T("아이템의 내부 ID입니다."), PROP_GROUP_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("그룹 ID"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).szName, _T("그룹의 ID를 지정합니다."), PROP_GROUP_NAME));
				pGroup->AddSubItem(new CBCGPProp(_T("그룹 설명"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).szNote, _T("그룹의 설명을 지정합니다."), PROP_GROUP_NOTE));

				CBCGPProp*	pWidth	= new CBCGPProp(_T("가로 크기"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth, _T("그룹의 가로 크기를 지정합니다."), PROP_GROUP_WIDTH);
				CBCGPProp*	pHeight	= new CBCGPProp(_T("세로 크기"), (_variant_t)pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight, _T("그룹의 세로 크기를 지정합니다."), PROP_GROUP_HEIGHT);

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
			CBCGPProp*	pGroup	= new CBCGPProp(_T("기본 설정"));

			dwPage	= pDoc->GetPageByID(pDoc->m_dwCPageID);

			if (dwPage != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUIPageC.GetAt(dwPage).dwPageID);

				CBCGPProp*	pID		= new CBCGPProp(_T("내부 ID"), (_variant_t)strID, _T("아이템의 내부 ID입니다."), PROP_PAGE_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("페이지 ID"), (_variant_t)pDoc->m_arrUIPageC.GetAt(dwPage).szName, _T("페이지의 ID를 지정합니다."), PROP_PAGE_NAME));
				pGroup->AddSubItem(new CBCGPProp(_T("페이지 설명"), (_variant_t)pDoc->m_arrUIPageC.GetAt(dwPage).szNote, _T("페이지의 설명을 지정합니다."), PROP_PAGE_NOTE));

				for (lp = 0; lp < pDoc->m_arrUIPageS.GetCount(); lp++)
				{
					if ((pDoc->m_arrUIPageS.GetAt(lp).dwPageID == pDoc->m_dwCPageID) && (pDoc->m_arrUIPageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
					{
						pGroup->AddSubItem(new CBCGPProp(_T("페이지 사용"), (_variant_t)(bool)(pDoc->m_arrUIPageS.GetAt(lp).bEnable == TRUE)));
						break;
					}
				}

				m_wndPropList.AddProperty(pGroup);
			}
		}
		break;
	case UI_ITEM_CTRL:
		{
			CBCGPProp*	pGroup	= new CBCGPProp(_T("기본 설정"));

			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			if (dwCtrl != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUICtrlC.GetAt(dwCtrl).dwCtrlID);

				CBCGPProp*	pID		= new CBCGPProp(_T("내부 ID"), (_variant_t)strID, _T("아이템의 내부 ID입니다."), PROP_CTRL_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("컨트롤 ID"), (_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szName, _T("컨트롤의 ID를 지정합니다."), PROP_CTRL_NAME));
				pGroup->AddSubItem(new CBCGPProp(_T("컨트롤 설명"), (_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szNote, _T("컨트롤의 설명을 지정합니다."), PROP_CTRL_NOTE));
				pGroup->AddSubItem(new CBCGPProp(_T("추가 텍스트"), (_variant_t)pDoc->m_arrUICtrlC.GetAt(dwCtrl).szText, _T("컨트롤에 이미지가 지정되지 않았을 경우에 보여줄 텍스트를 지정합니다."), PROP_CTRL_TEXT));

				for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
				{
					if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
					{
						pGroup->AddSubItem(new CBCGPProp(_T("컨트롤 사용"), (_variant_t)(bool)(pDoc->m_arrUICtrlS.GetAt(lp).bEnable == TRUE), _T("현재 컨트롤을 사용할지의 여부를 지정합니다."), PROP_CTRL_ENABLE));

						CBCGPProp*	pType;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).nType)
						{
						case UI_CTRL_IMAGE:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("이미지"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_BUTTON:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("버튼"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_LISTBOX:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("리스트 박스"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_EDITBOX:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("에디트 박스"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_COMBOBOX:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("콤보 박스"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						case UI_CTRL_REGION:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("영역"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						default:
							{
								pType	= new CBCGPProp(_T("컨트롤 종류"), (_variant_t)_T("알 수 없음"), _T("컨트롤의 종류를 지정합니다."), PROP_CTRL_TYPE);
							}
							break;
						}

						pType->AddOption(_T("이미지"));
						pType->AddOption(_T("버튼"));
						pType->AddOption(_T("리스트 박스"));
						pType->AddOption(_T("에디트 박스"));
						pType->AddOption(_T("콤보 박스"));
						pType->AddOption(_T("영역"));
						pType->AddOption(_T("알 수 없음"));
						pType->AllowEdit(FALSE);
						pGroup->AddSubItem(pType);

						pGroup->AddSubItem(new CBCGPProp(_T("공용 컨트롤"), (_variant_t)(bool)(pDoc->m_arrUICtrlS.GetAt(lp).bCommon == TRUE), _T("공용 컨트롤로 사용할지의 여부를 지정합니다."), PROP_CTRL_COMMON));
						pGroup->AddSubItem(new CBCGPProp(_T("배경 컨트롤"), (_variant_t)(bool)(pDoc->m_arrUICtrlS.GetAt(lp).bBackground == TRUE), _T("배경 컨트롤로 사용할지의 여부를 지정합니다."), PROP_CTRL_BG));

						m_wndPropList.AddProperty(pGroup);

						CBCGPProp*	pSize	= new CBCGPProp(_T("컨트롤 위치/크기"));

						pSize->AddSubItem(new CBCGPProp(_T("가로 위치"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left, _T("컨트롤의 위치를 지정합니다."), PROP_CTRL_LEFT));
						pSize->AddSubItem(new CBCGPProp(_T("세로 위치"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top, _T("컨트롤의 위치를 지정합니다."), PROP_CTRL_TOP));
						pSize->AddSubItem(new CBCGPProp(_T("가로 길이"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uWidth, _T("컨트롤의 크기를 지정합니다."), PROP_CTRL_WIDTH));
						pSize->AddSubItem(new CBCGPProp(_T("세로 길이"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uHeight, _T("컨트롤의 크기를 지정합니다."), PROP_CTRL_HEIGHT));

						m_wndPropList.AddProperty(pSize);

						CBCGPProp*	pPin		= new CBCGPProp(_T("컨트롤 위치 고정"));

						CBCGPProp*	pPinLeft;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinLeft)
						{
						case UI_PIN_LEFT:
							{
								pPinLeft	= new CBCGPProp(_T("좌측"), (_variant_t)_T("좌측 거리 고정"), _T("컨트롤의 좌측 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINLEFT);
							}
							break;
						case UI_PIN_RIGHT:
							{
								pPinLeft	= new CBCGPProp(_T("좌측"), (_variant_t)_T("우측 거리 고정"), _T("컨트롤의 좌측 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINLEFT);
							}
							break;
						default:
							{
								pPinLeft	= new CBCGPProp(_T("좌측"), (_variant_t)_T("절대 좌표 고정"), _T("컨트롤의 좌측 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINLEFT);
							}
							break;
						}

						pPinLeft->AddOption(_T("절대 좌표 고정"));
						pPinLeft->AddOption(_T("좌측 거리 고정"));
						pPinLeft->AddOption(_T("우측 거리 고정"));
						pPin->AddSubItem(pPinLeft);

						CBCGPProp*	pPinTop;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinTop)
						{
						case UI_PIN_TOP:
							{
								pPinTop	= new CBCGPProp(_T("상단"), (_variant_t)_T("상측 거리 고정"), _T("컨트롤의 상단 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINTOP);
							}
							break;
						case UI_PIN_BOTTOM:
							{
								pPinTop	= new CBCGPProp(_T("상단"), (_variant_t)_T("하측 거리 고정"), _T("컨트롤의 상단 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINTOP);
							}
							break;
						default:
							{
								pPinTop	= new CBCGPProp(_T("상단"), (_variant_t)_T("절대 좌표 고정"), _T("컨트롤의 상단 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINTOP);
							}
							break;
						}

						pPinTop->AddOption(_T("절대 좌표 고정"));
						pPinTop->AddOption(_T("상측 거리 고정"));
						pPinTop->AddOption(_T("하측 거리 고정"));
						pPin->AddSubItem(pPinTop);

						CBCGPProp*	pPinRight;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinRight)
						{
						case UI_PIN_LEFT:
							{
								pPinRight	= new CBCGPProp(_T("우측"), (_variant_t)_T("좌측 거리 고정"), _T("컨트롤의 우측 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINRIGHT);
							}
							break;
						case UI_PIN_RIGHT:
							{
								pPinRight	= new CBCGPProp(_T("우측"), (_variant_t)_T("우측 거리 고정"), _T("컨트롤의 우측 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINRIGHT);
							}
							break;
						default:
							{
								pPinRight	= new CBCGPProp(_T("우측"), (_variant_t)_T("절대 좌표 고정"), _T("컨트롤의 우측 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINRIGHT);
							}
							break;
						}

						pPinRight->AddOption(_T("절대 좌표 고정"));
						pPinRight->AddOption(_T("좌측 거리 고정"));
						pPinRight->AddOption(_T("우측 거리 고정"));
						pPin->AddSubItem(pPinRight);

						CBCGPProp*	pPinBottom;

						switch (pDoc->m_arrUICtrlS.GetAt(lp).uPinBottom)
						{
						case UI_PIN_TOP:
							{
								pPinBottom	= new CBCGPProp(_T("하단"), (_variant_t)_T("상측 거리 고정"), _T("컨트롤의 하단 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINBOTTOM);
							}
							break;
						case UI_PIN_BOTTOM:
							{
								pPinBottom	= new CBCGPProp(_T("하단"), (_variant_t)_T("하측 거리 고정"), _T("컨트롤의 하단 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINBOTTOM);
							}
							break;
						default:
							{
								pPinBottom	= new CBCGPProp(_T("하단"), (_variant_t)_T("절대 좌표 고정"), _T("컨트롤의 하단 모서리 고정 방법을 지정합니다."), PROP_CTRL_PINBOTTOM);
							}
							break;
						}

						pPinBottom->AddOption(_T("절대 좌표 고정"));
						pPinBottom->AddOption(_T("상측 거리 고정"));
						pPinBottom->AddOption(_T("하측 거리 고정"));
						pPin->AddSubItem(pPinBottom);

						m_wndPropList.AddProperty(pPin);

						CBCGPProp*	pRemote	= new CBCGPProp(_T("리모컨 키"));

						pRemote->AddSubItem(new CBCGPProp(_T("좌측 ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDLeft, _T("왼쪽 리모컨 키의 ID를 지정합니다."), PROP_CTRL_IDLEFT));
						pRemote->AddSubItem(new CBCGPProp(_T("상측 ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDUp, _T("위쪽 리모컨 키의 ID를 지정합니다."), PROP_CTRL_IDUP));
						pRemote->AddSubItem(new CBCGPProp(_T("우측 ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDRight, _T("오른쪽 리모컨 키의 ID를 지정합니다."), PROP_CTRL_IDRIGHT));
						pRemote->AddSubItem(new CBCGPProp(_T("하측 ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDDown, _T("아래쪽 리모컨 키의 ID를 지정합니다."), PROP_CTRL_IDDOWN));
						pRemote->AddSubItem(new CBCGPProp(_T("실행 ID"), (_variant_t)pDoc->m_arrUICtrlS.GetAt(lp).uIDEnter, _T("실행 리모컨 키의 ID를 지정합니다."), PROP_CTRL_IDENTER));

						m_wndPropList.AddProperty(pRemote);
						break;
					}
				}
			}
		}
		break;
	case UI_ITEM_IMAGE:
		{
			CBCGPProp*	pGroup	= new CBCGPProp(_T("기본 설정"));

			dwImage	= pDoc->GetImageByID(pDoc->m_dwCImageID);

			if (dwImage != UI_INVALIDID)
			{
				strID.Format(_T("%08X"), pDoc->m_arrUIImageC.GetAt(dwImage).dwImageID);

				CBCGPProp*	pID		= new CBCGPProp(_T("내부 ID"), (_variant_t)strID, _T("아이템의 내부 ID입니다."), PROP_IMAGE_ID);

				pID->AllowEdit(FALSE);
				pGroup->AddSubItem(pID);

				pGroup->AddSubItem(new CBCGPProp(_T("이미지 ID"), (_variant_t)pDoc->m_arrUIImageC.GetAt(dwImage).szName, _T("이미지의 ID를 지정합니다. 이미지의 ID는 파일 이름과 동일합니다."), PROP_IMAGE_NAME));

				for (lp = 0; lp < pDoc->m_arrUIImageS.GetCount(); lp++)
				{
					if ((pDoc->m_arrUIImageS.GetAt(lp).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
					{
						CBCGPProp*	pType;

						switch (pDoc->m_arrUIImageS.GetAt(lp).nType)
						{
						case UI_IMAGE_BMP32:
							{
								pType	= new CBCGPProp(_T("종류"), (_variant_t)_T("32비트 BMP"), _T("이미지의 종류입니다. (읽기 전용)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_BMP24:
							{
								pType	= new CBCGPProp(_T("종류"), (_variant_t)_T("24비트 BMP"), _T("이미지의 종류입니다. (읽기 전용)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_BMP16:
							{
								pType	= new CBCGPProp(_T("종류"), (_variant_t)_T("16비트 BMP"), _T("이미지의 종류입니다. (읽기 전용)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_PNG32:
							{
								pType	= new CBCGPProp(_T("종류"), (_variant_t)_T("32비트 PNG"), _T("이미지의 종류입니다. (읽기 전용)"), PROP_IMAGE_TYPE);
							}
							break;
						case UI_IMAGE_PNG24:
							{
								pType	= new CBCGPProp(_T("종류"), (_variant_t)_T("24비트 PNG"), _T("이미지의 종류입니다. (읽기 전용)"), PROP_IMAGE_TYPE);
							}
							break;
						default:
							{
								pType	= new CBCGPProp(_T("종류"), (_variant_t)_T("알 수 없음"), _T("이미지의 종류입니다. (읽기 전용)"), PROP_IMAGE_TYPE);
							}
							break;
						}

						CBCGPProp*	pWidth		= new CBCGPProp(_T("폭"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uWidth, _T("이미지의 폭입니다. (읽기 전용)"), PROP_IMAGE_WIDTH);
						CBCGPProp*	pHeight		= new CBCGPProp(_T("높이"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uHeight, _T("이미지의 높이입니다. (읽기 전용)"), PROP_IMAGE_HEIGHT);
						CBCGPProp*	pSize		= new CBCGPProp(_T("파일 크기"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).dwSize, _T("이미지의 파일 크기입니다. (읽기 전용)"), PROP_IMAGE_SIZE);
						CBCGPProp*	pMaskSize	= new CBCGPProp(_T("마스크 크기"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).dwMaskSize, _T("이미지의 마스크 크기입니다. (읽기 전용)"), PROP_IMAGE_MASKSIZE);

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

						CBCGPProp*	pAG		= new CBCGPProp(_T("알파블랜딩 그라디언트"));
						CBCGPProp*	pAGType;

						switch (pDoc->m_arrUIImageS.GetAt(lp).nAlphaType)
						{
						case UI_ABG_NONE:
							{
								pAGType	= new CBCGPProp(_T("종류"), (_variant_t)_T("없음"), _T("이미지에 적용할 알파블랜딩 그라디언트의 종류를 지정합니다."), PROP_IMAGE_ALPHA);
							}
							break;
						case UI_ABG_UPDOWN:
							{
								pAGType	= new CBCGPProp(_T("종류"), (_variant_t)_T("상하 방향"), _T("이미지에 적용할 알파블랜딩 그라디언트의 종류를 지정합니다."), PROP_IMAGE_ALPHA);
							}
							break;
						case UI_ABG_LEFTRIGHT:
							{
								pAGType	= new CBCGPProp(_T("종류"), (_variant_t)_T("좌우 방향"), _T("이미지에 적용할 알파블랜딩 그라디언트의 종류를 지정합니다."), PROP_IMAGE_ALPHA);
							}
							break;
						}

						pAGType->AddOption(_T("없음"));
						pAGType->AddOption(_T("상하 방향"));
						pAGType->AddOption(_T("좌우 방향"));
						pAGType->AllowEdit(FALSE);

						pAG->AddSubItem(pAGType);
						pAG->AddSubItem(new CBCGPProp(_T("시작 투명도"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uFirstOpacity, _T("알파블랜딩 그라디언트에 적용할 시작 투명도를 지정합니다."), PROP_IMAGE_FOPACITY));
						pAG->AddSubItem(new CBCGPProp(_T("종료 투명도"), (_variant_t)pDoc->m_arrUIImageS.GetAt(lp).uLastOpacity, _T("알파블랜딩 그라디언트에 적용할 종료 투명도를 지정합니다."), PROP_IMAGE_LOPACITY));

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
