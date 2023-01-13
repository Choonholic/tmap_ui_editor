// ImageHandle.cpp

#include "StdAfx.h"
#include "UIEditor.h"
#include "MainFrm.h"
#include "ImageHandle.h"
#include "ShellUtilities.h"
#include "UIStruct.h"
#include "setjmp.h"
#include "png.h"

#ifdef	_DEBUG
#pragma comment(lib, "libpngd.lib")
#pragma comment(lib, "zlibd.lib")
#else
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "zlib.lib")
#endif

static void png_read_data(png_structp ctx, png_bytep area, png_size_t size)
{
	HANDLE	hFile	= (HANDLE)(png_get_io_ptr(ctx));
	DWORD	dwRead;

	ReadFile(hFile, area, (DWORD)size, &dwRead, NULL);
}

static void png_write_data(png_structp ctx, png_bytep area, png_size_t size)
{
	HANDLE	hFile	= (HANDLE)png_get_io_ptr(ctx);
	DWORD	dwWritten;

	WriteFile(hFile, area, (DWORD)size, &dwWritten, NULL);
}

static void png_flush_data(png_structp ctx)
{
	HANDLE	hFile	= (HANDLE)png_get_io_ptr(ctx);

	FlushFileBuffers(hFile);
}

BOOL GetImageType(LPCTSTR lpszFileName, int &nType, DWORD &dwSize, USHORT &uWidth, USHORT &uHeight, BOOL &bMask)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cHeader[4];
	DWORD		dwRead;

	// Initialize

	nType	= UI_IMAGE_UNKNOWN;
	uWidth	= 0;
	uHeight	= 0;
	bMask	= FALSE;

	// Check Image Header

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("Image file %s does not exist"), lpszFileName);

		return FALSE;
	}

	ReadFile(hFile, cHeader, 4, &dwRead, NULL);

	dwSize	= SetFilePointer(hFile, 0, NULL, FILE_END);

	CloseHandle(hFile);

	// Windows or OS/2 BMP

	if ((cHeader[0] == 'B') && (cHeader[1] == 'M'))
	{
		BITMAPFILEHEADER	bmfh;
		BITMAPINFOHEADER	bmih;

		hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
		ReadFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwRead, NULL);
		CloseHandle(hFile);

		if ((bmfh.bfSize == dwSize) && (bmih.biSize == sizeof(BITMAPINFOHEADER)))
		{
			uWidth	= static_cast<USHORT>(bmih.biWidth);
			uHeight	= static_cast<USHORT>(bmih.biHeight);
			
			switch (bmih.biBitCount)
			{
			case 32:
				{
					nType	= UI_IMAGE_BMP32;
					bMask	= TRUE;

					OUTPUT_STR1(_T("Image %s is 32 Bits BMP"), lpszFileName);
				}
				break;
			case 24:
				{
					nType	= UI_IMAGE_BMP24;
					bMask	= FALSE;

					OUTPUT_STR1(_T("Image %s is 24 Bits BMP"), lpszFileName);
				}
				break;
			case 16:
				{
					nType	= UI_IMAGE_BMP16;
					bMask	= FALSE;

					OUTPUT_STR1(_T("Image %s is 16 Bits BMP"), lpszFileName);
				}
				break;
			default:
				{
					// 1, 4 and 8 Bits BMP is not applicable
					OUTPUT_STR1(_T("Image %s is BMP, but unsupported"), lpszFileName);
				}
				return FALSE;
			}

			return TRUE;
		}
	}
	else if ((cHeader[0] == 0x89) && (cHeader[1] == 'P') && (cHeader[2] == 'N') && (cHeader[3] == 'G'))
	{
		png_structp	png_ptr;
		png_infop	info_ptr;

		png_ptr		= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		info_ptr	= png_create_info_struct(png_ptr);

		setjmp(png_ptr->jmpbuf);

		hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		png_set_read_fn(png_ptr, hFile, png_read_data);
		png_read_info(png_ptr, info_ptr);

		uWidth	= static_cast<USHORT>(png_get_image_width(png_ptr, info_ptr));
		uHeight	= static_cast<USHORT>(png_get_image_height(png_ptr, info_ptr));
		bMask	= static_cast<BOOL>(png_get_channels(png_ptr, info_ptr) == 4);

		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);
		CloseHandle(hFile);

		if (bMask)
		{
			nType	= UI_IMAGE_PNG32;

			OUTPUT_STR1(_T("Image %s is 32 Bits PNG"), lpszFileName);
		}
		else
		{
			nType	= UI_IMAGE_PNG24;

			OUTPUT_STR1(_T("Image %s is 24 Bits PNG"), lpszFileName);
		}

		return TRUE;
	}

	OUTPUT_STR1(_T("File %s is unsupported"), lpszFileName);

	return FALSE;
}

