#pragma once

/* 게임에 필요한 플래그들을 정의합니다. */

// 장면 타입
enum SCENE_CREATE
{
	SC_CURRENT,
	SC_NEXT
};

// 방향을 정하는 타입
enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

// 충돌체도 여러가지가 있을 수 있기 때문에 이에 대한 대응책으로
// 이 enum문을 선언한다.
enum COLLIDER_TYPE
{
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_POINT,
	CT_PIXEL,
	CT_END
};

// 충돌 상태
enum COLLISION_STATE
{
	CS_ENTER,
	CS_STAY,
	CS_LEAVE,
	CS_END
};

// 애니메이션 클립 이미지 타입
// 하나하나 낱장(아틀라스)
// 한 장에 많은 그림이 그려져 있음(프레임)
// 프레임의 장점은 한 번의 IO로 애니메이션을 로딩한다.
enum ANIMATION_TYPE
{
	AT_ATLAS,
	AT_FRAME,
	AT_END
};

// 애니메이션 옵션
// 루프 : 반복(Idle 모션에서 보통 사용한다.)
// AO_ONCE_RETURN : 한 번 돌고 default 모션으로 돌아간다.
// AO_ONCE_DESTROY : 애니메이션이 돌고 이 오브젝트를 삭제한다. (이펙트에서 사용)
// AO_TIME_RETURN : 일정 시간동안 돌아가다 idle로 돌아간다. (버프 받은 경우)
// AO_TIME_DESTROY : 일정 이상의 시간동안 돌아가다 이펙트가 사라진다.
enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_RETURN,
	AO_ONCE_DESTROY,
	AO_TIME_RETURN,
	AO_TIME_DESTROY
};