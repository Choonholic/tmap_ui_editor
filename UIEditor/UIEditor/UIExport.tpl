// UIRes.h
// Generated by UI Editor 2.0 automatically
// $[RELEASE_DATE]

#ifndef __UIRES_H_
#define __UIRES_H_

// 버전 정보
#define	UI_UDB_VERSION     0x00020000
#define UI_UPD_VERSION     $[UPDATE_VERSION]
#define UI_EXP_VERSION     $[EXPORT_VERSION]

// 아이디 최대값
#define	ID_MAX             0xFFFF
#define ID_MAX_CPP         0x0200

// 파일정보 및 리소스 정보
typedef struct tagResourceInfo
{
    unsigned int uKey;                            // 파일 키 (파일 전체크기 * 5 + 1234, 리소스 파일 체크 목적)
    unsigned int uUIVersion;                      // UI 버전 (0x00020000)
    unsigned int uUpdateVersion;                  // 업데이트 버전 (페이지, 컨트롤, 이미지 인덱스 및 개수가 달라지면 번호를 증가시킨다.)
    unsigned int uExportVersion;                  // UDB 버전 (변경 시마다 번호를 증가시킨다.)
    char         szDate[16];                      // 생성 날짜 YYYYMMDDHHMM (ex. 200803171420)
    unsigned int uWidth;                          // 화면 크기 X (픽셀)
    unsigned int uHeight;                         // 화면 크기 Y (픽셀)
    unsigned int uPageCount;                      // 페이지 개수
    unsigned int uControlCount;                   // 컨트롤 개수
    unsigned int uImageCount;                     // 이미지 개수
    unsigned int uImageMaxSize;                   // 이미지 최대 크기
    unsigned int uImageCompressionMaxSize;        // 이미지 압축 후 최대 크기
    unsigned int uMaskMaxSize;                    // 마스크 최대 크기
    unsigned int uMaskCompressionMaxSize;         // 마스크 압축 후 최대 크기
    unsigned int uResourceInfoSize;               // RESOURCE_INFO 구조체 크기
    unsigned int uPageInfoSize;                   // PAGE_INFO 구조체 크기
    unsigned int uControlInfoSize;                // CONTROL_INFO 구조체 크기
    unsigned int uImageInfoSize;                  // IMAGE_INFO 구조체 크기
    char         byBlank[16];                     // 100 bytes 여분
} RESOURCE_INFO, *PRESOURCE_INFO;

// 페이지 정보
typedef struct tagPageInfo
{
    unsigned short bEnable;                       // 사용여부 (0: 사용 안 함, 1: 사용함)
    unsigned short uStartIDC;                     // 시작 컨트롤 ID
    unsigned short uControlCount;                 // 컨트롤 개수
    unsigned short uDefaultIDC;                   // 디폴트 컨트롤 ID
} PAGE_INFO, *PPAGE_INFO;

// 컨트롤 정보
typedef struct tagControlInfo
{
    unsigned short bEnable;                       // 사용 여부 (0: 사용 안 함, 1: 사용함)
    unsigned short bBackground;                   // 배경 여부 (0: 클릭 시 우선 순위 높음, 1: 클릭 시 우선 순위 낮음)
    unsigned short bCommon;                       // 공용 컨트롤 여부 (0: 단독, 1: 공용)
    unsigned short uControlType;                  // 컨트롤 타입
    unsigned short uImageCount;                   // 이미지 개수
    long           nLeft;                         // 컨트롤 영역 좌표
    long           nTop;
    long           nRight;
    long           nBottom;
    unsigned short uWidth;                        // 컨트롤 가로 길이
    unsigned short uHeight;                       // 컨트롤 세로 길이
    unsigned short uPinLeft;                      // 핀 설정
    unsigned short uPinTop;
    unsigned short uPinRight;
    unsigned short uPinBottom;
    char           szText[32];                    // 이미지 없을때 사용할 텍스트
    // 리모컨(상위 1Bit는 해당 컨트롤 아이디로 이동하지 않고 실행한다.)
    // (ID == ID_MAX 이면 동작하지 않는다.)
    unsigned short uLKeyIDC;                      // 리모컨키 Left일 때 이동할 컨트롤 ID
    unsigned short uUKeyIDC;                      // 리모컨키 Up일 때 이동할 컨트롤 ID
    unsigned short uRKeyIDC;                      // 리모컨키 Right일 때 이동할 컨트롤 ID
    unsigned short uDKeyIDC;                      // 리모컨키 Down일 때 이동할 컨트롤 ID
    unsigned short uEKeyIDC;                      // 리모컨키 Enter일 때 이동할 컨트롤 ID
} CONTROL_INFO, *PCONTROL_INFO;

