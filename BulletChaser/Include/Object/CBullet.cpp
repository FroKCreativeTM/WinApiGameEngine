#include "CBullet.h"
#include "../Resources/CTexture.h"
#include "../Core/CCamera.h"

CBullet::CBullet() :
	m_fDist(0.f),
	m_fLimitDist(500.f)
{
}

CBullet::CBullet(const CBullet& bullet) : 
	CMoveObj(bullet)
{
	this->m_fDist = bullet.m_fDist;
	this->m_fLimitDist = bullet.m_fLimitDist;
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	SetSpeed(500.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Bullet", L"golf.bmp");

	m_pTexture->SetColorKey(0, 248, 0);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveAngle(fDeltaTime);
	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fLimitDist)
	{
		if (GET_SINGLE(CCamera)->GetTarget()->GetTag()
			== "PlayerBullet")
		{
			// 카메라의 타겟을 다시 플레이어로 바꿔주고, 
			// 레퍼런스 카운터 감소
			GET_SINGLE(CCamera)->SetTarget(FindObj("Player"));
			GET_SINGLE(CCamera)->SetPivot(0.8f, 0.3f);
			this->Release();
		}

		Die();		
	}

	return 0;
}

int CBullet::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBullet::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CBullet::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}