#include "StdAfx.h"
#include "ImageLoader.h"

ImageLoader::ImageLoader(void)
{
	dprintfln("ImageLoader();");
	for(int i=0;i<ITEM_MAX;i++){
		m_items[i]=0;
	}
	m_count=0;
}


ImageLoader::~ImageLoader(void)
{
	dprintfln("~ImageLoader();");
	for(int i=0;i<m_count;i++){
		delete m_items[i];
		m_items[i]=0;
	}
}

int ImageLoader::GetItemByName(char *name){	//名前でアイテムを取得

	for(int i=0;i<m_count;i++){
		ImageLoaderItem *item=m_items[i];
		if(strcmp(name,item->Name())==0) return item->Handler();
	}
	dprintfln("%sという名前の画像は存在しません", name);
	return -1;								//失敗した場合は-1を返す
}

int ImageLoader::GetItemByIndex(int index){	//数字でアイテムを取得(実際使うことはないだろうが一応)
	if((m_count-1)<index) {
		dprintfln("%dに画像が存在しません",index);
		return -1;		//失敗した場合は-1を返す
	}
	return m_items[index]->Handler();
}


void ImageLoader::add_image(char *itemname,char *filename){				//ファイルネームで画像を追加
	int handler=LoadGraph(filename);
	if(handler==-1){
		dprintfln("%sが存在しないか、読み込みに失敗しました",filename);
	}else{
		m_items[m_count]=new ImageLoaderItem();
		m_items[m_count]->init(handler,itemname);
		m_count++;
	}
}
void ImageLoader::add_divimage(char *itemname,char *filename,int AllNum,int XNum,int YNum,int Xsize,int Ysize){//一つの画像を分割して分割した数だけ画像を追加
	int i;
	if(AllNum>(ITEM_MAX+m_count)){ 
		dprintfln("合計%d個以上画像を追加できません",ITEM_MAX);
		return;
	}
	int handler[ITEM_MAX]={0};
	if(LoadDivGraph(filename,AllNum,XNum,YNum,Xsize,Ysize,handler)==-1){//handlerに分割した画像のハンドラをセット
		dprintfln("%sが存在しないか、読み込みに失敗しました",filename);
	}else{
		for(i=0;i<AllNum;i++){
			char Name[256]="\0";
			char number[24];
			sprintf_s(number,"%d",i);//設定したアイテムネームのあとに数字を連結しておく。 ex) "item_name0","item_name1",...
			strcat_s(Name,itemname);
			strcat_s(Name,number);
			m_items[i+m_count]=new ImageLoaderItem();
			m_items[i+m_count]->init(handler[i],Name);
		}
		m_count=m_count+AllNum;
	}
}