#pragma once
#include "../Core/CRef.h"

// ������ ��Ʈ�ѷ�
// �ȿ��� �������� ����� ������ �����鼭 �� ������ �͵��� ������ �ִ´�.
class CAnimation :
    public CRef
{
public : 
    bool Init();
    void Update(float fDeltaTime);
    CAnimation* Clone();

public : 
    bool AddClip(const string& strName, ANIMATION_TYPE eType,
        ANIMATION_OPTION eOption, float fAnimationLimitTime,
        int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
        int nLengthX, int nLengthY, float fOptionLimitTime,
        const string& strTexKey, const wchar_t* pFileName,
        const string& strPathKey = TEXTURE_PATH);

private : 
    unordered_map<string, PANIMATIONCLIP> m_mapClip;

private : 
    friend class CObj;

private : 
    CAnimation();
    CAnimation(const CAnimation& anim);
    ~CAnimation();
};

