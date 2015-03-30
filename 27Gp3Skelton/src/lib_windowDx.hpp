#pragma once

#include "lib_window.hpp"
#include "../../lib/gplib.h"

namespace ci_ext
{

class WindowDx : public Window
{
public:
  //����������
  WindowDx(const std::string& title, int w, int h,
    const char* classname = "default_class_name)")
    :
    Window(title, w, h, classname)
  {
    void Draw_InitImgTable();
    void Draw_InitFont();
    void InitPlayerInput();

    //�E�C���h�E�n���h����gplib�֓o�^���Ă��珉�����������s��
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

  //�I������DirectGraphics�֘A������
  ~WindowDx() override
  {
    void Draw_DelImgTable();
    void Draw_DeleteFont();
    void DeletePlayerInput();

    Draw_DelImgTable();
    Draw_DeleteFont();
    gplib::system::DelDx();
  }
  //�O�����ŃL�[�`�F�b�N�ƃ����_�����O�o�b�t�@���N���A
  void update_before() override
  {
    gplib::graph::Draw_Clear();
    gplib::input::CheckKey();
    gplib::XInput::CheckKey();
  }
  //�㏈���Ń����_�����O���ʂ�����ʂ֓]������
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
    //�T�E���h�I���`�F�b�N
#ifdef USE_DIRECTSHOW
    gplib::bgm::DShow_EndCheck();
#endif
#ifdef USE_DIRECTSOUND
    gplib::se::DSound_EndCheck();
#endif
    //�z�C�[��delta�N���A
    ClearWheelDelta();
    gplib::graph::Draw_3DUpdate();
    //TIMER�X�V
    gplib::system::FrameTime = gplib::time::Time_Update();
  }

};


}
*/