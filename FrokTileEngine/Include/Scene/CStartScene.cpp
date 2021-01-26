#include "CStartScene.h"
#include "../Object/CUIPanel.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Collider/CRectCollider.h"
#include "../CCore.h"
#include "../Object/CUIButton.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CMapEditScene.h"

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

	CUIButton* pStartButton = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartButton->SetPos(GET_RESOLUTION.nWidth / 2 - 100, GET_RESOLUTION.nHeight / 2 - 300);
	pStartButton->SetSize(356.f, 102.f);
	pStartButton->SetTexture("StartButton", L"StartButton.bmp");

	CRectCollider* pRectCollider = (CRectCollider*)pStartButton->GetCollider("ButtonBody");

	POSITION tPos = pStartButton->GetPos();
	// 상대적 위치다!
	pRectCollider->SetRect(0.f, 0.f, 356.f, 102.f);

	SAFE_RELEASE(pRectCollider);
	pStartButton->SetCallback(this, &CStartScene::StartButtonCallback);
	SAFE_RELEASE(pStartButton);

	CUIButton* pEditButton = CObj::CreateObj<CUIButton>("EditButton", pLayer);

	pEditButton->SetPos(GET_RESOLUTION.nWidth / 2 - 100, GET_RESOLUTION.nHeight / 2 - 100);
	pEditButton->SetSize(356.f, 102.f);
	pEditButton->SetTexture("EditButton", L"EditButton.bmp");

	pRectCollider = (CRectCollider*)pEditButton->GetCollider("ButtonBody");

	tPos = pEditButton->GetPos();
	// 상대적 위치다!
	pRectCollider->SetRect(0.f, 0.f, 356.f, 102.f);
	 
	SAFE_RELEASE(pRectCollider);
	pEditButton->SetCallback(this, &CStartScene::EditButtonCallback);
	SAFE_RELEASE(pEditButton);

	CUIButton* pEndButton = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndButton->SetPos(GET_RESOLUTION.nWidth / 2 - 100, GET_RESOLUTION.nHeight / 2 + 100);
	pEndButton->SetSize(356.f, 102.f);
	pEndButton->SetTexture("EndButton", L"EndButton.bmp");

	pRectCollider = (CRectCollider*)pEndButton->GetCollider("ButtonBody");

	tPos = pEndButton->GetPos();
	// 상대적 위치다!
	pRectCollider->SetRect(0.f, 0.f, 356.f, 102.f);
	pRectCollider->AddCollisionFunction(CS_ENTER, pEndButton, &CUIButton::MouseOn);
	pRectCollider->AddCollisionFunction(CS_LEAVE, pEndButton, &CUIButton::MouseOut);

	SAFE_RELEASE(pRectCollider);
	pEndButton->SetCallback(this, &CStartScene::EndButtonCallback);
	SAFE_RELEASE(pEndButton);

	return true;
}

void CStartScene::StartButtonCallback(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CStartScene::EditButtonCallback(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CMapEditScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fDeltaTime)
{
	// 윈도우 핸들을 없애며 게임 끝
	GET_SINGLE(CCore)->DestroyGame();
}
