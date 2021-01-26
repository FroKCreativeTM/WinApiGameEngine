#pragma once

#include "CScene.h"


class CMapEditScene : 
	public CScene
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

private : 
	TILE_EDIT_MODE				m_eTem;
	TILE_OPTION					m_eEditOption;
	vector<class CTexture*>		m_vecTileTexture;
	int							m_nEditTileTex;
	class CStage*				m_pStage;

private:
	friend class CSceneManager; // 씬 매니저만 이 클래스에 접근 가능하다.

private:
	CMapEditScene();
	~CMapEditScene();
};

