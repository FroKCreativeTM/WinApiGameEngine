#include "CInGameScene.h"
#include "../Object/CPlayer.h"
#include "../Object/CMushroom.h"
#include "../Object/CBullet.h"
#include "../Object/CStage.h"
#include "CLayer.h"
#include "../Core/CCamera.h"
#include "../Collider/CPixelCollider.h"

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

	/* 카메라 세팅을 한다. */
	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.8f, 0.3f);

	/* 이제 레이어에 플레이어가 들어가서 필요 없으니 지운다. */
	/* 지역 변수라 다른 곳에서 참조가 안 되니  */
	SAFE_RELEASE(pPlayer);

	/* 적 생성 */
	CMushroom* pMushroom = CObj::CreateObj<CMushroom>
		("Mushroom", pLayer);
	SAFE_RELEASE(pMushroom);

	/* 총알 프로토타입 */
	CBullet* pBullet = CScene::CreatePrototype<CBullet>
		("Bullet");
	pBullet->SetSize(50.f, 50.f);
	SAFE_RELEASE(pBullet);

	/* 스테이지(백그라운드) 생성 */
	// 레이어를 약간 다른 것을 쓸 것이다.
	CLayer* pStageLayer = FindLayer("Stage");
	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	// 스테이지 콜리더 설정
	CPixelCollider* pPixel = pStage->AddCollider<CPixelCollider>("StageCollder");
	pPixel->SetPixelInfo("Background.bmp");

	SAFE_RELEASE(pPixel);
	SAFE_RELEASE(pStage);

	return true;
}