BOOL DrawBMP(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc)
{
	DECLARE_FRAME()

	CDC			MemDC;
	CBitmap		Bitmap;
	CBitmap*	OldBmp;
			
	Bitmap.m_hObject	= (HBITMAP)::LoadImage(NULL, lpszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (Bitmap.m_hObject != NULL)
	{
		MemDC.CreateCompatibleDC(pDC);
			
		OldBmp	= MemDC.SelectObject(&Bitmap);

		pDC->BitBlt(lprc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top, &MemDC, 0, 0, SRCCOPY);	
		MemDC.SelectObject(OldBmp);
		MemDC.DeleteDC();
		Bitmap.DeleteObject();

		return TRUE;
	}

	OUTPUT_STR1(_T("File %s could not be loaded"), lpszFileName);

	return FALSE;
}

BOOL DrawPNG(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc)
{
	DECLARE_FRAME()

	CDC					MemDC;
	CBitmap				Bitmap;
	CBitmap*			OldBmp;
	png_structp			png_ptr;
	png_infop			info_ptr;
	HANDLE				hFile;
	png_uint_32			width;
	png_uint_32			height;
	int					bit_depth;
	int					color_type;
	int					interlace_type;
	volatile int		ckey	= -1;
	png_color_16*		transv;
	png_bytep* volatile	row_pointers;
	int					row;
	BITMAPINFO			bmi;
	BOOL				bMask;

	hFile		= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("File %s could not be loaded"), lpszFileName);

		return FALSE;
	}

	png_ptr		= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr	= png_create_info_struct(png_ptr);

	setjmp(png_ptr->jmpbuf);

	png_set_read_fn(png_ptr, hFile, png_read_data);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);

	if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		png_set_expand(png_ptr);
	}

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		int		num_trans;
		LPBYTE	trans;

		png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &transv);

		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			int	i;
			int	t	= -1;

			for (i = 0; i < num_trans; i++)
			{
				if (trans[i] == 0)
				{
					if (t >= 0)
					{
						break;
					}

					t	= i;
				}
				else if (trans[i] != 255)
				{
					break;
				}
			}

			if (i == num_trans)
			{
				ckey	= t;
			}
			else
			{
				png_set_expand(png_ptr);
			}
		}
		else
		{
			ckey	= 0;
		}
	}

	if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		png_set_gray_to_rgb(png_ptr);
	}

	png_read_update_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

	if (ckey != -1)
	{
		if (color_type != PNG_COLOR_TYPE_PALETTE)
		{
			ckey	= RGB(transv->red, transv->green, transv->blue);
		}

		// TODO: Set Color Key
	}

	bMask			= (BOOL)(png_get_channels(png_ptr, info_ptr) == 4);
	row_pointers	= (png_bytep*)malloc(sizeof(png_bytep) * height);

	for (row = 0; row < (int)height; row++)
	{
		row_pointers[row]	= (png_bytep)malloc(sizeof(png_byte) * bit_depth * info_ptr->channels * width);
	}

	png_read_image(png_ptr, row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);

	CloseHandle(hFile);

	void*	pBits	= NULL;
	BYTE*	pPixel;

	memset(&bmi, 0, sizeof(BITMAPINFOHEADER));

	bmi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth			= width;
	bmi.bmiHeader.biHeight			= height;
	bmi.bmiHeader.biPlanes			= 1;
	bmi.bmiHeader.biBitCount		= 32;
	bmi.bmiHeader.biCompression		= BI_RGB;
	bmi.bmiHeader.biSizeImage		= 0;

	Bitmap.m_hObject	= CreateDIBSection(pDC->m_hDC, &bmi, DIB_RGB_COLORS, &pBits, NULL, NULL);

	for (row = 0; row < (int)height; row++)
	{
		pPixel	= (LPBYTE)pBits + width * 4 * row;

		for (int i = 0; i < (int)width; i++)
		{
			if (bMask)
			{
				pPixel[0]	= row_pointers[height - row - 1][i * 4 + 2] * row_pointers[height - row - 1][i * 4 + 3] / 255;
				pPixel[1]	= row_pointers[height - row - 1][i * 4 + 1] * row_pointers[height - row - 1][i * 4 + 3] / 255;
				pPixel[2]	= row_pointers[height - row - 1][i * 4 + 0] * row_pointers[height - row - 1][i * 4 + 3] / 255;
				pPixel[3]	= row_pointers[height - row - 1][i * 4 + 3];
			}
			else
			{
				pPixel[0]	= row_pointers[height - row - 1][i * 3 + 2];
				pPixel[1]	= row_pointers[height - row - 1][i * 3 + 1];
				pPixel[2]	= row_pointers[height - row - 1][i * 3 + 0];
			}

			pPixel	+= 4;
		}
	}

	for (row = 0; row < (int)height; row++)
	{
		free(row_pointers[row]);
	}

	free(row_pointers);

	MemDC.CreateCompatibleDC(pDC);
		
	OldBmp	= MemDC.SelectObject(&Bitmap);

	if (bMask)
	{
		BLENDFUNCTION		BlendFunction;

		BlendFunction.BlendOp				= AC_SRC_OVER;
		BlendFunction.BlendFlags			= 0;
		BlendFunction.SourceConstantAlpha	= 255;
		BlendFunction.AlphaFormat			= AC_SRC_ALPHA;

		AlphaBlend(pDC->m_hDC, lprc->left, lprc->top, width, height, MemDC.m_hDC, 0, 0, width, height, BlendFunction);
	}
	else
	{
		pDC->BitBlt(lprc->left, lprc->top, width, height, &MemDC, 0, 0, SRCCOPY);
	}

	MemDC.SelectObject(OldBmp);
	MemDC.DeleteDC();
	Bitmap.DeleteObject();

	return TRUE;
}

