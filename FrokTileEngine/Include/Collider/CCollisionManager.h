#pragma once

#include "../Game.h"

// �浹 �������Դϴ�.
class CCollisionManager
{
	DECLARE_SINGLE(CCollisionManager)

public : 
	void AddObject(class CObj* pObj);
	void Collision(float fDeltaTime);

	// �� ������Ʈ�� �浹 ó���� ����Ѵ�.
	bool Collision(CObj* pSrc, CObj* pDst, float fDeltaTime);

	// �� ��ȭ ����� ��츦 ���� �浹ü�� ��� �����ش�.
	void ClearScene();

private : 
	// �浹ü�� �ִ� ������Ʈ��� ����Ʈ�� ä��� ���
	list<class CObj*> m_CollisionList;
};

