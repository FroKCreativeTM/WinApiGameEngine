#pragma once

#include "CStaticObj.h"
 
class CStage :
	public CStaticObj
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStage* Clone();	
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public : 
	// 격자 생성
	// @ 파라미터
	// int nNumX, int nNumY		- 타일 갯수
	// int nSizeX, int nSizeY	- 각 텍스처의 사이즈
	void CreateTile(int nNumX, int nNumY, int nSizeX, int nSizeY,
		const string& strKey = "", const wchar_t * pFileName = nullptr,
		const string& strPathKey = TEXTURE_PATH);

	void ChangeTileTex(const POSITION& tPos, class CTexture* pTexture);
	void ChangeTileOption(const POSITION& tPos, TILE_OPTION eOption);
	int GetTileIndex(const POSITION& tPos);
	int GetTileIndex(float x, float y);

private:
	// 타일은 유동적으로 수가 변하니까 벡터로
	vector<class CTile*>		m_vecTile;
	int							m_nTileNumX;		// 가로 갯수
	int							m_nTileNumY;		// 세로 갯수
	int							m_nTileSizeX;		// 가로 사이즈
	int							m_nTileSizeY;		// 세로 사이즈

private : 
	friend class CObj;
	friend class CScene;

private : 
	CStage();
	CStage(const CStage& pStage);
	~CStage();
};

