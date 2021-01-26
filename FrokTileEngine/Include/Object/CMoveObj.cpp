#include "CMoveObj.h"

CMoveObj::CMoveObj() :
	m_fAngle(0.f),
	m_fSpeed(100.f),
	m_isMove(false),
	m_isFalling(true),
	m_fForceOrigin(0.f),
	m_fForce(0.f)
{
}

// 부모의 복사 생성자 먼저!
CMoveObj::CMoveObj(const CMoveObj& ref) : 
	CObj(ref)
{
	this->m_fAngle = ref.m_fAngle;
	this->m_fSpeed = ref.m_fSpeed;

	m_fForceOrigin = ref.m_fForceOrigin;
	m_fForce = 0.f;

	m_isMove = false;
	m_isFalling = false;
}

CMoveObj::~CMoveObj()
{
}


void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	m_isMove = true;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;

	m_isMove = true;
}

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove;

	m_isMove = true;
}

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;

	m_isMove = true;
}

void CMoveObj::MoveX(float x)
{
	m_tPos.x += x;

	m_isMove = true;
}

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.x += m_fSpeed * fDeltaTime * eDir;

	m_isMove = true;
}

void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x* fDeltaTime;

	m_isMove = true;
}

void CMoveObj::MoveY(float y)
{
	m_tPos.y += y;

	m_isMove = true;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;

	m_isMove = true;
}

void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;

	m_isMove = true;
}

void CMoveObj::MoveAngle()
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed;

	m_isMove = true;
}

void CMoveObj::MoveAngle(float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fDeltaTime;

	m_isMove = true;
}

void CMoveObj::Jump()
{
	// 점프 시작
	if (!m_isFalling)
	{
		m_isFalling = true;
		m_fForce = m_fForceOrigin;
	}
}

void CMoveObj::JumpEnd()
{
	// 충돌처리가 된 경우 자동으로 점프를 종료한다.
	m_isFalling = false;
	m_fForce = 0.f;
}

void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	// 물리 적용
	if (m_bPhysics)
	{
		m_fGravityTime += fDeltaTime;
		// 점프 상태일 경우 힘을 감소 시킨다.
		m_fForce -= (GRAVITY * m_fGravityTime * m_fGravityTime);
		m_tPos.y -= m_fForce * fDeltaTime;
	}

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

	m_isMove = false;
}
