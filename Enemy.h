#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
private:
	SpriteNode* m_icon;
	int m_Emergency_interval;	//����������o���܂ł̎���
	int m_alpha;				//�G�A�C�R���̓����x�B���ʂƂ��ɏ����Ă����A0�ɂȂ�Ə���
	double m_speed;				//�G�̈ړ����x�B�����ŏo��
	void Launch();
	void Move();
	void Death();
public:
	Enemy(void);
	~Enemy(void);	
	void update(KeyState* Key,ImageLoader* loader);							//�X�V�֐�:�h���N���X��private�Ɋe��X�V���܂Ƃ߂��֐�������A��������Ɏ��s����
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);	//�A�N�^�[�������֐�
	void Hit();																//�Q�[���V�[�����Ŕ��肪�Փ˂����ꍇ�ɌĂяo�����B
	bool Kill();															//enemy�͎��񂾎��A�I�u�W�F�N�g�ȊO�����ׂď���������B
	void On();
};

