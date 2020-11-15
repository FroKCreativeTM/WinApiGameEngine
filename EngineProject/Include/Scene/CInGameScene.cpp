#include "CInGameScene.h"
#include "../Object/CPlayer.h"
#include "../Object/CMushroom.h"
#include "CLayer.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	// 부모 Scene 클래스의 초기화 함수를 호출해준다.
	if (!CScene::Init())
	{
		return false;
	}

	/* 레이어를 찾아야한다. */
	CLayer* pLayer = FindLayer("Default");

	/* 플레이어 생성 */
	// 여기서 pPlayer의 레퍼런스 카운터는 2다.
	// Init는 자동으로 호출된다.
	CPlayer* pPlayer = CObj::CreateObj<CPlayer>
		("Player", pLayer);

	/* 이제 레이어에 플레이어가 들어가서 필요 없으니 지운다. */
	/* 지역 변수라 다른 곳에서 참조가 안 되니  */
	SAFE_RELEASE(pPlayer);

	/* 적 생성 */
	CMushroom* pMushroom = CObj::CreateObj<CMushroom>
		("Mushroom", pLayer);
	SAFE_RELEASE(pMushroom);

	return true;
}
