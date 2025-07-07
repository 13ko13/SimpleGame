#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"

//#include <math.h>
#include <cmath>

namespace
{
	//�t�F�[�h�ɂ�����t���[����
	constexpr int kFadeFrame = 30;

}

SceneMain::SceneMain() :
	m_itemGetSeHandle(-1),
	m_scoreFontHandle(-1),
	m_playerGraphHandle(-1),
	m_enemyGraphHandle(-1),
	m_itemGraphHandle(-1),
	m_bgGraphHandle(-1),
	m_mainBgmHandle(-1),
	m_gameoverBgmHandle(-1),
	m_resultFontHandle(-1),
	m_mainVolume(0),
	m_gameoverVolume(0),
	m_gameSeq(SeqFadeIn),
	m_frameCount(0),
	m_fadeFrame(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()	//������
{
	//�Q�[���Ŏg�p����t�H���g���쐬
	m_scoreFontHandle = CreateFontToHandle("HGP�n�p�p�߯�ߑ�", 32, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	m_resultFontHandle = CreateFontToHandle("HGP�s����", 96, -1, -1);

	//�����V�[�P���X�̌���
	m_gameSeq = SeqFadeIn;
	m_frameCount = 0;

	//�t�F�[�h��Ԃ̏�����
	m_fadeFrame = 0;

	//�O���t�B�b�N�̃��[�h
	m_playerGraphHandle = LoadGraph("data/Idle.png");
	m_enemyGraphHandle = LoadGraph("data/Enemy.png");
	m_itemGraphHandle = LoadGraph("data/Melon.png");
	m_bgGraphHandle = LoadGraph("data/Mapchip.png");
	//�T�E���h�̃��[�h
	m_itemGetSeHandle = LoadSoundMem("data/ItemGet.mp3");
	m_mainBgmHandle = LoadSoundMem("data/MainBgm.mp3");
	m_gameoverBgmHandle = LoadSoundMem("data/GameoverBgm.mp3");

	//BGM�̍Đ��J�n
	m_mainVolume = 128;
	m_gameoverVolume = 0;

	PlaySoundMem(m_mainBgmHandle, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(170, m_mainBgmHandle);

	//�e�I�u�W�F�N�g�̏�����
	m_player.Init(m_playerGraphHandle);
	for (auto& enemy : m_enemyTbl)
	{
		enemy.Init(m_enemyGraphHandle);
	}

	for (auto& item : m_itemTbl)
	{
		item.Init(m_itemGraphHandle);
	}

	m_bg.Init(m_bgGraphHandle);
}

void SceneMain::End()			//�I������
{
	//BGM���~����
	StopSoundMem(m_mainBgmHandle);
	StopSoundMem(m_gameoverBgmHandle);

	m_player.End();
	for (auto& enemy : m_enemyTbl)
	{
		enemy.End();
	}

	for (auto& item : m_itemTbl)
	{
		item.End();
	}
	m_bg.End();
	//�t�H���g�̍폜
	DeleteFontToHandle(m_scoreFontHandle);
	DeleteFontToHandle(m_resultFontHandle);
	//�O���t�B�b�N�����
	DeleteGraph(m_playerGraphHandle);
	DeleteGraph(m_enemyGraphHandle);
	DeleteGraph(m_itemGraphHandle);
	DeleteGraph(m_bgGraphHandle);
	//�T�E���h���폜
	DeleteSoundMem(m_itemGetSeHandle);
	DeleteSoundMem(m_mainBgmHandle);
	DeleteSoundMem(m_gameoverBgmHandle);
}

void SceneMain::Update()	//���t���[���̍X�V
{
	//���݂̃V�[�P���X�̌o�߃t���[�������J�E���g
	m_frameCount++;
	switch (m_gameSeq)
	{
	case SeqFadeIn:
		UpdateFadeIn();
		break;
	case SeqGame:
		UpdateGame();
		break;
	case SeqClear:
		UpdateClear();
		break;
	case SeqGameover:
		UpdateGameover();
		break;
	}
	//UpdateGame();
}

void SceneMain::Draw()	//�`��
{
	m_bg.Draw();
	m_player.Draw();
	for (auto& enemy : m_enemyTbl)
	{
		enemy.Draw();
	}

	for (auto& item : m_itemTbl)
	{
		item.Draw();
	}
	//�c��A�C�e������\������
	int itemNum = GetItemNum();

	//��������ʉE��ɕ\������
	int strWidth = GetDrawFormatStringWidthToHandle(m_scoreFontHandle, "�̂���%d��", itemNum);

	DrawFormatStringToHandle(Game::kScreenWidth - strWidth, 16, //���W
		GetColor(255, 255, 255), m_scoreFontHandle, "�̂���%d��", itemNum);

	//�Q�[���N���A�\��
	if (itemNum == 0)
	{
		strWidth = GetDrawFormatStringWidthToHandle(m_resultFontHandle, "�ԍ�o�[���P���ԍ�o�[���P��");
		//int x = Game::kScreenWidth / 2 - strWidth / 2;
		int x = -3; //�V�с@//������������o������
		int y = Game::kScreenHeight / 2 - 96 / 2;
		DrawStringToHandle(x, y, "�ԍ�o�[���P�� �ԍ�o�[���P��", GetColor(240, 32, 32), m_resultFontHandle);
	}
	else if (m_player.IsDead()) //����ł�����
	{
		strWidth = GetDrawFormatStringWidthToHandle(m_resultFontHandle, "�ԍ�o���X");
		int x = Game::kScreenWidth / 2 - strWidth / 2;
		int y = Game::kScreenHeight / 2 - 96 / 2;
		DrawStringToHandle(x, y, "�ԍ�o���X", GetColor(240, 32, 32), m_resultFontHandle);

		if ((m_frameCount / 30) % 2)
		{
			strWidth = GetDrawFormatStringWidthToHandle(m_scoreFontHandle, "A:���g���C");
			x = Game::kScreenWidth / 2 - strWidth / 2;
			y = Game::kScreenHeight / 2 + 64;
			DrawStringToHandle(x, y, "A:���g���C", GetColor(240, 32, 255), m_scoreFontHandle);
		}

#ifdef _DEBUG
		//���ݎ��s���̃V�[���̃f�o�b�O�\��
		DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
		DrawString(0, 16, "X�{�^���ŃQ�[���N���A", GetColor(255, 255, 255));
#endif
		//�t�F�[�h�̕`��
		int fadeAlpha = 0;

		//�t���[���J�E���g���t�F�[�h�̐i�s�x(����)�ɕϊ�����
		float fadeProgress = static_cast<float>(m_fadeFrame) / kFadeFrame;
		//255 -> 0�ɕω����������̂Ŋ������t�]������ 0.0 -> 1.0  1.0 -> 0.0
		fadeProgress = 1.0f - fadeProgress;
		//�����������邱�ƂŌ��݂̃t�F�[�h�l�����肷��
		fadeAlpha = 255 * fadeProgress;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

int SceneMain::GetItemNum()
{
	int itemNum = 0;
	for (auto& item : m_itemTbl)
	{
		if (item.IsExist())
		{
			itemNum++;
		}
	}
	return itemNum;
}

void SceneMain::UpdateFadeIn()
{
	m_fadeFrame++;
	if (m_fadeFrame > kFadeFrame)
	{
		m_fadeFrame = kFadeFrame;
		//�t�F�[�h���ʊ��������̂ŃQ�[���{�̂ɑJ�ڂ���
		m_gameSeq = SeqGame;
		m_frameCount = 0;
		//printfDx("abc");
	}
	//�L�����N�^�[�͓������Ȃ��̂ňȍ~�Ă΂Ȃ�
}

void SceneMain::UpdateGame()
{
#ifdef _DEBUG
	//�{�^���ꔭ�ŃN���A�ł���f�o�b�O�@�\

	//X�{�^������������N���A�ɂȂ�悤�ɂ���
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//pad��X�{�^���������̓L�[�{�[�h��C���������Ƃ�
	if ((pad & PAD_INPUT_3) != 0) //&���Z:�r�b�g�P�ʂ̉��Z
	{
		//m_gameSeq = SeqCliar;
			//���������𖞂����悤�ȏ���������
		for (auto& item : m_itemTbl)
		{
			//���ׂẴA�C�e�����擾�ς݂̏�Ԃɂ���
			item.SetExist(false);
		}
	}
#endif

	m_player.Update();
	for (auto& enemy : m_enemyTbl)
	{
		enemy.Update();
	}

	for (auto& item : m_itemTbl)
	{
		item.Update();
	}
	m_bg.Update();

	//�v���C���[�ƓG�̓����蔻����Ƃ�
	const float playerX = m_player.GetPosX();
	const float playerY = m_player.GetPosY();
	const float playerRadius = m_player.GetRadius();
	for (auto& enemy : m_enemyTbl)
	{
		const float enemyX = enemy.GetPosX();
		const float enemyY = enemy.GetPosY();
		const float enemyRadius = enemy.GetRadius();

		//�O�����̒藝���g���ĉ~���m�̋��������߂�
		float distX = playerX - enemyX;
		float distY = playerY - enemyY;

		//������2������߂�
		float dist = (distX * distX) + (distY * distY);
		//������2��̕�����������
		dist = sqrtf(dist);

		if (dist < (playerRadius + enemyRadius))
		{
			/*printfDx("������������Ă�yo!\n");*/
			m_player.SetDead(true);
			m_gameSeq = SeqGameover;
			m_frameCount = 0;
			//BGM���Q�[���I�[�o�[�̎��̂��̂ɐ؂�ւ�
		//	StopSoundMem(m_mainBgmHandle);
			m_gameoverVolume = 0;
			PlaySoundMem(m_gameoverBgmHandle, DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(m_gameoverVolume, m_gameoverBgmHandle);
		}
	}


	//�v���C���[�ƃA�C�e���̓����蔻����擾����
	for (auto& item : m_itemTbl)
	{
		//���݂��Ȃ��A�C�e���͎擾�ł��Ȃ�
		if (!item.IsExist())
		{
			continue;
		}
		const float itemX = item.GetPos().x;
		const float itemY = item.GetPos().y;
		const float itemRadius = item.GetRadius();

		float distX = playerX - itemX;
		float distY = playerY - itemY;

		float dist = (distX * distX) + (distY * distY);
		dist = sqrtf(dist);
		if (dist < (playerRadius + itemRadius))
		{
			//	printfDx("�A�C�e���ɓ������Ă�!\n");
			item.SetExist(false);
			//	PlaySoundFile("data/ItemGet.mp3", DX_PLAYTYPE_BACK);
			PlaySoundMem(m_itemGetSeHandle, DX_PLAYTYPE_BACK);
		}
	}
	//�A�C�e���̐���0�ɂȂ�����Q�[���N���A
	if (GetItemNum() == 0)
	{
		m_gameSeq = SeqClear;
		m_frameCount = 0;
	}
}

void SceneMain::UpdateClear()
{
	m_player.Update();
}

void SceneMain::UpdateGameover()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((pad & PAD_INPUT_1) != 0)
	{
		m_player.Init(m_playerGraphHandle);
		for (auto& enemy : m_enemyTbl)
		{
			enemy.Init(m_enemyGraphHandle);
		}
		for (auto& item : m_itemTbl)
		{
			item.Init(m_itemGraphHandle);
		}
		m_bg.Init(m_bgGraphHandle);
		//BGM�{�����[���̍Đݒ�
		m_mainVolume = 128;
		m_gameoverVolume = 0;
		ChangeVolumeSoundMem(m_mainVolume, m_mainBgmHandle);
		StopSoundMem(m_gameoverBgmHandle);

		m_gameSeq = SeqGame;
		m_frameCount = 0;
	}


	m_mainVolume--;
	if (m_mainVolume < 0)
	{
		m_mainVolume = 0;
	}
	//gameover�̃{�����[���グ��
	m_gameoverVolume++;
	if (m_gameoverVolume > 128)
	{
		m_gameoverVolume = 128;
	}
	ChangeVolumeSoundMem(m_mainVolume, m_mainBgmHandle);
	ChangeVolumeSoundMem(m_gameoverVolume, m_gameoverBgmHandle);
}
