// UIBin.h

#pragma once

// UDB ����
#define	UDB_VERSION	0x00020000

// ���̵� �ִ밪
#define	ID_MAX		0xFFFF

// �������� �� ���ҽ� ����
typedef struct tagResourceInfo
{
	unsigned int	uKey;						// ���� Ű (���� ��üũ�� * 5 + 1234, ���ҽ� ���� üũ ����)
	unsigned int	uUIVersion;					// UI ���� (0x00020000)
	unsigned int	uUpdateVersion;				// ������Ʈ ���� (������, ��Ʈ��, �̹��� �ε��� �� ������ �޶����� ��ȣ�� ������Ų��.)
	unsigned int	uExportVersion;				// UDB ���� (���� �ø��� ��ȣ�� ������Ų��.)
	char			szDate[16];					// ���� ��¥ YYYYMMDDHHMM (ex. 200803171420)
	unsigned int	uWidth;						// ȭ�� ũ�� X (�ȼ�)
	unsigned int	uHeight;					// ȭ�� ũ�� Y (�ȼ�)
	unsigned int	uPageCount;					// ������ ����
	unsigned int	uControlCount;				// ��Ʈ�� ����
	unsigned int	uImageCount;				// �̹��� ����
	unsigned int	uImageMaxSize;				// �̹��� �ִ� ũ��
	unsigned int	uImageCompressionMaxSize;	// �̹��� ���� �� �ִ� ũ��
	unsigned int	uMaskMaxSize;				// ����ũ �ִ� ũ��
	unsigned int	uMaskCompressionMaxSize;	// ����ũ ���� �� �ִ� ũ��
	unsigned int	uResourceInfoSize;			// RESOURCE_INFO ����ü ũ��
	unsigned int	uPageInfoSize;				// PAGE_INFO ����ü ũ��
	unsigned int	uControlInfoSize;			// CONTROL_INFO ����ü ũ��
	unsigned int	uImageInfoSize;				// IMAGE_INFO ����ü ũ��
	char			byBlank[16];				// 100 bytes ����
} RESOURCE_INFO, *PRESOURCE_INFO;

// ������ ����
typedef struct tagPageInfo
{
	unsigned short	bEnable;					// ��뿩�� (0: ��� �� ��, 1: �����)
	unsigned short	uStartIDC;					// ���� ��Ʈ�� ID
	unsigned short	uControlCount;				// ��Ʈ�� ����
	unsigned short	uDefaultIDC;				// ����Ʈ ��Ʈ�� ID
} PAGE_INFO, *PPAGE_INFO;

// ��Ʈ�� ����
typedef struct tagControlInfo
{
	unsigned short	bEnable;					// ��� ���� (0: ��� �� ��, 1: �����)
	unsigned short	bBackground;				// ��� ���� (0: Ŭ�� �� �켱 ���� ����, 1: Ŭ�� �� �켱 ���� ����)
	unsigned short	bCommon;					// ���� ��Ʈ�� ���� (0: �ܵ�, 1: ����)
	unsigned short	uControlType;				// ��Ʈ�� Ÿ��
	unsigned short	uImageCount;				// �̹��� ����
	long			nLeft;						// ��Ʈ�� ���� ��ǥ
	long			nTop;
	long			nRight;
	long			nBottom;
	unsigned short	uWidth;						// ��Ʈ�� ���� ����
	unsigned short	uHeight;					// ��Ʈ�� ���� ����
	unsigned short	uPinLeft;					// �� ����
	unsigned short	uPinTop;
	unsigned short	uPinRight;
	unsigned short	uPinBottom;
	char			szText[32];					// �̹��� ������ ����� �ؽ�Ʈ
	// ������(���� 1Bit�� �ش� ��Ʈ�� ���̵�� �̵����� �ʰ� �����Ѵ�.)
	// (ID == ID_MAX �̸� �������� �ʴ´�.)
	unsigned short	uLKeyIDC;					// ������Ű Left�� �� �̵��� ��Ʈ�� ID
	unsigned short	uUKeyIDC;					// ������Ű Up�� �� �̵��� ��Ʈ�� ID
	unsigned short	uRKeyIDC;					// ������Ű Right�� �� �̵��� ��Ʈ�� ID
	unsigned short	uDKeyIDC;					// ������Ű Down�� �� �̵��� ��Ʈ�� ID
	unsigned short	uEKeyIDC;					// ������Ű Enter�� �� �̵��� ��Ʈ�� ID
} CONTROL_INFO, *PCONTROL_INFO;

// �̹��� ���� ��ġ
typedef struct tagImageInfo
{
	unsigned int	uOffset;					// �̹��� �� ��ġ
	unsigned short	bCompress;					// ���� ���� (0: ���� �� ��, 1: ������)
	unsigned int	uSizeOriginal;				// ���� �� �̹��� �� ũ��
	unsigned int	uMaskOriginal;				// ���� �� ����ũ �� ũ��
	unsigned int	uSize;						// ���� �� �̹��� �� ũ��
	unsigned int	uMask;						// ���� �� ����ũ �� ũ��
} IMAGE_INFO, *PIMAGE_INFO;

// ��Ʈ�� ����
typedef struct tagBitmapInfo
{
	unsigned short	uWidth;						// �̹��� ���� ����
	unsigned short	uHeight;					// �̹��� ���� ����
	unsigned short	uType;						// �̹��� ����
	unsigned short	uMask;						// ���� ���� ����ũ ���� ���� (0: ���� �� ��, 1: ������)
	unsigned short	uAlphaGradient;				// ���� ���� �׶���Ʈ ���� (0: ����, 1: ����, 2: �¿�)
	unsigned short	uFirstOpacity;				// ó�� ������ (0 ~ 255)
	unsigned short	uLastOpacity;				// ������ ������ (0 ~ 255)
} BITMAP_INFO, *PBITMAP_INFO;
