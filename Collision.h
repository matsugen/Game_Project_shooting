#pragma once
#include"stdafx.h"
class Actor;
class DrawSystem;
class SpriteNode;
namespace OWNER{
enum OWNER{
	NONE=-1,
	PLAYER,
	BULLET,
	ENEMY};
}

typedef struct collision_option{//collision�̃I�v�V������ݒ�
	double m_x,m_y,m_w,m_h;		//�����`�̍���̑��΍��W�Ƃ��̑傫��
	double abs_x,abs_y;			//������W�̐�΍��W
	bool hit_flg;				//�q�b�g�������ǂ����̔��f
	bool effective;				//���̔��肪�L�����ǂ���
	OWNER::OWNER owner;				//���̔���̏����Җ�
}C_OPTION;
class Collision
{
private:
	Actor* m_owner;									//����collision����������A�N�^�[�̃|�C���^
	collision_option m_option;						//collision�̃X�e�[�^�X
#ifndef NDEBUG
	DrawSystem* m_drawsystem;
	SpriteNode* m_box;
#endif
public:
	Collision(void);
	Collision(Actor* owner,collision_option option,DrawSystem* ds);
	~Collision(void);
	void Hit();										//hit_flg��true�ɂ���
	C_OPTION Get_Option();							//Collision�̓��e���擾�B
	void Set_Option(C_OPTION option);
	void update();									//����collision����������Actor�ɍ��킹�ē���
	void On();										//����Collision��L���ɂ���
	void Off();										//����Collision�𖳌��ɂ���B�q�b�g����͕ς��Ȃ�
	void Reset();									//Collision���L�����ǂ����ƃq�b�g���������false�ɂ���B
};
