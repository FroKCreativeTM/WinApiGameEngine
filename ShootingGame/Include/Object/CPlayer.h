#pragma once

#include "CMoveObj.h"

class CPlayer :
    public CMoveObj
{
private : 
	friend class CObj;

private : 
	list<class CBullet*> m_BulletList;
	int m_nSkillCoolTime;				// ½ºÅ³ ÄðÅ¸ÀÓ

private :
	CPlayer();
	CPlayer(const CPlayer& ref);
    ~CPlayer();

private : 
	void Shot();
	void Skill();

public:
	virtual bool Init();		
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

