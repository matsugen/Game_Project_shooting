#include "StdAfx.h"
#include "SpriteNode.h"


SpriteNode::SpriteNode(void)
{
	dprintfln("SpriteNode();");
	m_x=m_y=m_ID=0;								//座標はひとまず(0,0,0)に
	m_type=NONE;								//何も無いスプライトとして設定
	m_color_r=m_color_g=m_color_b=0;			//デフォルトは黒
	m_Blend_Mode=DX_BLENDMODE_NOBLEND;
	m_Blend_Pal=0;								//デフォルトはブレンドモードは無く、パラメータも0
	/*画像スプライトに使うメンバ変数*/
	m_image_handler=-1;							//LoadGraph関数はエラーでのみ-1を吐くので-1で初期化したほうが安心
	m_magni_w=m_magni_h=1.0;					//デフォルトは等倍
	m_turn=false;								//デフォルトでは反転しない
	m_trans=true;								//透過処理はデフォルトは行う
	m_cx=0,m_cy=0;								//ひとまず0で初期化
	m_rad=0;									//デフォルトでは回転しない

	/*文字スプライトに使うメンバ変数*/
	m_text[0]='\0';
	m_fontname[0]='\0';						//フォントは空文字列。Dxライブラリのデフォルトを用いる
	m_fontsize=DEFAULT_FONTSIZE;			//12がデフォルト

	/*直線・矩形スプライトに使うメンバ変数*/
	m_w=m_h=0;									//サイズ0で設定

	/*円のスプライトに使うメンバ変数*/
	m_radius=0;								//半径0で初期化
	m_fill=true;
}



SpriteNode::~SpriteNode(void)
{	
	dprintfln("\t~SpriteNode();");
	/*今は親子関係を作らない。面倒だけどすべてのスプライトを管理する
	delete Parent;
	Parent=0;
	for(double i=0;i<CHILDREN_MAX;i++){
		delete Children[i];
		Children[i]=0;
	}
	*/
	m_x=m_y=0;								//座標はひとまず(0,0,0)に
	m_ID=0;
	m_type=NONE;								//何も無いスプライトとして設定
	m_color_r=m_color_g=m_color_b=0;			//デフォルトは黒
	m_Blend_Mode=DX_BLENDMODE_NOBLEND;
	m_Blend_Pal=0;								//デフォルトはブレンドモードは無く、パラメータも0
	/*画像スプライトに使うメンバ変数*/
	m_image_handler=-1;							//LoadGraph関数はエラーでのみ-1を吐くので-1で初期化したほうが安心
	m_magni_w=m_magni_h=1.0;					//デフォルトは等倍
	m_turn=false;								//デフォルトでは反転しない
	m_trans=true;								//透過処理はデフォルトは行う
	m_cx=0,m_cy=0;								//ひとまず0で初期化
	m_rad=0;									//デフォルトでは回転しない

	/*文字スプライトに使うメンバ変数*/
	char* m_fontname="\0";						//フォントは空文字列。Dxライブラリのデフォルトを用いる
	double m_fontsize=-1;							//-1で初期化変更が無ければDxライブラリのデフォルト

	/*直線・矩形スプライトに使うメンバ変数*/
	m_w=m_h=0;									//サイズ0で設定

	/*円のスプライトに使うメンバ変数*/
	m_radius=0;								//半径0で初期化
}
	/*スプライトの親子関係関数*/
