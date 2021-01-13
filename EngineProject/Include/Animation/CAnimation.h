#pragma once
#include "../Core/CRef.h"

// 일종의 컨트롤러
// 안에서 여러가지 모션을 가지고 있으면서 그 동작할 것들을 가지고 있는다.
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

