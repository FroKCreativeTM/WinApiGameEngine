#include "CCore.h"
#include "Scene/CSceneManager.h"

// nullptr 선언은 여기서 가능하다.
// 왜냐면 얘는 프로그램 시작과 생기는 인스턴스고
// 전역변수니까(static)
CCore* CCore::m_pInstance   = nullptr;
bool   CCore::m_bLoop       = true;

CCore* CCore::GetInst()
{
	if (!m_pInstance)
	{
		m_pInstance = new CCore;
	}
	return m_pInstance;
}

void CCore::DestroyInst()
{
	SAFE_DELETE(m_pInstance);
}

bool CCore::Init(HINSTANCE hInstance)
{
	m_hInst = hInstance;

	// 윈도우창 생성
    MyRegisterClass();
    // 해상도 설정
    m_tRS.nWidth = 1280;
    m_tRS.nHeight = 720;

    Create();

    /* 서브 관리 클래스 초기화 */
    if (!GET_SINGLE(CSceneManager)->Init())
    {
        return false;
    }

	return true;
}

int CCore::Run()
{
    MSG msg;
    ::ZeroMemory(&msg, sizeof(MSG));

    while (m_bLoop)
    {
        // 윈도우 메시지 큐를 처리하는 함수입니다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 윈도우 데드타임
        else
        {

        }
    }

	return (int)msg.wParam;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CCore::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"FroK's Engine";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
    m_Hwnd = CreateWindowW(
        L"FroK's Engine",
        L"FroK's Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
        nullptr, nullptr,m_hInst, nullptr);

    if (!m_Hwnd)
    {
        return FALSE;
    }

    // 실제 타이틀바나 윈도우를 포함한 크기를 구해준다.
    RECT rc = { 0,0,m_tRS.nWidth,m_tRS.nHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 위에서 구해준 크기로 윈도우 클라이언트 크기를 원하는 크기로 맞춰줘야 한다.
    SetWindowPos(m_Hwnd, HWND_TOPMOST, 100, 100, rc.right-rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_Hwnd, SW_SHOW);
    UpdateWindow(m_Hwnd);

    return TRUE;
}

CCore::CCore() 
{
}

CCore::~CCore()
{
    // 서브 관리 클래스들을 전부 해제한다.
    DESTROY_SINGLE(CSceneManager);
}
