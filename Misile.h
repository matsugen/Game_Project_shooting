#pragma once
class Misile:
	public Actor
{
private:
	SpriteNode* m_icon;	//�e�ۂ̃A�C�R��
	void Move();		//�e�ۂ̍��W�ړ��������s���B
public:
	Misile(void);
	Misile(Actor* parent);
	~Misile(void);
	void update(KeyState* Key,ImageLoader* loader);//�X�V�֐�
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//�A�N�^�[�������֐�
	void Hit();
	bool Kill();
	void On();
	void Off();
};

