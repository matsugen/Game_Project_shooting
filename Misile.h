#pragma once
class Misile:
	public Actor
{
private:
	double m_move_time;	//�~�T�C���̏o������̎���
	double m_angle;		//�~�T�C���̕���
	SpriteNode* m_icon;	//�e�ۂ̃A�C�R��
	void Move();		//�e�ۂ̍��W�ړ��������s���B
	double Misile_Speed();
	SpriteNode* m_dbg;
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

