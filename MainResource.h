/*�Q�[���̊�b�����ɐݒ肷�郊�\�[�X*/
#pragma once

/*���ׂẴQ�[���Ɏg�����`*/
#define SAFE_DELETE(x) if(x){delete x;x=0;}
#define SAMPLE_NUM 60
#define KEYNUM 256			//DX���C�u�����ŗp����L�[���i�[����L�[�̐�
#define FPS 60				//�Q�[����fps(frame per second)�̒l
#define BACKGROUND_R 0xff	//������������ʂ̔w�i�F�̐�
#define BACKGROUND_G 0xff	//�����
#define BACKGROUND_B 0xff	//�����
#define WINDOW_WIDTH 640	//�Q�[����ʂ̉��𑜓x
#define WINDOW_HEIGHT 480	//�Q�[����ʂ̃^�e�𑜓x
#define COLOR_BIT 16		//�Q�[���̃r�b�g��
#define PI	3.1415926535897932384626433832795f//�~����
#define NUMBER_MAX 8	//�Y���Ɏg���鐔���̍ő包��
#define STRING_MAX 256	//�������̍ő吔

#define BACK_GROUND_ID -1
#define FRONT_GROUND_ID 0