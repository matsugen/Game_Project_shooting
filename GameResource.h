
#pragma once
/*�R���p�C����������`*/
#define COLLISION //COLLISION����`���ꂽ��Actor��Get_Collision,Set_Collision���g����悤�ɂȂ�B
#define COLLISION_ID 256
/*�Q�[���V�[���̃��\�[�X*/
#define PLAYABLE_WIDTH 400		//Player�������鍶�E�̕�
namespace GAME_RESOURCE_ID{
	enum DESCRIPTION_ID{
		BULLET=1,
		ENEMY,
		PLAYER
	};
}

#define MOVE_SPEED 4	//�v���C���[�A�N�^�[�̈ړ����x
/*Player�A�N�^�[�̌����Ă������*/
#define DIRECTION_DOWN 0		//������
#define DIRECTION_LEFT_DOWN 3	//��������
#define DIRECTION_LEFT 6		//������
#define DIRECTION_RIGHT_DOWN 9	//�E������
#define DIRECTION_RIGHT 12		//�E����
#define DIRECTION_LEFT_UP 15	//�������
#define DIRECTION_UP 18			//�����
#define DIRECTION_RIGHT_UP 21	//�E�����
#define PLAYER_WIDTH 40			//�v���C���[�A�C�R���̉���
#define PLAYER_HEIGHT 56		//�v���C���[�A�C�R���̂̏c��

/*�e�ۂ̃X�e�[�^�X*/
#define MAX_BULLET 7			//1��ʏ�ő��݂ł���e�̐�
#define BULLET_WIDTH 1.0f		//�e�ۂ̉���
#define BULLET_HEIGHT 30	//�e�ۂ̏c��
#define BULLET_SPEED 5.5f		//�e�ۂ̑��x
/*�~�T�C���̃X�e�[�^�X*/
#define MAX_MISILE 1			//1��ʏ�ő��݂ł���e�̐�
#define MISILE_WIDTH 11.0f		//�e�ۂ̉���
#define MISILE_HEIGHT 50.0f		//�e�ۂ̏c��
#define MISILE_MAX_SPEED 7.0f	//�e�ۂ̑��x

/*EnemyActor�̃X�e�[�^�X*/
#define ENEMY_SPEED_MAX 3.0f		//�G�̈ړ����x�ő�l
#define ENEMY_SPEED_MIN 2.0f		//�G�̈ړ����x�ŏ��l
#define ENEMY_WIDTH 40		//�G�A�C�R���̉���
#define ENEMY_HEIGHT 56		//�G�A�C�R���̂̏c��
#define ENEMYS_MAX 10		//1��ʏ�ɑ��݂ł���G�̍ő吔
#define CREATE_INTERVAL_MAX 200//�G�𐶐�����Ԋu(�P�ʂ̓t���[��)
#define CREATE_INTERVAL_MIN 100