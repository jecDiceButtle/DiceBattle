#include "stage.h"
#include <memory>
#include <string>
#include <iostream>

#include "logo.hpp"

#include <stdio.h>

namespace game
{

	CSceneStage::CSceneStage(const std::string& objectName)
		:
		Object(objectName)
	{
	}

	//�R���X�g���N�^�ł͐e�q�֌W���\�z����Ă��Ȃ��̂ŁA
	//�ʓrinit()�Őe�q�֌W���\�z���Ȃ���΂Ȃ�Ȃ�
	void CSceneStage::init()
	{

	}


	void CSceneStage::render()
	{

#if _DEBUG
		gplib::font::Draw_FontTextNC(0, 0, 0.f, "�Q�[�����", ARGB(255, 255, 255, 255), 0);
#endif

	}

	void CSceneStage::update()
	{

		if (gplib::input::CheckPress(gplib::input::KEY_BTN0))
		{
			kill();
			//�V�[���J��
			insertToParent(new Logo("scene_logo"));
		}

	}

}