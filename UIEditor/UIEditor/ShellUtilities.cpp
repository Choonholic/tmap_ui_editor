// ShellUtilities.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "MainFrm.h"
#include "ShellUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL ShellCreate(LPCTSTR lpszItem)
{
	DECLARE_FRAME()

	if (!CreateDirectory(lpszItem, NULL))
	{
		DWORD	dwError	= GetLastError();

		if (dwError != ERROR_ALREADY_EXISTS)
		{
			OUTPUT_STR2(_T("[0x%08X] Failed to create directory %s"), dwError, lpszItem);

			return FALSE;
		}
	}

	OUTPUT_STR1(_T("Directory %s has been created"), lpszItem);

	return TRUE;
}

BOOL ShellCopy(LPCTSTR lpszSource, LPCTSTR lpszTarget)
{
	DECLARE_FRAME()

	SHFILEOPSTRUCT	shfos	= { 0 };
	TCHAR			szSource[MAX_PATH];
	TCHAR			szTarget[MAX_PATH];
	int				nRetCode;

	_tcscpy_s(szSource, MAX_PATH, lpszSource);
	_tcscpy_s(szTarget, MAX_PATH, lpszTarget);

	szSource[_tcslen(lpszSource) + 1]	= NULL;
	szTarget[_tcslen(lpszTarget) + 1]	= NULL;

	shfos.hwnd					= NULL;
	shfos.wFunc					= FO_COPY;
	shfos.pFrom					= szSource;
	shfos.pTo					= szTarget;
	shfos.fFlags				= FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
	shfos.fAnyOperationsAborted	= FALSE;
	shfos.hNameMappings			= NULL;
	shfos.lpszProgressTitle		= NULL;

	nRetCode	= SHFileOperation(&shfos);

	OUTPUT_STR3(_T("[0x%08X] %s to %s"), nRetCode, lpszSource, lpszTarget);

	return (BOOL)(nRetCode == 0);
}

BOOL ShellMove(LPCTSTR lpszSource, LPCTSTR lpszTarget)
{
	DECLARE_FRAME()

	SHFILEOPSTRUCT	shfos	= { 0 };
	TCHAR			szSource[MAX_PATH];
	TCHAR			szTarget[MAX_PATH];
	int				nRetCode;

	_tcscpy_s(szSource, MAX_PATH, lpszSource);
	_tcscpy_s(szTarget, MAX_PATH, lpszTarget);

	szSource[_tcslen(lpszSource) + 1]	= NULL;
	szTarget[_tcslen(lpszTarget) + 1]	= NULL;

	shfos.hwnd					= NULL;
	shfos.wFunc					= FO_MOVE;
	shfos.pFrom					= szSource;
	shfos.pTo					= szTarget;
	shfos.fFlags				= FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
	shfos.fAnyOperationsAborted	= FALSE;
	shfos.hNameMappings			= NULL;
	shfos.lpszProgressTitle		= NULL;

	nRetCode	= SHFileOperation(&shfos);

	OUTPUT_STR3(_T("[0x%08X] %s to %s"), nRetCode, lpszSource, lpszTarget);

	return (BOOL)(nRetCode == 0);
}

BOOL ShellDelete(LPCTSTR lpszItem)
{
	DECLARE_FRAME()

	SHFILEOPSTRUCT	shfos	= { 0 };
	TCHAR			szItem[MAX_PATH];
	int				nRetCode;

	_tcscpy_s(szItem, MAX_PATH, lpszItem);

	szItem[_tcslen(lpszItem) + 1]	= NULL;

	shfos.hwnd					= NULL;
	shfos.wFunc					= FO_DELETE;
	shfos.pFrom					= szItem;
	shfos.pTo					= NULL;
	shfos.fFlags				= FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
	shfos.fAnyOperationsAborted	= FALSE;
	shfos.hNameMappings			= NULL;
	shfos.lpszProgressTitle		= NULL;

	nRetCode	= SHFileOperation(&shfos);

	OUTPUT_STR2(_T("[0x%08X] %s"), nRetCode, lpszItem);

	return (BOOL)(nRetCode == 0);
}

LPCTSTR TakeName(LPCTSTR lpszFullPath, LPTSTR lpszName, int nSize)
{
	LPCTSTR	lpszFound	= _tcsrchr(lpszFullPath, _T('\\'));
	int		nPos		= -1;

	if (lpszFound != NULL)
	{
		nPos	= static_cast<int>(lpszFound - lpszFullPath);
	}

	if (nPos >= 0)
	{
		_tcscpy_s(lpszName, nSize, lpszFound + 1);

		if (!_tcslen(lpszName))
		{
			_tcscpy_s(lpszName, nSize, _T("\\"));
		}
	}

	return static_cast<LPCTSTR>(lpszName);
}

