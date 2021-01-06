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