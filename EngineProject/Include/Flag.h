#pragma once

/* ���ӿ� �ʿ��� �÷��׵��� �����մϴ�. */

// ��� Ÿ��
enum SCENE_CREATE
{
	SC_CURRENT,
	SC_NEXT
};

// ������ ���ϴ� Ÿ��
enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

// �浹ü�� ���������� ���� �� �ֱ� ������ �̿� ���� ����å����
// �� enum���� �����Ѵ�.
enum COLLIDER_TYPE
{
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_POINT,
	CT_PIXEL,
	CT_END
};

// �浹 ����
enum COLLISION_STATE
{
	CS_ENTER,
	CS_STAY,
	CS_LEAVE,
	CS_END
};