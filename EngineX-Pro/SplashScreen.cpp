#include "stdafx.h"
#include "SplashScreen.h"

#include "windowsx.h"
#include "resource.h"


typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes)
        (HWND hWnd, COLORREF cr, BYTE bAlpha, DWORD dwFlags);

lpfnSetLayeredWindowAttributes g_pSetLayeredWindowAttributes;
#define WS_EX_LAYERED 0x00080000 

static LRESULT CALLBACK ExtWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static CSplash * spl = NULL;
    if(uMsg == WM_CREATE)
    {
        spl = (CSplash*)((LPCREATESTRUCT)lParam)->lpCreateParams;
    }
    if(spl)
        return spl->WindowProc(hwnd, uMsg, wParam, lParam);
    else
        return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CSplash::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			OnPaint(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void CSplash::OnPaint(HWND hwnd)
{
    if (!m_hBitmap)
        return;

    PAINTSTRUCT ps ;
    HDC hDC = BeginPaint (hwnd, &ps) ;

    RECT   rect;
    ::GetClientRect(m_hwnd, &rect);
    
    HDC hMemDC      = ::CreateCompatibleDC(hDC);
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, m_hBitmap);
    
    BitBlt(hDC, 0, 0, m_dwWidth, m_dwHeight, hMemDC, 0, 0, SRCCOPY);

    ::SelectObject(hMemDC, hOldBmp);

    ::DeleteDC(hMemDC);

	if(m_ShowText == 1)
	{
		HFONT hFont = CreateFont(14,0,0,0,FW_LIGHT,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));
		SelectObject(hDC, hFont);
		SetBkMode(hDC,TRANSPARENT);
		SetTextColor(hDC, m_TextColor);
		TextOutA(hDC, 90, 70, m_TextToDisplay, strlen(m_TextToDisplay));
	}

    EndPaint (hwnd, &ps) ;
}

void CSplash::Init()
{

    m_hwnd = NULL;
    m_lpszClassName = TEXT("SPLASH");
    m_colTrans = 0;
    HMODULE hUser32 = GetModuleHandle(TEXT("USER32.DLL"));

    g_pSetLayeredWindowAttributes = (lpfnSetLayeredWindowAttributes)
        GetProcAddress(hUser32, "SetLayeredWindowAttributes");
}

CSplash::CSplash(int resourceId, HINSTANCE hins)
{
    m_resourceId = resourceId;
    m_hins = hins;
    Init();
}

void CSplash::Start( COLORREF colTrans)
{
	m_ShowText = 0;
    HICON hBitmap = NULL;
	hBitmap = (HICON)::LoadImageA(m_hins, MAKEINTRESOURCE(m_resourceId), IMAGE_ICON, 0, 0, 0);
	SetBitmap(hBitmap);
	SetTransparentColor(colTrans);
}

void CSplash::Start(COLORREF colTrans, bool hShowText, char hText[255], COLORREF hTextColor)
{
	m_ShowText = hShowText;
	strcpy_s(m_TextToDisplay,hText);
	m_TextColor = hTextColor;

    HICON hBitmap = NULL;
	hBitmap = (HICON)::LoadImageA(m_hins, MAKEINTRESOURCE(m_resourceId), IMAGE_ICON, 0, 0, 0);
	SetBitmap(hBitmap);
	SetTransparentColor(colTrans);
}

void CSplash::Start(LPCTSTR lpszFileName, COLORREF colTrans)
{
	SetBitmap(lpszFileName);
	SetTransparentColor(colTrans);
}

CSplash::~CSplash()
{
    FreeResources();
}

