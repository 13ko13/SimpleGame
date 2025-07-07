#pragma once
#include "Vec2.h"

class Item
{
public:
	Item();
	~Item();

	void Init(int handle);
	void End();
	void Update();
	void Draw();

	Vec2 GetPos() const { return m_pos; }
	float GetRadius() const { return m_radius; }

	//�A�C�e���擾����m_isExist��false�ɂ��邽�߂̊֐�
	void SetExist(bool isExist) {  m_isExist = isExist; }

	//���̃A�C�e�����Q�[�����ɑ��݂��邩
	bool IsExist() const { return m_isExist; }

	//�O���t�B�b�N�n���h��
	int m_handle;

private:

	//���̃A�C�e�����Q�[�����ɑ��݂��邩
	bool m_isExist;

	Vec2 m_pos;
	float m_radius;
};

