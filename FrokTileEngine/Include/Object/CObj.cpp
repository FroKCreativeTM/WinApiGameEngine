#include "CObj.h"
#include "../Scene/CLayer.h"
#include "../Scene/CSceneManager.h"
#include "../Scene/CScene.h"
#include "../Resources/CResourceManager.h"
#include "../Resources/CTexture.h"
#include "../Core/CCamera.h"
#include "../Animation/CAnimation.h"
#include "../Core/CPathManager.h"

#include "../Collider/CRectCollider.h"
#include "../Collider/CPixelCollider.h"
#include "../Collider/CPointCollider.h"
#include "../Collider/CSphereCollider.h"

// static
list<CObj*> CObj::m_ObjList;

CCollider* CObj::GetCollider(const string& strTag)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

void CObj::Input(float fDeltaTime)
{
}

int CObj::Update(float fDeltaTime)
{
	/* �浹ü�� ������. */
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		// �ݶ��̴��� ��Ȱ��ȭ �Ǿ��ִٸ�
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	if (m_pAnimation)
	{
		m_pAnimation->Update(fDeltaTime);
	}

	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		// �ݶ��̴��� ��Ȱ��ȭ �Ǿ��ִٸ�
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	POSITION tPos = m_tPos - m_tSize * m_tPivot;

	// ī�޶� ��ġ�� ���� ��ũ���� �ȴ�.
	tPos -= GET_SINGLE(CCamera)->GetPos();

	// �ػ󵵸� ���´�.
	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetClientResolution();
	// Ŭ���̾�Ʈ â �ȿ� �ֳ��� �����Ѵ�.
	bool isInClient = true;

	// ����ϰ����ϴ� right�� 0���� ũ��.
	if (tPos.x + m_tSize.x < 0)
	{
		isInClient = false;
	}
	// left�� ���� Ŭ���̾�Ʈ ������ ���̶��
	else if (tPos.x > tClientRS.nWidth)
	{
		isInClient = false;
	}
	// ����ϰ����ϴ� bottom�� 0���� ũ��.
	else if (tPos.y + m_tSize.y < 0)
	{
		isInClient = false;
	}
	// top�� ���� Ŭ���̾�Ʈ �Ʒ��� �ִٸ�
	else if (tPos.y > tClientRS.nHeight)
	{
		isInClient = false;
	}

	// �ؽ�ó�� �ִ� ���
	if (m_pTexture && isInClient)
	{
		POSITION tImagePos; // (0,0)

		// ���� �ִϸ��̼��� �ִٸ�
		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			// �̹��� ũ�� ����
			if (pClip->eType == AT_ATLAS)
			{
				// ��Ʋ�󽺴� �������� �ִϸ��̼��� �ִ� ���� �� �� �����Ѵ�.
				tImagePos.x = pClip->nFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->nFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		// �÷�Ű Ȱ��ȭ ���ο� ���� �ٸ���.
		if (m_pTexture->GetColorKeyEnable())
		{
			// ���ڰ� 
			TransparentBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,		// ���� ��ġ
				m_tSize.x, m_tSize.y, 	// ũ��
				m_pTexture->GetColorKey());
		}
		else
		{
			// ȭ�鿡 DC�� ���ִ� ������ ������ִ� �Լ��̴�.
			// 1. DC
			// 2~3. ��� ����Ұ��ΰ�
			// 4~5. ȭ��� �󸶳� ũ�� ����ҷ�
			// 6. source�� DC
			// 7~8. �̹����� ������ ���?
			// 9. 6�� ���ڿ� ����
			BitBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,
				SRCCOPY);
		}		
	}
	
	// â �ȿ� �־�߸� ����Ѵ�.
	if (isInClient) 
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd;)
		{
			// �ݶ��̴��� ��Ȱ��ȭ �Ǿ��ִٸ�
			if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, fDeltaTime);

			if (!(*iter)->GetLife())
			{
				SAFE_RELEASE((*iter));
				iter = m_ColliderList.erase(iter);
				iterEnd = m_ColliderList.end();
			}
			else
				++iter;
		}
	}
}

void CObj::SaveFromPath(const char* pFileName, const string& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(DATA_PATH);
	string strFullPath;

	if (pPath)
	{
		strFullPath = pPath;
	}
	strFullPath += pFileName;
 
	SaveFromFullPath(strFullPath.c_str());
}

