#include "DxLib.h"
#include <math.h>

#define WIDTH 960
#define HEIGHT 640

#define PI 3.14159263589793

//列挙体/構造体ブッ宣言ゾーン
enum eWhatYouWant {
    eX,
    eY,
    eRAD,
    eALL,
};

template <typename T>
struct sParameter {
    T x;
    T y;
    int rad;
};
template <typename T>
struct sAxis {
    T x;
    T y;
};

//関数ブッ宣言ゾーン
template <typename T>
float twoPointDistance(T, T, T, T);

sAxis<int> getKeyState(void);

const unsigned colWhite = GetColor(255, 255, 255);

//クラス宣言
class cObject {
protected:
    sParameter<float> status;
public:
    cObject() : cObject(0, 0, 0) { }
    cObject(int xCenter, int yCenter, int rad) : status{(float)xCenter, (float)yCenter, rad} { }
    virtual ~cObject() = 0;
    float getStatus(eWhatYouWant is) {
        switch (is) {
        case(eX):
            return status.x;
            break;
        case(eY):
            return status.y;
            break;
        case(eRAD):
            return status.rad;
            break;
        default:
            return 0.0f;
        }
    }
};
cObject::~cObject() {}
//抽象クラスを作成するための純粋仮想関数ができなさそうなとき、仮想デストラクタを宣言する
//この時クラス外に仮想デストラクタの内容を上記のように名前解決演算子を使用して記述する

class cObstacle : public cObject {
public:
};

class cBall : public cObject{
private:
    float speed;
public:
    cBall() : cBall(0.0f, 0.0f, 0) { }
    cBall (float x, float y, int rad) : cObject(x, y, rad), speed(1.0f) { }

    void move(void) {
        status.x += speed;
        status.y += speed;
    }

    void drawBall(void) {
        DrawCircle(status.x, status.y, status.rad, colWhite, true);
    }
};

class cPaddle : public cObject {
private:
    int width;
    int height;
    float axel;
    
public:
    cPaddle() : cPaddle(0.0f, 0.0f, 0, 0) { }
    cPaddle(float xCenter, float yCenter, int paddleWidth, int paddleHeight) : cObject(xCenter, yCenter, 0), width(paddleWidth), height(paddleHeight), axel(0.1f) { }
    bool operator == (cObject &ball) const {
        if (ball.getStatus(eX) > status.x - width / 2 + ball.getStatus(eRAD) && ball.getStatus(eX) < status.x - width / 2 + ball.getStatus(eRAD)) {

        }
        //if(radSum > twoPointDistance(this->status.x, ball.getStatus(eX), this->status.y, ball.getStatus(eY)) ? true : false);
    }

    void move(sAxis<int> input) {
        axel += 0.1f; //もしボタンを重ねるように入力すると加速が受け継がれて高速で移動する仕様がありますが、面白いので対策は限界値のみとします
        status.x += axel * input.x;
        (input.x == 0 ? axel = 0.0f : NULL); //入力がなくなれば加速をゼロに
        (status.x - width / 2 < 0 ? status.x = width / 2 : NULL); //場外判定
        (status.x + width / 2 > WIDTH ? status.x = WIDTH - width / 2 : NULL); //上に同じ
        (axel >= 10.0f ? axel = 10.0f : NULL); //加速のマックス判定
    }

    void drawPaddle(void) {
        DrawBox(status.x - width / 2, status.y - height / 2, status.x + width / 2, status.y + height / 2, colWhite, true);
    }
};

//main部
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetWindowText("ブロック崩し");
    SetGraphMode(WIDTH, HEIGHT, 32);
    ChangeWindowMode(TRUE);
    SetBackgroundColor(0, 0, 0);
    SetDrawScreen(DX_SCREEN_BACK);
    SetMouseDispFlag(TRUE);

    const int paddleWidth = 50;
    const int paddleHeight = 10;
    const int ballRad = 10;
    
    cPaddle iPaddle(WIDTH / 2, (HEIGHT / 8) * 7, paddleWidth, paddleHeight);
    cBall iBall(WIDTH / 2, HEIGHT / 2, ballRad);

    while (!CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClearDrawScreen();
        iBall.drawBall();
        iPaddle.drawPaddle();
        iPaddle.move(getKeyState());
        DrawFormatString(0, 0, colWhite, "x: %d, y: %d", getKeyState().x, getKeyState().y);
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}

//関数実宣言
template <typename T>
float twoPointDistance(T x1, T x2, T y1, T y2) {
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

sAxis<int> getKeyState(void) {
    sAxis<int> input{ 0, 0 };
    if (CheckHitKey(KEY_INPUT_A)) {
        input.x = -1;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        input.x = 1;
    }
    return input;
}