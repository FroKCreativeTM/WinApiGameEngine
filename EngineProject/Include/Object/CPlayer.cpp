#include "CPlayer.h"
#include "../Core/CInput.h"
#include "CBullet.h"

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

    if (KEYPRESS("MoveFront"))
    {
        MoveYFromSpeed(fDeltaTime, MD_BACK);
    }
    if (KEYPRESS("MoveBack"))
    {
        MoveYFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (KEYPRESS("MoveLeft"))
    {
        MoveXFromSpeed(fDeltaTime, MD_BACK);
    }
    if (KEYPRESS("MoveRight"))
    {
        MoveXFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (KEYPRESS("Fire"))
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

    // CS_LEAVE : 빠지나갈때 삭제
    pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

    POSITION tPos;
    tPos.x = GetRight() 
        + pBullet->GetSize().x * pBullet->GetPivot().x;
    tPos.y = GetCenter().y;

    // 위에서 구한 좌표를 적용한다.
    pBullet->SetPos(tPos);

    SAFE_RELEASE(pBullet);
}
