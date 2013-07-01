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

int ImageLoader::GetItemByName(char *name){	//���O�ŃA�C�e�����擾

	for(int i=0;i<m_count;i++){
		ImageLoaderItem *item=m_items[i];
		if(strcmp(name,item->Name())==0) return item->Handler();
	}
	dprintfln("%s�Ƃ������O�̉摜�͑��݂��܂���", name);
	return -1;								//���s�����ꍇ��-1��Ԃ�
}

int ImageLoader::GetItemByIndex(int index){	//�����ŃA�C�e�����擾(���ێg�����Ƃ͂Ȃ����낤���ꉞ)
	if((m_count-1)<index) {
		dprintfln("%d�ɉ摜�����݂��܂���",index);
		return -1;		//���s�����ꍇ��-1��Ԃ�
	}
	return m_items[index]->Handler();
}


void ImageLoader::add_image(char *itemname,char *filename){				//�t�@�C���l�[���ŉ摜��ǉ�
	int handler=LoadGraph(filename);
	if(handler==-1){
		dprintfln("%s�����݂��Ȃ����A�ǂݍ��݂Ɏ��s���܂���",filename);
	}else{
		m_items[m_count]=new ImageLoaderItem();
		m_items[m_count]->init(handler,itemname);
		m_count++;
	}
}
void ImageLoader::add_divimage(char *itemname,char *filename,int AllNum,int XNum,int YNum,int Xsize,int Ysize){//��̉摜�𕪊����ĕ��������������摜��ǉ�
	int i;
	if(AllNum>(ITEM_MAX+m_count)){ 
		dprintfln("���v%d�ȏ�摜��ǉ��ł��܂���",ITEM_MAX);
		return;
	}
	int handler[ITEM_MAX]={0};
	if(LoadDivGraph(filename,AllNum,XNum,YNum,Xsize,Ysize,handler)==-1){//handler�ɕ��������摜�̃n���h�����Z�b�g
		dprintfln("%s�����݂��Ȃ����A�ǂݍ��݂Ɏ��s���܂���",filename);
	}else{
		for(i=0;i<AllNum;i++){
			char Name[256]="\0";
			char number[24];
			sprintf_s(number,"%d",i);//�ݒ肵���A�C�e���l�[���̂��Ƃɐ�����A�����Ă����B ex) "item_name0","item_name1",...
			strcat_s(Name,itemname);
			strcat_s(Name,number);
			m_items[i+m_count]=new ImageLoaderItem();
			m_items[i+m_count]->init(handler[i],Name);
		}
		m_count=m_count+AllNum;
	}
}