#pragma once
#include "../../lib/ci_ext/object.hpp"

#include "../../lib/ci_ext/xinput.hpp" 

#include "Logo.hpp"
//debug
#include "stage.h"

#include"lib_WindowDx.hpp"
#include"lib_Window.hpp"


//���[�g�I�u�W�F�N�g
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

  RECT getWindowSize()
  {
	  return window_.lock()->getWndSize();
  }
};
