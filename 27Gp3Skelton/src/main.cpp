#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/counter.hpp"
#include "../../lib/ci_ext/Console.hpp"
#include <iostream>
#include <Windows.h>
//Xinputライブラリ
#include "../../lib/ci_ext/xinput.hpp" 

#include "../../lib/gplib.h" 
#include"lib_WindowDx.hpp"
#include <string>


#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"

//3Dカメラ
Dx_Camera *dxCamera = nullptr;
//メッシュ全体管理クラス
DX3DMESHMANAGER *meshManage = nullptr;




namespace gplib{
  namespace system{
    const char USERNAME[256] = "ゲームPG補足サンプル";

    const int WINW = 1280; //PS VITAサイズ
    const int WINH = 720;  //
    bool WindowMode = true;//フルスクリーン対応
    int  KeyboardMode = 0; //pad disable:1 pad enable:0
  }
}
int ci_ext::Object::uid_ = 0;
int ci_ext::Window::uid_ = 0;

//継承、内包でのゲーム実装例 コメントアウトで内包例
//内包例ではwindowを複数作る際のサンプル
// FIXME:msg関連をthreadにすれば良くなりそう
//#define EXTENDS

#ifndef EXTENDS

#include "root.hpp"

//ゲームクラス
//このクラスは、ルートの管理のみ行い、ゲーム特有の処理はルートオブジェクトで行う
class Game
{
  std::shared_ptr<Root> root;
  std::shared_ptr<ci_ext::WindowDx> window_;
  LRESULT OnPause(HWND, UINT, WPARAM w, LPARAM, void* p)
  {
    auto game = static_cast<Game*>(p);//この場合はthisポインタでもOKですがサンプルなので
    //非アクティブからアクティブになった時の処理
    //Pause <=> Runの切り替え
    if (w == TRUE)
    {
      game->root->runAll();
      std::cout << "アクティブ" << std::endl;
    }
    else
    {
      game->root->pauseAll();
      std::cout << "非アクティブ" << std::endl;
    }
    return 0;
  }
public:
  int num;
  Game()
    :
    window_(new ci_ext::WindowDx("タイトル", gplib::system::WINW, gplib::system::WINH))
  {
    root = std::make_shared<Root>(window_);
    root->init(root);

    //ウインドウのアクティブ非アクティブのメッセージ処理を上書きする
    window_->insertMsg(WM_ACTIVATEAPP, BindPtr(this, &Game::OnPause), this);

    while (run());
  }

  //ゲームメイン処理
  bool run()
  {
    auto ret = window_->doMsg2();
    //ルートオブジェクトから処理を行う
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

//エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
  //アプリケーション終了時にメモリ情報をデバッグウインドウへ出力
  //リークの確認
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  {
    ShowConsole();//コンソール表示（スコープ概念あり）
    Game game;//コンストラクタでアプリ駆動Game()でもOK
  }
  return 0;
}


void gplib::system::OnCreate()
{
	////////
	//debug
	////////




	gplib::camera::InitCamera(gplib::system::WINW / 2, gplib::system::WINH / 2, 0, 0);

	//3Dカメラ設定　カメラ位置はデフォルト　注視点は0,0,0
	float eye_pos_x = 0.0f;
	float eye_pos_y = 0.0f;
	float eye_pos_z = -50.0f;
	float eye_look_x = 0.0f;
	float eye_look_y = -10.0f;
	float eye_look_z = -30.0f;

	/////////////////////////////////////////////////////////////////////////　　
	//?)このカメラは何に使うんだ？
	//////////////////////////////////////////////////////////////////////////
	dxCamera = new Dx_Camera();
	dxCamera->SetEyePos(DxVec3(eye_pos_x, eye_pos_y, eye_pos_z));
	dxCamera->SetLookPos(eye_look_x, eye_look_y, eye_look_z);

	/////////////////////////////////////////////////////////////////////////　　
	//?)meshManageとは一体
	//////////////////////////////////////////////////////////////////////////
	//ステージ３Dオブジェクト
	meshManage = new DX3DMESHMANAGER();
	//カメラからビュー行列と射影行列を設定
	meshManage->getG()->Setup3DEnv(dxCamera);

	meshManage->loadMesh("dice", "dice.x", "res/x/", DX3DMESHMANAGER::MESHTYPE::MESH);
}

void gplib::system::OnDestroy(){
	SAFE_DELETE(meshManage);
	//カメラの破棄
	SAFE_DELETE(dxCamera);
}



#else

//ルートオブジェクト
//このクラスの子供にゲームのオブジェクトを追加していく
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

//ゲームクラス
//ルートになるクラスで、mainで宣言する。
class Game : public ci_ext::WindowDx
{
  std::shared_ptr<Root> root;//ルートオブジェクト
  LRESULT OnPause(HWND, UINT, WPARAM w, LPARAM, void*)
  {
    //非アクティブからアクティブになった時の処理
    //Pause <=> Runの切り替え
    if (w == TRUE)
    {
      root->runAll();
      std::cout << "アクティブ" << std::endl;
    }
    else
    {
      root->pauseAll();
      std::cout << "非アクティブ" << std::endl;
    }
    return 0;
  }
public:
  Game(const std::string& title, int w, int h,
    const char* classname = "default_class_name")
    :
    ci_ext::WindowDx(title, w, h, classname)
  {
    //ルートオブジェクトを作成し、メッセージループを起動させる
    root = std::make_shared<Root>();
    root->init(root);//init()は仕方ない

    //ウインドウのアクティブ非アクティブのメッセージ処理を上書きする
    insertMsg(WM_ACTIVATEAPP, BindThisPtr(&Game::OnPause));

    doMsgLoop();
  }

  void update() override
  {
    //ルートオブジェクトから処理を行う
    root->updateWithChildren();
    root->renderWithChildren();
  }
};

//エントリポイント
//mainやWinMainはreturnは省略可、引数名は使用しないので省略
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  //アプリケーション終了時にメモリ情報をデバッグウインドウへ出力
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //確認したい場合は、以下のコメントをとってデバッグ開始する
  //int* ptr = new int[100];

  //デバッグ終了後、VisualStudioの出力ウインドウに
  //  Detected memory leaks!
  //  Dumping objects ->
  //  {165} normal block at 0x00C70910, 400 bytes long.
  //  Data: <                > CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD
  //  Object dump complete.
  //とリークを検出してくれるのが確認できる

  //ローカル変数の寿命を明確にするためにスコープで区切る
  {
    ShowConsole();//コンソール表示（スコープ概念あり）
    Game game("タイトル", 1280, 720);//Game("タイトル", 1280, 720)でもOK
  }
}
#endif