/*	今は親子関係を作らない。面倒だけどすべてのスプライトを管理する
	void SpriteNode::Set_Parent(SpriteNode *parent){				//親スプライトをセット
			Parent=parent;
	}
	void SpriteNode::add_Child(SpriteNode *child){	//子スプライトの追加。
		Children[children_count]=child;
		Children[children_count]->Set_Parent(this);
		children_count++;
	}
	void SpriteNode::remove_Child(SpriteNode *child){//子スプライトの削除。子が削除された場合その子より下位層のスプライトも削除
	}
*/
/*情報取得関数*/

	double SpriteNode::Get_W(){								//矩形幅の取得
		if(m_type==LINE||m_type==BOX){
			return m_w;
		}
		printf("矩形または直線モードでないため取得出来ません\n");
		return -1;
	}
	double SpriteNode::Get_H(){								//矩形高さの取得
		if(m_type==LINE||m_type==BOX){
			return m_h;
		}
		printf("矩形または直線モードでないため取得出来ません\n");
		return -1;
	}	
	double SpriteNode::Get_Center_X(){							//中心X座標の取得
		if(m_type==IMAGE){
			return m_cx;
		}
		printf("画像モードでないため取得出来ません\n");
			return -1;
	}
	double SpriteNode::Get_Center_Y(){							//中心Y座標の取得
		if(m_type==IMAGE){
			return m_cy;
		}
		printf("画像モードでないため取得出来ません\n");
			return -1;
	}
	double SpriteNode::Get_Radius(){							//半径座標の取得
		if(m_type==CIRCLE){
			return m_radius;
		}
		printf("円モードでないため取得出来ません\n");
			return -1;
	}

void SpriteNode::MoveTo(double x,double y){
	m_x=x;
	m_y=y;
}
void SpriteNode::Set_ID(int id){
	m_ID=id;
}
void SpriteNode::Change_Color(int r,int g,int b){							//色設定
	if(m_type==IMAGE||m_type==NONE){
		printf("カラーの設定ができないタイプです Type code:%d\n",m_type);
		return;
	}
	m_color_r=r;
	m_color_b=b;
	m_color_g=g;
}
void SpriteNode::Blend_Setting(int mode,int pal){							//ブレンドモードのセットとパラメータの設定
	m_Blend_Mode=mode;
	m_Blend_Pal=pal;
}
/*画像スプライトに使うメンバ関数*/
void SpriteNode::init_Image(ImageLoader* loader,char* item_name){			//アイテム名でローダーから画像を取ってくる。
	m_type=IMAGE;
	m_image_handler=loader->GetItemByName(item_name);
}
void SpriteNode::init_Image(ImageLoader* loader,char* item_name,int index){	//アイテム名とインデックス(0スタート)でローダーからがぞうを取ってくる(add_divimageで登録したタイプの画像)
	m_type=IMAGE;
	char name[256]="\0",number[NUMBER_MAX];
	sprintf_s(number,"%d",index);												//数値を文字化する
	strcat_s(name,item_name);
	strcat_s(name,number);												//名前と数字を連結
	m_image_handler=loader->GetItemByName(name);
}
void SpriteNode::Image_Rotate(double rad){									//画像の回転角(rad)を設定
	if(m_type!=IMAGE){
		printf("画像モードではないので角度設定ができません Type code:%d\n",m_type);
		return;
	}
	m_rad=rad;
}
void SpriteNode::Image_Magnificant(double w,double h){							//横とタテの拡大率設定
	if(m_type!=IMAGE){
		printf("画像モードではないので拡大率設定ができません Type code:%d\n",m_type);
		return;
	}
	m_magni_w=w;
	m_magni_h=h;
}
void SpriteNode::Image_Reverse(){											//現在の状態から画像を反転
	if(m_type!=IMAGE){
		printf("画像モードではないので反転設定ができません Type code:%d\n",m_type);
		return ;
	}
	m_turn=!m_turn;
}
void SpriteNode::Image_Trans(bool flg){						//透過処理を行うかどうかを設定
	if(m_type!=IMAGE){
		printf("画像モードではないので透過処理設定ができません Type code:%d\n",m_type);
		return ;
	}
	m_trans=flg;
}
void SpriteNode::Image_Spin_Center(double cx,double cy){							//画像を回転させる中心点
	if(m_type!=IMAGE){
		printf("画像モードではないので回転中心点の設定ができません Type code:%d\n",m_type);
		return ;
	}
	m_cx=cx;
	m_cy=cy;
}
/*文字スプライトに使うメンバ関数*/
void SpriteNode::init_Text(const char* text,...){										//文字列をセット
	m_type=TEXT;
	va_list ap ;

	va_start(ap,text) ;
    vsprintf_s(m_text,text,ap) ;
	va_end(ap) ;

}
void SpriteNode::Text_Font(char *fontname){									//フォント設定
	if(m_type!=TEXT){
		printf("文字モードではないのでフォント設定ができません Type code:%d\n",m_type);
		return ;
	}
	strcpy_s(m_fontname,_countof(m_fontname),fontname);
}
void SpriteNode::Text_Size(int size){										//文字サイズの設定
	if(m_type!=TEXT){
		printf("文字モードではないので文字サイズ設定ができません Type code:%d\n",m_type);
		return ;
	}
	m_fontsize=size;
}
/*直線・矩形スプライトに使うメンバ関数*/
void SpriteNode::init_Line(double x,double y){									//(0,0)からの終端座標で直線をセット
	m_type=LINE;
	m_w=x;
	m_h=y;
}
void SpriteNode::init_Box(double w,double h){										//幅と高さを設定して矩形をセット
	m_type=BOX;
	m_w=w;
	m_h=h;
}
void SpriteNode::Box_Fill(bool flg){										//矩形を塗りつぶすか否か
	if(m_type!=BOX){
		printf("矩形モードではないので塗りつぶし設定ができません Type code:%d\n",m_type);
		return ;
	}
	m_fill=flg;
}
/*円スプライトに使いメンバ関数*/
void SpriteNode::init_Circle(double r){										//円の半径を設定
	m_type=CIRCLE;
	m_radius=r;
}
void SpriteNode::Circle_Fill(bool flg){										//円を塗りつぶすか否か
	if(m_type!=CIRCLE){
		printf("円モードではないので塗りつぶし設定ができません Type code:%d\n",m_type);
		return ;
	}
	m_fill=flg;
}

