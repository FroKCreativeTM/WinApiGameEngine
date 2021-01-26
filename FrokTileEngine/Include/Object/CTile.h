#pragma once
#include "CStaticObj.h"
class CTile :
	public CStaticObj
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CTile* Clone();

public : 
	void SetTileOption(TILE_OPTION eType);

	TILE_OPTION GetTileOption() const
	{
		return m_eOption;
	}

private:
	TILE_OPTION				m_eOption;
	class CTexture*			m_pOptionTex;

private:
	friend class CObj;
	friend class CStage;		// ���������� �̸� �����Ѵ�.

private:
	CTile();
	CTile(const CTile& pTile);
	~CTile();
};

