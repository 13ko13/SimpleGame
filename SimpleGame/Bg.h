#pragma once
class Bg
{
public:
	Bg();
	~Bg();

	void Init(int handle);
	void End();
	void Update();
	void Draw();

private:

	//�O���t�B�b�N�n���h��
	int m_handle;
	//�O���t�B�b�N�����ɉ��`�b�v�����邩�̏��
	int m_graphChipNumX;
};