HWND CSplash::RegAndCreateWindow()
{
    //  =======================================================================
    //  Register the window with ExtWndProc as the window procedure
    //  =======================================================================
    WNDCLASSEX wndclass;
    wndclass.cbSize         = sizeof (wndclass);
    wndclass.style          = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW;
    wndclass.lpfnWndProc    = ExtWndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance      = m_hins;
    wndclass.hIcon          = NULL;
    wndclass.hCursor        = ::LoadCursor( NULL, IDC_WAIT );
    wndclass.hbrBackground  = (HBRUSH)::GetStockObject(LTGRAY_BRUSH);
    wndclass.lpszMenuName   = NULL;
    wndclass.lpszClassName  = m_lpszClassName;
    wndclass.hIconSm        = NULL;

    if(!RegisterClassEx (&wndclass))
        return NULL;

    //  =======================================================================
    //  Create the window of the application, passing the this pointer so that
    //  ExtWndProc can use that for message forwarding
    //  =======================================================================
    DWORD nScrWidth  = ::GetSystemMetrics(SM_CXFULLSCREEN);
    DWORD nScrHeight = ::GetSystemMetrics(SM_CYFULLSCREEN);

    int x = (nScrWidth  - m_dwWidth) / 2;
    int y = (nScrHeight - m_dwHeight) / 2;
    m_hwnd = ::CreateWindowEx(WS_EX_TOPMOST|WS_EX_TOOLWINDOW, m_lpszClassName, 
                              TEXT("Banner"), WS_POPUP, x, y, 
                              m_dwWidth, m_dwHeight, NULL, NULL, m_hins, this);

    //  =======================================================================
    //  Display the window
    //  =======================================================================
    if(m_hwnd)
    {
        MakeTransparent();
        ShowWindow   (m_hwnd, SW_SHOW) ;
        UpdateWindow (m_hwnd);
    }
    return m_hwnd;
}

int CSplash::DoLoop()
{
    //  =======================================================================
    //  Show the window
    //  =======================================================================
    if(!m_hwnd)
        ShowSplash();

    //  =======================================================================
    //  Get into the modal loop
    //  =======================================================================
    MSG msg ;
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage  (&msg) ;
    }

    return msg.wParam ;

}

void CSplash::ShowSplash()
{
    CloseSplash();
    RegAndCreateWindow();
}

DWORD CSplash::SetBitmap(LPCTSTR lpszFileName)
{
    //  =======================================================================
    /*HICON hIcon = (HICON)*/
    //  =======================================================================
        HICON    hBitmap       = NULL;
    hBitmap = (HICON)::LoadImage(0, lpszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return SetBitmap(hBitmap);
}

DWORD CSplash::SetBitmap(HICON hBitmap)
{
    int nRetValue;
    BITMAP  csBitmapSize;
    
    //  =======================================================================
    //  Free loaded resource
    //  =======================================================================
    FreeResources();
    
    if (hBitmap)
    {
        m_hBitmap = hBitmap;
        
        //  ===================================================================
        //  Get bitmap size
        //  ===================================================================
        nRetValue = ::GetObject(hBitmap, sizeof(csBitmapSize), &csBitmapSize);
        if (nRetValue == 0)
        {
            FreeResources();
            return 0;
        }
        m_dwWidth = (DWORD)csBitmapSize.bmWidth;
        m_dwHeight = (DWORD)csBitmapSize.bmHeight;
    }
       
    return 1;
}

void CSplash::FreeResources()
{
    if (m_hBitmap)
        ::DeleteObject (m_hBitmap);
    m_hBitmap = NULL;
}

int CSplash::CloseSplash()
{
    
    if(m_hwnd)
    {
        SendMessage(m_hwnd, WM_CLOSE, 0, 0);
        m_hwnd = 0;
        UnregisterClass(m_lpszClassName, m_hins);
        return 1;
    }
    return 0;
}

bool CSplash::SetTransparentColor(COLORREF col)
{
    m_colTrans = col;

    return MakeTransparent();
}

bool CSplash::MakeTransparent()
{

    if(m_hwnd && g_pSetLayeredWindowAttributes && m_colTrans )
    {
        //  set layered style for the window
        SetWindowLong(m_hwnd, GWL_EXSTYLE, GetWindowLong(m_hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        //  call it with 0 alpha for the given color
        g_pSetLayeredWindowAttributes(m_hwnd, m_colTrans, 0, LWA_COLORKEY);
    }    
    return TRUE;
}
