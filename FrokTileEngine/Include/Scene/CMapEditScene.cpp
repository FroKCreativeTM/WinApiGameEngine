#include "CMapEditScene.h"
#include "CStartScene.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Collider/CRectCollider.h"
#include "../CCore.h"
#include "CSceneManager.h"
#include "CStartScene.h"
#include "../Object/CStage.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Core/CInput.h"
#include "../Resources/CResourceManager.h"
#include "../resource.h"
#include "../Resources/CTexture.h"
#include "../Core/CPathManager.h"

wchar_t CMapEditScene::m_strText[MAX_PATH] = {};

CMapEditScene::CMapEditScene() : 
	m_nEditTileTex(0)
{
	m_eTem = TEM_TEXTURE;
}

CMapEditScene::~CMapEditScene()
{
	Safe_Release_VecList(m_vecTileTexture);
	SAFE_RELEASE(m_pStage);
}

bool CMapEditScene::Init()
{
	GET_SINGLE(CCamera)->SetWorldResolution(4800, 4800);

	CTexture* pNoneTex = GET_SINGLE(CResourceManager)->LoadTexture("TileNone", L"Tile/OverWorld/OptionNone.bmp");
	pNoneTex->SetColorKey(255, 0, 255);
	SAFE_RELEASE(pNoneTex);

	CTexture* pNoMoveTex = GET_SINGLE(CResourceManager)->LoadTexture("TileNoMove", L"Tile/OverWorld/OptionNoMove.bmp");
	pNoMoveTex->SetColorKey(255, 0, 255);
	SAFE_RELEASE(pNoMoveTex);

	/* ��������(��׶���) ���� */
	// ���̾ �ణ �ٸ� ���� �� ���̴�.
	CLayer* pStageLayer = FindLayer("Stage");
	m_pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	// ���̽� Ÿ�Ϸν� 48x48 �������� Sky.bmp�� 100x100�� ���.
	m_pStage->CreateTile(100, 100, 48, 48, "BaseTile", L"Tile/OverWorld/Sky.bmp");

	CTexture* pTex = GET_SINGLE(CResourceManager)->FindTexture("BaseTile");
	m_vecTileTexture.push_back(pTex);

	pTex = GET_SINGLE(CResourceManager)->LoadTexture("Block1", L"Tile/OverWorld/Block1.bmp");
	m_vecTileTexture.push_back(pTex);

	pTex = GET_SINGLE(CResourceManager)->LoadTexture("Ground1", L"Tile/OverWorld/Ground1.bmp");
	m_vecTileTexture.push_back(pTex);

	m_nEditTileTex = 0;
	m_eEditOption = TO_NONE;

	GET_SINGLE(CInput)->AddKey("Save", 'S', VK_CONTROL);
	GET_SINGLE(CInput)->AddKey("Load", 'O', VK_CONTROL);

	return true;
}

void CMapEditScene::Input(float fDeltaTime)
{
	CScene::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000)
	{
		GET_SINGLE(CCamera)->Scroll(0.f, -300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		GET_SINGLE(CCamera)->Scroll(0.f, 300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		GET_SINGLE(CCamera)->Scroll(-300.f * fDeltaTime, 0.f);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		GET_SINGLE(CCamera)->Scroll(300.f * fDeltaTime, 0.f);
	}
	// �巡���ص� �Դ´�.
	if (KEYPRESS("MouseLButton"))
	{
		POSITION tMouseWorldPos = MOUSEWORLDPOS;
		
		switch (m_eTem)
		{
		case TEM_TEXTURE:
			m_pStage->ChangeTileTex(tMouseWorldPos, m_vecTileTexture[m_nEditTileTex]);
			break;
		case TEM_OPTION:
			m_pStage->ChangeTileOption(tMouseWorldPos, m_eEditOption);
			break;
		}

	}

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		// �ؽ�ó �������
		m_eTem = TEM_TEXTURE;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		// �ɼ� �������
		m_eTem = TEM_OPTION;
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		switch (m_eTem)
		{
		case TEM_TEXTURE:
			m_nEditTileTex = 0;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NONE;
			break;
		}
	}

	if (GetAsyncKeyState('2') & 0x8000)
	{
		switch (m_eTem)
		{
		case TEM_TEXTURE:
			m_nEditTileTex = 1;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		}
	}

	if (GetAsyncKeyState('3') & 0x8000)
	{
		switch (m_eTem)
		{
		case TEM_TEXTURE:
			m_nEditTileTex = 2;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		}
	}

	if (KEYPRESS("MouseRButton"))
	{

	}

	if (KEYDOWN("Save"))
	{
		ShowCursor(TRUE);
		// �׳� ��� ������� �����
		DialogBox(GET_WINDOWINSTANCE, MAKEINTRESOURCE(IDD_DIALOG1),
			GET_WINDOWHANDLE, CMapEditScene::DlgProc);
		ShowCursor(FALSE);

		// ���ϸ��� �̿��ؼ� �����Ѵ�.
		// ��Ƽ����Ʈ�� ��ȯ �ʿ�
		char strFileName[MAX_PATH] = {};
		WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName, lstrlen(m_strText), 0, 0);

		m_pStage->SaveFromPath(strFileName);
	}

	if (KEYDOWN("Load"))
	{

	}
}

INT_PTR CMapEditScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG : 
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			// Edit Box���� ���ڿ��� �����´�.
			memset(m_strText, 0, sizeof(wchar_t) * MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDIT1, m_strText, MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
		return FALSE;
	}

	return LRESULT();
}
