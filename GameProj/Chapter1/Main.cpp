#include "DxLib.h"
#include <string>
#include <iostream>
#include <vector>

constexpr int FUNC_SUCCESS = 0;
constexpr int FUNC_ERROR = -1;

//class Character {
//private:
//	bool is_right_slide = true;
//	std::string name{};
//	int slide_speed = 0;
//public:
//	int x = 0;
//	int y = 0;
//
//	Character(bool b, int xx, int yy, int s, std::string n) :
//		is_right_slide{ b }, x{ xx }, y{ yy }, slide_speed{ s }, name{ n } {}
//	~Character() {}
//
//	void slide() {
//		x += slide_speed;
//	}
//};
//
//std::vector<Character> characters{};

int draw_image(int x, int y, std::string& image_path) {
	// �t�@�C���p�X���w�肵�C�f�B�X�N��̃t�@�C����\������B
	// �f�B�X�N����read���ĕ\�����邽�ߒᑬ�C�e�X�g�݂̂Ŏg���֐��Ƃ̂��ƁB
	//LoadGraphScreen(50, 100, img_path.c_str(), TRUE);

	// ��ʓI�Ɏg����摜�\����@�B�܂��摜���������ɍڂ��C�n���h�����擾�B
	// �Q�[�����̂�����NowLoading...�̂Ƃ��Ƃ��ɂ���Ă�Ƃ̂��ƁB
	int img_handler = LoadGraph(image_path.c_str());
	if (img_handler == -1) {
		std::cerr << "LoadGraph error. image_path = " << image_path << std::endl;
		return FUNC_ERROR;
	}

	//for (auto& c : characters) {
	//	if (DrawGraph(c.x, c.y, img_handler, TRUE)) {
	//		std::cerr << "DrawGraph error" << std::endl;
	//		return FUNC_ERROR;
	//	}
	//	c.slide();
	//}

	// �擾�����n���h�����w�肵�`��B
	if (DrawGraph(x, y, img_handler, TRUE)) {
		std::cerr << "DrawGraph error" << std::endl;
		return FUNC_ERROR;
	}

	if (DrawGraph(x / 2, y + 100, img_handler, TRUE)) {
		std::cerr << "DrawGraph error" << std::endl;
		return FUNC_ERROR;
	}

	if (DrawGraph(x / 4, y + 200, img_handler, TRUE)) {
		std::cerr << "DrawGraph error" << std::endl;
		return FUNC_ERROR;
	}

	// ����ʂɕ`�悵���摜��\��ʂɔ��f�B
	if (ScreenFlip()) {
		std::cerr << "ScreenFlip error" << std::endl;
		return FUNC_ERROR;
	}
	// ��ʂ��N���A����BScreenFlip�d�l���ɁC���s��Clear����Ƃ���̂ŁC�����Ŏ��s�B
	if (ClearDrawScreen()) {
		std::cerr << "ClearDrawScreen error" << std::endl;
		return FUNC_ERROR;
	}
	return FUNC_SUCCESS;
}

bool is_exit_requested() {
	// ESC�L�[�����͂��ꂽ��I��
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		return TRUE;
	}
	// ProcessMessage�͂����Ɨ����ł��Ă��Ȃ��B
	// �E�B���h�E�́~�������ꂽ��I�����������C���߂̏����B
	// �ڍׂ͎����Q�� http://dxlib.o.oo7.jp/dxfunc.html#R1N3
	if (ProcessMessage()) {
		return TRUE;
	}
	return FALSE;
}

//void init_characters() {
//	characters.push_back(Character{ true, 0, 0, 2, std::string{"character1"} });
//	characters.push_back(Character{ true, 0, 100, 4, std::string{"character2"} });
//	characters.push_back(Character{ true, 0, 200, 8, std::string{"character3"} });
//}

int exec_main() {
	std::string img_path = "../�摜/�L�����N�^01.png";
	//draw_image(50, 100, img_path);

	//init_characters();s

	int x = 100;
	constexpr int sleep_msec = 7;
	while (!is_exit_requested()) {
		if (draw_image(x, 100, img_path))
			break;
		x += 2;
	}
	return FUNC_SUCCESS;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// DX���C�u�����̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	// �`���𗠉�ʂɐݒ肷��(�`��r���̉摜���\������Ă��܂����ƂȂǂ�h�~���邽��)
	// �ڍׂ͎����Q�� http://dxlib.o.oo7.jp/function/dxfunc_graph3.html#R4N6
	SetDrawScreen(DX_SCREEN_BACK);

	// �_��ł�
	//DrawPixel(320, 240, GetColor(255, 255, 255));

	exec_main();

	// �L�[���͑҂�
	//WaitKey();

	// DX���C�u�����g�p�̏I��
	DxLib_End();

	return 0;
}
