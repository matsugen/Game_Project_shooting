#pragma once
#include"stdafx.h"
#include"Actor.h"
/*�e�ۃN���X*/
/*
�e����������N���X�ŁA���ˎ�(������)���ݐe�ɒǐ�����B
���̂��߃R���X�g���N�^�ɐe�ƂȂ�A�N�^�[�������Ɏ��҂�����(new Bullet(this)�ȂǂŐe�A�N�^�[�͎��g�������Ƃ���)����B
*/

class Bullet :
	public Actor
{
private:
	SpriteNode* m_icon;	//�e�ۂ̃A�C�R��
	void Move();		//�e�ۂ̍��W�ړ��������s���B
public:
	Bullet(void);
	Bullet(Actor* parent);
	~Bullet(void);
	void update(KeyState* Key,ImageLoader* loader);//�X�V�֐�
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//�A�N�^�[�������֐�
	void Hit();
	bool Kill();
	void On();
	void Off();
};