// 이미지 파일 위치
typedef struct tagImageInfo
{
    unsigned int   uOffset;                       // 이미지 블럭 위치
    unsigned short bCompress;                     // 압축 여부 (0: 압축 안 함, 1: 압축함)
    unsigned int   uSizeOriginal;                 // 압축 전 이미지 블럭 크기
    unsigned int   uMaskOriginal;                 // 압축 전 마스크 블럭 크기
    unsigned int   uSize;                         // 압축 후 이미지 블럭 크기
    unsigned int   uMask;                         // 압축 후 마스크 블럭 크기
} IMAGE_INFO, *PIMAGE_INFO;

// 비트맵 정보
typedef struct tagBitmapInfo
{
    unsigned short uWidth;                        // 이미지 가로 길이
    unsigned short uHeight;                       // 이미지 세로 길이
    unsigned short uType;                         // 이미지 형태
    unsigned short uMask;                         // 알파 블랜딩 마스크 존재 여부 (0: 존재 안 함, 1: 존재함)
    unsigned short uAlphaGradient;                // 알파 블랜딩 그라디언트 형태 (0: 없음, 1: 상하, 2: 좌우)
    unsigned short uFirstOpacity;                 // 처음 불투명도 (0 ~ 255)
    unsigned short uLastOpacity;                  // 마지막 불투명도 (0 ~ 255)
} BITMAP_INFO, *PBITMAP_INFO;

// 컨트롤 타입
#ifndef UI_CTRLTYPES
#define UI_CTRLTYPES
#define UI_CTRL_IMAGE       0x0001                // 이미지
#define UI_CTRL_BUTTON      0x0002                // 버튼
#define UI_CTRL_LISTBOX     0x0003                // 리스트 박스
#define UI_CTRL_EDITBOX     0x0004                // 에디트 박스
#define UI_CTRL_COMBOBOX    0x0005                // 콤보 박스
#define UI_CTRL_REGION      0x0006                // 영역
#endif

// 핀 타입
#ifndef UI_PINTYPES
#define UI_PINTYPES
#define UI_PIN_ALL          0x0000                // 절대 좌표 고정
#define UI_PIN_LEFT         0x0001                // 좌측 거리 고정
#define UI_PIN_TOP          0x0001                // 상단 거리 고정
#define UI_PIN_RIGHT        0x0002                // 우측 거리 고정
#define UI_PIN_BOTTOM       0x0002                // 하단 거리 고정
#endif

// 이미지 타입
#ifndef UI_IMAGETYPES
#define UI_IMAGETYPES
#define UI_IMAGE_BMP        0x0010                // BMP Mask
#define UI_IMAGE_BMP32      0x0011                // 32 Bits BMP with Alpha Blending Mask
#define UI_IMAGE_BMP24      0x0012                // 24 Bits BMP
#define UI_IMAGE_BMP16      0x0013                // 16 Bits BMP
#define UI_IMAGE_BMP08      0x0014                // 8 Bits BMP
#define UI_IMAGE_PNG        0x0020                // PNG Mask
#define UI_IMAGE_PNG32      0x0021                // 32 Bits PNG with Alpha Blending Mask
#define UI_IMAGE_PNG24      0x0022                // 24 Bits PNG
#define UI_IMAGE_JPG        0x0030                // JPG Mask
#define UI_IMAGE_JPG24      0x0031                // 24 Bits JPG
#define UI_IMAGE_GIF        0x0040                // GIF Mask
#define UI_IMAGE_GIF08      0x0041                // 8 Bits GIF
#define UI_IMAGE_TYPE       0x00F0                // Type Mask
#define UI_IMAGE_UNKNOWN    0xFFFF                // Unknown
#endif

// 알파 블랜딩 그라디언트 타입
#ifndef UI_ABGTYPES
#define UI_ABGTYPES
#define UI_ABG_NONE         0x0000                // 없음
#define UI_ABG_UPDOWN       0x0001                // 상하
#define UI_ABG_LEFTRIGHT    0x0002                // 좌우
#define UI_ABG_VERTICAL     0x0001                // 세로
#define UI_ABG_HORIZONTAL   0x0002                // 가로
#endif

// 페이지 ID
typedef enum _PAGE_ID
{
    IDP_NOTHING = -1,                             // 페이지 선택 안함
    $[PAGE_ID]
    MAX_PAGE                                      // 페이지 개수
} PAGE_ID;

// 컨트롤 ID
typedef enum _CONTROL_ID
{
    IDC_NOTHING = -1,                             // 컨트롤 선택 안함
    $[CTRL_ID]
    MAX_CONTROL                                   // 컨트롤 개수
} CONTROL_ID;

// 이미지 ID
typedef enum _IMAGE_ID
{
    IDI_NOTHING = -1,                             // 이미지 선택 안함
    $[IMAGE_ID]
    MAX_IMAGE                                     // 이미지 개수
} IMAGE_ID;

#endif // __UIRES_H_
