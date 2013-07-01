#pragma once
#include"stdafx.h"
#include"SpriteNode.h"
/*描画システムクラス
	完全に2D描画用。手前か奥かを決定するためにz座標を用いているが、遠近感を表現していない。
	また、SpriteNodeを生成・保管する部分であるので当然こちらで削除も行う。
	MoveToなどといった操作はActor側にさせるため、Spriteを追加したらポインタを返す。
*/
class DrawSystem
{
private:
	/*	SpriteNodeをベクターで格納し、描画するときはz座標でマージソートして表示。
		現在不具合有り。ActorやSpriteNodeとの兼ね合いに注意。
	*/
	std::vector<SpriteNode*> m_Sprite;
public:
	DrawSystem(void);
	~DrawSystem(void);
	/*	登録されたSpriteNodeを描画する。その時、SpriteNodeのz座標でマージソートする
		ソートは昇順で、z座標が大きいものほど奥に描画される。
	*/
	void Draw();							//すべてのスプライトを描画。描画する際、
	/*	SpriteNodeを登録する
	TODO:
		以前はActor内のSpriteNodeをそのまま登録していたが、Actor側のSpriteNodeをdeleteしてもこちらに登録しているSpriteNodeが上手く削除されないので、
		add_Sprite(new SpriteNode())として登録する。
		この場合、SpriteNodeの初期化をどうするか、Actor側でどうやってSpriteNodeを操作するかという課題が生じる。
	*/
	SpriteNode* add_Sprite();				//スプライトを追加、Actorに操作させるためにポインタを返す。
	void remobe_Sprite(SpriteNode* sprite);	//引数と同じスプライトを削除。削除したものは同時にSAFE_DELETEする。
};

