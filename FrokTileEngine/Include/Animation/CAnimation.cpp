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

	// ���������� ���� �ɸ� �� �ִ�.
	// ���ε�� ���� 8���� �������� ������
	// 8 / 0.125(1/8)�̴�.
	m_pCurClip->fAnimationTime += fDeltaTime;

	// ���� �� �ɷ��� ������ �ð��� �����ٸ�
	// �׳� �ǳʵ��� �Ѵ�.
	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFrameTime)
	{
		m_pCurClip->fAnimationTime -= m_pCurClip->fAnimationFrameTime;

		++m_pCurClip->nFrameX;

		if (m_pCurClip->nFrameX - m_pCurClip->nStartX == m_pCurClip->nLengthX)
		{
			// x�� �ʱ�ȭ
			m_pCurClip->nFrameX = m_pCurClip->nStartX;
			++m_pCurClip->nFrameY;

			if (m_pCurClip->eType == AT_FRAME)
			{	// ���� �������̶�� 
				// nFrameX�� �̹����� ��ü���ش�.
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->nFrameX]);
			}
			
			// �� ������ ���
			if (m_pCurClip->nFrameY - m_pCurClip->nStartY == m_pCurClip->nLengthY)
			{
				// y�� �ʱ�ȭ
				m_pCurClip->nFrameY = m_pCurClip->nStartY;
				// ��� ��
				m_bMotionEnd = true;
				// �ɼ�üũ
				switch (m_pCurClip->eOption)
				{
				case AO_ONCE_RETURN : 
					ChangeClip(m_strDefaultClip);
					break;
				case AO_ONCE_DESTROY:
					// ������ �ִ� ������Ʈ�� ���δ�.
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
			{	// ���� �������̶�� 
				// nFrameX�� �̹����� ��ü���ش�.
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
	// �±� ����(������!!!)
	int nLength = m_strTag.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strTag.c_str(), 1, nLength, pFile);

	int nCount = m_mapClip.size();
	fwrite(&nCount, 4, 1, pFile); 

	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	// ��� Ŭ�� ���� ����
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

	// Default Clip ����
	nLength = m_strDefaultClip.length();
	fwrite(&nLength, 4, 1, pFile);
	fwrite(m_strDefaultClip.c_str(), 1, nLength, pFile);
	// Current Clip ����
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

	//  nLengthX * nLengthY : ������ ��ü ���� 
	pClip->fAnimationFrameTime = fAnimationLimitTime / (nLengthX * nLengthY);

	CTexture* pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strTexKey, pFileName, strPathKey);

	pClip->tFrameSize.x = pTexture->GetWidth() / nFrameMaxX;
	pClip->tFrameSize.y = pTexture->GetHeight() / nFrameMaxY;

	pClip->vecTexture.push_back(pTexture);

	pClip->fAnimationTime = 0.f;
	pClip->nFrameX = nStartX;
	pClip->nFrameY = nStartY;
	pClip->fOptionTime = 0.f;

	// ���� ù �ִϸ��̼� Ŭ���̶��
	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
	{
		// �⺻ �ִϸ��̼� Ŭ������ �����Ѵ�.
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

	//  nLengthX * nLengthY : ������ ��ü ���� 
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

	// ���� ù �ִϸ��̼� Ŭ���̶��
	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strDefaultClip.empty())
	{
		// �⺻ �ִϸ��̼� Ŭ������ �����Ѵ�.
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
	// ���� �ٲٷ��� Ŭ���� ���ٸ�?
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
	{	// ���� ��Ʋ�󽺶��
		// ù �ؽ�ó ������ �Ѱ��ش�.
		m_pObj->SetTexture(m_pCurClip->vecTexture[0]);
	}
	else if (m_pCurClip->eType == AT_FRAME)
	{	// ���� �������̶�� 
		// �ؽ�ó�� X��ǥ�� �������� �ȴ�.
		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->nFrameX]);
	}
}

void CAnimation::ReturnClip()
{
	// ����Ʈ�� ���ư���.
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

		// �� ����
		*pClip = *iter->second;

		// �ܼ��� ���縸 �Ǿ��� ������ ���� ī���͸� ���� ��Ų��.
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
