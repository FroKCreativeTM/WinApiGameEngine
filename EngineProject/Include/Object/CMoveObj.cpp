#include "CMoveObj.h"

CMoveObj::CMoveObj() : 
	m_fAngle(0.f),
	m_fSpeed(100.f)
{
}

// 부모의 복사 생성자 먼저!
CMoveObj::CMoveObj(const CMoveObj& ref) : 
	CObj(ref)
{
	this->m_fAngle = ref.m_fAngle;
	this->m_fSpeed = ref.m_fSpeed;
}

CMoveObj::~CMoveObj()
{
}


void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;
}

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove;
}

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;
}

void CMoveObj::MoveX(float x)
{
	m_tPos.x += x;
}

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.x += m_fSpeed * fDeltaTime * eDir;
}

void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x* fDeltaTime;
}

void CMoveObj::MoveY(float y)
{
	m_tPos.y += y;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;
}

void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
}

void CMoveObj::MoveAngle()
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed;
}

void CMoveObj::MoveAngle(float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fDeltaTime;
}

void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);
	return 0;
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
}
