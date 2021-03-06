#include "CScene.h"
#include "CLayer.h"
#include "../Object/CObj.h"

unordered_map<string, CObj*> CScene::m_mapPrototype[SC_END];

CScene::CScene()
{
    // 장면이 시작하면 아무 레이어도 없으니
    // 하나는 만들어두자.
    CLayer* pLayer = CreateLayer("Default", 1);
    pLayer = CreateLayer("HUD", INT_MAX - 1);
    pLayer = CreateLayer("UI", INT_MAX); // 맨 뒤에 있단 뜻
    pLayer = CreateLayer("Stage", 0); // 맨 뒤에 있단 뜻
    m_eSceneType = SC_CURRENT;
}

CScene::~CScene()
{
    ErasePrototype(m_eSceneType);
    Safe_Delete_VecList(m_LayerList);
}

// 새로운 레이어 생성
CLayer* CScene::CreateLayer(const string& strTag, int nZOrder)
{
    CLayer* pLayer = new CLayer();

    // 이 장면에 넣을 새로운 레이어 정보를 채운다.
    pLayer->SetTag(strTag);
    pLayer->SetZOrder(nZOrder);
    pLayer->SetScene(this);

    // 리스트에 레이어를 넣는다.
    m_LayerList.push_back(pLayer);

    // 리스트가 2개를 넘으면 Z순서에 맞게 정렬한다.
    // (오름차순)
    if (m_LayerList.size() >= 2)
    {
        // 함수 객체로 bool type의 template 타입의 함수 포인터가 들어간다.
        // 이 때 호출자(caller)는 전역함수 포인터를 받는다.
        m_LayerList.sort(CScene::LayerSort);
    }

    return nullptr;
}

// 레이어 찾기
// @parameter
// strTag : 찾으려는 레이어의 태그
CLayer* CScene::FindLayer(const string& strTag)
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
    {
        if ((*iter)->GetTag() == strTag)
        {
            return *iter;
        }
    }
    return nullptr;
}

bool CScene::LayerSort(CLayer* pL1, CLayer* pL2)
{
    // zOrder에 따른 오름차순 정렬을 할 것이다.
    // = 들어가면 crash 오지게 나오니까 주의
    return pL1->GetZOrder() < pL2->GetZOrder();
}

bool CScene::Init()
{
    return true;
}

void CScene::Input(float fDeltaTime)
{
    // 레이어 리스트를 반복해서 돌려야 처리가 가능하다.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// 비활성화시
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Input(fDeltaTime);

        // 만약 이 레이어가 죽었다면
        if (!(*iter)->GetLife())
        {
            SAFE_DELETE((*iter));
            iter = m_LayerList.erase(iter);
            iterEnd = m_LayerList.end();
        }
        else
        {
            ++iter;
        }
    }
}

int CScene::Update(float fDeltaTime)
{
    // 레이어 리스트를 반복해서 돌려야 처리가 가능하다.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {
        // 비활성화시
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Update(fDeltaTime);

        // 만약 이 레이어가 죽었다면
        if (!(*iter)->GetLife())
        {
            SAFE_DELETE((*iter));
            iter = m_LayerList.erase(iter);
            iterEnd = m_LayerList.end();
        }
        else
        {
            ++iter;
        }
    }

    return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
    // 레이어 리스트를 반복해서 돌려야 처리가 가능하다.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// 비활성화시
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->LateUpdate(fDeltaTime);

        // 만약 이 레이어가 죽었다면
        if (!(*iter)->GetLife())
        {
            SAFE_DELETE((*iter));
            iter = m_LayerList.erase(iter);
            iterEnd = m_LayerList.end();
        }
        else
        {
            ++iter;
        }
    }

    return 0;
}

void CScene::Collision(float fDeltaTime)
{
    // 레이어 리스트를 반복해서 돌려야 처리가 가능하다.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// 비활성화시
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Collision(fDeltaTime);

        // 만약 이 레이어가 죽었다면
        if (!(*iter)->GetLife())
        {
            SAFE_DELETE((*iter));
            iter = m_LayerList.erase(iter);
            iterEnd = m_LayerList.end();
        }
        else
        {
            ++iter;
        }
    }
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
    // 레이어 리스트를 반복해서 돌려야 처리가 가능하다.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// 비활성화시
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Render(hDC, fDeltaTime);

        // 만약 이 레이어가 죽었다면
        if (!(*iter)->GetLife())
        {
            SAFE_DELETE((*iter));
            iter = m_LayerList.erase(iter);
            iterEnd = m_LayerList.end();
        }
        else
        {
            ++iter;
        }
    }
}

void CScene::ErasePrototype(SCENE_CREATE sc)
{
    // 전체 프로토타입을 통으로 날린다.
    Safe_Release_Map(m_mapPrototype[sc]);
}

void CScene::ErasePrototype(const string& strTag, SCENE_CREATE sc)
{
    unordered_map<string, CObj*>::iterator iter
        = m_mapPrototype[sc].find(strTag);

    if (!iter->second)
    {
        return;
    }

    SAFE_RELEASE(iter->second);
    m_mapPrototype[sc].erase(iter);
}

CObj* CScene::FindPrototype(const string& strTag, SCENE_CREATE sc)
{
    unordered_map<string, CObj*>::iterator iter = m_mapPrototype[sc].find(strTag);

    if (iter == m_mapPrototype[sc].end())
    {
        return nullptr;
    }

    return iter->second;
}

void CScene::ChangePrototype()
{
    ErasePrototype(SC_CURRENT);
    m_mapPrototype[SC_CURRENT] = m_mapPrototype[SC_NEXT];
    m_mapPrototype[SC_NEXT].clear();
}
