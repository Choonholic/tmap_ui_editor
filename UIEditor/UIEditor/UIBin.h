// UIBin.h

#pragma once

// UDB 버전
#define	UDB_VERSION	0x00020000

// 아이디 최대값
#define	ID_MAX		0xFFFF

// 파일정보 및 리소스 정보
typedef struct tagResourceInfo
{
	unsigned int	uKey;						// 파일 키 (파일 전체크기 * 5 + 1234, 리소스 파일 체크 목적)
	unsigned int	uUIVersion;					// UI 버전 (0x00020000)
	unsigned int	uUpdateVersion;				// 업데이트 버전 (페이지, 컨트롤, 이미지 인덱스 및 개수가 달라지면 번호를 증가시킨다.)
	unsigned int	uExportVersion;				// UDB 버전 (변경 시마다 번호를 증가시킨다.)
	char			szDate[16];					// 생성 날짜 YYYYMMDDHHMM (ex. 200803171420)
	unsigned int	uWidth;						// 화면 크기 X (픽셀)
	unsigned int	uHeight;					// 화면 크기 Y (픽셀)
	unsigned int	uPageCount;					// 페이지 개수
	unsigned int	uControlCount;				// 컨트롤 개수
	unsigned int	uImageCount;				// 이미지 개수
	unsigned int	uImageMaxSize;				// 이미지 최대 크기
	unsigned int	uImageCompressionMaxSize;	// 이미지 압축 후 최대 크기
	unsigned int	uMaskMaxSize;				// 마스크 최대 크기
	unsigned int	uMaskCompressionMaxSize;	// 마스크 압축 후 최대 크기
	unsigned int	uResourceInfoSize;			// RESOURCE_INFO 구조체 크기
	unsigned int	uPageInfoSize;				// PAGE_INFO 구조체 크기
	unsigned int	uControlInfoSize;			// CONTROL_INFO 구조체 크기
	unsigned int	uImageInfoSize;				// IMAGE_INFO 구조체 크기
	char			byBlank[16];				// 100 bytes 여분
} RESOURCE_INFO, *PRESOURCE_INFO;

// 페이지 정보
typedef struct tagPageInfo
{
	unsigned short	bEnable;					// 사용여부 (0: 사용 안 함, 1: 사용함)
	unsigned short	uStartIDC;					// 시작 컨트롤 ID
	unsigned short	uControlCount;				// 컨트롤 개수
	unsigned short	uDefaultIDC;				// 디폴트 컨트롤 ID
} PAGE_INFO, *PPAGE_INFO;

// 컨트롤 정보
typedef struct tagControlInfo
{
	unsigned short	bEnable;					// 사용 여부 (0: 사용 안 함, 1: 사용함)
	unsigned short	bBackground;				// 배경 여부 (0: 클릭 시 우선 순위 높음, 1: 클릭 시 우선 순위 낮음)
	unsigned short	bCommon;					// 공용 컨트롤 여부 (0: 단독, 1: 공용)
	unsigned short	uControlType;				// 컨트롤 타입
	unsigned short	uImageCount;				// 이미지 개수
	long			nLeft;						// 컨트롤 영역 좌표
	long			nTop;
	long			nRight;
	long			nBottom;
	unsigned short	uWidth;						// 컨트롤 가로 길이
	unsigned short	uHeight;					// 컨트롤 세로 길이
	unsigned short	uPinLeft;					// 핀 설정
	unsigned short	uPinTop;
	unsigned short	uPinRight;
	unsigned short	uPinBottom;
	char			szText[32];					// 이미지 없을때 사용할 텍스트
	// 리모컨(상위 1Bit는 해당 컨트롤 아이디로 이동하지 않고 실행한다.)
	// (ID == ID_MAX 이면 동작하지 않는다.)
	unsigned short	uLKeyIDC;					// 리모컨키 Left일 때 이동할 컨트롤 ID
	unsigned short	uUKeyIDC;					// 리모컨키 Up일 때 이동할 컨트롤 ID
	unsigned short	uRKeyIDC;					// 리모컨키 Right일 때 이동할 컨트롤 ID
	unsigned short	uDKeyIDC;					// 리모컨키 Down일 때 이동할 컨트롤 ID
	unsigned short	uEKeyIDC;					// 리모컨키 Enter일 때 이동할 컨트롤 ID
} CONTROL_INFO, *PCONTROL_INFO;

// 이미지 파일 위치
typedef struct tagImageInfo
{
	unsigned int	uOffset;					// 이미지 블럭 위치
	unsigned short	bCompress;					// 압축 여부 (0: 압축 안 함, 1: 압축함)
	unsigned int	uSizeOriginal;				// 압축 전 이미지 블럭 크기
	unsigned int	uMaskOriginal;				// 압축 전 마스크 블럭 크기
	unsigned int	uSize;						// 압축 후 이미지 블럭 크기
	unsigned int	uMask;						// 압축 후 마스크 블럭 크기
} IMAGE_INFO, *PIMAGE_INFO;

// 비트맵 정보
typedef struct tagBitmapInfo
{
	unsigned short	uWidth;						// 이미지 가로 길이
	unsigned short	uHeight;					// 이미지 세로 길이
	unsigned short	uType;						// 이미지 형태
	unsigned short	uMask;						// 알파 블랜딩 마스크 존재 여부 (0: 존재 안 함, 1: 존재함)
	unsigned short	uAlphaGradient;				// 알파 블랜딩 그라디언트 형태 (0: 없음, 1: 상하, 2: 좌우)
	unsigned short	uFirstOpacity;				// 처음 불투명도 (0 ~ 255)
	unsigned short	uLastOpacity;				// 마지막 불투명도 (0 ~ 255)
} BITMAP_INFO, *PBITMAP_INFO;
