#include "CZako.h"
#include "../CCore.h"

CZako::CZako()
{
}

CZako::CZako(const CZako& zako) :
	CMoveObj(zako),
	m_eDir(zako.m_eDir)
{
}

CZako::~CZako()
{
}

bool CZako::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);

	SetSpeed(300.f);

	m_eDir = MD_FRONT;

	return true;
}

int CZako::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	// 멋대로 움직이게 만들어본다.
	MoveXFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.x + m_tSize.x >= GET_RESOLUTION.nWidth)
	{
		m_tPos.x = GET_RESOLUTION.nWidth- m_tSize.x;
		m_eDir = MD_BACK;
	}

	else if (m_tPos.x + m_tSize.x <= 0)
	{
		m_tPos.x = 0.f;
		m_eDir = MD_FRONT;
	}

	return 0;
}

int CZako::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CZako::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CZako::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
	Rectangle(hDC, m_tPos.x, m_tPos.y,
		m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}
