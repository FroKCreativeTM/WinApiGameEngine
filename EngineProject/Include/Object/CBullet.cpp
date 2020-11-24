#include "CBullet.h"

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

	SetTexture("Bullet", L"golf.bmp");

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