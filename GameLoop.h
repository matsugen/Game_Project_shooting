#pragma once
#include"stdafx.h"
#include"GameScene.h"
#include"ImageLoader.h"
#include"KeyState.h"
/*�Q�[���̃��C������*/
class GameLoop
{
private:
	/*���Ԍv���p*/
	double draw_time;
	double update_time;
	int init_time;
	int elasped_time;
	/**/
	int m_StartTime;						//����J�n����
	int m_Count;							//�J�E���^
	float m_Fps;							//fps
	GameScene* m_Scene;						//�Q�[���̏������̂���
	KeyState* m_Key;						//�L�[���͏��
	bool m_game_quit;						//�Q�[�����I�����ǂ����̃t���O
	ImageLoader* m_loader;					//�Q�[�����ɉ摜��ۊǂ��郍�[�_�[
public:
	GameLoop(void);
	~GameLoop(void);
	void init(GameScene::MODE mode);		//���[�h���w�肵�ăQ�[����������
	void update();							//�t���[���J�n���̃A�b�v�f�[�g
	void draw();							//�t���[���I�����ɌĂяo���`��֐�
	bool IsQuit(){return m_game_quit;}		//�Q�[�����I����Ԃ��ǂ����̎擾
	void wait();
};