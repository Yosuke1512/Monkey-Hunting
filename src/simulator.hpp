#ifndef     Simulator_HPP
#define     Simulator_HPP

#include <SDL3/SDL.h>
#include "vector.hpp"
#include "object.hpp"

// Simulatorクラス
class Simulator {
private:
    // 入力処理
    void ProcessInput();
    // 更新
    void UpdateSimulator();
    // 出力処理
    void GenerateOutput();

    // シミュレータ画面続行のフラグ
    bool mIsRunning;
    // シミュレーション開始のフラグ
    bool mIsSimulating;
    // SDLが作るウィンドウ
    SDL_Window *mWindow;
    // レンダラー
    SDL_Renderer *mRenderer;

    // 前フレームでのSDL_GetTicksNS()の結果[ms]
    Uint64 mTicksCount;

    // シミュレーション時間
    float mTime;
    // ハンター
    Obj2 mHunter;
    // 弾丸
    Obj2 mBullet;
    // 猿
    Obj2 mMonkey;

    // 弾丸と猿の初期位置での中心距離
    float l, h;

    // 速度の絶対値[px/s]と角度[deg]から弾丸の初速度を決定
    Vec2f vBullet0(float v0, float deg);
public:
    // シミュレーションリセット
    void SimReset();
    // コンストラクタ
    Simulator();
    // シミュレータを初期化
    bool Init();
    // シミュレータループ
    void RunLoop();
    // シミュレータをシャットダウン
    void Shutdown();
};

#endif  //  Simulator_HPP