#if FALSE
BOOL DrawJPG(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc)
{
	return FALSE;
}

BOOL DrawGIF(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc)
{
	return FALSE;
}
#endif

#define	BUFSIZE		(256 * 1024)

BOOL SaveBufferBMP(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwRead;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ReadFile(hFile, cBuffer, dwReadSize, &dwRead, NULL);
			ar.Write(cBuffer, dwReadSize);

			dwCurPos += dwReadSize;
		}

		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been saved"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to save image %s"), lpszFileName);

	return FALSE;
}

BOOL LoadBufferBMP(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwWritten;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ar.Read(cBuffer, dwReadSize);
			WriteFile(hFile, cBuffer, dwReadSize, &dwWritten, NULL);

			dwCurPos	+= dwReadSize;
		}

		FlushFileBuffers(hFile);
		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been loaded"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to load image %s"), lpszFileName);

	return FALSE;
}

BOOL SaveBufferPNG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwRead;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ReadFile(hFile, cBuffer, dwReadSize, &dwRead, NULL);
			ar.Write(cBuffer, dwReadSize);

			dwCurPos += dwReadSize;
		}

		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been saved"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to save image %s"), lpszFileName);

	return FALSE;
}

BOOL LoadBufferPNG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwWritten;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ar.Read(cBuffer, dwReadSize);
			WriteFile(hFile, cBuffer, dwReadSize, &dwWritten, NULL);

			dwCurPos	+= dwReadSize;
		}

		FlushFileBuffers(hFile);
		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been loaded"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to load image %s"), lpszFileName);

	return FALSE;
}

#if FALSE
BOOL SaveBufferJPG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}

BOOL LoadBufferJPG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}

BOOL SaveBufferGIF(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}

BOOL LoadBufferGIF(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}
#endif

BOOL SaveBufferBMP(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwRead;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ReadFile(hFile, cBuffer, dwReadSize, &dwRead, NULL);
			file.Write(cBuffer, dwReadSize);

			dwCurPos += dwReadSize;
		}

		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been saved"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to save image %s"), lpszFileName);

	return FALSE;
}

BOOL LoadBufferBMP(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwWritten;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			file.Read(cBuffer, dwReadSize);
			WriteFile(hFile, cBuffer, dwReadSize, &dwWritten, NULL);

			dwCurPos	+= dwReadSize;
		}

		FlushFileBuffers(hFile);
		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been loaded"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to load image %s"), lpszFileName);

	return FALSE;
}

BOOL SaveBufferPNG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwRead;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			ReadFile(hFile, cBuffer, dwReadSize, &dwRead, NULL);
			file.Write(cBuffer, dwReadSize);

			dwCurPos += dwReadSize;
		}

		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been saved"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to save image %s"), lpszFileName);

	return FALSE;
}

BOOL LoadBufferPNG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	DECLARE_FRAME()

	HANDLE		hFile;
	BYTE		cBuffer[BUFSIZE];
	DWORD		dwWritten;
	DWORD		dwCurPos	= 0;
	DWORD		dwReadSize	= BUFSIZE;

	hFile	= CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		while (dwCurPos < dwSize)
		{
			if (dwCurPos + BUFSIZE > dwSize)
			{
				dwReadSize	= dwSize - dwCurPos;
			}

			file.Read(cBuffer, dwReadSize);
			WriteFile(hFile, cBuffer, dwReadSize, &dwWritten, NULL);

			dwCurPos	+= dwReadSize;
		}

		FlushFileBuffers(hFile);
		CloseHandle(hFile);

		OUTPUT_STR1(_T("Image %s has been loaded"), lpszFileName);

		return TRUE;
	}

	OUTPUT_STR1(_T("Failed to load image %s"), lpszFileName);

	return FALSE;
}

#if FALSE
BOOL SaveBufferJPG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}

BOOL LoadBufferJPG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}

BOOL SaveBufferGIF(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}

BOOL LoadBufferGIF(CFile &file, LPCTSTR lpszFileName, DWORD dwSize)
{
	return FALSE;
}
#endif

