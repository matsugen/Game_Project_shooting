#pragma once
#include"stdafx.h"
#include "Actor.h"
class Score_Board :
	public Actor
{
private:
	SpriteNode* m_back;
	SpriteNode* m_text;
	int m_point;
public:
	Score_Board(void);
	~Score_Board(void);
	void update(KeyState* Key,ImageLoader* loader);//�X�V�֐�
	void init(DrawSystem *ds,ImageLoader* loader,ActorManager* manager);//�A�N�^�[�������֐�
	void add_point();
	void reduce_point();
	int get_point(){return m_point;}
};

