#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/Console.hpp"
#include <iostream>
#include <Windows.h>
//Xinput���C�u����
#include "../../lib/ci_ext/xinput.hpp" 

#include "../../lib/gplib.h" 
#include"lib_WindowDx.hpp"
#include <string>


#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"

//3D�J����
Dx_Camera *dxCamera = nullptr;
//���b�V���S�̊Ǘ��N���X
DX3DMESHMANAGER *meshManage = nullptr;




namespace gplib{
  namespace system{
    const char USERNAME[256] = "�Q�[��PG�⑫�T���v��";

    const int WINW = 1280; //PS VITA�T�C�Y
    const int WINH = 720;  //
    bool WindowMode = true;//�t���X�N���[���Ή�
    int  KeyboardMode = 0; //pad disable:1 pad enable:0
  }
}
int ci_ext::Object::uid_ = 0;
int ci_ext::Window::uid_ = 0;

//�p���A����ł̃Q�[�������� �R�����g�A�E�g�œ����
//�����ł�window�𕡐����ۂ̃T���v��
// FIXME:msg�֘A��thread�ɂ���Ηǂ��Ȃ肻��
//#define EXTENDS

#ifndef EXTENDS

#include "root.hpp"

//�Q�[���N���X
//���̃N���X�́A���[�g�̊Ǘ��̂ݍs���A�Q�[�����L�̏����̓��[�g�I�u�W�F�N�g�ōs��
class Game
{
  std::shared_ptr<Root> root;
  std::shared_ptr<ci_ext::WindowDx> window_;
  LRESULT OnPause(HWND, UINT, WPARAM w, LPARAM, void* p)
  {
    auto game = static_cast<Game*>(p);//���̏ꍇ��this�|�C���^�ł�OK�ł����T���v���Ȃ̂�
    //��A�N�e�B�u����A�N�e�B�u�ɂȂ������̏���
    //Pause <=> Run�̐؂�ւ�
    if (w == TRUE)
    {
      game->root->runAll();
      std::cout << "�A�N�e�B�u" << std::endl;
    }
    else
    {
      game->root->pauseAll();
      std::cout << "��A�N�e�B�u" << std::endl;
    }
    return 0;
  }
public:
  int num;
  Game()
    :
    window_(new ci_ext::WindowDx("�^�C�g��", gplib::system::WINW, gplib::system::WINH))
  {
    root = std::make_shared<Root>(window_);
    root->init(root);

    //�E�C���h�E�̃A�N�e�B�u��A�N�e�B�u�̃��b�Z�[�W�������㏑������
    window_->insertMsg(WM_ACTIVATEAPP, BindPtr(this, &Game::OnPause), this);

    while (run());
  }

  //�Q�[�����C������
  bool run()
  {
    auto ret = window_->doMsg2();
    //���[�g�I�u�W�F�N�g���珈�����s��
    if (ret == ci_ext::Window::MsgReturn::update)
	{
      window_->update_before();
      root->updateWithChildren();
      root->renderWithChildren();
      window_->update_after();
    }
    return ret == ci_ext::Window::MsgReturn::quit ? false: true;
  }

};

//�G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
  //�A�v���P�[�V�����I�����Ƀ����������f�o�b�O�E�C���h�E�֏o��
  //���[�N�̊m�F
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  {
    ShowConsole();//�R���\�[���\���i�X�R�[�v�T�O����j
    Game game;//�R���X�g���N�^�ŃA�v���쓮Game()�ł�OK
  }
  return 0;
}


