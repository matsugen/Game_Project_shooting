#pragma once
#include"stdafx.h"
#include "Actor.h"
#include "Bullet.h"
#include"Misile.h"
#include"ImageLoader.h"
#include"DrawSystem.h"
//#include"ActorManager.h"
class Player :
	public Actor
{
public:
	enum BULLET_TYPE{
		VULCAN,
		MISILE,
		SHOTGUN
	};
private:
	/*�ړ��֌W�̕ϐ�*/
	int m_d;							//�L�����̕���
	int m_walk_time;
	int m_freeze_time;					//�����Ȃ�����
	/*�U���֌W�̕ϐ�*/
	int m_attack_num;					//�U���e���̌�
	Player::BULLET_TYPE m_type;		//�g���e�̎��
	double m_angle;						//����̊p�x
	/*�\���֌W�̕ϐ�*/
	SpriteNode* m_icon;					//�e�A�C�R��
	/*Player�̓������֐���*/
	void Move(KeyState* Key);			//�L�����̍��W���ړ�
	void Attack(KeyState* Key);			//���^�[���L�[���X�y�[�X�L�[�������ꂽ���A���S��ԂłȂ��A�����s��ԂłȂ��e�ۂ�����s��Ԃɂ��ďI������
	void Weapon_Change(KeyState* Key);
	/*Player����������e�̃A�N�^�[*/
	std::vector<Bullet*> m_bullet;		//�e�A�N�^�[�̑��݊m�F�p�x�N�^�[
	std::vector<Misile*> m_misile;		//�e�A�N�^�[�̑��݊m�F�p�x�N�^�[
public:
	Player(void);
	~Player(void);
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//�v���C���[�̏�ԏ�����(��ɕ`��)
	void update(KeyState* Key,ImageLoader* loader);//�X�V�֐�
};