BOOL SaveDatabaseBMP(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress)
{
	DECLARE_FRAME()

	HANDLE				hFile;
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	int					nLine;
	LPBYTE				cBuffer;
	LPWORD				wBuffer;
	LPBYTE				cMask;
	DWORD				dwRead;
	DWORD				dwWritten;
	int					lp1;
	int					lp2;
	BYTE				cExtra[BMP_EXTRA_BYTES];

	OUTPUT_STR1(_T("File %s will be embedded into database"), lpszFileName);

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("File %s does not exist"), lpszFileName);

		return FALSE;
	}

	ReadFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
	ReadFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwRead, NULL);

	if ((bmfh.bfType != 0x4D42) || (bmih.biSize != sizeof(BITMAPINFOHEADER)))
	{
		CloseHandle(hFile);

		OUTPUT_STR1(_T("File %s is not BMP"), lpszFileName);

		return FALSE;
	}

	nLine	= (int)((((bmih.biWidth * bmih.biBitCount) / CHAR_BIT) % sizeof(DWORD)) ? (((((bmih.biWidth * bmih.biBitCount) / CHAR_BIT) / sizeof(DWORD)) + 1) * sizeof(DWORD)) : ((bmih.biWidth * bmih.biBitCount) / CHAR_BIT));

	cBuffer	= new BYTE[nLine * bmih.biHeight];

	ReadFile(hFile, cBuffer, (nLine * bmih.biHeight) * sizeof(BYTE), &dwRead, NULL);

	nLine	= (int)((((bmih.biWidth * UDB_DEST_BPP) / CHAR_BIT) % sizeof(DWORD)) ? (((((bmih.biWidth * UDB_DEST_BPP) / CHAR_BIT) / sizeof(DWORD)) + 1) * sizeof(DWORD)) : ((bmih.biWidth * UDB_DEST_BPP) / CHAR_BIT));

	wBuffer	= new WORD[(nLine / sizeof(WORD)) * bmih.biHeight];
	
	if (uMaskSize)
	{
		cMask	= new BYTE[bmih.biWidth * bmih.biHeight];
	}

	bmih.biBitCount		= UDB_DEST_BPP;
	bmih.biSizeImage	= nLine * bmih.biHeight;
	bmfh.bfSize			= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (nLine * bmih.biHeight) + BMP_EXTRA_BYTES;

	switch (bmih.biBitCount)
	{
	case 32:
		{
			for (lp1 = 0; lp1 < static_cast<int>(bmih.biHeight); lp1++)
			{
				for (lp2 = 0; lp2 < static_cast<int>(bmih.biWidth); lp2++)
				{
					wBuffer[((nLine / sizeof(WORD)) * lp1) + lp2]			= RGB555(cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 0)], cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 1)], cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 2)]);
					cMask[(bmih.biWidth * (bmih.biHeight - lp1 - 1)) + lp2]	= cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 3)];
				}
			}

		}
		break;
	case 24:
		{
			for (lp1 = 0; lp1 < static_cast<int>(bmih.biHeight); lp1++)
			{
				for (lp2 = 0; lp2 < static_cast<int>(bmih.biWidth); lp2++)
				{
					wBuffer[((nLine / sizeof(WORD)) * lp1) + lp2]			= RGB555(cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 0)], cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 1)], cBuffer[(((nLine / sizeof(WORD)) * lp1) * (bmih.biBitCount / CHAR_BIT)) + (lp2 * (bmih.biBitCount / CHAR_BIT) + 2)]);
				}
			}
		}
		break;
	case 16:
		{
			memcpy((LPVOID)wBuffer, cBuffer, nLine * bmih.biHeight);
		}
		break;
	default:
		{
			delete [] cBuffer;
			delete [] wBuffer;
			
			if (uMaskSize)
			{
				delete [] cMask;
			}

			OUTPUT_STR1(_T("Image %s is unsupported"), lpszFileName);
		}
		return FALSE;
	}

	memset(cExtra, 0, BMP_EXTRA_BYTES);

	if (bCompress)
	{
		LPBYTE	cCompress		= new BYTE[(nLine * bmih.biHeight) * 2];
		DWORD	dwCompressed	= ((nLine * bmih.biHeight) * 2);

		compress(cCompress, &dwCompressed, (LPBYTE)wBuffer, nLine * bmih.biHeight);

		WriteFile(hStream, (LPVOID)&bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)&bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)cCompress, dwCompressed, &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)cExtra, BMP_EXTRA_BYTES, &dwWritten, NULL);

		uSize	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwCompressed + BMP_EXTRA_BYTES;

		if (uMaskSize)
		{
			dwCompressed	= ((nLine * bmih.biHeight) * 2);

			compress(cCompress, &dwCompressed, cMask, bmih.biWidth * bmih.biHeight);

			WriteFile(hStream, (LPVOID)cCompress, dwCompressed, &dwWritten, NULL);

			uMaskSize	= dwCompressed;
		}

		delete [] cCompress;
	}
	else
	{
		WriteFile(hStream, (LPVOID)&bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)&bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)wBuffer, nLine * bmih.biHeight, &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)cExtra, BMP_EXTRA_BYTES, &dwWritten, NULL);

		uSize	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (nLine * bmih.biHeight) + BMP_EXTRA_BYTES;

		if (uMaskSize)
		{
			WriteFile(hStream, (LPVOID)cMask, bmih.biWidth * bmih.biHeight, &dwWritten, NULL);

			uMaskSize	= bmih.biWidth * bmih.biHeight;
		}
	}
	
	delete [] wBuffer;
	delete [] cBuffer;

	if (uMaskSize)
	{
		delete [] cMask;
	}

	CloseHandle(hFile);

	OUTPUT_STR1(_T("Image %s has been embedded"), lpszFileName);

	return TRUE;
}

