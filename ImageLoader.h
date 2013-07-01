#pragma once
#include"stdafx.h"
#include"ImageLoaderItem.h"
#define ITEM_MAX 1024 //ImageLoaderItemの最大保有数
class ImageLoader
{
private:
	ImageLoaderItem *m_items[ITEM_MAX];				//ImageLoaderItemを保管
	int m_count;									//現在のItem保管数
public:
	ImageLoader(void);
	~ImageLoader(void);
	int TheNumber_Items(){return m_count;}			//今アイテムが何個あるかを取得
	int GetItemByName(char *name);					//名前でアイテムを取得
	int GetItemByIndex(int index);					//数字でアイテムを取得(実際使うことはないだろうが一応)
	/*仕様上、何も描画されていない状態でアイテムを追加する必要がある。*/
	void add_image(char *itemname,char *filename);	//ファイルネームで画像を追加
	void add_divimage(char *itemname,char *filename,int AllNum,int XNum,int YNum,int Xsize,int Ysize);//一つの画像を分割して分割した数だけ画像を追加
};