void CObj::Save(FILE* pFile)
{
	// �±� ����(������!!!)
	int nLength = m_strTag.length();

	// �±� ���� ����
	fwrite(&nLength, 4, 1, pFile);

	// ���ڿ� ����
	fwrite(m_strTag.c_str(), 1, nLength, pFile);

	// ���� ��뿩�� ����
	fwrite(&m_bPhysics, 1, 1, pFile);

	// ��ġ ����
	fwrite(&m_tPos, sizeof(m_tPos), 1, pFile);

	// ũ�� ����
	fwrite(&m_tSize, sizeof(m_tSize), 1, pFile);

	// �̹��� ������
	fwrite(&m_tImageOffset, sizeof(m_tImageOffset), 1, pFile);

	// �Ǻ� ����
	fwrite(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	// �ؽ�ó ���� ����
	bool bTexture = false;
	if (m_pTexture) 
	{
		bTexture = true;
		fwrite(&bTexture, 1, 1, pFile);
		m_pTexture->Save(pFile);
	}
	else
	{
		fwrite(&bTexture, 1, 1, pFile);
	}

	// �浹ü ���� ����
	// �浹ü ���� �����Ѵ�.
	nLength = m_ColliderList.size();
	fwrite(&nLength, 4, 1, pFile);
	
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; iter++)
	{
		COLLIDER_TYPE eType = (*iter)->GetColliderType();
		fwrite(&eType, 4, 1, pFile);
		((*iter)->Save(pFile));
	}

	// �ִϸ��̼� ����
	bool bAnimation = false;
	if (m_pAnimation)
	{
		bAnimation = true;
		fwrite(&bAnimation, 1, 1, pFile);
		m_pAnimation->Save(pFile);
	}
	else
	{
		fwrite(&bAnimation, 1, 1, pFile);
	}
}

void CObj::SaveFromFullPath(const char* pFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPath, "wb");

	if (pFile)
	{
		Save(pFile);
		fclose(pFile);
	}
}

void CObj::LoadFromPath(const char* pFileName, const string& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(DATA_PATH);
	string strFullPath;

	if (pPath)
	{
		strFullPath = pPath;
	}
	strFullPath += pFileName;

	LoadFromFullPath(strFullPath.c_str());
}

void CObj::Load(FILE* pFile)
{
	// �±� ����(������!!!)
	int nLength = 0;
	char strText[MAX_PATH] = {};

	// �±� ���� �о����
	fread(&nLength, 4, 1, pFile);

	// �±� �о����
	fread(strText, 1, nLength, pFile);
	strText[nLength] = 0;
	m_strTag = strText;

	// ���� ��뿩�� �о����
	fread(&m_bPhysics, 1, 1, pFile);

	// ��ġ �о����
	fread(&m_tPos, sizeof(m_tPos), 1, pFile);

	// ũ�� �о����
	fread(&m_tSize, sizeof(m_tSize), 1, pFile);

	// �̹��� ������
	fread(&m_tImageOffset, sizeof(m_tImageOffset), 1, pFile);

	// �Ǻ� �о����
	fread(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	// �ؽ�ó ���� �о����
	bool bTexture = false;
	fread(&bTexture, 1, 1, pFile);
	SAFE_RELEASE(m_pTexture);

	if (bTexture)
	{
		// �ؽ�ó�� �ε��Ѵ�.
		m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(pFile);
	}

	// �浹ü ���� �о����
	// �浹ü ���� �о����.
	nLength = 0;
	fread(&nLength, 4, 1, pFile);

	for (size_t i = 0; i < nLength; i++)
	{
		// �浹ü�� �����Ѵ�.
		// �浹ü Ÿ���� �о�´�.
		COLLIDER_TYPE eType;
		fread(&eType, 4, 1, pFile);

		CCollider* pCollider = nullptr;

		switch (eType)
		{
		case CT_RECT:
			pCollider = AddCollider<CRectCollider>("");
			break;
		case CT_SPHERE:
			pCollider = AddCollider<CSphereCollider>("");
			break;
		case CT_POINT:
			pCollider = AddCollider<CPointCollider>("");
			break;
		case CT_PIXEL:
			pCollider = AddCollider<CPixelCollider>("");
			break;
		}
		pCollider->Load(pFile);
		SAFE_RELEASE(pCollider);
	}

	// �ִϸ��̼� ����
	bool bAnimation = false;
	fread(&bAnimation, 1, 1, pFile);
	SAFE_RELEASE(m_pAnimation);
	if (bAnimation)
	{
		m_pAnimation = new CAnimation;

		m_pAnimation->Init();
		m_pAnimation->Load(pFile);
	}
}

void CObj::LoadFromFullPath(const char* pFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPath, "rb");

	if (pFile)
	{
		Load(pFile);
		fclose(pFile);
	}
}

void CObj::AddObj(CObj* pObj)
{
	// ���ڷ� ���� ���ǵ��� �� �־��ش�.
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

CObj* CObj::FindObj(const string& strTag)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}
	return nullptr;
}

