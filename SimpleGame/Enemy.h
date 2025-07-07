#pragma once
#include "Vec2.h"

class Enemy
{
public:
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();

	void Init(int handle);	//������
	void End();		//�I������

	void Update();	//���t���[��
	void Draw();	//�`��

	//�����蔻��̏��擾�p�֐�
	float GetPosX() const { return m_pos.x; }
	float GetPosY() const { return m_pos.y; }
	float GetRadius() const { return m_radius; }

	
private:
	//�����_���ɏ����ʒu��ݒ肷��
	void SetupPos();

private:
	//�O���t�B�b�N�n���h��
	int m_handle;
	//�\���ʒu
	Vec2 m_pos;
	//���a
	float m_radius;

	//�ړ����
	float m_moveX;
};

