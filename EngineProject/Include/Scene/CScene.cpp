#include "CScene.h"
#include "CLayer.h"

CScene::CScene()
{
    // ����� �����ϸ� �ƹ� ���̾ ������
    // �ϳ��� ��������.
    CLayer* pLayer = CreateLayer("Default");
    pLayer = CreateLayer("UI", INT_MAX); // �� �ڿ� �ִ� ��
}

CScene::~CScene()
{
    Safe_Delete_VecList(m_LayerList);
}

// ���ο� ���̾� ����
CLayer* CScene::CreateLayer(const string& strTag, int nZOrder)
{
    CLayer* pLayer = new CLayer();

    // �� ��鿡 ���� ���ο� ���̾� ������ ä���.
    pLayer->SetTag(strTag);
    pLayer->SetZOrder(nZOrder);
    pLayer->SetScene(this);

    // ����Ʈ�� ���̾ �ִ´�.
    m_LayerList.push_back(pLayer);

    // ����Ʈ�� 2���� ������ Z������ �°� �����Ѵ�.
    // (��������)
    if (m_LayerList.size() >= 2)
    {
        // �Լ� ��ü�� bool type�� template Ÿ���� �Լ� �����Ͱ� ����.
        // �� �� ȣ����(caller)�� �����Լ� �����͸� �޴´�.
        m_LayerList.sort(CScene::LayerSort);
    }

    return nullptr;
}

// ���̾� ã��
// @parameter
// strTag : ã������ ���̾��� �±�
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
    // zOrder�� ���� �������� ������ �� ���̴�.
    // = ���� crash ������ �����ϱ� ����
    return pL1->GetZOrder() < pL2->GetZOrder();
}

bool CScene::Init()
{
    return true;
}

void CScene::Input(float fDeltaTime)
{
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Input(fDeltaTime);
    }
}

int CScene::Update(float fDeltaTime)
{
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Update(fDeltaTime);
    }

    return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->LateUpdate(fDeltaTime);
    }

    return 0;
}

void CScene::Collision(float fDeltaTime)
{
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Collision(fDeltaTime);
    }
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
    {
        (*iter)->Render(hDC, fDeltaTime);
    }
}
