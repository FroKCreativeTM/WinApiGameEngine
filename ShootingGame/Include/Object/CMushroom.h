#pragma once
#include "CMoveObj.h"
class CMushroom :
    public CMoveObj
{
private:
	friend class CObj;

private:
	CMushroom();
	CMushroom(const CMushroom& mushroom);
	~CMushroom();

private : 
	MOVE_DIR		m_eDir;

public:
	virtual bool Init();
	// ���̴ϱ� ��������� �Է��� �ʿ����.
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

