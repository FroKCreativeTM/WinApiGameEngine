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
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Fire()
{
    CObj* pBullet = 
        CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

    POSITION tPos;
    tPos.x = GetRight() 
        + pBullet->GetSize().x * pBullet->GetPivot().x;
    tPos.y = GetCenter().y;

    // 위에서 구한 좌표를 적용한다.
    pBullet->SetPos(tPos);

    SAFE_RELEASE(pBullet);
}
