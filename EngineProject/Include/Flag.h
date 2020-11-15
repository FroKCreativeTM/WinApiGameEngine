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