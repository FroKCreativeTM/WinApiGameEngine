#include "CStartScene.h"
#include "../Object/CUIPanel.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Collider/CPixelCollider.h"
#include "../CCore.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	// 부모 Scene 클래스의 초기화 함수를 호출해준다.
	if (!CScene::Init())
	{
		return false;
	}

	/* 레이어를 찾아야한다. */
	// start는 UI다.
	CLayer* pLayer = FindLayer("UI");
	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GET_RESOLUTION.nWidth, GET_RESOLUTION.nHeight);
	pBackPanel->SetTexture("StartBack", L"StartBackground.bmp");

	SAFE_RELEASE(pBackPanel);

	return true;
}