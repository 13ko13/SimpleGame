#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Bg.h"

class SceneMain
{
public:
	SceneMain();  //�R���X�g���N�^
	~SceneMain(); //�f�X�g���N�^

	void Init();	//������
	void End();		//�I������
	void Update();	//���t���[���̍X�V
	void Draw();	//�`��

private:
	//�V�[�P���X
	enum Seq
	{
		SeqFadeIn,
		SeqGame,
		SeqClear,
		SeqGameover,

		SeqNum
	};

private:
	//�c��A�C�e�����̎擾
	int GetItemNum();

	//�V�[�P���X����Update������؂�ւ���
	void UpdateFadeIn();
	void UpdateGame();

	void UpdateClear();
	void UpdateGameover();

private:
	//�t�H���g�̃n���h��
	int m_scoreFontHandle;		//�c��H��\������t�H���g
	int m_resultFontHandle;		//�Q�[���I�[�o�[�A�N���A��\������t�H���g

	//�g�p����O���t�B�b�N
	int m_playerGraphHandle;	//�v���C���[�̃O���t�B�b�N
	int m_enemyGraphHandle;		//�G�̃O���t�B�b�N
	int m_itemGraphHandle;		//�A�C�e���̃O���t�B�b�N
	int m_bgGraphHandle;		//�w�i�̃O���t�B�b�N

	int m_mainBgmHandle;		//BGM
	int m_gameoverBgmHandle;		//�Q�[���I�[�o�[����BGM
	int m_itemGetSeHandle;		//�A�C�e���擾���̃T�E���h

	//�T�E���h�̉���
	int m_mainVolume;
	int m_gameoverVolume;

	//���݂̃V�[�P���X
	Seq m_gameSeq;
	int m_frameCount;

	//�t�F�[�h�̃t���[���� 0:�^����
	int m_fadeFrame;

	//�v���C���[
	Player m_player;
	//�G
	Enemy m_enemyTbl[16];
	//�W�߂�A�C�e��
	Item m_itemTbl[16];

	//�w�i
	Bg m_bg;
};

