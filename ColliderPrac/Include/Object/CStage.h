#pragma once

#include "CStaticObj.h"
 
class CStage :
	public CStaticObj
{
private : 
	friend class CObj;
	friend class CScene;

private : 
	CStage();
	CStage(const CStage& pStage);
	~CStage();

public :
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStage* Clone();
};

