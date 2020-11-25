#include "CPlayer.h"
#include "../Core/CInput.h"
#include "../Core/CCamera.h"

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
    if (KEYPRESS("Skill1"))
    {
        Skill1();
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

void CPlayer::Skill1()
{
    // 스킬은 카메라의 타켓이 플레이어인 경우에만 처리되도록 설정한다.
    if (GET_SINGLE(CCamera)->GetTarget()->GetTag() == "Player")
    {
        CObj* pBullet =
            CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

        POSITION tPos;
        tPos.x = GetRight()
            + pBullet->GetSize().x * pBullet->GetPivot().x;
        tPos.y = GetCenter().y;

        // 위에서 구한 좌표를 적용한다.
        pBullet->SetPos(tPos);

        // 카메라의 타겟을 탄알로 만들고 레퍼런스 카운터 증가
        GET_SINGLE(CCamera)->SetTarget(pBullet);
        GET_SINGLE(CCamera)->SetPivot(0.5f, 0.5f);
        pBullet->AddRef();

        SAFE_RELEASE(pBullet);
    }
}