void CObj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

void CObj::EraseObj(CObj* pObj)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pObj)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj(const string& strTag)
{
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::SetTexture(CTexture* pTexture)
{
	// ���� �ؽ�ó�� ������.
	SAFE_RELEASE(m_pTexture);

	m_pTexture = pTexture;

	// �ؽ�ó�� �־ ������ �� �� ��쿡��
	if (pTexture)
	{
		m_pTexture->AddRef();
	}
}

void CObj::SetTexture(const string& strKey, 
	const wchar_t* pFileName, 
	const string& strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourceManager)->
		LoadTexture(strKey, pFileName, strPathKey);
}

CAnimation* CObj::CreateAnimation(const string& strTag)
{
	SAFE_RELEASE(m_pAnimation);

	m_pAnimation = new CAnimation;

	// �±׿� �Բ� �ڱ� �ڽ��� �� �ִϸ��̼��� ������ ������ ����Ѵ�.
	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObj(this);
	if (!m_pAnimation->Init())
	{
		SAFE_RELEASE(m_pAnimation);
		return nullptr;
	}

	m_pAnimation->AddRef();

	return m_pAnimation;
}

bool CObj::AddAnimationClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, 
	float fAnimationLimitTime, 
	int nFrameMaxX, int nFrameMaxY,
	int nStartX, int nStartY, 
	int nLengthX, int nLengthY, 
	float fOptionLimitTime, 
	const string& strTexKey, const wchar_t* pFileName, const string& strPathKey)
{
	// �ִϸ��̼��� �������� ���� ���¿��� Ŭ���߰� �Ұ�
	if (!m_pAnimation)
	{
		return false;
	}

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime,
		nFrameMaxX, nFrameMaxY, nStartX, nStartY, nLengthX, nLengthY,
		fOptionLimitTime, strTexKey, pFileName, strPathKey);

	return true;
}

bool CObj::AddAnimationClip(const string& strName, 
	ANIMATION_TYPE eType, ANIMATION_OPTION eOption, 
	float fAnimationLimitTime, 
	int nFrameMaxX, int nFrameMaxY, 
	int nStartX, int nStartY, 
	int nLengthX, int nLengthY, 
	float fOptionLimitTime, 
	const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey)
{
	// �ִϸ��̼��� �������� ���� ���¿��� Ŭ���߰� �Ұ�
	if (!m_pAnimation)
	{
		return false;
	}

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime,
		nFrameMaxX, nFrameMaxY, nStartX, nStartY, nLengthX, nLengthY,
		fOptionLimitTime, strTexKey, vecFileName, strPathKey);

	return true;
}

void CObj::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void CObj::SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned b)
{
	if (m_pAnimation)
	{
		m_pAnimation->SetClipColorKey(strClip, r, g, b);
	}
}

// m_nRef�� 0�̸� ��������.
// �� �̰��� ����� �������� �������� �� ������Ʈ�� �����Ѵ�.
CObj::CObj() :
	m_pTexture(nullptr), m_bPhysics(false), m_fGravityTime(0.f), m_pAnimation(nullptr)
{
}

// ��� ������ �� ��������.
CObj::CObj(const CObj& ref)
{
	*this = ref;
	m_nRef = 1;

	// ������ ��ü�� �ִϸ��̼��� �ִٸ�
	if (ref.m_pAnimation)
	{
		m_pAnimation = ref.m_pAnimation->Clone();
	}

	m_fGravityTime = 0.f;

	// ���� �ؽ�ó�� ������ �ִٸ� ������ ������
	// ���۷��� ī���͸� ������Ų��.
	if (m_pTexture)
	{
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();

	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = ref.m_ColliderList.end();

	for (iter = ref.m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		CCollider* pColl = (*iter)->Clone();
		pColl->SetObj(this);
		m_ColliderList.push_back(pColl); 
	}
}

CObj::~CObj()
{
	SAFE_RELEASE(m_pAnimation);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);
}

CObj* CObj::CreateCloneObj(const string& strProtoKey,
	const string& strTag,
	SCENE_CREATE sc,
	CLayer* pLayer)
{
	// � Ÿ������ �˾Ƽ� ã�Ƽ� �����ϵ���
	// ¥�� static�̶� CScene::
	CObj* pPrototype = CScene::FindPrototype(strProtoKey, sc);

	if (!pPrototype)
	{
		return nullptr;
	}

	CObj* pObj = pPrototype->Clone();
	pObj->SetTag(strTag);

	if (pLayer)
	{
		pLayer->AddObj(pObj);
	}

	AddObj(pObj);

	return pObj;
}

