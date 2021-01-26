#include "CMouse.h"
#include "../CCore.h"
#include "../Collider/CPointCollider.h"
#include "../Core/CCamera.h"

CMouse::CMouse()
{
}

CMouse::CMouse(const CMouse& ref) : 
	CUI(ref)
{
}

CMouse::~CMouse()
{
}

bool CMouse::Init()
{
	POINT pt;
	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

	// ��ũ�� ��ǥ �������� ���´�.
	GetCursorPos(&pt);
	// Ŭ���̾�Ʈ ��ǥ�� �ٲ۴�.
	ScreenToClient(GET_WINDOWHANDLE, &pt);

	ShowCursor(FALSE);

	// Ŭ���̾�Ʈ ��ǥ
	m_tPos = pt;
	// ���� ��ǥ
	m_tWorldPos = m_tPos + tCamPos;

	CPointCollider* pCol = AddCollider<CPointCollider>("Mouse");
	SAFE_RELEASE(pCol);

	return true;
}

void CMouse::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CMouse::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);

	POINT pt;
	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

	// ��ũ�� ��ǥ �������� ���´�.
	GetCursorPos(&pt);
	// Ŭ���̾�Ʈ ��ǥ�� �ٲ۴�.
	ScreenToClient(GET_WINDOWHANDLE, &pt);

	// ���� ��ġ���� ���� ��ġ���� �󸶳� �Դ°�.
	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y;

	m_tPos = pt;
	m_tWorldPos = m_tPos + tCamPos;

	return 0;
}

int CMouse::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CMouse::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CMouse::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CMouse* CMouse::Clone()
{
	return new CMouse(*this);
}

void CMouse::Hit(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
}
