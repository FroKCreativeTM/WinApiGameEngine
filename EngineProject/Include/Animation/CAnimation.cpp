#include "CAnimation.h"
#include "../Resources/CTexture.h"
#include "../Resources/CResourceManager.h"

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

	m_mapClip.insert(make_pair(strName, pClip));

	return true;
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

		// �� ����
		*pClip = *iter->second;

		// �ܼ��� ���縸 �Ǿ��� ������ ���� ī���͸� ���� ��Ų��.
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

	// �� �ݺ� �����鼭 
	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		// �ܼ��� ���縸 �Ǿ��� ������ ���� ī���͸� ���� ��Ų��.
		for (size_t i = 0; i < iter->second->vecTexture.size(); ++i)
		{
			SAFE_RELEASE(iter->second->vecTexture[i]);
		}
		SAFE_DELETE(iter->second);
	}

	m_mapClip.clear();
}
