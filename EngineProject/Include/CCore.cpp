#include "CCore.h"
#include "Scene/CSceneManager.h"
#include "Core/CTimer.h"

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

    // 윈도우 클래스 등록
    MyRegisterClass();

    // 해상도 설정
    m_tRS.nWidth = 1280;
    m_tRS.nHeight = 720;

    // 윈도우창 생성
    Create();

    // 렌더 타깃인 화면 DC를 만들어준다.
    m_hDC = GetDC(m_hWnd);

    // 타이머(FPS, 델타타임) 초기화
    if (!GET_SINGLE(CTimer)->Init())
    {
        return false;
    }

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
            // 게임의 로직이 실행된다.
            Logic();
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = CCore::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = m_hInst;
    wcex.hIcon          = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = L"FroK's Engine";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
    m_hWnd = CreateWindowW(
        L"FroK's Engine",
        L"FroK's Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
        nullptr, nullptr,m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    // 실제 타이틀바나 윈도우를 포함한 크기를 구해준다.
    RECT rc = { 0,0,m_tRS.nWidth,m_tRS.nHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 위에서 구해준 크기로 윈도우 클라이언트 크기를 원하는 크기로 맞춰줘야 한다.
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right-rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

void CCore::Logic()
{
    // 타이머 갱신
    GET_SINGLE(CTimer)->Update();

    // 우리가 함수를 만들고 그 델타타임에 이것을 전달하면 된다.
    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    // 입력을 받는다.
    Input(fDeltaTime);
    Update(fDeltaTime);
    LateUpdate(fDeltaTime);
    Collision(fDeltaTime);
    Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Update(fDeltaTime);
    return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
    return 0;
}

void CCore::Collision(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
    // 씬 매니저부터는 DC가 필요하다!
    // 렌더 타깃
    GET_SINGLE(CSceneManager)->Render(m_hDC, fDeltaTime);
}

CCore::CCore() 
{
}

CCore::~CCore()
{
    // 서브 관리 클래스들을 전부 해제한다.
    DESTROY_SINGLE(CSceneManager);
    DESTROY_SINGLE(CTimer);
}
