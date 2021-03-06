#pragma once

#include "../Core/CRef.h"
#include "../Collider/CCollider.h"

class CScene;
class CLayer;

// 게임 내 보이는 모든 오브젝트들이 상속받을 클래스입니다.
// 움직임이 있는가 없는가를 나눈다.
// 위치와 크기가 필요하다.

// CRef : 레퍼런스 카운터를 담당하는 기능이다.
class CObj : 
	public CRef
{
public : 
	/* Setter */
	void SetTag(const string& tag)
	{
		this->m_strTag = tag;
	}

	void SetPos(const POSITION& ref)
	{
		this->m_tPos = ref;
	}

	void SetPos(float x, float y)
	{
		this->m_tPos.x = x;
		this->m_tPos.y = y;
	}

	void SetSize(const _SIZE& ref)
	{
		this->m_tSize = ref;
	}

	void SetSize(float x, float y)
	{
		this->m_tSize.x = x;
		this->m_tSize.y = y;
	}

	void SetScene(class CScene* pScene)
	{
		this->m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		this->m_pLayer = pLayer;
	}

	void SetPivot(const _SIZE& ref)
	{
		this->m_tPivot = ref;
	}

	void SetPivot(float x, float y)
	{
		this->m_tPivot.x = x;
		this->m_tPivot.y = y;
	}

	void SetPhysics(bool bPhysics)
	{
		m_bPhysics = bPhysics;
	}

	void SetImageOffset(const _SIZE& tOffset)
	{
		m_tImageOffset = tOffset;
	}

	void SetImageOffset(float x, float y)
	{
		m_tImageOffset.x = x;
		m_tImageOffset.y = y;
	}

	/* Getter */
	CCollider* GetCollider(const string& strTag);

	string GetTag() const
	{
		return m_strTag;
	}

	POSITION GetPos() const
	{
		return m_tPos;
	}

	_SIZE GetSize() const
	{
		return m_tSize;
	}

	_SIZE GetPivot() const
	{
		return m_tPivot;
	}

	float GetLeft() const
	{
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}

	float GetRight() const
	{
		return GetLeft() + m_tSize.x ;
	}

	float GetTop() const
	{
		return m_tPos.y - m_tSize.y * m_tPivot.y;
	}

	float GetBottom() const
	{
		return GetTop() + m_tSize.y;
	}

	POSITION GetCenter() const
	{
		return POSITION(GetLeft() + m_tSize.x / 2.f,
			GetTop() + m_tSize.y / 2.f);
	}

	class CScene* GetScene() const
	{
		return m_pScene;
	}

	class CLayer* GetLayer() const
	{
		return m_pLayer;
	}

	// 리스트 포인터를 넘긴다.
	const list<CCollider*>* GetColliderList() const
	{
		return &m_ColliderList;
	}

	bool GetPhysics() const
	{
		return m_bPhysics;
	}

/* 게임 요소를 위한 메소드 */
public : 	
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CObj* Clone() = 0;	

// 오브젝트 자료 다루기 
public :
	static void AddObj(CObj* pObj);
	static CObj* FindObj(const string& strTag);
	static void EraseObj();	// 전체
	static void EraseObj(CObj* pObj);
	static void EraseObj(const string& strTag);

// 텍스쳐 세팅
public : 
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strKey,
		const wchar_t* pFileName = nullptr,
		const string& strPathKey = TEXTURE_PATH);

// 애니메이션 관련 메서드
public : 
	class CAnimation* CreateAnimation(const string& strTag);
	// 아틀라스 애니메이션용
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
		int nLengthX, int nLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	// 프레임 애니메이션용
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int nFrameMaxX, int nFrameMaxY, int nStartX, int nStartY,
		int nLengthX, int nLengthY, float fOptionLimitTime,
		const string& strTexKey, const vector<wstring>& vecFileName,
		const string& strPathKey = TEXTURE_PATH);

	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	void SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned b);

public:
	// 굉장히 다양한 타입의 오브젝트를 만들기 위한 
	// 템플릿 타입의 메소드이다.
	template <typename T>
	static T* CreateObj(const string& strTag,
		class CLayer* pLayer = nullptr);
	// 생성된 프로토타입의 복사를 생성한다.
	// 템플릿으로 만들 이유도 없다.
	static CObj* CreateCloneObj(const string& strProtoKey,
		const string& strTag, 
		SCENE_CREATE sc,
		class CLayer* pLayer = nullptr);
	template <typename T>
	void AddCollisionFunction(const string& strTag,
		COLLISION_STATE eState, T* pObj,
		void(T::* pFunc)(CCollider*, CCollider*, float));

public:
	template <typename T>
	T* AddCollider(const string& strTag)
	{
		// 충돌체를 생성하고 이 충돌체를 가질 오브젝트의 정보를 전달한다
		T* pCollider = new T;
		pCollider->SetObj(this);
		pCollider->SetTag(strTag);

		if (!pCollider->Init())
		{
			SAFE_RELEASE(pCollider);
			return nullptr;
		}

		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);

		return pCollider;
	}

	bool CheckCollider()
	{
		// 충돌이 있나없나를 검사한다.
		return !m_ColliderList.empty();
	}

	void ClearGravity()
	{
		m_fGravityTime = 0.f;
	}


protected :
	CObj();
	CObj(const CObj& ref);
	virtual ~CObj();

protected :
	// 오브젝트도 태그를 가진다.
	string					m_strTag;	
	// 위치와 크기
	POSITION				m_tPos;
	_SIZE					m_tSize;
	_SIZE					m_tImageOffset;		// 오프셋? 내가 원하는 특정 좌표값만큼 출력한다.
	POSITION				m_tPivot;
	// 텍스처 정보
	class CTexture*			m_pTexture;
	// 충돌체에 대한 정보
	list<CCollider*>		m_ColliderList;
	// 물리적인 힘을 받는 객체인다.
	bool					m_bPhysics;
	// 중력 시간값
	float					m_fGravityTime;
	// 오브젝트의 애니메이션 정보가 담기는 클래스
	class CAnimation*		m_pAnimation;

protected:
	// 자기가 속한 장면과 레이어를 알게 한다.
	class CScene* m_pScene;
	class CLayer* m_pLayer;

protected : 
	friend class CScene;

private : 
	// 생성되는 모든 오브젝트들은 여기서 저장된다.
	// 즉 레이어에 배치되면서 동시에 여기에 들어온다는 뜻이다.
	// (실제 배치됨)
	static list<CObj*>	m_ObjList;


};

#include "CObj.inl"