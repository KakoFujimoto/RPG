#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // DX���C�u�����̏�����
    if (DxLib_Init() == -1) {
        return -1;
    }

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // �v���C���[�̍��W
    int playerX = 320;
    int playerY = 240;

    while (ProcessMessage() == 0) {
        ClearDrawScreen();

        DrawString(playerX, playerY, "P", GetColor(255, 255, 255));

        ScreenFlip(); // ����ʂƕ\��ʂ����ւ�
    }

    DxLib_End();
    return 0;
}