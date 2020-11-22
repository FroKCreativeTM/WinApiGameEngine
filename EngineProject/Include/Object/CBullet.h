#pragma once
#include "CMoveObj.h"
class CBullet :
    public CMoveObj
{
public : 
	void SetBulletDist(float fDist)
	{
		this->m_fLimitDist = fDist;
	}

private:
	friend class CObj;
	friend class CScene;

private:
	CBullet();
	CBullet(const CBullet& bullet);
	~CBullet();

public:
	virtual bool Init();
	// �Ѿ��̴ϱ� ��������� �Է��� �ʿ����.
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CBullet* Clone();

private:
	float m_fDist;		// �Ÿ�
	float m_fLimitDist;	// �����Ÿ�
};


