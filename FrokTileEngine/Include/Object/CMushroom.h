#pragma once
#include "CMoveObj.h"
class CMushroom :
    public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;

private:
	CMushroom();
	CMushroom(const CMushroom& mushroom);
	~CMushroom();

private : 
	MOVE_DIR		m_eDir;
	float			m_fFireTime;
	float			m_fFireLimitTime;

public:
	virtual bool Init();
	// ���̴ϱ� ��������� �Է��� �ʿ����.
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMushroom* Clone();

public : 
	void CollisionBullet(class CCollider* pSrc,
		class CCollider* pDst, float fDeltaTime);

private : 
	void Fire();
};

