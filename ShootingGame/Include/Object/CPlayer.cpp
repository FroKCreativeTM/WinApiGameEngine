#include "CPlayer.h"
#include "CBullet.h"
#include "../CCore.h"

CPlayer::CPlayer() : 
    m_nSkillCoolTime(0)
{

}

CPlayer::CPlayer(const CPlayer& ref) : 
    CMoveObj(ref)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Shot()
{
    /*
    RECTANGLE bullet;

    bullet.left = (this->GetPos().x + this->GetSize().x);
    bullet.right = bullet.left + 50.f;
    bullet.top = this->GetPos().y + (this->GetSize().y / 4.f);
    bullet.bottom = bullet.top + 50.f;

    m_BulletList.push_back(bullet);
    */


}

void CPlayer::Skill()
{
    /* 다량의 총알을 발사한다. */

    if (m_nSkillCoolTime == 0)
    {   // 만약 스킬을 쓸 수 있는 경우 경우

    }
    else if((m_nSkillCoolTime & 0b00000001))
    {
        // 이미 사용했다면.
        return;
    }
}

bool CPlayer::Init()
{
    SetPos(100.f, 100.f);
    SetSize(100.f, 100.f);

    SetSpeed(400.f);

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
        // 총을 쏜다.
        Shot();
    }
    if (GetAsyncKeyState('R') & 0x8000)
    {
        // 총을 쏜다.
        Skill();
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

    /*
    // 만약 탄약이 들었다면?
    if (m_BulletList.size() != 0)
    {
        list<RECTANGLE>::iterator iter;
        list<RECTANGLE>::iterator iterEnd = m_BulletList.end();

        for (iter = m_BulletList.begin(); iter != iterEnd;)
        {
            (*iter).left += fDeltaTime * 600.f;
            (*iter).right += fDeltaTime * 600.f;

            if ((*iter).left > GET_RESOLUTION.nWidth)
            {
                iter = m_BulletList.erase(iter);
                iterEnd = m_BulletList.end();
            }
            else
                ++iter;
        }
    }
    */

    Rectangle(hDC, m_tPos.x, m_tPos.y,
        m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);   

    /*
    if (m_BulletList.size() != 0)
    {
        list<RECTANGLE>::iterator iter;
        list<RECTANGLE>::iterator iterEnd = m_BulletList.end();

        for (iter = m_BulletList.begin(); iter != iterEnd; ++iter)
        {
            Ellipse(hDC, (*iter).left, (*iter).top, 
                (*iter).right, (*iter).bottom);
        }
    }
    */
}
