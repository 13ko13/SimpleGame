#include "DxLib.h"
#include "Game.h"


#include "SceneMain.h"




namespace
{
	
}



// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h�ݒ�
	ChangeWindowMode(true);
	//�E�B���h�E�̃^�C�g���ύX
	SetMainWindowText("�Q�[����");
	//��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�`��Ώۂ��o�b�N�o�b�t�@�ɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	SceneMain scene;
	scene.Init();
		
	while (ProcessMessage() != -1)
	{
		//���̃t���[���̊J�n���Ԃ��擾
		LONGLONG start = GetNowHiPerformanceCount();

		//�O�̃t���[���ɕ`�悵�����e���N���A����
		ClearDrawScreen();

		//�����ɃQ�[���̏���������
		scene.Update();
				
		//�L�����N�^�[�̕`��
		scene.Draw();
		
		//�`�悵�����e����ʂɔ��f����
		ScreenFlip();

		//esc�L�[����������Q�[���������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		

		//�t���[�����[�g60�ɌŒ�
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}
	}

	//��������̃O���t�B�b�N�����
	scene.End();
	
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

