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
	// ¥�� �Ѿ��� ��� ����� ���� ��������
	// �� �κи� ���ָ� �ȴ�.
	SetPos(fObjX, fObjY);
	SetSize(50.f, 50.f);
	SetSpeed(300.f);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	// ���� ���� ��� ���̶��, �÷��̾����� �� �ʿ䰡 �ִ�.

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