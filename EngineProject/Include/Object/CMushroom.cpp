#include "CMushroom.h"
#include "../CCore.h"
#include "../Collider/CRectCollider.h"

// 2초에 한 번씩 발사한다.
CMushroom::CMushroom() : 
	m_fFireTime(0.f),
	m_fFireLimitTime(1.13f)
{
}

CMushroom::CMushroom(const CMushroom& mushroom) : 
	CMoveObj(mushroom)
{
	this->m_eDir = mushroom.m_eDir;
	this->m_fFireTime = mushroom.m_fFireTime;
	this->m_fFireLimitTime = mushroom.m_fFireLimitTime;
}

CMushroom::~CMushroom()
{
}

bool CMushroom::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(300.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Mushroom", L"neil.bmp");

	m_eDir = MD_FRONT;

	CRectCollider* pRC = AddCollider<CRectCollider>("Mushroom");
	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	SAFE_RELEASE(pRC);

	return true;
}

int CMushroom::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	// 멋대로 움직이게 만들어본다.
	MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.y + m_tSize.y >= GET_RESOLUTION.nHeight)
	{
		m_tPos.y = GET_RESOLUTION.nHeight - m_tSize.y;
		m_eDir = MD_BACK;
	}

	else if (m_tPos.y + m_tSize.y <= 0)
	{
		m_tPos.y = 0.f;
		m_eDir = MD_FRONT;
	}

	m_fFireTime += fDeltaTime;

	// 2초가 지났다면 
	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime -= m_fFireLimitTime;
		Fire();
	}

	return 0;
}

int CMushroom::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMushroom::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMushroom::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

CMushroom* CMushroom::Clone()
{
	return new CMushroom(*this);
}

void CMushroom::Fire()
{
	CObj* pBullet =
		CObj::CreateCloneObj("Bullet", "EnemyBullet", m_pLayer);

	((CMoveObj*)pBullet)->SetAngle(PI);

	float x = GetLeft() - 
		pBullet->GetSize().x * (1.f - pBullet->GetPivot().x);
	float y = GetCenter().y;

	pBullet->SetPos(x, y);

	SAFE_RELEASE(pBullet);
}