LPCTSTR TakePath(LPCTSTR lpszFullPath, LPTSTR lpszPath, int nSize, BOOL bAddSeparator)
{
	LPCTSTR	lpszFound	= _tcsrchr(lpszFullPath, _T('\\'));
	int		nPos		= -1;

	if (lpszFound != NULL)
	{
		nPos	= static_cast<int>(lpszFound - lpszFullPath);
	}

	if (nPos > 0)
	{
		_tcsncpy_s(lpszPath, nSize, lpszFullPath, nPos);

		lpszPath[nPos]	= NULL;

		if (bAddSeparator)
		{
			_tcscat_s(lpszPath, nSize, _T("\\"));
		}
	}
	else if (nPos == 0)
	{
		_tcscpy_s(lpszPath, nSize, _T("\\"));
	}

	return static_cast<LPCTSTR>(lpszPath);
}

LPCTSTR TakeFileName(LPCTSTR lpszFullPath, LPTSTR lpszFileName, int nSize)
{
	LPCTSTR	lpszFound	= _tcsrchr(lpszFullPath, _T('\\'));
	int		nPos		= -1;

	if (lpszFound != NULL)
	{
		nPos	= static_cast<int>(lpszFound - lpszFullPath);
	}

	if (nPos >= 0)
	{
		_tcscpy_s(lpszFileName, nSize, lpszFound + 1);
	}

	return static_cast<LPCTSTR>(lpszFileName);
}

LPCTSTR TakeTitle(LPCTSTR lpszFullPath, LPTSTR lpszTitle, int nSize)
{
	TCHAR	szFileName[MAX_PATH + 1];

	if (TakeFileName(lpszFullPath, szFileName, MAX_PATH + 1))
	{
		LPTSTR	lpszFound	= _tcsrchr(szFileName, _T('.'));
		int		nPos		= -1;

		if (lpszFound != NULL)
		{
			nPos	= static_cast<int>(lpszFound - szFileName);
		}

		if (nPos > 0)
		{
			_tcsncpy_s(lpszTitle, nSize, szFileName, nPos);

			lpszTitle[nPos]	= NULL;
		}
	}

	return static_cast<LPCTSTR>(lpszTitle);
}

LPCTSTR TakeExtension(LPCTSTR lpszFullPath, LPTSTR lpszExt, int nSize)
{
	TCHAR	szFileName[MAX_PATH + 1];

	if (TakeFileName(lpszFullPath, szFileName, MAX_PATH + 1))
	{
		LPTSTR	lpszFound	= _tcsrchr(szFileName, _T('.'));
		int		nPos		= -1;

		if (lpszFound != NULL)
		{
			nPos	= static_cast<int>(lpszFound - szFileName);
		}

		if (nPos > 0)
		{
			_tcscpy_s(lpszExt, nSize, lpszFound + 1);
		}
	}

	return static_cast<LPCTSTR>(lpszExt);
}

BOOL ReadFileString(HANDLE hFile, LPSTR lpszBuffer, int nMax)
{
	BYTE	ch[2];
	DWORD	dwRead;
	int		nRead	= 0;
	BOOL	bExist	= FALSE;

	if (lpszBuffer != NULL)
	{
		while (nRead < nMax)
		{
			if (!ReadFile(hFile, ch, 1, &dwRead, NULL))
			{
				break;
			}

			if (dwRead == 0)
			{
				// EOF
				break;
			}

			bExist	= TRUE;

			if ((ch[0] == '\n') || (ch[0] == '\r'))
			{
				if (ch[0] == '\r')
				{
					ReadFile(hFile, ch, 1, &dwRead, NULL);	// Always break even if an error occurs
				}

				break;
			}

			lpszBuffer[nRead++]	= ch[0];
		}

		lpszBuffer[nRead]	= '\0';
	}

	return bExist;
}

BOOL MakeCapitalized(LPTSTR lpszNew, int nLen, LPCTSTR lpszOld)
{
	TCHAR	cBuffer;
	BOOL	bCapitalize	= FALSE;
	int		nOldLen		= static_cast<int>(_tcslen(lpszOld));
	int		nPos		= 0;
	int		lp;

	if (nLen < (nOldLen + 1))
	{
		return FALSE;
	}

	memset(lpszNew, 0, sizeof(TCHAR) * nLen);

	for (lp = 0; lp < nOldLen; lp++)
	{
		if (lp == 0)
		{
			cBuffer				= lpszOld[lp];
			lpszNew[nPos + 0]	= (_istlower(cBuffer) ? _toupper(cBuffer) : cBuffer);
			lpszNew[nPos + 1]	= NULL;
			nPos++;

			continue;
		}

		if (lpszOld[lp] == _T('_'))
		{
			bCapitalize		= TRUE;

			continue;
		}

		if (bCapitalize == TRUE)
		{
			bCapitalize			= FALSE;
			cBuffer				= lpszOld[lp];
			lpszNew[nPos + 0]	= (_istlower(cBuffer) ? _toupper(cBuffer) : cBuffer);
			lpszNew[nPos + 1]	= NULL;
			nPos++;

			continue;
		}

		cBuffer				= lpszOld[lp];
		lpszNew[nPos + 0]	= (_istupper(cBuffer) ? _tolower(cBuffer) : cBuffer);
		lpszNew[nPos + 1]	= NULL;
		nPos++;
	}

	return TRUE;
}
