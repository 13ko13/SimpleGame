#include "Item.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	//���a
	constexpr float kRadius = 16.0f;
	//�z�u���
	constexpr float kSettingSpaceX = 160;
	constexpr float kSettingSpaceY = 120;
	//�O���t�B�b�N�T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

Item::Item() :
	m_isExist(true),
	m_handle(-1),
	m_radius(0.0f)
{
}

Item::~Item()
{
}

void Item::Init(int handle)
{
	//������Ԃł͑��݂���
	m_isExist = true;

	//�O���t�B�b�N���󂯎��
	m_handle = handle;

	//�����_���Ȉʒu�ɒu��
	m_pos.x = GetRand(Game::kScreenWidth - kSettingSpaceX * 2) + kSettingSpaceX;
	m_pos.y = GetRand(Game::kScreenHeight - kSettingSpaceY * 2) + kSettingSpaceY;
	//���a�̐ݒ�
	m_radius = kRadius;
}

void Item::End()
{

}

void Item::Update()
{
	//���̃A�C�e�������݂��Ȃ��ꍇ�A���������ɏI���
	if (!m_isExist)
	{
		//�ȍ~�̏����͍s�킸�����Ŋ֐����I������
		return;
	}

	if (m_isExist)
	{

		//m_isExist = true�̎����s�����
	}
}

void Item::Draw()
{
	//���̃A�C�e�������݂��Ȃ��ꍇ�A���������ɏI���
	if (!m_isExist)
	{
		//�ȍ~�̏����͍s�킸�����Ŋ֐����I������
		return;
	}

	DrawRectGraph(static_cast<int>(m_pos.x - kWidth / 2), static_cast<int>(m_pos.y - kHeight / 2),
		0, 0, 32, 32,
		m_handle, true);

#ifdef _DEBUG
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		static_cast<int>(m_radius), GetColor(256, 0, 255), false);
#endif
}