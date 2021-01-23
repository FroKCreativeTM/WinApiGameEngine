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
	// �θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init())
	{
		return false;
	}

	/* ���̾ ã�ƾ��Ѵ�. */
	// start�� UI��.
	CLayer* pLayer = FindLayer("UI");
	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GET_RESOLUTION.nWidth, GET_RESOLUTION.nHeight);
	pBackPanel->SetTexture("StartBack", L"StartBackground.bmp");

	SAFE_RELEASE(pBackPanel);

	return true;
}