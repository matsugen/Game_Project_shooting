// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once
//#define NDEBUG//�f�o�b�O���[�h����Ȃ��Ƃ��Ɏg���B�f�o�b�O���̓R�����g�A�E�g
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
/*���̃v���W�F�N�g�ȊO�ł��g���w�b�_(<>�Ŋ�������)*/
#include<string.h>
#include<DxLib.h>
#include<math.h>
#include<boost/shared_ptr.hpp>
#include<boost/make_shared.hpp>
#include<boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include<vector>
/*���̃v���W�F�N�g�ł̂ݎg���w�b�_(""�Ŋ���ׂ�����)*/
/*�f�o�b�O�p�w�b�_*/
#include"UsrDebug.h"
/*�l�ō�郊�\�[�X�w�b�_*/
#include"MainResource.h"
/*��̃^�C�g���Ɍ������w�b�_*/
#include"GameResource.h"
#include"Collision.h"
/*�Q�[���̓y�䕔��*/
#include"KeyState.h"
#include"GameLoop.h"
#include"SpriteNode.h"
#include"ImageLoader.h"
#include"DrawSystem.h"
#include"Actor.h"
#include"ActorManager.h"
#include"GameScene.h"
/*��̃^�C�g���Ɍ������w�b�_*/
#include"TestScene.h"
#include"Player.h"
#include"Bullet.h"
#include"Score_Board.h"
#include"Enemy.h"