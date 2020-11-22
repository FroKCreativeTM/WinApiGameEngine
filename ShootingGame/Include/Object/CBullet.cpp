#include "CBullet.h"

CBullet::CBullet()
{

}

CBullet::CBullet(const CBullet& bullet) : 
	CMoveObj(bullet)
{

}

CBullet::~CBullet()
{
}

bool CBullet::Init(float fObjX, float fObjY)
{
	// 짜피 총알은 쏘는 사람에 의해 정해지니
	// 그 부분만 해주면 된다.
	SetPos(fObjX, fObjY);
	SetSize(50.f, 50.f);
	SetSpeed(300.f);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	// 만약 적이 쏘는 것이라면, 플레이어한테 갈 필요가 있다.

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
	Ellipse(hDC, m_tPos.x, m_tPos.y,
		m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}