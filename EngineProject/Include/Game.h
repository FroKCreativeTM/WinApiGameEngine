#pragma once

// 게임을 총괄 및 관리
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

#include "resource.h"
#include "Macro.h"
#include "Flag.h"
#include "Types.h"

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

