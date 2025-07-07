#pragma once
#include "Vec2.h"

//�v���C���[�N���X
class Player
{

	
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//�Q�[�����ɓo�ꂷ�镨�̂Ɏ������郁���o�[�֐��̒�Ԃ����݂���
	void Init(int handle); //������
	void End();  //�I������

	void Update(); //���t���[���̍X�V�����@�L�����N�^�[�̈ړ��Ȃ�
	void Draw();	//Update()�ł̍X�V�𓥂܂��ĕ`����s��

	//�����蔻��̏��擾�p�֐�
	float GetPosX() const { return m_pos.x; }
	float GetPosY() const { return m_pos.y; }
	float GetRadius() const { return m_radius; }
//	float GetPosX() const;	//�錾�����̂݊e�ꍇ�͂���Ȋ���

	//���S���̐ݒ�
	void SetDead(bool isDead) { m_isDead = isDead; }
	//���S���̎擾
	bool IsDead() const { return m_isDead; }

private:
	//�����o�[�ϐ�
	int m_handle; //�O���t�B�b�N�n���h��

	//�����Ă��邩����ł��邩
	bool m_isDead;

//	int m_x;	  //���S���WX
//	int m_y;	  //���S���WY
	Vec2 m_pos;	
	//�����蔻��̔��a
	float m_radius;


	bool m_isTurn;//���E���]���邩

	//�A�j���[�V�����֘A

	int m_animFrame;	//�A�j���[�V�����̃t���[����
};



