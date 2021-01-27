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

    void SaveFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
    void Save(FILE* pFile);
    void LoadFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
    void Load(FILE* pFile);

public : 
    void SetObj(class CObj* pObj);

    PANIMATIONCLIP GetCurrentClip() const
    {
        return m_pCurClip;
    }

    bool GetMotionEnd() const
    {
        return m_bMotionEnd;
    }

    // 아틀라스 애니메이션용
    bool AddClip(const string& strName, ANIMATION_TYPE eType,
        ANIMATION_OPTION eOption, float fAnimationLimitTime,
        int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
        int nLengthX, int nLengthY, float fOptionLimitTime,
        const string& strTexKey, const wchar_t* pFileName,
        const string& strPathKey = TEXTURE_PATH);

    // 프레임 애니메이션은 문제는 키값도 여러개
    // 텍스트키도 여러개가 된다.
    bool AddClip(const string& strName, ANIMATION_TYPE eType,
        ANIMATION_OPTION eOption, float fAnimationLimitTime,
        int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
        int nLengthX, int nLengthY, float fOptionLimitTime,
        const string& strTexKey, const vector<wstring>& vecFileName,
        const string& strPathKey = TEXTURE_PATH);

    void SetClipColorKey(const string& strClip,
        unsigned char r, unsigned char g, unsigned b);
    void SetCurrentClip(const string& strCurClip);
    void SetDefaultClip(const string& strDefaultClip);
    void ChangeClip(const string& strClip);
    void ReturnClip();

private : 
    PANIMATIONCLIP FindClip(const string& strClip);

private : 
    unordered_map<string, PANIMATIONCLIP>   m_mapClip;
    PANIMATIONCLIP                          m_pCurClip;
    string                                  m_strCurClip;
    string                                  m_strDefaultClip;
    class CObj*                             m_pObj;
    bool                                    m_bMotionEnd;

private : 
    friend class CObj;

private : 
    CAnimation();
    CAnimation(const CAnimation& anim);
    ~CAnimation();
};

