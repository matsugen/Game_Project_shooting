#pragma once
#include"stdafx.h"
#include "GameScene.h"
#include"DrawSystem.h"
#include"KeyState.h"
#include"SpriteNode.h"
#include"Actor.h"
#include"ActorManager.h"
#include"ImageLoader.h"
#include"Score_Board.h"
class TestScene :
	public GameScene
{
private:
	void Collision_judge();
	Score_Board* m_score;
public:
	TestScene(void);
	~TestScene(void);
	GameScene* update(KeyState *Key);
	void Draw();
	void init(ImageLoader *loader);
};