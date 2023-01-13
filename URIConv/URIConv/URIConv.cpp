// URIConv.cpp

#include "stdafx.h"
#include "OldStruct.h"
#include "NewStruct.h"

#define	BUFSIZE	(256 * 1024)

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE			hSource;
	HANDLE			hTarget;
	DWORD			dwRead;
	DWORD			dwWritten;
	OLD_UI_HEADER	OldUIHeader;
	OLD_UI_GROUP	OldUIGroup;
	OLD_UI_PAGEC	OldUIPageC;
	OLD_UI_PAGES	OldUIPageS;
	OLD_UI_CTRLC	OldUICtrlC;
	OLD_UI_CTRLS	OldUICtrlS;
	OLD_UI_IMAGEC	OldUIImageC;
	OLD_UI_IMAGES	OldUIImageS;
	UI_HEADER		UIHeader;
	UI_GROUP		UIGroup;
	UI_PAGEC		UIPageC;
	UI_PAGES		UIPageS;
	UI_CTRLC		UICtrlC;
	UI_CTRLS		UICtrlS;
	UI_IMAGEC		UIImageC;
	UI_IMAGES		UIImageS;
	int				lp;
	BYTE			cBuffer[BUFSIZE];
	DWORD			dwSize;
	DWORD			dwCurPos;
	DWORD			dwReadSize;

	_tprintf(_T("UI Resource Information Converter, Version 0.3.0925\n"));
	_tprintf(_T("Copyright (c) 2008 SK okcashbag service Corp. All Right Reserved.\n\n"));

	if (argc != 3)
	{
		_tprintf(_T("ERROR: Invalid arguments\n"));
		return -1;
	}

	_tprintf(_T("Converting %s to %s\n\n"), argv[1], argv[2]);

	hSource	= CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSource == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("ERROR: Invalid source file\n"));
		return -1;
	}

	hTarget	= CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hSource, &OldUIHeader, sizeof(OLD_UI_HEADER), &dwRead, NULL);
	memcpy_s(&UIHeader, sizeof(UI_HEADER), &OldUIHeader, sizeof(OLD_UI_HEADER));
	WriteFile(hTarget, &UIHeader, sizeof(UI_HEADER), &dwWritten, NULL);

	_tprintf(_T("Write Header                                    \r"));

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwGroups); lp++)
	{
		ReadFile(hSource, &OldUIGroup, sizeof(OLD_UI_GROUP), &dwRead, NULL);
		memcpy_s(&UIGroup, sizeof(UI_GROUP), &OldUIGroup, sizeof(OLD_UI_GROUP));
		memset(UIGroup.cReserved, 0, sizeof(BYTE) * 32);
		WriteFile(hTarget, &UIGroup, sizeof(UI_GROUP), &dwWritten, NULL);

		_tprintf(_T("Group %05d/%05d                               \r"), lp + 1, OldUIHeader.dwGroups);
	}

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwPages); lp++)
	{
		ReadFile(hSource, &OldUIPageC, sizeof(OLD_UI_PAGEC), &dwRead, NULL);
		memcpy_s(&UIPageC, sizeof(UI_PAGEC), &OldUIPageC, sizeof(OLD_UI_PAGEC));
		WriteFile(hTarget, &UIPageC, sizeof(UI_PAGEC), &dwWritten, NULL);

		_tprintf(_T("PageC %05d/%05d                               \r"), lp + 1, OldUIHeader.dwPages);
	}

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwCtrls); lp++)
	{
		ReadFile(hSource, &OldUICtrlC, sizeof(OLD_UI_CTRLC), &dwRead, NULL);
		memcpy_s(&UICtrlC, sizeof(UI_CTRLC), &OldUICtrlC, sizeof(OLD_UI_CTRLC));
		WriteFile(hTarget, &UICtrlC, sizeof(UI_CTRLC), &dwWritten, NULL);

		_tprintf(_T("CtrlC %05d/%05d                               \r"), lp + 1, OldUIHeader.dwCtrls);
	}

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwImages); lp++)
	{
		ReadFile(hSource, &OldUIImageC, sizeof(OLD_UI_IMAGEC), &dwRead, NULL);
		memcpy_s(&UIImageC, sizeof(UI_IMAGEC), &OldUIImageC, sizeof(OLD_UI_IMAGEC));
		WriteFile(hTarget, &UIImageC, sizeof(UI_IMAGEC), &dwWritten, NULL);

		_tprintf(_T("ImageC %05d/%05d                              \r"), lp + 1, OldUIHeader.dwImages);
	}

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwGroups * OldUIHeader.dwPages); lp++)
	{
		ReadFile(hSource, &OldUIPageS, sizeof(OLD_UI_PAGES), &dwRead, NULL);
		memcpy_s(&UIPageS, sizeof(UI_PAGES), &OldUIPageS, sizeof(OLD_UI_PAGES));
		memset(UIPageS.cReserved, 0, sizeof(BYTE) * 32);
		WriteFile(hTarget, &UIPageS, sizeof(UI_PAGES), &dwWritten, NULL);

		_tprintf(_T("PageS %05d/%05d                               \r"), lp + 1, (OldUIHeader.dwGroups * OldUIHeader.dwPages));
	}

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwGroups * OldUIHeader.dwCtrls); lp++)
	{
		ReadFile(hSource, &OldUICtrlS, sizeof(OLD_UI_CTRLS), &dwRead, NULL);
		memcpy_s(&UICtrlS, sizeof(UI_CTRLS), &OldUICtrlS, sizeof(OLD_UI_CTRLS));
		memset(UICtrlS.cReserved, 0, sizeof(BYTE) * 32);
		WriteFile(hTarget, &UICtrlS, sizeof(UI_CTRLS), &dwWritten, NULL);

		_tprintf(_T("CtrlS %05d/%05d                               \r"), lp + 1, (OldUIHeader.dwGroups * OldUIHeader.dwCtrls));
	}

	for (lp = 0; lp < static_cast<int>(OldUIHeader.dwGroups * OldUIHeader.dwImages); lp++)
	{
		ReadFile(hSource, &OldUIImageS, sizeof(OLD_UI_IMAGES), &dwRead, NULL);
		memcpy_s(&UIImageS, sizeof(UI_IMAGES), &OldUIImageS, sizeof(OLD_UI_IMAGES));
		memset(UIImageS.cReserved, 0, sizeof(BYTE) * 32);
		WriteFile(hTarget, &UIImageS, sizeof(UI_IMAGES), &dwWritten, NULL);

		_tprintf(_T("ImageS %05d/%05d                              \r"), lp + 1, (OldUIHeader.dwGroups * OldUIHeader.dwImages));

		dwSize		= UIImageS.dwSize;
		dwCurPos	= 0;
		dwReadSize	= BUFSIZE;

		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ReadFile(hSource, cBuffer, dwReadSize, &dwRead, NULL);
			WriteFile(hTarget, cBuffer, dwReadSize, &dwWritten, NULL);

			dwCurPos += dwReadSize;
		}
	}

	CloseHandle(hTarget);
	CloseHandle(hSource);

	return 0;
}
