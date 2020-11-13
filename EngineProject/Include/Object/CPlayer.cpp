#include "CPlayer.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& ref) : 
    CMoveObj(ref)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    return false;
}

void CPlayer::Input(float fDeltaTime)
{
}

int CPlayer::Update(float fDeltaTime)
{
    return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
    return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
    Rectangle(hDC, m_tPos.x, m_tPos.y,
        m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}
