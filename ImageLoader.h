#pragma once
#include"stdafx.h"
#include"ImageLoaderItem.h"
#define ITEM_MAX 1024 //ImageLoaderItem�̍ő�ۗL��
class ImageLoader
{
private:
	ImageLoaderItem *m_items[ITEM_MAX];				//ImageLoaderItem��ۊ�
	int m_count;									//���݂�Item�ۊǐ�
public:
	ImageLoader(void);
	~ImageLoader(void);
	int TheNumber_Items(){return m_count;}			//���A�C�e���������邩���擾
	int GetItemByName(char *name);					//���O�ŃA�C�e�����擾
	int GetItemByIndex(int index);					//�����ŃA�C�e�����擾(���ێg�����Ƃ͂Ȃ����낤���ꉞ)
	/*�d�l��A�����`�悳��Ă��Ȃ���ԂŃA�C�e����ǉ�����K�v������B*/
	void add_image(char *itemname,char *filename);	//�t�@�C���l�[���ŉ摜��ǉ�
	void add_divimage(char *itemname,char *filename,int AllNum,int XNum,int YNum,int Xsize,int Ysize);//��̉摜�𕪊����ĕ��������������摜��ǉ�
};