void gplib::system::OnCreate()
{
	////////
	//debug
	////////




	gplib::camera::InitCamera(gplib::system::WINW / 2, gplib::system::WINH / 2, 0, 0);

	//3D�J�����ݒ�@�J�����ʒu�̓f�t�H���g�@�����_��0,0,0
	float eye_pos_x = 0.0f;
	float eye_pos_y = 0.0f;
	float eye_pos_z = -50.0f;
	float eye_look_x = 0.0f;
	float eye_look_y = -10.0f;
	float eye_look_z = -30.0f;

	/////////////////////////////////////////////////////////////////////////�@�@
	//?)���̃J�����͉��Ɏg���񂾁H
	//////////////////////////////////////////////////////////////////////////
	dxCamera = new Dx_Camera();
	dxCamera->SetEyePos(DxVec3(eye_pos_x, eye_pos_y, eye_pos_z));
	dxCamera->SetLookPos(eye_look_x, eye_look_y, eye_look_z);

	/////////////////////////////////////////////////////////////////////////�@�@
	//?)meshManage�Ƃ͈��
	//////////////////////////////////////////////////////////////////////////
	//�X�e�[�W�RD�I�u�W�F�N�g
	meshManage = new DX3DMESHMANAGER();
	//�J��������r���[�s��Ǝˉe�s���ݒ�
	meshManage->getG()->Setup3DEnv(dxCamera);

	meshManage->loadMesh("dice", "dice.x", "res/x/", DX3DMESHMANAGER::MESHTYPE::MESH);
}

void gplib::system::OnDestroy(){
	SAFE_DELETE(meshManage);
	//�J�����̔j��
	SAFE_DELETE(dxCamera);
}



#else

//���[�g�I�u�W�F�N�g
//���̃N���X�̎q���ɃQ�[���̃I�u�W�F�N�g��ǉ����Ă���
class Root : public ci_ext::Object
{
  int frame_;
public:
  Root()
    :
    Object("root"),
    frame_(0)
  {
  }

  void init(std::shared_ptr<ci_ext::Object> thisObjectPtr)
  {
    setWeakPtr(thisObjectPtr);
    insertAsChild(new game::Logo("logo"));
  }

  void update() override
  {
    ++frame_;
  }

  void render() override
  {
  }
  int frame() const { return frame_; }
};

//�Q�[���N���X
//���[�g�ɂȂ�N���X�ŁAmain�Ő錾����B
class Game : public ci_ext::WindowDx
{
  std::shared_ptr<Root> root;//���[�g�I�u�W�F�N�g
  LRESULT OnPause(HWND, UINT, WPARAM w, LPARAM, void*)
  {
    //��A�N�e�B�u����A�N�e�B�u�ɂȂ������̏���
    //Pause <=> Run�̐؂�ւ�
    if (w == TRUE)
    {
      root->runAll();
      std::cout << "�A�N�e�B�u" << std::endl;
    }
    else
    {
      root->pauseAll();
      std::cout << "��A�N�e�B�u" << std::endl;
    }
    return 0;
  }
public:
  Game(const std::string& title, int w, int h,
    const char* classname = "default_class_name")
    :
    ci_ext::WindowDx(title, w, h, classname)
  {
    //���[�g�I�u�W�F�N�g���쐬���A���b�Z�[�W���[�v���N��������
    root = std::make_shared<Root>();
    root->init(root);//init()�͎d���Ȃ�

    //�E�C���h�E�̃A�N�e�B�u��A�N�e�B�u�̃��b�Z�[�W�������㏑������
    insertMsg(WM_ACTIVATEAPP, BindThisPtr(&Game::OnPause));

    doMsgLoop();
  }

  void update() override
  {
    //���[�g�I�u�W�F�N�g���珈�����s��
    root->updateWithChildren();
    root->renderWithChildren();
  }
};

//�G���g���|�C���g
//main��WinMain��return�͏ȗ��A�������͎g�p���Ȃ��̂ŏȗ�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  //�A�v���P�[�V�����I�����Ƀ����������f�o�b�O�E�C���h�E�֏o��
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //�m�F�������ꍇ�́A�ȉ��̃R�����g���Ƃ��ăf�o�b�O�J�n����
  //int* ptr = new int[100];

  //�f�o�b�O�I����AVisualStudio�̏o�̓E�C���h�E��
  //  Detected memory leaks!
  //  Dumping objects ->
  //  {165} normal block at 0x00C70910, 400 bytes long.
  //  Data: <                > CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD
  //  Object dump complete.
  //�ƃ��[�N�����o���Ă����̂��m�F�ł���

  //���[�J���ϐ��̎����𖾊m�ɂ��邽�߂ɃX�R�[�v�ŋ�؂�
  {
    ShowConsole();//�R���\�[���\���i�X�R�[�v�T�O����j
    Game game("�^�C�g��", 1280, 720);//Game("�^�C�g��", 1280, 720)�ł�OK
  }
}
#endif