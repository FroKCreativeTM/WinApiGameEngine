#include "CStage.h"
#include "../Resources/CTexture.h"
#include "../CCore.h"
#include "../Core/CCamera.h"
#include "CTile.h"
#include "../Scene/CLayer.h"
#include "../Core/CPathManager.h"

CStage::CStage()
{
}

CStage::CStage(const CStage& pStage) : 
	CStaticObj(pStage)
{
	m_vecTile.clear();

	for (size_t i = 0; i < pStage.m_vecTile.size(); i++)
	{
		m_vecTile.push_back(pStage.m_vecTile[i]->Clone());
	}
}

CStage::~CStage()
{
	// 타일 정보를 모두 날린다.
	Safe_Release_VecList(m_vecTile);
}

bool CStage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1580.f, 740.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage1", L"Background.bmp");

	return true;
}

void CStage::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hDC, float fDeltaTime)
{
	// CStaticObj::Render(hDC, fDeltaTime);

	// 배경이 있는 경우
	if (m_pTexture)
	{
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();

		// 화면에 DC에 들어가있는 도구를 출력해주는 함수이다.
		// 1. DC
		// 2~3. 어디에 출력할것인가
		// 4~5. 화면상 얼마나 크게 출력할래 (창의 크기만큼!)
		// 6. source의 DC
		// 7~8. 이미지의 어디부터 출력?
		// 9. 6번 인자에 복사
		BitBlt(hDC, tPos.x, tPos.y,
			GET_RESOLUTION.nWidth, GET_RESOLUTION.nHeight,
			m_pTexture->GetDC(),
			tCameraPos.x, tCameraPos.y,
			SRCCOPY);
	}

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Render(hDC, fDeltaTime);
	}

	POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();
	// Grid 그리기
	// 카메라 위치 적용 안 한다면 삐뚤어져서 그려진다.
	for (int i = 1; i < m_nTileNumY; ++i)
	{
		// 가로줄 그리기
		MoveToEx(hDC, 0.f, i * m_nTileSizeY - tCameraPos.y, NULL);	 // 시작점
		LineTo(hDC, m_nTileNumX * m_nTileSizeX, i * m_nTileSizeY - tCameraPos.y);	// 도착점
	}

	// 세로줄 그리기
	for (int i = 1; i < m_nTileNumX; ++i)
	{
		MoveToEx(hDC, i * m_nTileSizeX - tCameraPos.x, 0, NULL);	 // 시작점
		LineTo(hDC, i * m_nTileSizeX - tCameraPos.x, m_nTileNumY * m_nTileSizeY);	// 도착점
	}
}

CStage* CStage::Clone()
{
	return new CStage(*this);
}

void CStage::Save(FILE* pFile)
{
	CStaticObj::Save(pFile);

	// 스테이지 정보 저장
	fwrite(&m_nTileNumX, 4, 1, pFile);
	fwrite(&m_nTileNumY, 4, 1, pFile);
	fwrite(&m_nTileSizeX, 4, 1, pFile);
	fwrite(&m_nTileSizeY, 4, 1, pFile);

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Save(pFile);
	}
}

void CStage::Load(FILE* pFile)
{
	CStaticObj::Load(pFile);
	
	// 스테이지 정보 저장
	fread(&m_nTileNumX, 4, 1, pFile);
	fread(&m_nTileNumY, 4, 1, pFile);
	fread(&m_nTileSizeX, 4, 1, pFile);
	fread(&m_nTileSizeY, 4, 1, pFile);

	Safe_Release_VecList(m_vecTile);

	for (size_t i = 0; i < m_nTileNumX * m_nTileNumY; ++i)
	{
		CTile* pTile = CObj::CreateObj<CTile>("Tile");

		pTile->Load(pFile);

		m_vecTile.push_back(pTile);

		SAFE_RELEASE(pTile);
	}

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Save(pFile);
	}
}

void CStage::CreateTile(int nNumX, int nNumY, int nSizeX, int nSizeY, 
	const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	// 기존에 가진 건 다 날려준다.
	Safe_Release_VecList(m_vecTile);

	m_nTileNumX = nNumX;
	m_nTileNumY = nNumY;
	m_nTileSizeX = nSizeX;
	m_nTileSizeY = nSizeY;

	for (size_t y = 0; y < nNumY; ++y)
	{
		for (size_t x = 0; x < nNumX; ++x)
		{
			CTile* pTile = CObj::CreateObj<CTile>("Tile");

			pTile->SetSize(nSizeX, nSizeY);
			pTile->SetPos(x * nSizeX, y * nSizeY);
			pTile->SetTexture(strKey, pFileName, strPathKey);

			m_vecTile.push_back(pTile);

			SAFE_RELEASE(pTile);
		}
	}

}

void CStage::ChangeTileTex(const POSITION& tPos, CTexture* pTexture)
{
	int nIndex = GetTileIndex(tPos);

	if (nIndex == -1)
	{
		return;
	}

	// 텍스쳐 교체
	m_vecTile[nIndex]->SetTexture(pTexture);
}

void CStage::ChangeTileOption(const POSITION& tPos, TILE_OPTION eOption)
{
	int nIndex = GetTileIndex(tPos);

	if (nIndex == -1)
	{
		return;
	}

	// 타일 옵션 교체
	m_vecTile[nIndex]->SetTileOption(eOption);
}

int CStage::GetTileIndex(const POSITION& tPos)
{
	return GetTileIndex(tPos.x, tPos.y);
}

int CStage::GetTileIndex(float x, float y)
{
	int idxX = (int)x / m_nTileSizeX;
	int idxY = (int)y / m_nTileSizeY;

	if (idxX < 0 || idxX >= m_nTileNumX)
	{
		return -1;
	}

	if (idxY < 0 || idxY >= m_nTileNumY)
	{
		return -1;
	}

	return idxY * m_nTileNumX + idxX;
}
