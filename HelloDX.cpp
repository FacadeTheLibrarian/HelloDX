//#include "DxLib.h"
//#include <math.h>
//
//#define WIDTH 960
//#define HEIGHT 640
//
//#define PI 3.14159263589793
//
//template <typename T>
//struct sAxis {
//    T x;
//    T y;
//};
//
//template <typename T>
//float twoPointDistance(T, T);
//template <typename T>
//float twoPointDistance(T, T, T, T);
//
//int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
//    if (DxLib_Init() == -1)
//    {
//        return -1;
//    }
//
//    SetWindowText("テンプレートは超便利");
//    SetGraphMode(WIDTH, HEIGHT, 32);
//    ChangeWindowMode(TRUE);
//    SetBackgroundColor(0, 0, 0);
//    SetDrawScreen(DX_SCREEN_BACK);
//    SetMouseDispFlag(TRUE);
//
//    const unsigned colWhite = GetColor(255, 255, 255);
//    const unsigned short fixedCircleRad = 100;
//    const unsigned short movingCircleRad = 50;
//    const sAxis<int> fixedCircle = { WIDTH / 2, HEIGHT / 2 };
//    sAxis<int> mousePos = { 0, 0 };
//    sAxis<float> circlePosOnCollision = { 0.0f, 0.0f };
//    sAxis<float> relPos = { 0.0f, 0.0f };
//
//    float atanVal = 0;
//
//    while (!CheckHitKey(KEY_INPUT_ESCAPE)) {
//        ClearDrawScreen();
//        GetMousePoint(&mousePos.x, &mousePos.y);
//        relPos.x = (float)(fixedCircle.x - mousePos.x);
//        relPos.y = (float)(fixedCircle.y - mousePos.y);
//        DrawCircle(fixedCircle.x, fixedCircle.y, fixedCircleRad, colWhite, TRUE);
//
//        if ((fixedCircleRad + movingCircleRad) > twoPointDistance<float>(relPos.x, relPos.y)){
//            DrawFormatString(0, 60, colWhite, "接触");
//            atanVal = atan2(relPos.y, relPos.x) + PI;
//
//            circlePosOnCollision.x = fixedCircle.x + cos(atanVal) * (fixedCircleRad + movingCircleRad);
//            circlePosOnCollision.y = fixedCircle.y + sin(atanVal) * (fixedCircleRad + movingCircleRad);
//            DrawCircle(circlePosOnCollision.x, circlePosOnCollision.y, movingCircleRad, colWhite, TRUE);
//        }
//        else {
//            DrawCircle(mousePos.x, mousePos.y, movingCircleRad, colWhite, TRUE);
//        }
//        DrawFormatString(0, 0, colWhite, "マウスの座標 x: %d, y: %d", mousePos.x, mousePos.y);
//        DrawFormatString(0, 20, colWhite, "接触時の座標 x: %f, y: %f", circlePosOnCollision.x, circlePosOnCollision.y);
//        DrawFormatString(0, 40, colWhite, "atan2の値: %f", atanVal);
//
//        ScreenFlip();
//    }
//
//    DxLib_End();
//    return 0;
//}
//
//template <typename T>
//float twoPointDistance(T x, T y) {
//    return sqrtf(x * x + y * y);
//}
//
//template <typename T>
//float twoPointDistance(T x1, T x2, T y1, T y2) {
//    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
//}