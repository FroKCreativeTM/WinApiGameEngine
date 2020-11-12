#include "CScene.h"
#include "CLayer.h"

CScene::CScene()
{
    // 장면이 시작하면 아무 레이어도 없으니
    // 하나는 만들어두자.
    CLayer* pLayer = CreateLayer("Default");
    pLayer = CreateLayer("UI", INT_MAX); // 맨 뒤에 있단 뜻
}

CScene::~CScene()
{
    Safe_Delete_VecList(m_LayerList);
}

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
