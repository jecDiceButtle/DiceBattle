#include "stage.h"
#include "title.h"
#include "movableObject.h"
#include <memory>
#include <string>
#include <iostream>

#include "collider.h"
#include "logo.hpp"

#include "background.h"

#include <stdio.h>

#include "root.hpp"

namespace game
{

  CSceneTitle::CSceneTitle(const std::string& objectName)
  :
  Object(objectName),
  state_(STATE::FADEIN)
{
}

//コンストラクタでは親子関係が構築されていないので、
//別途init()で親子関係を構築しなければならない
void CSceneTitle::init()
{

	auto root = getRootObject();
	auto object = ci_ext::weak_to_shared<Root>(root);

	auto wndsize = object->getWindowSize();


  insertAsChild(new IBackGround("title_back","title_back"));
}

void CSceneTitle::InAnim()
{
		state_ = STATE::WAIT;

}
void CSceneTitle::Wait()
{
	if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
	{
		state_ = STATE::FADEOUT;
	}
}


void CSceneTitle::render()
{

}

void CSceneTitle::update()
{
	switch (state_)
	{
	case STATE::FADEIN:

			state_ = STATE::IN_ANIM;

		break;

	case STATE::IN_ANIM:

		InAnim();

		break;

	case STATE::WAIT:

		Wait();
		break;

	case STATE::FADEOUT:


		insertToParentSleep(new Stage("Stage1"), 120);

		kill();
		//シーン遷移
		break;
	}

}

}