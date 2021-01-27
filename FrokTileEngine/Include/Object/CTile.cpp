#include "CTile.h"
#include "../Resources/CResourceManager.h"
#include "../Resources/CTexture.h"
#include "../Core/CCamera.h"

CTile::CTile() : 
    m_eOption(TO_NONE)
{
    // 디폴트 텍스처 지정
    m_pOptionTex = GET_SINGLE(CResourceManager)->FindTexture("TileNone");
}

CTile::CTile(const CTile& pTile) : 
    CStaticObj(pTile)
{
    m_eOption = pTile.m_eOption;
    m_pOptionTex = pTile.m_pOptionTex;

    if (m_pOptionTex)
    {
        m_pOptionTex->AddRef();
    }
}

CTile::~CTile()
{
    SAFE_RELEASE(m_pOptionTex);
}

bool CTile::Init()
{
    return true;
}

void CTile::Input(float fDeltaTime)
{
    CStaticObj::Input(fDeltaTime);
}

int CTile::Update(float fDeltaTime)
{
    CStaticObj::Update(fDeltaTime);
    return 0;
}

int CTile::LateUpdate(float fDeltaTime)
{
    CStaticObj::LateUpdate(fDeltaTime);
    return 0;
}

void CTile::Collision(float fDeltaTime)
{
    CStaticObj::Collision(fDeltaTime);
}

void CTile::Render(HDC hDC, float fDeltaTime)
{
    CStaticObj::Render(hDC, fDeltaTime);

	POSITION tPos = m_tPos - m_tSize * m_tPivot;

	// 카메라 위치를 빼야 스크롤이 된다.
	tPos -= GET_SINGLE(CCamera)->GetPos();

	// 해상도를 들고온다.
	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetClientResolution();
	// 클라이언트 창 안에 있나를 선별한다.
	bool isInClient = true;

	// 출력하고자하는 right가 0보다 크다.
	if (tPos.x + m_tSize.x < 0)
	{
		isInClient = false;
	}
	// left가 만약 클라이언트 오른쪽 밖이라면
	else if (tPos.x > tClientRS.nWidth)
	{
		isInClient = false;
	}
	// 출력하고자하는 bottom이 0보다 크다.
	else if (tPos.y + m_tSize.y < 0)
	{
		isInClient = false;
	}
	// top이 만약 클라이언트 아래에 있다면
	else if (tPos.y > tClientRS.nHeight)
	{
		isInClient = false;
	}

	// 텍스처가 있는 경우
	if (m_pTexture && isInClient)
	{
		POSITION tImagePos; // (0,0)

		tImagePos += m_tImageOffset;

		// 컬러키 활성화 여부에 따라 다르다.
		if (m_pOptionTex->GetColorKeyEnable())
		{
			// 인자가 
			TransparentBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pOptionTex->GetDC(),
				tImagePos.x, tImagePos.y,		// 시작 위치
				m_tSize.x, m_tSize.y, 	// 크기
				m_pOptionTex->GetColorKey());
		}
		else
		{
			// 화면에 DC에 들어가있는 도구를 출력해주는 함수이다.
			// 1. DC
			// 2~3. 어디에 출력할것인가
			// 4~5. 화면상 얼마나 크게 출력할래
			// 6. source의 DC
			// 7~8. 이미지의 어디부터 출력?
			// 9. 6번 인자에 복사
			BitBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pOptionTex->GetDC(),
				tImagePos.x, tImagePos.y,
				SRCCOPY);
		}
	}
}

CTile* CTile::Clone()
{
    return new CTile(*this);
}


void CTile::Save(FILE* pFile)
{
	CStaticObj::Save(pFile);

	fwrite(&m_eOption, 4, 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	CStaticObj::Load(pFile);

	fread(&m_eOption, 4, 1, pFile);
}

void CTile::SetTileOption(TILE_OPTION eType)
{
    m_eOption = eType;

    // 바꾸기 전에 먼저 지워준다.
    SAFE_RELEASE(m_pOptionTex);

    switch (m_eOption)
    {
    case TO_NONE:
        m_pOptionTex = GET_SINGLE(CResourceManager)->FindTexture("TileNone");
        break;
    case TO_NOMOVE:
        m_pOptionTex = GET_SINGLE(CResourceManager)->FindTexture("TileNoMove");
        break;
    }
}
