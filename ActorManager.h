#pragma once
#include"stdafx.h"
/*
TODO:
*/
/*�V�[���̒��ɂ���A�N�^�[���Ǘ�����N���X*/
/*
	Actor�̔h���N���X�𐶐��E�ۊǂ��邽�߁A���R�폜�����̃N���X���S���B
*/
class Actor;
#include"Actor.h"
class ActorManager
{
private:
	std::vector<Actor*> m_Actor;											//�Ǘ�����A�N�^�[��ۊǂ���x�N�^�[
	int m_count;															//�A�N�^�[�̐�
public:
	ActorManager(void);
	~ActorManager(void);
	void update(KeyState* Key,ImageLoader* loader);							//�Ǘ�����Ă��邷�ׂẴA�N�^�[�̍X�V�����s����Bnull�ɂȂ����A�N�^�[�͍폜����
	void init(DrawSystem* ds,ImageLoader* loader,ActorManager* manager);	//�Ǘ�����Ă��邷�ׂẴA�N�^�[�̏��������s��
	Actor* add_actor(Actor* actor);											//�A�N�^�[���t�@�N�g���ɒǉ�����B�֐����ŃC���X�^���X�����A���̃|�C���^��Scene���ɊǗ������邽�߃|�C���^��Ԃ�
	void remove_actor(Actor* actor);										//�w�肵���A�N�^�[���폜����B��{�I�ɂ�Actor::m_death_flg���g���č폜����邪�A�f�X�g���N�^�Ȃǂł͂�������g��
	std::vector<Actor*> Get_AllActors();									//���ׂẴA�N�^�[���擾�Bvector�̌`��
};