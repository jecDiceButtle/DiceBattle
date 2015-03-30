#pragma once

#include "lib_window.hpp"
#include "../../lib/gplib.h"

namespace ci_ext
{

class WindowDx : public Window
{
public:
  //初期化処理
  WindowDx(const std::string& title, int w, int h,
    const char* classname = "default_class_name)")
    :
    Window(title, w, h, classname)
  {
    void Draw_InitImgTable();
    void Draw_InitFont();
    void InitPlayerInput();

    //ウインドウハンドルをgplibへ登録してから初期化処理を行う
    gplib::system::hWnd = windowhandle();
    gplib::system::InitDx();
    Draw_InitImgTable();
    Draw_InitFont();
    gplib::math::RandomInit();
    gplib::camera::InitCamera(gplib::system::WINW / 2.0f, gplib::system::WINH / 2.0f, 0, 0);
    gplib::font::Draw_CreateFont(0, 20, "consolas");
    //input
    InitPlayerInput();
    for (int i = 0; i < gplib::system::PLAYER_NUM; i++)
      gplib::input::InitKeyInfo(i);
  }

  //終了時にDirectGraphics関連を消去
  ~WindowDx() override
  {
    void Draw_DelImgTable();
    void Draw_DeleteFont();
    void DeletePlayerInput();

    Draw_DelImgTable();
    Draw_DeleteFont();
    gplib::system::DelDx();
  }
  //前処理でキーチェックとレンダリングバッファをクリア
  void update_before() override
  {
    gplib::graph::Draw_Clear();
    gplib::input::CheckKey();
    gplib::XInput::CheckKey();
  }
  //後処理でレンダリング結果を可視画面へ転送する
  void update_after()  override
  {
    gplib::camera::StepCamera();
    gplib::graph::Draw_Refresh();
    gplib::graph::Draw_3DUpdate();
  }
};
}
/*
#pragma once

#include "lib_window.hpp"
#include "../../lib/gplib.h"

namespace ci_ext
{

class WindowDx : public Window
{
  LRESULT OnDestroy(HWND, UINT, WPARAM, LPARAM)
  {
    void Draw_DelImgTable();
    void Draw_DeleteFont();
    void DeletePlayerInput();

    Draw_DelImgTable();
    Draw_DeleteFont();
    //sound com release
#ifdef CI_EXT
    ci_ext::dsRelease();
#endif
#ifdef USE_DIRECTSOUND
    gplib::se::DSound_Del();

#endif
#ifdef USE_DIRECTSHOW
    gplib::bgm::DShow_Del();
#endif
    //directx release
    gplib::system::DelDx();
    //pad delete
    DeletePlayerInput();
    PostQuitMessage(0);
    return 0;
  }
public:
  WindowDx(const std::string& title, int w, int h,
    const char* classname = "default_class_name)")
    :
    Window(title, w, h, classname)
  {
    void Draw_InitImgTable();
    void Draw_InitFont();
    void InitPlayerInput();
    void InitFlagStage();

    insertMsg(WM_DESTROY, BindThisPtr(&WindowDx::OnDestroy));

    gplib::system::hWnd = windowhandle();
    gplib::system::InitDx();
    //resource table init
    Draw_InitImgTable();
    Draw_InitFont();
    //player input init
    InitPlayerInput(); 
    
    for (int i = 0; i < gplib::system::PLAYER_NUM; i++)
      gplib::input::InitKeyInfo(i);
    //stage flag init
    InitFlagStage();
    gplib::math::RandomInit();
    //sound com init
#ifdef USE_DIRECTSOUND
    gplib::se::DSound_Init();
#endif
#ifdef USE_DIRECTSHOW
    gplib::bgm::DShow_Init();
#endif
    srand((unsigned)::time(NULL));
    gplib::time::Time_CheckTimer();
    gplib::camera::InitCamera(gplib::system::WINW / 2.0f, gplib::system::WINH / 2.0f, 0, 0);
  }

  ~WindowDx() override
  {
  }

  void update_before() override
  {
    gplib::graph::Draw_Clear();
    gplib::input::CheckKey();
  }

  void update_after()  override
  {
    void ClearWheelDelta();

    gplib::camera::StepCamera();
    gplib::graph::Draw_Refresh();
    //サウンド終了チェック
#ifdef USE_DIRECTSHOW
    gplib::bgm::DShow_EndCheck();
#endif
#ifdef USE_DIRECTSOUND
    gplib::se::DSound_EndCheck();
#endif
    //ホイールdeltaクリア
    ClearWheelDelta();
    gplib::graph::Draw_3DUpdate();
    //TIMER更新
    gplib::system::FrameTime = gplib::time::Time_Update();
  }

};


}
*/