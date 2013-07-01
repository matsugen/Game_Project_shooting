#pragma once
#include"stdafx.h"
#include "GameScene.h"
#include"DrawSystem.h"
#include"KeyState.h"
#include"SpriteNode.h"
#include"Actor.h"
#include"ActorManager.h"
#include"ImageLoader.h"
/*�Q�[���Ɏg�p����V�[���̊�b�ƂȂ�N���X�B�����h�����Ďg���B*/
class GameScene
{
protected:
	DrawSystem* m_drawsystem;		//�`��V�X�e���BGameScene�Ő�������B
	ImageLoader* m_loader;			//ImageLoader����摜���Ƃ��Ă���B�����GameLoop���玝���Ă���
	ActorManager* m_manager;		//�A�N�^�[���Ǘ�����t�@�N�g���BGameScene�Ő�������B
public:
	/*�Q�[���̃��[�h��񋓌^�ō���ăf�o�b�O�ȂǂŊm�F�ł���悤�ɂ���*/
	enum MODE{
		NONE,
		TEST
	};
	GameScene(void);
	virtual ~GameScene(void);
	virtual GameScene* update(KeyState* Key)=0;							//�t���[�����ƂɌĂяo�����V�[�����X�V����֐�
	virtual void Draw()=0;												//�t���[�����ƂɌĂяo�����`��֐�
	virtual void init(ImageLoader* loader)=0;							//�������������z�֐�
};

