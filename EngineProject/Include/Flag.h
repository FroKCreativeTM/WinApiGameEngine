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

// �ִϸ��̼� Ŭ�� �̹��� Ÿ��
// �ϳ��ϳ� ����(��Ʋ��)
// �� �忡 ���� �׸��� �׷��� ����(������)
// �������� ������ �� ���� IO�� �ִϸ��̼��� �ε��Ѵ�.
enum ANIMATION_TYPE
{
	AT_ATLAS,
	AT_FRAME,
	AT_END
};

// �ִϸ��̼� �ɼ�
// ���� : �ݺ�(Idle ��ǿ��� ���� ����Ѵ�.)
// AO_ONCE_RETURN : �� �� ���� default ������� ���ư���.
// AO_ONCE_DESTROY : �ִϸ��̼��� ���� �� ������Ʈ�� �����Ѵ�. (����Ʈ���� ���)
// AO_TIME_RETURN : ���� �ð����� ���ư��� idle�� ���ư���. (���� ���� ���)
// AO_TIME_DESTROY : ���� �̻��� �ð����� ���ư��� ����Ʈ�� �������.
enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_RETURN,
	AO_ONCE_DESTROY,
	AO_TIME_RETURN,
	AO_TIME_DESTROY
};