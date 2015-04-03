#include "stage.h"
#include "title.h"
#include <memory>
#include <string>
#include <iostream>

#include "logo.hpp"

#include "root.hpp"

namespace game
{

  CSceneTitle::CSceneTitle(const std::string& objectName)
  :
  Object(objectName),
  state_(STATE::FADEIN)
{
}

//�R���X�g���N�^�ł͐e�q�֌W���\�z����Ă��Ȃ��̂ŁA
//�ʓrinit()�Őe�q�֌W���\�z���Ȃ���΂Ȃ�Ȃ�
void CSceneTitle::init()
{

	auto root = getRootObject();
	auto object = ci_ext::weak_to_shared<Root>(root);

	auto wndsize = object->getWindowSize();

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
#if _DEBUG
	gplib::font::Draw_FontTextNC(0, 0, 0.f, "�^�C�g�����", ARGB(255, 255, 255, 255), 0);
#endif
}

void CSceneTitle::update()
{
	switch (state_)
	{
	case STATE::FADEIN:

		state_ = STATE::WAIT;

		break;

	case STATE::WAIT:

		Wait();
		break;

	case STATE::FADEOUT:


		insertToParentSleep(new CSceneStage("scene_stage1"), 120);
		kill();
		//�V�[���J��
		break;
	}

}

}