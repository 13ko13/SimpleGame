#include "Player.h"
#include "Dxlib.h"
#include "Enemy.h"
#include "SceneMain.h"

//�萔��`
namespace
{
	//�v���C���[�̊J�n�ʒu
	constexpr int kPlayerStartX = 256;
	constexpr int kPlayerStartY = 128;
	//�v���C���[�O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
	//�A�j���[�V�������
	constexpr int kIdleAnimNum = 11;
	constexpr int kAnimWaitFrame = 5;	//�A�j��1�R�}������̃t���[����

	//�����蔻��̔��a
	constexpr float kDefaultRadius = 16.0f;

	//�ړ����x
	constexpr int kSpeed = 4;
}

//�R���X�g���N�^
// �R���X�g���N�^��Player�̃��������m�ۂ��ꂽ�Ƃ��A
// �����I�ɁA�ŏ��� �K���Ăяo�����
// 
//�R���X�g���N�^�ł��ׂẴ����o�[�ϐ��̏��������s���Ă���

//�R���X�g���N�^�ł̕ϐ��̏��������s���Ƃ��́y�R���X�g���N�^�������q�z
//���g���ď��������s��
Player::Player() :
	m_handle(-1),
	m_isDead(false),
	m_radius(0.0f),
	m_isTurn(false),
	m_animFrame(0)
{	
}

//�f�X�g���N�^
//����������������Ƃ��A
//�����I�ɁA �Ō�� �Ă΂��
Player::~Player()
{
	
}



void Player::Init(int handle)
{
	//�e�ϐ��̏�����
	m_handle = handle;
	m_isDead = false;
	m_pos.x = kPlayerStartX;
	m_pos.y = kPlayerStartY;
	m_radius = kDefaultRadius;
	m_isTurn = false;

	m_animFrame = 0;
}

void Player::End()
{
}

void Player::Update()
{
	m_animFrame++;
	if (m_animFrame >= kIdleAnimNum * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}
	

	//�R���g���[���[�̃{�^���̉����ꂽ��Ԃ��擾����
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((pad & PAD_INPUT_UP) != 0) //&���Z:�r�b�g�P�ʂ̉��Z
	{
		m_pos.y -= kSpeed;
	}
	if ((pad & PAD_INPUT_DOWN) != 0)
	{
		m_pos.y += kSpeed;
	}
	if ((pad & PAD_INPUT_LEFT) != 0)
	{
		m_pos.x -= kSpeed;
		m_isTurn = true;
	}
	if ((pad & PAD_INPUT_RIGHT) != 0)
	{
		m_pos.x += kSpeed;
		m_isTurn = false;
	}
}



void Player::Draw()
{
	//�A�j���[�V�����̃t���[��������\���������R�}�ԍ����v�Z�ŋ��߂�
	int animNo = m_animFrame / kAnimWaitFrame;

	//�A�j���[�V�����̐i�s�ɍ��킹�ăO���t�B�b�N�̐؂���ʒu��ύX����
	int srcX = kGraphWidth * animNo;
	int srcY = 0;
	
	DrawRectGraph(static_cast<int>(m_pos.x) - kGraphWidth / 2,
		static_cast<int>(m_pos.y) - kGraphHeight / 2,
		srcX,srcY,
		kGraphWidth,kGraphHeight,
		m_handle, true, m_isTurn
	);
#ifdef _DEBUG
	DrawCircle(static_cast<int>(m_pos.x),
			   static_cast<int>(m_pos.y),
			   static_cast<int>(m_radius),
			   GetColor(255, 255, 0), false
	          );
#endif
}