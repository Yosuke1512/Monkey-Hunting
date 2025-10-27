#include <SDL3/SDL.h>
#include "simulator.hpp"
#include <iostream>
#include <cmath>

#define WINDOW_WIDTH    1024
#define WINDOW_HIGHT    768

// 円周率
const float pi = acos(-1);

// 弾丸, 猿のサイズと位置, 画面のサイズによって変わる
const float l = 956.5F;
const float h = 693.0F;

// 弾丸の初速度[px/sec], 角度[deg]
const float v0 = 300.0F;
float rad = atan2(l, -h); // 衝突する角度
//float rad = 3.0F/4.0F * pi; // 衝突しない角度
float vx_bullet = v0*sin(rad);
float vy_bullet = v0*cos(rad);

// 重力加速度[px/sec^2]
const float g = 9.8F;

/* 目に優しい配色 (カラーユニバーサルデザイン)
- ベースカラー
    #ffcabf : 明るいピンク
    #ffff80 : クリーム
    #d8f255 : 明るい黄緑
    #bfe4ff : 明るい空
    #ffca80 : ベージュ
    #77d9a8 : 明るい緑
    #c9ace6 : 明るい紫
- アクセントカラー
    #ff4b00 : 赤
    #fff100 : 黄
    #03af7a : 緑
    #005aff : 青
    #4dc4ff : 空
    #ff8082 : ピンク
    #f6aa00 : オレンジ
    #990099 : 紫
    #804000 : 茶
- 無彩色
    #ffffff : 白
    #c8c8cb : 明るい灰
    #84919e : 灰
    #000000 : 黒
*/

// 入力処理
void Simulator::ProcessInput() {
    SDL_Event event;
    // キューにイベントがあれば繰り返す
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_EVENT_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const bool *state = SDL_GetKeyboardState(nullptr);

    // [ESC] : 終了
    if(state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    // [SPACE] : シミュレーション開始
    if(state[SDL_SCANCODE_SPACE]) {
        mIsSimulating = true;
    }

    // [S] : シミュレーション一時停止
    if(state[SDL_SCANCODE_S]) {
        mIsSimulating = false;
    }
}

// シミュレータの更新
void Simulator::UpdateSimulator() {
    // フレーム制限
    while(SDL_GetTicks() < mTicksCount + 16) {
        SDL_Delay(1);  // busy-waitを避けるため、1msずつ待機
    }

    // デルタタイム[s]
    float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0F;
    mTicksCount = SDL_GetTicks();

    // デルタタイムを最大値で制限
    float deltatime_max = 0.05;
    if(deltatime > deltatime_max) {
        deltatime = deltatime_max;
    }

    // シミュレーション更新
    float dt = deltatime;

    if(mIsSimulating) {
        std::cout << "mTime: " << mTime << "\n"; // 後で消す

        // 弾丸の更新
        float dx_bullet = vx_bullet*dt;
        float dy_bullet = vy_bullet*dt + 1.0F/2.0F*g*dt*(2.0F*mTime + dt);
        mBullet.pos += Vec2f(dx_bullet, dy_bullet);

        // 猿の更新
        float dx_monkey = 0.0F;
        float dy_monkey = 1.0F/2.0F*g*dt*(2.0F*mTime + dt);
        mMonkey.pos += Vec2f(dx_monkey, dy_monkey);

        // 弾丸と猿の衝突判定
        if(isCollision(mBullet, mMonkey)) {
            std::cout << "HIT!!\n";
            mIsSimulating = false;
        } else if(mBullet.pos.getX()-mBullet.w() > WINDOW_WIDTH) {
            std::cout << "Didn't hit...\n";
            mIsSimulating = false;
        }

        // シミュレーション時間更新
        mTime = mTime + dt;
    }
}

// 出力処理
void Simulator::GenerateOutput() {
    /* 背景 */
    SDL_SetRenderDrawColor(mRenderer, 0xbf, 0xe4, 0xff, 0xff); // #bfe4ff
    SDL_RenderClear(mRenderer);

    /* 物体 */

    // ハンター
    SDL_FRect hunter{mHunter.pos.getX()-mHunter.w()/2.0F, mHunter.pos.getY()-mHunter.h()/2.0F, mHunter.w(), mHunter.h()};
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0x4b, 0x00, 0xff); // #ff4b00
    SDL_RenderFillRect(mRenderer, &hunter);

    // 弾丸
    SDL_FRect bullet{mBullet.pos.getX()-mBullet.w()/2.0F, mBullet.pos.getY()-mBullet.h()/2.0F, mBullet.w(), mBullet.h()};
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xff); // #000000
    SDL_RenderFillRect(mRenderer, &bullet);

    // 猿
    SDL_FRect monkey{mMonkey.pos.getX()-mMonkey.w()/2.0F, mMonkey.pos.getY()-mMonkey.h()/2.0F, mMonkey.w(), mMonkey.h()};
    SDL_SetRenderDrawColor(mRenderer, 0x80, 0x40, 0x00, 0xff); // #804000
    SDL_RenderFillRect(mRenderer, &monkey);

    // フロントバッファとバックバッファの交換
    SDL_RenderPresent(mRenderer);
}

// 速度の絶対値[px/s]と角度[deg]から弾丸の初速度を決定
Vec2f Simulator::vBullet0(float v0, float deg) {
    float rad = deg * pi / 180;
    float vx = v0*sin(rad);
    float vy = v0*cos(rad);
    return Vec2f(vx, vy);
}

// コンストラクタ
Simulator::Simulator() {
    mWindow = nullptr;
    mIsRunning = true;
    mIsSimulating = false;
    mRenderer = nullptr;
    mTicksCount = 0;

    // 初期時間
    mTime = 0.0F;

    // ハンターの初期化
    mHunter.setWidth(50);
    mHunter.setHight(100);
    mHunter.pos = Vec2f(mHunter.w()/2.0F, WINDOW_HIGHT-mHunter.h()/2.0F);
    mHunter.vel = Vec2f();

    // 弾丸の初期化
    mBullet.setWidth(10);
    mBullet.setHight(10);
    mBullet.pos = Vec2f(mHunter.w()+mBullet.w()/2.0F, WINDOW_HIGHT-mHunter.h()/2.0F);    
    mBullet.vel = Vec2f(vx_bullet, vy_bullet);

    // 猿の初期化
    mMonkey.setWidth(25);
    mMonkey.setHight(50);
    mMonkey.pos = Vec2f(WINDOW_WIDTH-mMonkey.w()/2.0F, mMonkey.h()/2.0F);
    mMonkey.vel = Vec2f();
}

// ゲームを初期化
bool Simulator::Init() {
    // SDL初期化
    if(SDL_Init(SDL_INIT_VIDEO) == false) {
        std::cerr << "Error init SDL\n";
        return false;
    }

    // ウィンドウ初期化
    mWindow = SDL_CreateWindow("Monkey Hunting", WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_RESIZABLE);
    if(mWindow == nullptr) {
        SDL_Log("ウィンドウの作成に失敗しました : %s", SDL_GetError());
        return false;
    }

    // レンダラー初期化
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if(mRenderer == nullptr) {
        SDL_Log("レンダラーの作成に失敗しました : %s", SDL_GetError());
        return false;
    }

    return true;
}

// ゲームループ
void Simulator::RunLoop() {
    while(mIsRunning) {
        ProcessInput();
        UpdateSimulator();
        GenerateOutput();
    }
}

// ゲームをシャットダウン
void Simulator::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}