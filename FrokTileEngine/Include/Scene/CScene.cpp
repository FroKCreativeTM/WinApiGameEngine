#include "CScene.h"
#include "CLayer.h"
#include "../Object/CObj.h"

unordered_map<string, CObj*> CScene::m_mapPrototype[SC_END];

CScene::CScene()
{
    // ����� �����ϸ� �ƹ� ���̾ ������
    // �ϳ��� ��������.
    CLayer* pLayer = CreateLayer("Default", 1);
    pLayer = CreateLayer("HUD", INT_MAX - 1);
    pLayer = CreateLayer("UI", INT_MAX); // �� �ڿ� �ִ� ��
    pLayer = CreateLayer("Stage", 0); // �� �ڿ� �ִ� ��
    m_eSceneType = SC_CURRENT;
}

CScene::~CScene()
{
    ErasePrototype(m_eSceneType);
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

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// ��Ȱ��ȭ��
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Input(fDeltaTime);

        // ���� �� ���̾ �׾��ٸ�
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
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {
        // ��Ȱ��ȭ��
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Update(fDeltaTime);

        // ���� �� ���̾ �׾��ٸ�
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
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// ��Ȱ��ȭ��
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->LateUpdate(fDeltaTime);

        // ���� �� ���̾ �׾��ٸ�
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
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// ��Ȱ��ȭ��
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Collision(fDeltaTime);

        // ���� �� ���̾ �׾��ٸ�
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
    // ���̾� ����Ʈ�� �ݺ��ؼ� ������ ó���� �����ϴ�.
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for (iter = m_LayerList.begin(); iter != iterEnd;)
    {// ��Ȱ��ȭ��
        if (!(*iter)->GetEnable())
        {
            ++iter;
            continue;
        }

        (*iter)->Render(hDC, fDeltaTime);

        // ���� �� ���̾ �׾��ٸ�
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
    // ��ü ������Ÿ���� ������ ������.
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
