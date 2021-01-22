#include "CPlayer.h"
#include "../Core/CInput.h"
#include "CBullet.h"
#include "../Collider/CRectCollider.h"
#include "../Core/CCamera.h"
#include "../Animation/CAnimation.h"

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
    SetSize(108.75f, 121.f);
    SetImageOffset(108.75f, 121.f);
    SetSpeed(400.f);
    SetPivot(0.5f, 0.5f);

    SetTexture("Player", L"Player.bmp");
    SetColorKey(255, 255, 255); // 흰색

    CRectCollider* pRC = AddCollider<CRectCollider>("PlayerBody");
    pRC->SetRect(-54.375f, -60.5f, 54.375f, 60.5f);
    pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
    pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

    m_nHP = 100;

    SetPhysics(true);
    SetForce(200.f);

    CAnimation * pAnima = CreateAnimation("PlayerAnimation");

    AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP,
        0.5f,
        8, 1, // 8장에 1줄짜리
        0, 0,
        8, 1,
        0.f,
        "PlayerIdleLeft", L"Player/Idle/Left/PlayerIdleLeft.bmp");
    SetAnimationClipColorKey("IdleLeft", 255, 0, 255);

    AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN,
        0.5f,
        4, 1, // 4장에 1줄짜리
        0, 0,
        4, 1,
        0.f,
        "PlayerRunLeft", L"Player/Run/Left/PlayerRunLeft.bmp");
    SetAnimationClipColorKey("RunLeft", 255, 0, 255);

    AddAnimationClip("AttackLeft", AT_ATLAS, AO_ONCE_RETURN,
        0.5f,
        4, 1, // 4장에 1줄짜리
        0, 0,
        4, 1,
        0.f,
        "PlayerAttackLeft", L"Player/Attack/Left/PlayerAttackLeft.bmp");
    SetAnimationClipColorKey("AttackLeft", 255, 0, 255);

    AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP,
        0.5f,
        8, 1, // 8장에 1줄짜리
        0, 0,
        8, 1,
        0.f,
        "PlayerIdleRight", L"Player/Idle/Right/PlayerIdleRight.bmp");
    SetAnimationClipColorKey("IdleRight", 255, 0, 255);

    AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN,
        0.5f,
        4, 1, // 4장에 1줄짜리
        0, 0,
        4, 1,
        0.f,
        "PlayerRunRight", L"Player/Run/Right/PlayerRunRight.bmp");
    SetAnimationClipColorKey("RunRight", 255, 0, 255);

    AddAnimationClip("AttackRight", AT_ATLAS, AO_ONCE_RETURN,
        0.5f,
        4, 1, // 4장에 1줄짜리
        0, 0,
        4, 1,
        0.f,
        "PlayerAttackRight", L"Player/Attack/Right/PlayerAttackRight.bmp");
    SetAnimationClipColorKey("AttackRight", 255, 0, 255);

    SAFE_RELEASE(pAnima);

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
        m_isLeft = true;
        MoveXFromSpeed(fDeltaTime, MD_BACK);
        m_pAnimation->ChangeClip("RunLeft");
    }
    if (KEYPRESS("MoveRight"))
    {
        m_isLeft = false;
        MoveXFromSpeed(fDeltaTime, MD_FRONT);
        m_pAnimation->ChangeClip("RunRight");
    }
    if (KEYPRESS("Jump"))
    {
        Jump();
    }
    if (KEYPRESS("Fire"))
    {
        Fire();
        m_pAnimation->ChangeClip("AttackRight");
    }
}

int CPlayer::Update(float fDeltaTime)
{
    // 부모의 함수를 호출해준다.
    CMoveObj::Update(fDeltaTime);

    // 공격이 끝난 경우
    if (m_isAttack && m_pAnimation->GetMotionEnd())
    {
        m_isAttack = false;
    }

    if (!m_isMove && !m_isAttack)
    {
        if (m_isLeft)
        {
            m_pAnimation->ReturnClip();
        }
        else
        {
            m_pAnimation->SetCurrentClip("IdleRight");
        }
    }

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

    wchar_t strHP[32] = {};
    wsprintf(strHP, L"HP : %d", m_nHP);

    POSITION tPos = m_tPos - m_tSize * m_tPivot;
    tPos -= GET_SINGLE(CCamera)->GetPos();

    TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP));
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Hit(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetObj()->GetTag() == "EnemyBullet") 
    {
        m_nHP -= 5;
    }
    else if (pDst->GetTag() == "StageCollder")
    {
        ClearGravity();
        JumpEnd();
        m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
    }
}

// 중력이 멈춘 경우처럼 충돌이 지속적으로 일어날 때
// 이를 이용해서 그 상태로 냅둔다. (유한 상태머신)
void CPlayer::HitStay(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetTag() == "StageCollder")
    {
        ClearGravity();
        JumpEnd();
        m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;

    }
}

void CPlayer::Fire()
{
    m_isAttack = true;

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
