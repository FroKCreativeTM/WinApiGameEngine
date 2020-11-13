#include "CCore.h"
#include "Scene/CSceneManager.h"
#include "Core/CTimer.h"

// nullptr ������ ���⼭ �����ϴ�.
// �ֳĸ� ��� ���α׷� ���۰� ����� �ν��Ͻ���
// ���������ϱ�(static)
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

    // ������ Ŭ���� ���
    MyRegisterClass();

    // �ػ� ����
    m_tRS.nWidth = 1280;
    m_tRS.nHeight = 720;

    // ������â ����
    Create();

    // ���� Ÿ���� ȭ�� DC�� ������ش�.
    m_hDC = GetDC(m_hWnd);

    // Ÿ�̸�(FPS, ��ŸŸ��) �ʱ�ȭ
    if (!GET_SINGLE(CTimer)->Init())
    {
        return false;
    }

    /* ���� ���� Ŭ���� �ʱ�ȭ */
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
        // ������ �޽��� ť�� ó���ϴ� �Լ��Դϴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // ������ ����Ÿ��
        else
        {
            // ������ ������ ����ȴ�.
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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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

    // ���� Ÿ��Ʋ�ٳ� �����츦 ������ ũ�⸦ �����ش�.
    RECT rc = { 0,0,m_tRS.nWidth,m_tRS.nHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������ ������ ũ��� ������ Ŭ���̾�Ʈ ũ�⸦ ���ϴ� ũ��� ������� �Ѵ�.
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right-rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

void CCore::Logic()
{
    // Ÿ�̸� ����
    GET_SINGLE(CTimer)->Update();

    // �츮�� �Լ��� ����� �� ��ŸŸ�ӿ� �̰��� �����ϸ� �ȴ�.
    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    // �Է��� �޴´�.
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
    // �� �Ŵ������ʹ� DC�� �ʿ��ϴ�!
    // ���� Ÿ��
    GET_SINGLE(CSceneManager)->Render(m_hDC, fDeltaTime);
}

CCore::CCore() 
{
}

CCore::~CCore()
{
    // ���� ���� Ŭ�������� ���� �����Ѵ�.
    DESTROY_SINGLE(CSceneManager);
    DESTROY_SINGLE(CTimer);
}
