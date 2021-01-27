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
	// ���� ����
	// @ �Ķ����
	// int nNumX, int nNumY		- Ÿ�� ����
	// int nSizeX, int nSizeY	- �� �ؽ�ó�� ������
	void CreateTile(int nNumX, int nNumY, int nSizeX, int nSizeY,
		const string& strKey = "", const wchar_t * pFileName = nullptr,
		const string& strPathKey = TEXTURE_PATH);

	void ChangeTileTex(const POSITION& tPos, class CTexture* pTexture);
	void ChangeTileOption(const POSITION& tPos, TILE_OPTION eOption);
	int GetTileIndex(const POSITION& tPos);
	int GetTileIndex(float x, float y);

private:
	// Ÿ���� ���������� ���� ���ϴϱ� ���ͷ�
	vector<class CTile*>		m_vecTile;
	int							m_nTileNumX;		// ���� ����
	int							m_nTileNumY;		// ���� ����
	int							m_nTileSizeX;		// ���� ������
	int							m_nTileSizeY;		// ���� ������

private : 
	friend class CObj;
	friend class CScene;

private : 
	CStage();
	CStage(const CStage& pStage);
	~CStage();
};

