#include "CInGameScene.h"
#include "../Object/CPlayer.h"
#include "../Object/CMushroom.h"
#include "../Object/CBullet.h"
#include "CLayer.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	// �θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init())
	{
		return false;
	}

	/* ���̾ ã�ƾ��Ѵ�. */
	CLayer* pLayer = FindLayer("Default");

	/* �÷��̾� ���� */
	// ���⼭ pPlayer�� ���۷��� ī���ʹ� 2��.
	// Init�� �ڵ����� ȣ��ȴ�.
	CPlayer* pPlayer = CObj::CreateObj<CPlayer>
		("Player", pLayer);
	/* ���� ���̾ �÷��̾ ���� �ʿ� ������ �����. */
	/* ���� ������ �ٸ� ������ ������ �� �Ǵ�  */
	SAFE_RELEASE(pPlayer);

	/* �� ���� */
	CMushroom* pMushroom = CObj::CreateObj<CMushroom>
		("Mushroom", pLayer);
	SAFE_RELEASE(pMushroom);

	/* �Ѿ� ������Ÿ�� */
	CBullet* pBullet = CScene::CreatePrototype<CBullet>
		("Bullet");
	pBullet->SetSize(50.f, 50.f);
	SAFE_RELEASE(pBullet);

	return true;
}
