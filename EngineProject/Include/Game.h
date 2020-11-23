#pragma once

// 게임을 총괄 및 관리
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>			// 메모리 누수 체크용 헤더

using namespace std;

#include "resource.h"
#include "Macro.h"
#include "Flag.h"
#include "Types.h"

// 수학 연산에 필요한 상수들
#define PI		3.141592f

// 경로 관련 상수들
#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"

// 필요한 정적 라이브러리 링크
#pragma comment(lib, "msimg32") // 이미지 관련 헤더

// STL을 날리기 위한 함수
// 타입을 잡아줄 필요가 없기 때문에, 재사용성이 높다.
template <typename T>
void Safe_Delete_VecList(T& ref)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = ref.end();

	for (iter = ref.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	ref.clear();
}

// 레이어 소멸자에서
// 모든 오브젝트를 지운다.
template <typename T>
void Safe_Release_VecList(T& ref)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = ref.end();

	for (iter = ref.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	ref.clear();
}

template <typename T>
void Safe_Delete_Map(T& ref)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = ref.end();

	for (iter = ref.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	ref.clear();
}

template <typename T>
void Safe_Release_Map(T& ref)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = ref.end();

	for (iter = ref.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second);
	}

	ref.clear();
}


