#include "DxLib.h"

namespace System {
    bool Update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }
}

void Main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    DxLib::SetOutApplicationLogValidFlag(FALSE);
    DxLib::ChangeWindowMode(TRUE);
    DxLib::SetGraphMode(1280, 720, 32);
    DxLib::SetMainWindowText("PathPlanning");
    if (DxLib::DxLib_Init() == -1) return -1;
    DxLib::SetDrawScreen(DX_SCREEN_BACK);
    Main();
    return DxLib::DxLib_End();
}

void Main() {

    while (System::Update()) {



    }

}