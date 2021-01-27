#include "CTile.h"
#include "../Resources/CResourceManager.h"
#include "../Resources/CTexture.h"
#include "../Core/CCamera.h"

CTile::CTile() : 
    m_eOption(TO_NONE)
{
    // ����Ʈ �ؽ�ó ����
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

	// ī�޶� ��ġ�� ���� ��ũ���� �ȴ�.
	tPos -= GET_SINGLE(CCamera)->GetPos();

	// �ػ󵵸� ���´�.
	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetClientResolution();
	// Ŭ���̾�Ʈ â �ȿ� �ֳ��� �����Ѵ�.
	bool isInClient = true;

	// ����ϰ����ϴ� right�� 0���� ũ��.
	if (tPos.x + m_tSize.x < 0)
	{
		isInClient = false;
	}
	// left�� ���� Ŭ���̾�Ʈ ������ ���̶��
	else if (tPos.x > tClientRS.nWidth)
	{
		isInClient = false;
	}
	// ����ϰ����ϴ� bottom�� 0���� ũ��.
	else if (tPos.y + m_tSize.y < 0)
	{
		isInClient = false;
	}
	// top�� ���� Ŭ���̾�Ʈ �Ʒ��� �ִٸ�
	else if (tPos.y > tClientRS.nHeight)
	{
		isInClient = false;
	}

	// �ؽ�ó�� �ִ� ���
	if (m_pTexture && isInClient)
	{
		POSITION tImagePos; // (0,0)

		tImagePos += m_tImageOffset;

		// �÷�Ű Ȱ��ȭ ���ο� ���� �ٸ���.
		if (m_pOptionTex->GetColorKeyEnable())
		{
			// ���ڰ� 
			TransparentBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pOptionTex->GetDC(),
				tImagePos.x, tImagePos.y,		// ���� ��ġ
				m_tSize.x, m_tSize.y, 	// ũ��
				m_pOptionTex->GetColorKey());
		}
		else
		{
			// ȭ�鿡 DC�� ���ִ� ������ ������ִ� �Լ��̴�.
			// 1. DC
			// 2~3. ��� ����Ұ��ΰ�
			// 4~5. ȭ��� �󸶳� ũ�� ����ҷ�
			// 6. source�� DC
			// 7~8. �̹����� ������ ���?
			// 9. 6�� ���ڿ� ����
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

    // �ٲٱ� ���� ���� �����ش�.
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
