#include "CMouse.h"
#include "../CCore.h"
#include "../Collider/CPointCollider.h"

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

	// 스크린 좌표 기준으로 나온다.
	GetCursorPos(&pt);
	// 클라이언트 좌표로 바꾼다.
	ScreenToClient(GET_WINDOWHANDLE, &pt);

	ShowCursor(FALSE);

	m_tPos = pt;

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

	// 스크린 좌표 기준으로 나온다.
	GetCursorPos(&pt);
	// 클라이언트 좌표로 바꾼다.
	ScreenToClient(GET_WINDOWHANDLE, &pt);

	// 이전 위치부터 현재 위치까지 얼마나 왔는가.
	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y;

	m_tPos = pt;

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
