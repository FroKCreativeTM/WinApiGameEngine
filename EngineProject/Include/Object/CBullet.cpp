#include "CBullet.h"
#include "../Resources/CTexture.h"
#include "../Collider/CRectCollider.h"

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

	CRectCollider* pRC = AddCollider<CRectCollider>("Bullet");
	pRC->SetRect(-25.f, -25.f, 25.f, 25.f);
	SAFE_RELEASE(pRC);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveAngle(fDeltaTime);
	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fLimitDist)
	{
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