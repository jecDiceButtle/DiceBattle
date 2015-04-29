#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/gplib.h"
#include "effect.h"
#include "stage.h"

namespace game
{

	class Title : public ci_ext::Object
	{
	public:
		Title(const std::string& objectName) :
			Object(objectName)
		{
			effect::Create(0, 0, effect::EFFECTTYPE::FADEINWHITE);
			gplib::graph::Draw_LoadObject("titleback", "res/gra/StageBack.png");
			gplib::graph::Draw_LoadObject("titlelogo", "res/gra/title.png");
		}

		void render() override
		{
			float w = (float)gplib::graph::Draw_GetImageWidth("titleback");
				float h = (float)gplib::graph::Draw_GetImageHeight("titleback");
			gplib::graph::Draw_GraphicsLeftTop(0, 0, 1.f, "titleback",
				0, 0, (int)w, (int)h, 0.f, nullptr,
				gplib::system::WINW / w,
				gplib::system::WINH / h); 

			w = (float)gplib::graph::Draw_GetImageWidth("titlelogo");
			h = (float)gplib::graph::Draw_GetImageHeight("titlelogo");
			gplib::graph::Draw_Graphics(gplib::system::WINW / 2, 200, 1.f, "titlelogo",
				0, 0, (int)w, (int)h);
		}

		void resume() override
		{
			insertToParent(new game::CSceneStage("scene_stage"));
		}

		void update() override
		{
			if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
			{
				effect::Create(0, 0, effect::EFFECTTYPE::FADEOUTWHITE);
				sleep(30);
			}
		}
	};
}

