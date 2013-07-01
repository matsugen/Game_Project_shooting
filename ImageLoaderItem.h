#pragma once
#include"stdafx.h"
class ImageLoaderItem
{

private:
	static int m_count;							//imageloaderitemの総数。デバッグ用
	int image_handler;							//画像ハンドラ
	char image_name[STRING_MAX];				//画像の名前(これをつかって検索)
public:
	ImageLoaderItem(void);
	~ImageLoaderItem(void);
	void init(int handler,char *image_name);	//アイテム情報をセットする。
	int Handler(){return image_handler;}		//ハンドラの取得
	char* Name(){return image_name;}			//画像の名前の取得
};

