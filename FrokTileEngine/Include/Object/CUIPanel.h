#pragma once
#include "CUI.h"
class CUIPanel :
    public CUI
{
private:
	friend class CObj;
	friend class CScene;

private:
	CUIPanel();
	CUIPanel(const CUIPanel& ref);
	~CUIPanel();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUIPanel* Clone();
};

