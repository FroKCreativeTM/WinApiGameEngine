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
#include "../Resources/CTexture.h"

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

	/* 스테이지(백그라운드) 생성 */
	// 레이어를 약간 다른 것을 쓸 것이다.
	CLayer* pStageLayer = FindLayer("Stage");
	m_pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	// 베이스 타일로써 48x48 사이즈의 Sky.bmp를 100x100개 깐다.
	m_pStage->CreateTile(100, 100, 48, 48, "BaseTile", L"Tile/OverWorld/Sky.bmp");

	CTexture* pTex = GET_SINGLE(CResourceManager)->FindTexture("BaseTile");
	m_vecTileTexture.push_back(pTex);

	pTex = GET_SINGLE(CResourceManager)->LoadTexture("Block1", L"Tile/OverWorld/Block1.bmp");
	m_vecTileTexture.push_back(pTex);

	pTex = GET_SINGLE(CResourceManager)->LoadTexture("Ground1", L"Tile/OverWorld/Ground1.bmp");
	m_vecTileTexture.push_back(pTex);

	m_nEditTileTex = 0;
	m_eEditOption = TO_NONE;

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
	// 드래그해도 먹는다.
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
		// 텍스처 편집모드
		m_eTem = TEM_TEXTURE;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		// 옵션 편집모드
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
}
