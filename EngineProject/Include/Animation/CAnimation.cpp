#include "CAnimation.h"
#include "../Resources/CTexture.h"
#include "../Resources/CResourceManager.h"
#include "../Object/CObj.h"

bool CAnimation::Init()
{
	return true;
}

void CAnimation::Update(float fDeltaTime)
{

}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}

void CAnimation::SetObj(CObj* pObj)
{
	m_pObj = pObj;
}

bool CAnimation::AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
	float fAnimationLimitTime, int nFrameMaxX, int nFrameMaxY,
	int nStartX, int nStartY, 
	int nLengthX, int nLengthY, 
	float fOptionLimitTime, 
	const string& strTexKey, const wchar_t* pFileName, const string& strPathKey)
{
	PANIMATIONCLIP pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->nFrameMaxX = nFrameMaxX;
	pClip->nFrameMaxY = nFrameMaxY;
	pClip->nStartX = nStartX;
	pClip->nStartY = nStartY;
	pClip->nLengthX = nLengthX;
	pClip->nLengthY = nLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;

	CTexture* pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strTexKey, pFileName, strPathKey);

	pClip->fAnimationTime = 0.f;
	pClip->nFrameX = nStartX;
	pClip->nFrameY = nStartY;
	pClip->fOptionTime = 0.f;

	// 만약 첫 애니메이션 클립이라면
	if (m_mapClip.empty())
	{
		// 기본 애니메이션 클립으로 지정한다.
		SetDefaultClip(strName);
		SetCurrentClip(strName);
	}

	m_mapClip.insert(make_pair(strName, pClip));

	return true;
}

void CAnimation::SetCurrentClip(const string& strCurClip)
{
	ChangeClip(strCurClip);
}

void CAnimation::SetDefaultClip(const string& strDefaultClip)
{
	m_strDefaultClip = strDefaultClip;
}

void CAnimation::ChangeClip(const string& strClip)
{
	// 만약 바꾸려는 클립과 같다면?
	if (m_strCurClip == strClip) 
	{
		return;
	}

	m_strCurClip = strClip;

	if (m_pCurClip)
	{
		m_pCurClip->nFrameX = m_pCurClip->nFrameX;
		m_pCurClip->nFrameY = m_pCurClip->nFrameY;
		m_pCurClip->fAnimationTime = 0.f;
		m_pCurClip->fOptionTime = 0.f;
	}

	m_pCurClip = FindClip(strClip);
	
	if (m_pCurClip->eType == AT_ATLAS)
	{	// 만약 아틀라스라면
		// 첫 텍스처 파일을 넘겨준다.
		m_pObj->SetTexture(m_pCurClip->vecTexture[0]);
	}
	else if (m_pCurClip->eType == AT_FRAME)
	{	// 만약 프레임이라면 
		// 텍스처의 X좌표가 프레임이 된다.
		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->nFrameX]);
	}
}

PANIMATIONCLIP CAnimation::FindClip(const string& strClip)
{
	unordered_map<string, PANIMATIONCLIP>::iterator iter = m_mapClip.find(strClip);

	if (iter == m_mapClip.end())
	{
		return nullptr;
	}

	return iter->second;
}

CAnimation::CAnimation()
{
}

CAnimation::CAnimation(const CAnimation& anim)
{
	*this = anim;

	unordered_map<string, PANIMATIONCLIP>::const_iterator iter;
	unordered_map<string, PANIMATIONCLIP>::const_iterator iterEnd = anim.m_mapClip.end();

	for (iter = anim.m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		PANIMATIONCLIP pClip = new ANIMATIONCLIP;

		// 값 복사
		*pClip = *iter->second;

		// 단순히 복사만 되었기 때문에 참조 카운터를 증가 시킨다.
		for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
		{
			pClip->vecTexture[i]->AddRef();
		}
	}
}

CAnimation::~CAnimation()
{
	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	// 맵 반복 돌리면서 
	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		// 단순히 복사만 되었기 때문에 참조 카운터를 증가 시킨다.
		for (size_t i = 0; i < iter->second->vecTexture.size(); ++i)
		{
			SAFE_RELEASE(iter->second->vecTexture[i]);
		}
		SAFE_DELETE(iter->second);
	}

	m_mapClip.clear();
}
