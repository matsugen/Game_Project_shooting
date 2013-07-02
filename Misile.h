#pragma once
class Misile:
	public Actor
{
private:
	double m_move_time;	//�~�T�C���̏o������̎���
	double m_angle;		//�~�T�C���̕���
	SpriteNode* m_icon;	//�e�ۂ̃A�C�R��
	bool m_bomb_flg;	//�~�T�C���������������̔����̃t���O
	int m_bomb_time;	//�����̎���
	void Move();		//�e�ۂ̍��W�ړ��������s���B
	double Misile_Speed();
	void Bomb();		//�����𗯂߂�B
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

