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
	/* 충돌체를 돌린다. */
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		// 콜라이더가 비활성화 되어있다면
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
		// 콜라이더가 비활성화 되어있다면
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

	// 카메라 위치를 빼야 스크롤이 된다.
	tPos -= GET_SINGLE(CCamera)->GetPos();

	// 해상도를 들고온다.
	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetClientResolution();
	// 클라이언트 창 안에 있나를 선별한다.
	bool isInClient = true;

	// 출력하고자하는 right가 0보다 크다.
	if (tPos.x + m_tSize.x < 0)
	{
		isInClient = false;
	}
	// left가 만약 클라이언트 오른쪽 밖이라면
	else if (tPos.x > tClientRS.nWidth)
	{
		isInClient = false;
	}
	// 출력하고자하는 bottom이 0보다 크다.
	else if (tPos.y + m_tSize.y < 0)
	{
		isInClient = false;
	}
	// top이 만약 클라이언트 아래에 있다면
	else if (tPos.y > tClientRS.nHeight)
	{
		isInClient = false;
	}

	// 텍스처가 있는 경우
	if (m_pTexture && isInClient)
	{
		POSITION tImagePos; // (0,0)

		// 만약 애니메이션이 있다면
		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			// 이미지 크기 갱신
			if (pClip->eType == AT_ATLAS)
			{
				// 아틀라스는 오프셋은 애니메이션이 있던 없던 둘 다 적용한다.
				tImagePos.x = pClip->nFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->nFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		// 컬러키 활성화 여부에 따라 다르다.
		if (m_pTexture->GetColorKeyEnable())
		{
			// 인자가 
			TransparentBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,		// 시작 위치
				m_tSize.x, m_tSize.y, 	// 크기
				m_pTexture->GetColorKey());
		}
		else
		{
			// 화면에 DC에 들어가있는 도구를 출력해주는 함수이다.
			// 1. DC
			// 2~3. 어디에 출력할것인가
			// 4~5. 화면상 얼마나 크게 출력할래
			// 6. source의 DC
			// 7~8. 이미지의 어디부터 출력?
			// 9. 6번 인자에 복사
			BitBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y,
				m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y,
				SRCCOPY);
		}		
	}
	
	// 창 안에 있어야만 출력한다.
	if (isInClient) 
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd;)
		{
			// 콜라이더가 비활성화 되어있다면
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
	// 태그 저장(무조건!!!)
	int nLength = m_strTag.length();

	// 태그 길이 저장
	fwrite(&nLength, 4, 1, pFile);

	// 문자열 저장
	fwrite(m_strTag.c_str(), 1, nLength, pFile);

	// 물리 사용여부 저장
	fwrite(&m_bPhysics, 1, 1, pFile);

	// 위치 저장
	fwrite(&m_tPos, sizeof(m_tPos), 1, pFile);

	// 크기 저장
	fwrite(&m_tSize, sizeof(m_tSize), 1, pFile);

	// 이미지 오프셋
	fwrite(&m_tImageOffset, sizeof(m_tImageOffset), 1, pFile);

	// 피봇 저장
	fwrite(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	// 텍스처 정보 저장
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

	// 충돌체 정보 저장
	// 충돌체 수를 저장한다.
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

	// 애니메이션 저장
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
	// 태그 저장(무조건!!!)
	int nLength = 0;
	char strText[MAX_PATH] = {};

	// 태그 길이 읽어오기
	fread(&nLength, 4, 1, pFile);

	// 태그 읽어오기
	fread(strText, 1, nLength, pFile);
	strText[nLength] = 0;
	m_strTag = strText;

	// 물리 사용여부 읽어오기
	fread(&m_bPhysics, 1, 1, pFile);

	// 위치 읽어오기
	fread(&m_tPos, sizeof(m_tPos), 1, pFile);

	// 크기 읽어오기
	fread(&m_tSize, sizeof(m_tSize), 1, pFile);

	// 이미지 오프셋
	fread(&m_tImageOffset, sizeof(m_tImageOffset), 1, pFile);

	// 피봇 읽어오기
	fread(&m_tPivot, sizeof(m_tPivot), 1, pFile);

	// 텍스처 정보 읽어오기
	bool bTexture = false;
	fread(&bTexture, 1, 1, pFile);
	SAFE_RELEASE(m_pTexture);

	if (bTexture)
	{
		// 텍스처를 로딩한다.
		m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(pFile);
	}

	// 충돌체 정보 읽어오기
	// 충돌체 수를 읽어오기.
	nLength = 0;
	fread(&nLength, 4, 1, pFile);

	for (size_t i = 0; i < nLength; i++)
	{
		// 충돌체를 생성한다.
		// 충돌체 타입을 읽어온다.
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

	// 애니메이션 저장
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
	// 인자로 들어온 물건들을 다 넣어준다.
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
	// 기존 텍스처를 날린다.
	SAFE_RELEASE(m_pTexture);

	m_pTexture = pTexture;

	// 텍스처가 있어서 오류가 안 난 경우에만
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

	// 태그와 함께 자기 자신이 이 애니메이션을 가지고 있음을 명시한다.
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
	// 애니메이션이 생성되지 않은 상태에서 클립추가 불가
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
	// 애니메이션이 생성되지 않은 상태에서 클립추가 불가
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

// m_nRef가 0이면 지워진다.
// 즉 이것을 만드는 시점에서 누군가는 이 오브젝트를 참조한다.
CObj::CObj() :
	m_pTexture(nullptr), m_bPhysics(false), m_fGravityTime(0.f), m_pAnimation(nullptr)
{
}

// 모든 정보를 다 복사하자.
CObj::CObj(const CObj& ref)
{
	*this = ref;
	m_nRef = 1;

	// 복사할 객체가 애니메이션이 있다면
	if (ref.m_pAnimation)
	{
		m_pAnimation = ref.m_pAnimation->Clone();
	}

	m_fGravityTime = 0.f;

	// 만약 텍스처를 가지고 있다면 공유기 때문에
	// 레퍼런스 카운터만 증가시킨다.
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
	// 어떤 타입인지 알아서 찾아서 복사하도록
	// 짜피 static이라 CScene::
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

