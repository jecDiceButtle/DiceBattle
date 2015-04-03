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

	//コンストラクタでは親子関係が構築されていないので、
	//別途init()で親子関係を構築しなければならない
	void CSceneStage::init()
	{

	}


	void CSceneStage::render()
	{

#if _DEBUG
		gplib::font::Draw_FontTextNC(0, 0, 0.f, "ゲーム画面", ARGB(255, 255, 255, 255), 0);
#endif

	}

	void CSceneStage::update()
	{

		if (gplib::input::CheckPress(gplib::input::KEY_BTN0))
		{
			kill();
			//シーン遷移
			insertToParent(new Logo("scene_logo"));
		}

	}

}