BOOL SaveDatabasePNG(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress)
{
	DECLARE_FRAME()

	HANDLE				hFile;
	BYTE				cHeader[4];
	DWORD				dwRead;
	DWORD				dwWritten;
	png_structp			png_ptr;
	png_infop			info_ptr;
	png_uint_32			width;
	png_uint_32			height;
	int					bit_depth;
	int					color_type;
	int					interlace_type;
	volatile int		ckey	= -1;
	png_color_16*		transv;
	png_bytep* volatile	row_pointers;
	int					row;
	int					nLine;
	LPWORD				wBuffer;
	LPBYTE				cMask;
	int					lp;
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	BYTE				cExtra[BMP_EXTRA_BYTES];

	OUTPUT_STR1(_T("File %s will be embedded into database"), lpszFileName);

	hFile	= CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("File %s does not exist"), lpszFileName);

		return FALSE;
	}

	ReadFile(hFile, cHeader, 4, &dwRead, NULL);
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	if ((cHeader[0] != 0x89) || (cHeader[1] != 'P') || (cHeader[2] != 'N') || (cHeader[3] != 'G'))
	{
		CloseHandle(hFile);

		OUTPUT_STR1(_T("File %s is not PNG"), lpszFileName);

		return FALSE;
	}

	png_ptr		= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr	= png_create_info_struct(png_ptr);

	setjmp(png_ptr->jmpbuf);

	png_set_read_fn(png_ptr, hFile, png_read_data);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);

	if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		png_set_expand(png_ptr);
	}

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		int		num_trans;
		LPBYTE	trans;

		png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &transv);

		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			int	i;
			int	t	= -1;

			for (i = 0; i < num_trans; i++)
			{
				if (trans[i] == 0)
				{
					if (t >= 0)
					{
						break;
					}

					t	= i;
				}
				else if (trans[i] != 255)
				{
					break;
				}
			}

			if (i == num_trans)
			{
				ckey	= t;
			}
			else
			{
				png_set_expand(png_ptr);
			}
		}
		else
		{
			ckey	= 0;
		}
	}

	if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		png_set_gray_to_rgb(png_ptr);
	}

	png_read_update_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

	if (ckey != -1)
	{
		if (color_type != PNG_COLOR_TYPE_PALETTE)
		{
			ckey	= RGB(transv->red, transv->green, transv->blue);
		}

		// TODO: Set Color Key
	}

	row_pointers	= (png_bytep*)malloc(sizeof(png_bytep) * height);

	for (row = 0; row < (int)height; row++)
	{
		row_pointers[row]	= (png_bytep)malloc(sizeof(png_byte) * bit_depth * info_ptr->channels * width);
	}

	png_read_image(png_ptr, row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);

	nLine	= (int)((((width * UDB_DEST_BPP) / CHAR_BIT) % sizeof(DWORD)) ? (((((width * UDB_DEST_BPP) / CHAR_BIT) / sizeof(DWORD)) + 1) * sizeof(DWORD)) : ((width * UDB_DEST_BPP) / CHAR_BIT));

	wBuffer	= new WORD[(nLine / sizeof(WORD)) * height];

	if (uMaskSize)
	{
		cMask	= new BYTE[width * height];
	}

	for (row = 0; row < (int)height; row++)
	{
		for (lp = 0; lp < (int)width; lp++)
		{
			if (uMaskSize)
			{
				wBuffer[((nLine / sizeof(WORD)) * row) + lp]	= RGB555(row_pointers[height - row - 1][lp * 4 + 0], row_pointers[height - row - 1][lp * 4 + 1], row_pointers[height - row - 1][lp * 4 + 2]);
				cMask[(width * row) + lp]						= row_pointers[row][lp * 4 + 3];
			}
			else
			{
				wBuffer[((nLine / sizeof(WORD)) * row) + lp]	= RGB555(row_pointers[height - row - 1][lp * 3 + 0], row_pointers[height - row - 1][lp * 3 + 1], row_pointers[height - row - 1][lp * 3 + 2]);
			}
		}
	}

	for (row = 0; row < (int)height; row++)
	{
		free(row_pointers[row]);
	}

	free(row_pointers);

	bmfh.bfType				= 0x4D42;
	bmfh.bfSize				= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (nLine * height) + BMP_EXTRA_BYTES;
	bmfh.bfReserved1		= 0;
	bmfh.bfReserved2		= 0;
	bmfh.bfOffBits			= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmih.biSize				= sizeof(BITMAPINFOHEADER);
	bmih.biWidth			= width;
	bmih.biHeight			= height;
	bmih.biPlanes			= 1;
	bmih.biBitCount			= UDB_DEST_BPP;
	bmih.biCompression		= BI_RGB;
	bmih.biSizeImage		= nLine * height;
	bmih.biXPelsPerMeter	= 0;
	bmih.biYPelsPerMeter	= 0;
	bmih.biClrUsed			= 0;
	bmih.biClrImportant		= 0;

	memset(cExtra, 0, BMP_EXTRA_BYTES);

	if (bCompress)
	{
		LPBYTE	cCompress		= new BYTE[(nLine * bmih.biHeight) * 2];
		DWORD	dwCompressed	= ((nLine * bmih.biHeight) * 2);

		compress(cCompress, &dwCompressed, (LPBYTE)wBuffer, nLine * bmih.biHeight);

		WriteFile(hStream, (LPVOID)&bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)&bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)cCompress, dwCompressed, &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)cExtra, BMP_EXTRA_BYTES, &dwWritten, NULL);

		uSize	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwCompressed + BMP_EXTRA_BYTES;

		if (uMaskSize)
		{
			dwCompressed	= ((nLine * bmih.biHeight) * 2);

			compress(cCompress, &dwCompressed, cMask, bmih.biWidth * bmih.biHeight);

			WriteFile(hStream, (LPVOID)cCompress, dwCompressed, &dwWritten, NULL);

			uMaskSize	= dwCompressed;
		}

		delete [] cCompress;
	}
	else
	{
		WriteFile(hStream, (LPVOID)&bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)&bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)wBuffer, nLine * bmih.biHeight, &dwWritten, NULL);
		WriteFile(hStream, (LPVOID)cExtra, BMP_EXTRA_BYTES, &dwWritten, NULL);

		uSize	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (nLine * bmih.biHeight) + BMP_EXTRA_BYTES;

		if (uMaskSize)
		{
			WriteFile(hStream, (LPVOID)cMask, bmih.biWidth * bmih.biHeight, &dwWritten, NULL);

			uMaskSize	= bmih.biWidth * bmih.biHeight;
		}
	}

	delete [] wBuffer;

	if (uMaskSize)
	{
		delete [] cMask;
	}

	CloseHandle(hFile);

	OUTPUT_STR1(_T("Image %s has been embedded"), lpszFileName);

	return TRUE;
}

