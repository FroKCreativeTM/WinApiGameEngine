#include "CMushroom.h"
#include "../CCore.h"

CMushroom::CMushroom()
{
}

CMushroom::CMushroom(const CMushroom& mushroom) : 
	CMoveObj(mushroom),
	m_eDir(mushroom.m_eDir)
{
}

CMushroom::~CMushroom()
{
}

bool CMushroom::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);

	SetSpeed(300.f);

	m_eDir = MD_FRONT;

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
	Rectangle(hDC, m_tPos.x, m_tPos.y,
		m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}
