#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"


//�G�L�����N�^�[�̎���
//��ʔ������E�̂ǂ�������o�ꂷ��
//�E����o�Ă����獶�ցA������o�Ă�����E�ֈړ�����
//��ʊO�܂ňړ�������A�ēx���E�̂ǂ�������o�Ă���

namespace
{
	//�ړ����x
	constexpr float kSpeed = 5.0f;
	//���a
	constexpr float kDefaultRadius = 12.0f;
	//�v���C���[�O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 34;
	//�A�j���[�V�������
	constexpr int kRunAnimNum = 14;
}

Enemy::Enemy() :
	m_handle(-1),
	m_radius(0.0f),
	m_moveX(0.0f)
{
}

Enemy::~Enemy()
{

}

void Enemy::Init(int handle)
{
	m_handle = handle;
	m_radius = kDefaultRadius;
	
	SetupPos();

}

void Enemy:: End()
{
	
}

void Enemy::Update()
{
	m_pos.x += m_moveX;
	//��ʊO�ɏo���G���ēo�ꂳ����
	if (m_moveX < 0.0f)//���Ɉړ����Ă���G��
	{
		if (m_pos.x < 0.0f - m_radius)//��ʊO����O�ɏo����
		{
			SetupPos();
		}
	}
	if (m_moveX > 0.0f) //�E�Ɉړ����Ă���G��
	{
		if (m_pos.x > Game::kScreenWidth + m_radius) //��ʉE����O�ɏo����
		{
			SetupPos();
		}
	}
	
}

void Enemy::Draw()
{
	DrawRectGraph(static_cast<int>(m_pos.x) - kGraphWidth / 2,
				  static_cast<int>(m_pos.y) - kGraphHeight / 2,
				  0,0,kGraphWidth,kGraphHeight,
				  m_handle,true,false
				 );
//Release�łł́@���s���Ăق����Ȃ�������
//#ifdef _DEBUG �� #endif �ň͂�
//#ifdef _DEBUG �� #endif �ň͖��ꂽ������
//Debug�Ԃł͋@�\���邪�ARelease�Ԃł͋@�\���Ȃ�
#ifdef _DEBUG

	//�����蔻��̃f�o�b�O�\��
	//Release�Ԃł͕\�����Ȃ��悤�ɂ�����
	DrawCircle(static_cast<int>(m_pos.x),
			   static_cast<int>(m_pos.y),
			   static_cast<int>(m_radius),
			   GetColor(255, 0, 0), false);
#endif

//�t��Relese�łł̂ݎ��s��������������
//#ifdef NDEBUG �� #endif �ň͂�
#ifdef NDEBUG
#endif
}

void Enemy::SetupPos()
{
	if (GetRand(1))
	{
		//�E����o��
		m_pos.x = Game::kScreenWidth + m_radius;
		m_moveX = -kSpeed;
	}
	else
	{
		//������o��
		m_pos. x = 0 - m_radius;
		m_moveX = kSpeed;
	}
	m_pos.y = GetRand(Game::kScreenHeight - m_radius * 2) + m_radius;
}