#if FALSE
BOOL SaveDatabaseJPG(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress)
{
	return FALSE;
}

BOOL SaveDatabaseGIF(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress)
{
	return FALSE;
}
#endif

BOOL ResizeBMP(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize)
{
	DECLARE_FRAME()

	HANDLE				hOldFile;
	HANDLE				hNewFile;
	BITMAPFILEHEADER	bmfhOld;
	BITMAPINFOHEADER	bmihOld;
	DWORD				dwRead;
	int					nOldLine;
	LPBYTE				cOldBuffer;
	BITMAPFILEHEADER	bmfhNew;
	BITMAPINFOHEADER	bmihNew;
	DWORD				dwWritten;
	int					nNewLine;
	LPBYTE				cNewBuffer;
	BYTE				cExtra[BMP_EXTRA_BYTES];
	int					lp1;
	int					lp2;
	int					nX;
	int					nY;
	double				dbXFactor	= 1.0f;
	double				dbYFactor	= 1.0f;

	hOldFile	= CreateFile(lpszOldFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOldFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("File %s does not exist"), lpszOldFileName);

		return FALSE;
	}

	ReadFile(hOldFile, &bmfhOld, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
	ReadFile(hOldFile, &bmihOld, sizeof(BITMAPINFOHEADER), &dwRead, NULL);

	if ((bmfhOld.bfType != 0x4D42) || (bmihOld.biSize != sizeof(BITMAPINFOHEADER)))
	{
		CloseHandle(hOldFile);

		OUTPUT_STR1(_T("File %s is not BMP"), lpszOldFileName);

		return FALSE;
	}

	if ((bmihOld.biWidth == nNewWidth) && (bmihOld.biHeight == nNewHeight))
	{
		CloseHandle(hOldFile);

		OUTPUT_STR1(_T("File %s does not need to be resized"), lpszOldFileName);

		return (ShellCopy(lpszOldFileName, lpszNewFileName));
	}

	nOldLine	= (int)((((bmihOld.biWidth * bmihOld.biBitCount) / CHAR_BIT) % sizeof(DWORD)) ? (((((bmihOld.biWidth * bmihOld.biBitCount) / CHAR_BIT) / sizeof(DWORD)) + 1) * sizeof(DWORD)) : ((bmihOld.biWidth * bmihOld.biBitCount) / CHAR_BIT));

	cOldBuffer	= new BYTE[nOldLine * bmihOld.biHeight];

	ReadFile(hOldFile, cOldBuffer, (nOldLine * bmihOld.biHeight) * sizeof(BYTE), &dwRead, NULL);
	CloseHandle(hOldFile);

	memcpy_s(&bmfhNew, sizeof(BITMAPFILEHEADER), &bmfhOld, sizeof(BITMAPFILEHEADER));
	memcpy_s(&bmihNew, sizeof(BITMAPINFOHEADER), &bmihOld, sizeof(BITMAPINFOHEADER));

	bmihNew.biWidth		= nNewWidth;
	bmihNew.biHeight	= nNewHeight;

	nNewLine	= (int)((((bmihNew.biWidth * bmihNew.biBitCount) / CHAR_BIT) % sizeof(DWORD)) ? (((((bmihNew.biWidth * bmihNew.biBitCount) / CHAR_BIT) / sizeof(DWORD)) + 1) * sizeof(DWORD)) : ((bmihNew.biWidth * bmihNew.biBitCount) / CHAR_BIT));

	cNewBuffer	= new BYTE[nNewLine * bmihNew.biHeight];

	bmihNew.biSizeImage	= nNewLine * bmihNew.biHeight;
	bmfhNew.bfSize		= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (nNewLine * bmihNew.biHeight) + BMP_EXTRA_BYTES;

	dbXFactor	= (double)((double)(bmihNew.biWidth) / (double)(bmihOld.biWidth));
	dbYFactor	= (double)((double)(bmihNew.biHeight) / (double)(bmihOld.biHeight));

	switch (bmihOld.biBitCount)
	{
	case 32:
		{
			for (lp1 = 0; lp1 < static_cast<int>(bmihOld.biHeight); lp1++)
			{
				for (lp2 = 0; lp2 < static_cast<int>(bmihOld.biWidth); lp2++)
				{
					nX	= (int)(dbXFactor * lp2);
					nY	= (int)(dbYFactor * lp1);

					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 0)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 0)];
					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 1)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 1)];
					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 2)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 2)];
					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 3)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 3)];
				}
			}
		}
		break;
	case 24:
		{
			for (lp1 = 0; lp1 < static_cast<int>(bmihOld.biHeight); lp1++)
			{
				for (lp2 = 0; lp2 < static_cast<int>(bmihOld.biWidth); lp2++)
				{
					nX	= (int)(dbXFactor * lp2);
					nY	= (int)(dbYFactor * lp1);

					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 0)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 0)];
					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 1)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 1)];
					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 2)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 2)];
				}
			}
		}
		break;
	case 16:
		{
			for (lp1 = 0; lp1 < static_cast<int>(bmihOld.biHeight); lp1++)
			{
				for (lp2 = 0; lp2 < static_cast<int>(bmihOld.biWidth); lp2++)
				{
					nX	= (int)(dbXFactor * lp2);
					nY	= (int)(dbYFactor * lp1);

					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 0)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 0)];
					cNewBuffer[(nNewLine * nY) + (nX * (bmihNew.biBitCount / CHAR_BIT) + 1)]	= cOldBuffer[(nOldLine * lp1) + (lp2 * (bmihOld.biBitCount / CHAR_BIT) + 1)];
				}
			}
		}
		break;
	default:
		{
			delete [] cOldBuffer;
			delete [] cNewBuffer;

			OUTPUT_STR1(_T("Image %s is unsupported"), lpszOldFileName);
		}
		return FALSE;
	}

	delete [] cOldBuffer;

	hNewFile	= CreateFile(lpszNewFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hNewFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("Failed to create %s"), lpszNewFileName);

		return FALSE;
	}

	memset(cExtra, 0, BMP_EXTRA_BYTES);

	WriteFile(hNewFile, (LPVOID)&bmfhNew, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hNewFile, (LPVOID)&bmihNew, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hNewFile, (LPVOID)cNewBuffer, nNewLine * bmihNew.biHeight, &dwWritten, NULL);
	WriteFile(hNewFile, (LPVOID)cExtra, BMP_EXTRA_BYTES, &dwWritten, NULL);

	dwSize		= SetFilePointer(hNewFile, 0, NULL, FILE_CURRENT);
	dwMaskSize	= 0;

	FlushFileBuffers(hNewFile);
	CloseHandle(hNewFile);

	delete [] cNewBuffer;

	OUTPUT_STR3(_T("Image %s [Image Size: %d, Mask Size: %d]"), lpszNewFileName, dwSize, dwMaskSize);

	return TRUE;
}

