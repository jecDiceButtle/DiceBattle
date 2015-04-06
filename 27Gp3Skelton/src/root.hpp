#pragma once
#include "../../lib/ci_ext/object.hpp"

#include "../../lib/ci_ext/xinput.hpp" 

#include "Logo.hpp"

#ifdef _DEBUG
#include "stage.h"
#endif

#include"lib_WindowDx.hpp"
#include"lib_Window.hpp"


//ルートオブジェクト
class Root : public ci_ext::Object
{
  int frame_;
  std::weak_ptr<ci_ext::Window> window_;
public:
  Root(std::weak_ptr<ci_ext::Window> window)
    :
    Object("root"),
    frame_(0),
    window_(window)
  {
  }

  void init(std::shared_ptr<ci_ext::Object> thisObjectPtr)
  {
    setWeakPtr(thisObjectPtr);

#ifdef _DEBUG

	insertAsChild(new game::CSceneStage("scene_stage"));
#elif

	insertAsChild(new game::Logo("scene_logo"));

#endif

    
  }

  void update() override
  {
    ++frame_;
    
  }
  void render() override
  {
#ifdef _DEBUG

	  //gplib::debug::DFPS();

#endif
  }
  int frame() const { return frame_; }

  RECT getWindowSize()
  {
	  return window_.lock()->getWndSize();
  }
};
