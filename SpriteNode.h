#pragma once
#include"stdafx.h"
#include"ImageLoader.h"
#include<stdarg.h>
#define DEFAULT_FONTSIZE 12	//デフォルトのフォントサイズ
//#define CHILDREN_MAX 16		//一つのスプライトノードが保有できる子スプライトの最大個数
/*スプライト一個のデータクラス。DrawSystemクラスにvectorで格納しID順に描画する*/
class SpriteNode
{
public:
	enum TYPE{
		NONE,
		IMAGE,	//画像
		TEXT,	//文字
		LINE,	//直線
		BOX,	//矩形
		CIRCLE,	//円
		PIXEL
	};
private:
	/*今は親子関係を作らない。面倒だけどすべてのスプライトを管理する
	double children_count;							//子スプライトの数
	SpriteNode *Parent,*Children[CHILDREN_MAX];	//スプライトの親と子のポインタ
	*/
	double m_x,m_y;							//スプライトの座標(画像と円の場合は画像の中心点、点は点そのもの。それ以外は左上の座標)
	int m_ID;								//スプライトの描画順を表すID(基本,大きいものほど手前に表示)
	TYPE m_type;								//スプライトのタイプ
	int m_color_r,m_color_g,m_color_b;			//色　画像以外に使用
	bool m_fill;								//塗りつぶすかどうか　矩形と円に使用
	int m_Blend_Mode,m_Blend_Pal;				//ブレンドモードとパラメータ(0~255)
	/*画像スプライトに使うメンバ変数*/
	int m_image_handler;						//イメージハンドラ
	double m_magni_w,m_magni_h;					//スプライトの拡大率。画像スプライトにのみ適用
	bool m_turn,m_trans;						//スプライトの左右反転(m_trans)と透過処理(m_trans)の有無
	double m_cx,m_cy;								//画像を回転させる中心点の座標
	double m_rad;								//画像の回転角(rad)

	/*文字スプライトに使うメンバ変数*/
	char m_text[STRING_MAX];
	char m_fontname[STRING_MAX];				//フォント名
	int m_fontsize;								//フォントサイズ

	/*直線・矩形スプライトに使うメンバ変数*/
	double m_w,m_h;								//幅と高さ

	/*円のスプライトに使うメンバ変数*/
	double m_radius;								//円の半径
public:
	SpriteNode(void);
	~SpriteNode(void);
	/*スプライトの親子関係関数*/
	/*今は親子関係を作らない。面倒だけどすべてのスプライトを管理する
	void Set_Parent(SpriteNode *parent);
	void add_Child(SpriteNode *child);			//子スプライトの追加。
	void remove_Child(SpriteNode *child);		//子スプライトの削除。子が削除された場合その子より下位層のスプライトも削除
	void Get_Children(SpriteNode *children[]);	//すべての子スプライトを取得する
	*/
	/*情報取得関数*/
	double Get_X(){return m_x;}										//X座標の取得
	double Get_Y(){return m_y;}										//Y座標の取得
	int Get_ID(){return m_ID;}										//Z座標の取得
	double Get_W();													//矩形幅の取得
	double Get_H();													//矩形高さの取得
	double Get_Center_X();											//中心X座標の取得
	double Get_Center_Y();											//中心Y座標の取得
	double Get_Radius();											//半径の取得
	SpriteNode::TYPE Get_Type(){return m_type;}

	void MoveTo(double x,double y);
	void Set_ID(int id);
	void Change_Color(int r,int g,int b);							//色設定。これを行わない場合は(0,0,0)
	void Blend_Setting(int mode,int pal);							//ブレンドモードのセットとパラメータの設定。これを行わない場合はブレンドモードは無い
	/*画像スプライトに使うメンバ関数*/
	void init_Image(ImageLoader* loader,char* item_name);			//アイテム名でローダーから画像を取ってくる。
	void init_Image(ImageLoader* loader,char* item_name,int index);	//アイテム名とインデックス(0スタート)でローダーからがぞうを取ってくる(add_divimageで登録したタイプの画像)
	void Image_Rotate(double rad);									//画像の回転角(rad)を設定。これを行わない場合は回転しない
	void Image_Magnificant(double w,double h);						//横とタテの拡大率設定。これを行わない場合は等倍
	void Image_Reverse();											//現在の状態から画像を反転。これを行わない場合は反転しない
	void Image_Trans(bool flg);										//透過処理を行うかどうかを設定。これを行わない場合は透過処理を行う
	void Image_Spin_Center(double cx,double cy);							//画像を回転させる中心点。これを行わない場合は中心点は画像の左上端
	/*文字スプライトに使うメンバ関数*/
	void init_Text(const char* text,...);										//文字列をセット
	void Text_Font(char *fontname);									//フォント設定
	void Text_Size(int size);										//文字サイズの設定
	/*直線・矩形スプライトに使うメンバ関数*/
	void init_Line(double x,double y);									//(0,0)からの終端座標で直線をセット
	void init_Box(double w,double h);										//幅と高さを設定して矩形をセット
	void Box_Fill(bool flg);										//矩形を塗りつぶすか否か
	/*円スプライトに使メンバ関数*/
	void init_Circle(double r);										//円の半径を設定
	void Circle_Fill(bool flg);										//円を塗りつぶすか否か
	/*点スプライトに使うメンバ関数*/
	void init_Pixel();												//点スプライトとして設定
	/*表示されないスプライトに使うメンバ関数*/						
	void init_None();												//表示したくないスプライトに使う
	/*描画に使う関数*/
	void DrawThis();												//このスプライトを描画する
};