#include "stage.h"
#include "movableObject.h"
#include <memory>
#include <string>
#include <iostream>

#include "collider.h"
#include "logo.hpp"

#include "background.h"

#include <stdio.h>

namespace game
{

  Stage::Stage(const std::string& objectName)
  :
  Object(objectName),
  point_(0)
{
}

//�R���X�g���N�^�ł͐e�q�֌W���\�z����Ă��Ȃ��̂ŁA
//�ʓrinit()�Őe�q�֌W���\�z���Ȃ���΂Ȃ�Ȃ�
void Stage::init()
{

  timer_ = insertAsChildSleep(new game::Timer("LimitTimer"), 120);

}

void Stage::AddPoint(int pt)
{
	point_ += pt;
}


void Stage::render()
{
  gplib::graph::Draw_BoxCenter(
    gplib::system::WINW / 2, gplib::system::WINH / 2,
    10, 10, 0.f,
    ARGB(255, 255, 0, 0), ARGB(255, 255, 0, 0),
    1, 1);


 


}

void Stage::update()
{
  using namespace gplib::math;
  using namespace gplib::system;




  auto timer = ci_ext::weak_to_shared<game::Timer>(timer_);


  if (timer->get() > 10.0f)
  {
    kill();
    //�V�[���J��
    insertToParent(new Logo("Logo"));
  }

}

}