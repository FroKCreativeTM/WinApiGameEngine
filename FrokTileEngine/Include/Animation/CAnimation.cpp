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
	m_bMotionEnd = false;

	// 순간적으로 렉이 걸릴 수 있다.
	// 예로들어 지금 8장의 프레임이 있으니
	// 8 / 0.125(1/8)이다.
	m_pCurClip->fAnimationTime += fDeltaTime;

	// 만약 렉 걸려서 프레임 시간을 지났다면
	// 그냥 건너도록 한다.
	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFrameTime)
	{
		m_pCurClip->fAnimationTime -= m_pCurClip->fAnimationFrameTime;

		++m_pCurClip->nFrameX;

		if (m_pCurClip->nFrameX - m_pCurClip->nStartX == m_pCurClip->nLengthX)
		{
			// x축 초기화
			m_pCurClip->nFrameX = m_pCurClip->nStartX;
			++m_pCurClip->nFrameY;

			if (m_pCurClip->eType == AT_FRAME)
			{	// 만약 프레임이라면 
				// nFrameX의 이미지로 교체해준다.
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->nFrameX]);
			}
			
			// 다 돌았을 경우
			if (m_pCurClip->nFrameY - m_pCurClip->nStartY == m_pCurClip->nLengthY)
			{
				// y축 초기화
				m_pCurClip->nFrameY = m_pCurClip->nStartY;
				// 모션 끝
				m_bMotionEnd = true;
				// 옵션체크
				switch (m_pCurClip->eOption)
				{
				case AO_ONCE_RETURN : 
					ChangeClip(m_strDefaultClip);
					break;
				case AO_ONCE_DESTROY:
					// 가지고 있는 오브젝트를 죽인다.
					m_pObj->Die();
					break;
				case AO_TIME_RETURN:
					break;
				case AO_TIME_DESTROY:
					break;
				}
			}
		}
		else
		{
			if (m_pCurClip->eType == AT_FRAME)
			{	// 만약 프레임이라면 
				// nFrameX의 이미지로 교체해준다.
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->nFrameX]);
			}
		}
	}
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}

void CAnimation::SaveFromPath(const char* pFileName, const string& strPathKey)
{
}

void CAnimation::Save(FILE* pFile)
{
	// 태그 저장(무조건!!!)
	int nLength = m_strTag.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strTag.c_str(), 1, nLength, pFile);

	int nCount = m_mapClip.size();
	fwrite(&nCount, 4, 1, pFile); 

	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	// 모든 클립 정보 저장
	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		fwrite(&iter->second->eType, 4, 1, pFile);
		fwrite(&iter->second->eOption, 4, 1, pFile);

		nCount = iter->second->vecTexture.size();
		fwrite(&nCount, 4, 1, pFile);

		for (size_t i = 0; i < nCount; i++)
		{
			iter->second->vecTexture[i]->Save(pFile);
		}

		fwrite(&iter->second->fAnimationLimitTime, 4, 1, pFile);
		fwrite(&iter->second->fAnimationFrameTime, 4, 1, pFile);
		fwrite(&iter->second->nFrameMaxX, 4, 1, pFile);
		fwrite(&iter->second->nFrameMaxY, 4, 1, pFile);
		fwrite(&iter->second->nStartX, 4, 1, pFile);
		fwrite(&iter->second->nStartY, 4, 1, pFile);
		fwrite(&iter->second->nLengthX, 4, 1, pFile);
		fwrite(&iter->second->nLengthY, 4, 1, pFile);
		fwrite(&iter->second->fOptionLimitTime, 4, 1, pFile);
		fwrite(&iter->second->tFrameSize, sizeof(_SIZE), 1, pFile);
	}

	// Default Clip 저장
	nLength = m_strDefaultClip.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strDefaultClip.c_str(), 1, nLength, pFile);
	// Current Clip 저장
	nLength = m_strCurClip.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strCurClip.c_str(), 1, nLength, pFile);
}

void CAnimation::LoadFromPath(const char* pFileName, const string& strPathKey)
{
}

void CAnimation::Load(FILE* pFile)
{
}

void CAnimation::SetObj(CObj* pObj)
{
	m_pObj = pObj;
}

bool CAnimation::AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
	float fAnimationLimitTime, 
	int nFrameMaxX, int nFrameMaxY,
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

	//  nLengthX * nLengthY : 프레임 전체 갯수 
	pClip->fAnimationFrameTime = fAnimationLimitTime / (nLengthX * nLengthY);

	CTexture* pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strTexKey, pFileName, strPathKey);

	pClip->tFrameSize.x = pTexture->GetWidth() / nFrameMaxX;
	pClip->tFrameSize.y = pTexture->GetHeight() / nFrameMaxY;

	pClip->vecTexture.push_back(pTexture);

	pClip->fAnimationTime = 0.f;
	pClip->nFrameX = nStartX;
	pClip->nFrameY = nStartY;
	pClip->fOptionTime = 0.f;

	// 만약 첫 애니메이션 클립이라면
	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
	{
		// 기본 애니메이션 클립으로 지정한다.
		SetDefaultClip(strName);
	}
	if (m_strCurClip.empty())
	{
		SetCurrentClip(strName);
	}

	return true;
}

bool CAnimation::AddClip(const string& strName, 
	ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float 
	fAnimationLimitTime, 
	int nFrameMaxX, int nFrameMaxY, 
	int nStartX, int nStartY, 
	int nLengthX, int nLengthY, 
	float fOptionLimitTime, 
	const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey)
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

	//  nLengthX * nLengthY : 프레임 전체 갯수 
	pClip->fAnimationFrameTime = fAnimationLimitTime / (nLengthX * nLengthY);

	for (size_t i = 0; i < vecFileName.size(); i++)
	{
		char strKey[256] = {};
		sprintf_s(strKey, "%s%d", strTexKey.c_str(), i + 1);
		CTexture* pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strKey, vecFileName[i].c_str(), strPathKey);

		pClip->vecTexture.push_back(pTexture);
	}

	pClip->tFrameSize.x = pClip->vecTexture[0]->GetWidth() / nFrameMaxX;
	pClip->tFrameSize.y = pClip->vecTexture[0]->GetHeight() / nFrameMaxY;

	pClip->fAnimationTime = 0.f;
	pClip->nFrameX = nStartX;
	pClip->nFrameY = nStartY;
	pClip->fOptionTime = 0.f;

	// 만약 첫 애니메이션 클립이라면
	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
	{
		// 기본 애니메이션 클립으로 지정한다.
		SetDefaultClip(strName);
	}
	if (m_strCurClip.empty())
	{
		SetCurrentClip(strName);
	}

	return true;
}

void CAnimation::SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned b)
{
	PANIMATIONCLIP pClip = FindClip(strClip);

	if (!pClip)
	{
		return;
	}

	for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
	{
		pClip->vecTexture[i]->SetColorKey(r, g, b);
	}
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

void CAnimation::ReturnClip()
{
	// 디폴트로 돌아간다.
	ChangeClip(m_strDefaultClip);
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

CAnimation::CAnimation() : 
	m_pCurClip(nullptr),
	m_bMotionEnd(false)
{
}

CAnimation::CAnimation(const CAnimation& anim)
{
	*this = anim;
	m_bMotionEnd = false;

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

	m_pCurClip = nullptr;
	m_strCurClip = "";
	SetCurrentClip(anim.m_strCurClip);
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
