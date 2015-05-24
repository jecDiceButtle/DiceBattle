#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/gplib.h"
#include "effect.h"
#include "stage.h"
#include "Sound.h"

namespace game
{

	class Title : public ci_ext::Object
	{
		
	public:

		//soundÇÃÉ|ÉCÉìÉ^
		std::weak_ptr<ci_ext::Object> p_sound;

		Title(const std::string& objectName) :
			Object(objectName)
		{
			
			//effect::Create(0, 0, effect::EFFECTTYPE::FADEINWHITE);
			gplib::graph::Draw_LoadObject("titleback", "res/gra/title_back.png",0xFFFFFFFF);
			/*gplib::graph::Draw_LoadObject("titlelogo", "res/gra/title.png");*/
		}

		void init() override
		{
			p_sound = insertAsChild(new Sound("sound"));
		}

		void render() override
		{
			gplib::graph::Draw_2DClear();

			float w = (float)gplib::graph::Draw_GetImageWidth("titleback");
				float h = (float)gplib::graph::Draw_GetImageHeight("titleback");
			gplib::graph::Draw_GraphicsLeftTop(0, 0, 1.f, "titleback",
				0, 0, (int)w, (int)h, 0.f, nullptr,
				gplib::system::WINW / w,
				gplib::system::WINH / h);

			gplib::graph::Draw_2DRefresh();

			//w = (float)gplib::graph::Draw_GetImageWidth("titlelogo");
			//h = (float)gplib::graph::Draw_GetImageHeight("titlelogo");
			//gplib::graph::Draw_Graphics(gplib::system::WINW / 2, 200, 1.f, "titlelogo",
			//	0, 0, (int)w, (int)h);
		}

		void resume() override
		{
			
			static bool flag = true;
			if (flag){
				insertToParent(new game::CSceneStage("scene_stage"));
				flag = false;
			}
		}

		void update() override
		{
			//BGMçƒê∂
			Sound::BgmPayer("kb");
			if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
			{
				//effect::Create(0, 0, effect::EFFECTTYPE::FADEOUTWHITE);
				sleep(5);
				Sound::BgmStop("kb");
				killFromChildren("sound");
			}
		}
		
	};
}
