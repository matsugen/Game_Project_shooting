#pragma once
#include"stdafx.h"
#include "Actor.h"
#include "Bullet.h"
#include"ImageLoader.h"
#include"DrawSystem.h"
//#include"ActorManager.h"
class Player :
	public Actor
{
private:
	/*�ړ��֌W�̕ϐ�*/
	int m_d;							//�L�����̕���
	int m_walk_time;					//���s����
	/*�U���֌W�̕ϐ�*/
	int m_attack_num;					//�U���e���̌�
	double m_angle;						//����̊p�x
	/*�\���֌W�̕ϐ�*/
	SpriteNode* m_icon;					//�e�A�C�R��
	std::vector<Actor*> m_bullet;		//�e�A�N�^�[�̑��݊m�F�p�x�N�^�[
	/*Player�̓������֐���*/
	void Move(KeyState* Key);			//�L�����̍��W���ړ�
	void Attack(KeyState* Key);			//���^�[���L�[���X�y�[�X�L�[�������ꂽ���A���S��ԂłȂ��A�����s��ԂłȂ��e�ۂ�����s��Ԃɂ��ďI������
public:
	Player(void);
	~Player(void);
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//�v���C���[�̏�ԏ�����(��ɕ`��)
	void update(KeyState* Key,ImageLoader* loader);//�X�V�֐�
};