/*点スプライトに使うメンバ関数*/

void SpriteNode::init_Pixel(){
	m_type=PIXEL;
}

/*何も表示しないスプライトとして初期化する。再利用する時のためにすべて初期化する。座標などのパラメータはそのまま*/
void SpriteNode::init_None(){
	m_type=NONE;								//何も無いスプライトとして設定
}

void SpriteNode::DrawThis(){
	int color=GetColor(m_color_r,m_color_g,m_color_b);
	SetDrawBlendMode(m_Blend_Mode,m_Blend_Pal);
	/*タイプを見て描画方法を変える*/
	switch(m_type){
	case IMAGE:
		DrawRotaGraph3((int)m_x,(int)m_y,(int)m_cx,(int)m_cy,m_magni_w,m_magni_h,m_rad,m_image_handler,m_trans,m_turn) ;
		break;
	case TEXT:
			SetFontSize(m_fontsize);
			ChangeFont(m_fontname);
		DrawString((int)m_x,(int)m_y,m_text,color);
		break;
	case LINE:
		DrawLine((int)m_x,(int)m_y,(int)(m_x+m_w),(int)(m_y+m_h),color);
		break;
	case BOX:
		DrawBox((int)m_x,(int)m_y,(int)(m_x+m_w),(int)(m_y+m_h),color,m_fill);
		break;
	case CIRCLE:
		DrawCircle((int)m_x,(int)m_y,(int)m_radius,color,m_fill);
		break;
	case PIXEL:
		DrawPixel((int)m_x,(int)m_y,color);
		break;
	/*タイプがNONE、あるいは万が一存在しないモードが指定されていればエラーを吐く。子スプライトも書かない*/
	case NONE:
		break;
	default:
		printf("スプライトが設定されていません\n");
		return;
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,m_Blend_Pal);
	
}
