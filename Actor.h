#pragma once
#include"stdafx.h"
#include"KeyState.h"
#include"DrawSystem.h"
#include"ImageLoader.h"
#include"ActorManager.h"
/*�v���C���[��CPU�̊��N���X*/
class Actor
{
protected:
	bool m_death_flg;											//�A�N�^�[�̎����
	bool m_init_flg;											//���̃A�N�^�[���������ς݂��ǂ����̃t���O�BActorManager�ɂď���������Ă��Ȃ���Ώ��������s��
	bool m_launch_flg;											//���̃A�N�^�[�����s��Ԃł��邩�̃t���O�BOn,Off�֐��ɂ���ĊǗ�����
	Actor* m_Parent;											//�A�N�^�[�̐e�̑��݂������B
	ActorManager* m_manager;									//���̃A�N�^�[���o�^����Ă���A�N�^�[�t�@�N�g���[���m�ہB���ꂪ�Ȃ��Ǝq�𐶐����鎞�ʓ|
	DrawSystem* m_drawsystem;									//���̃A�N�^�[�ɓo�^�����SpriteNode���Ǘ�
	ImageLoader* m_loader;										//�A�N�^�[�̃A�C�R���������Ă��郍�[�_�[
	double m_x,m_y;											//���C���ƂȂ�X�v���C�g�̍��W
#ifdef COLLISION
	std::vector<Collision*> m_collisions;						//�Q�[���ɂ��Collision�̓��e�͕ω����邪�A���̒�`���ɂ͕K��"Collision"�Ő錾���邱�ƁB
#endif
	void Collision_update();
public:
	Actor(void);
	virtual ~Actor(void);
	virtual void update(KeyState* Key,ImageLoader* loader)=0;						//�X�V�֐�:�h���N���X��private�Ɋe��X�V���܂Ƃ߂��֐�������A��������Ɏ��s����
	virtual void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager)=0;	//�A�N�^�[�������֐�
	bool IsDeath(){return m_death_flg;}												//�A�N�^�[�̎���Ԃ��m�F
	void Die(){m_death_flg=true;}
	bool Initialized(){return m_init_flg;}											//���̃A�N�^�[���������ς݂��ǂ������m�F
	void Ended_init(){m_init_flg=true;}
	bool Parent_Exist();															//���̃A�N�^�[�ɐe�����邩�ǂ������m�F
	double Get_X(){return m_x;}														//x���W�擾
	double Get_Y(){return m_y;}														//y���W�擾
	virtual bool Kill();															//�A�N�^�[�����ʎ��̓���B������`����true��Ԃ����ƂŃA�N�^�[�̍ė��p���\�ɂ���(new-delete�����炷)
	virtual void On();																//�A�N�^�[�����s��Ԃɕω�������B���̍ۂɕK�v�ȏ��������s��
	virtual void Off();																//�A�N�^�[�����s��Ԃɕω�������B
	bool Get_Launch_flg(){return m_launch_flg;}															//���s��Ԃ��ǂ������m�F����
#ifdef COLLISION
	std::vector<Collision*> Get_Collision();										//�Q�[���V�[��������̏������s�����߂Ɏg���B				
	void Add_Collision(C_OPTION option);											//�I�v�V����������Ă��̉���Collision��ǉ�����B
	virtual void Hit();															//�Q�[���V�[�����Ŕ��肪�Փ˂����ꍇ�ɌĂяo�����B
#endif
};

