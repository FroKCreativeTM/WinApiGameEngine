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
    SetPos(100.f, 100.f);
    SetSize(100.f, 100.f);
    SetSpeed(400.f);
    SetPivot(0.5f, 0.5f);

    SetTexture("Player", L"todd.bmp");

    return true;
}

void CPlayer::Input(float fDeltaTime)
{
    // 부모의 함수를 호출해준다.
    CMoveObj::Input(fDeltaTime);

    if (GetAsyncKeyState('W') & 0x8000)
    {
        MoveYFromSpeed(fDeltaTime, MD_BACK);
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        MoveYFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        MoveXFromSpeed(fDeltaTime, MD_BACK);
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        MoveXFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        Fire();
    }
}

int CPlayer::Update(float fDeltaTime)
{
    // 부모의 함수를 호출해준다.
    CMoveObj::Update(fDeltaTime);
    return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
    // 부모의 함수를 호출해준다.
    CMoveObj::LateUpdate(fDeltaTime);

    return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
    // 부모의 함수를 호출해준다.
    CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
    // 부모의 함수를 호출해준다.
    CMoveObj::Render(hDC, fDeltaTime);
    // Rectangle(hDC, m_tPos.x, m_tPos.y,
    //     m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Fire()
{
    CObj* pBullet = 
        CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

    // 30퍼 정도 간다고 가정하자.
    // size * 0.3
    // 0.3은 어떻게? 지정하는 것마다 다르게 대응하게
    // 1에서 빼버려!
    // 오른쪽 가운데를 구한다.
    POSITION tPos;
    tPos.x = m_tPos.x + (1.f - m_tPivot.x) * m_tSize.x;
    tPos.y = m_tPos.y + (0.5f - m_tPivot.y) * m_tSize.y;

    // 위에서 구한 좌표를 적용한다.
    pBullet->SetPos(tPos.x, tPos.y - pBullet->GetSize().y / 2.f);

    SAFE_RELEASE(pBullet);
}