BOOL ResizePNG(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize)
{
	DECLARE_FRAME()

	png_structp			png_ptr;
	png_infop			info_ptr;
	png_uint_32			old_width;
	png_uint_32			old_height;
	png_uint_32			new_width;
	png_uint_32			new_height;
	int					bit_depth;
	int					color_type;
	int					interlace_type;
	volatile int		ckey	= -1;
	png_color_16*		transv;
	png_bytep* volatile	old_row_pointers;
	png_bytep* volatile	new_row_pointers;
	int					row;
	int					lp;
	HANDLE				hOldFile;
	HANDLE				hNewFile;
	BYTE				cHeader[4];
	DWORD				dwRead;
	int					nX;
	int					nY;
	double				dbXFactor	= 1.0f;
	double				dbYFactor	= 1.0f;

	hOldFile	= CreateFile(lpszOldFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOldFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("File %s does not exist"), lpszOldFileName);

		return FALSE;
	}

	ReadFile(hOldFile, cHeader, 4, &dwRead, NULL);
	SetFilePointer(hOldFile, 0, NULL, FILE_BEGIN);

	if ((cHeader[0] != 0x89) || (cHeader[1] != 'P') || (cHeader[2] != 'N') || (cHeader[3] != 'G'))
	{
		CloseHandle(hOldFile);

		OUTPUT_STR1(_T("File %s is not PNG"), lpszOldFileName);

		return FALSE;
	}

	png_ptr		= png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr	= png_create_info_struct(png_ptr);

	setjmp(png_ptr->jmpbuf);

	png_set_read_fn(png_ptr, hOldFile, png_read_data);
	png_read_info(png_ptr, info_ptr);

	if ((info_ptr->width == nNewWidth) && (info_ptr->height == nNewHeight))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);
		CloseHandle(hOldFile);

		OUTPUT_STR1(_T("File %s does not need to be resized"), lpszOldFileName);

		return (ShellCopy(lpszOldFileName, lpszNewFileName));
	}

	png_get_IHDR(png_ptr, info_ptr, &old_width, &old_height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);

	if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		png_set_expand(png_ptr);
	}

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		int		num_trans;
		LPBYTE	trans;

		png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &transv);

		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			int	i;
			int	t	= -1;

			for (i = 0; i < num_trans; i++)
			{
				if (trans[i] == 0)
				{
					if (t >= 0)
					{
						break;
					}

					t	= i;
				}
				else if (trans[i] != 255)
				{
					break;
				}
			}

			if (i == num_trans)
			{
				ckey	= t;
			}
			else
			{
				png_set_expand(png_ptr);
			}
		}
		else
		{
			ckey	= 0;
		}
	}

	if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		png_set_gray_to_rgb(png_ptr);
	}

	png_read_update_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &old_width, &old_height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

	if (ckey != -1)
	{
		if (color_type != PNG_COLOR_TYPE_PALETTE)
		{
			ckey	= RGB(transv->red, transv->green, transv->blue);
		}

		// TODO: Set Color Key
	}

	old_row_pointers	= (png_bytep*)malloc(sizeof(png_bytep) * old_height);

	for (row = 0; row < (int)old_height; row++)
	{
		old_row_pointers[row]	= (png_bytep)malloc(sizeof(png_byte) * bit_depth * info_ptr->channels * old_width);
	}

	png_read_image(png_ptr, old_row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);

	CloseHandle(hOldFile);

	hNewFile	= CreateFile(lpszNewFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hNewFile == INVALID_HANDLE_VALUE)
	{
		OUTPUT_STR1(_T("Failed to create %s"), lpszNewFileName);

		return FALSE;
	}

	png_ptr		= png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr	= png_create_info_struct(png_ptr);

	setjmp(png_ptr->jmpbuf);

	png_set_read_fn(png_ptr, hOldFile, png_read_data);
	png_set_write_fn(png_ptr, hNewFile, png_write_data, png_flush_data);

	setjmp(png_ptr->jmpbuf);

	new_width	= nNewWidth;
	new_height	= nNewHeight;

	png_set_IHDR(png_ptr, info_ptr, new_width, new_height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);

	setjmp(png_ptr->jmpbuf);

	dbXFactor	= (double)((double)(new_width) / (double)(old_width));
	dbYFactor	= (double)((double)(new_height) / (double)(old_height));

	new_row_pointers	= (png_bytep*)malloc(sizeof(png_bytep) * new_height);

	for (row = 0; row < (int)new_height; row++)
	{
		new_row_pointers[row]	= (png_bytep)malloc(sizeof(png_byte) * bit_depth * info_ptr->channels * new_width);
	}

	switch (info_ptr->channels)
	{
	case 4:
		{
			for (row = 0; row < (int)old_height; row++)
			{
				for (lp = 0; lp < (int)old_width; lp++)
				{
					nX	= (int)(dbXFactor * lp);
					nY	= (int)(dbYFactor * row);

					new_row_pointers[nY][nX * 4 + 0]	= old_row_pointers[row][lp * 4 + 0];
					new_row_pointers[nY][nX * 4 + 1]	= old_row_pointers[row][lp * 4 + 1];
					new_row_pointers[nY][nX * 4 + 2]	= old_row_pointers[row][lp * 4 + 2];
					new_row_pointers[nY][nX * 4 + 3]	= old_row_pointers[row][lp * 4 + 3];
				}
			}
		}
		break;
	case 3:
		{
			for (row = 0; row < (int)old_height; row++)
			{
				for (lp = 0; lp < (int)old_width; lp++)
				{
					nX	= (int)(dbXFactor * lp);
					nY	= (int)(dbYFactor * row);

					new_row_pointers[nY][nX * 3 + 0]	= old_row_pointers[row][lp * 3 + 0];
					new_row_pointers[nY][nX * 3 + 1]	= old_row_pointers[row][lp * 3 + 1];
					new_row_pointers[nY][nX * 3 + 2]	= old_row_pointers[row][lp * 3 + 2];
				}
			}
		}
		break;
	}

	png_write_image(png_ptr, new_row_pointers);

	setjmp(png_ptr->jmpbuf);

	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	
	for (row = 0; row < (int)old_height; row++)
	{
		free(old_row_pointers[row]);
	}

	free(old_row_pointers);

	for (row = 0; row < (int)new_height; row++)
	{
		free(new_row_pointers[row]);
	}

	free(new_row_pointers);

	CloseHandle(hNewFile);

	CFileStatus	fs;
	
	if (CFile::GetStatus(lpszNewFileName, fs))
	{
		dwSize		= static_cast<DWORD>(fs.m_size);
		dwMaskSize	= new_width * new_height;
	}

	OUTPUT_STR3(_T("Image %s [Image Size: %d, Mask Size: %d]"), lpszNewFileName, dwSize, dwMaskSize);

	return TRUE;
}

#if FALSE
BOOL ResizeJPG(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize)
{
	return FALSE;
}

BOOL ResizeGIF(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize)
{
	return FALSE;
}
#endif
