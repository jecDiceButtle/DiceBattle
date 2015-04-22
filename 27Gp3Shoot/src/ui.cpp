#include "ui.h"
#include "../../lib/gplib.h"


#include "movableObject.h"
#include "easing.h"
#include "timer.h"


namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//
	static const int srcX[] = { 0, 150, 300, 450 };

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	UI::UI(const std::string& objectName, UITYPE type, float x, float y)
		:
		MovableObject(objectName),
		type_(type),
		state_(MOVESTATE::RIGHTCENTER),
		initF(true),
		flag(false),
		x(x),
		y(y)
	{

		switch (type_)
		{
		case UITYPE::CUTIN:
			flagset();
			gplib::graph::Draw_LoadObject("Cutin", "res/gra/cutin.png");
			easing::Create("cutin1", easing::EASINGTYPE::CUBICIN, gplib::system::WINW + 400, 640, 60);
			easing::Create("cutin2", easing::EASINGTYPE::CUBICIN, 640, -300, 60);
			break;

		case UITYPE::POPUP:

			sizeX = 1.f;
			sizeY = 1.f;
			Yes = false;
			No = false;

			gplib::graph::Draw_LoadObject("question", "res/gra/question.png");
			gplib::graph::Draw_LoadObject("Yes", "res/gra/anser_yes.png");
			gplib::graph::Draw_LoadObject("No", "res/gra/anser_no.png");

			break;

		case UITYPE::CHARA:
			player1scale = 1.f;
			player2scale = 1.f;


			gplib::graph::Draw_LoadObject("player1", "res/gra/player1.png");
			gplib::graph::Draw_LoadObject("player2", "res/gra/player2.png");
			break;

		case UITYPE::PHASE:
			scaleX = 1.f;
			scaleY = 1.f;
			gplib::graph::Draw_LoadObject("phase", "res/gra/phase.png");

		}
	}

	void UI::flagset(){
		if (flag == false){
			flag = true;
		}
		else if (flag == true){
			flag = false;
		}
	}

	void UI::init()
	{
		timer_ = insertAsChildSleep(new game::Timer("LimitTimer"), 120);
	}

	void UI::render()
	{
		gplib::graph::Draw_2DClear();
		//cutin
		switch (type_)
		{
		case UITYPE::CUTIN:
			if (flag){
				gplib::graph::Draw_Graphics(x, y, 0.f, "Cutin", 0, 0, 600, 103, 0.f, 1.5f, 1.5f);
			}
			break;
		case UITYPE::POPUP:
			if (flag){
				std::string t = "行動を決定しますか？";
				gplib::graph::Draw_Graphics(x, y, 0.f, "question", 0, 0, 512, 128, 0.f, 1.5f, 1.5f);
				gplib::graph::Draw_Graphics(x - 200, y + 200, 0.f, "Yes", 0, 0, 128, 64, 0.f, sizeY, sizeY);
				gplib::graph::Draw_Graphics(x + 200, y + 200, 0.f, "No", 0, 0, 128, 64, 0.f, sizeX, sizeX);
				gplib::font::Draw_FontText(x, y, 0.f, t, ARGB(255, 255, 255, 255), 0);
			}
			break;
		case UITYPE::CHARA:

			gplib::graph::Draw_Graphics(100, 100, 0.f, "player1", 0, 0, 100, 100, 0, player1scale, player1scale);
			gplib::graph::Draw_Graphics(gplib::system::WINW - 100, 100, 0.f, "player2", 0, 0, 100, 100, 0, player2scale, player2scale);
			break;
		case UITYPE::PHASE:

			gplib::graph::Draw_Graphics(x, y, 0.f, "phase", srcX[i], 0, 150, 150, 0.f,scaleX,scaleY);
			break;
		}

		gplib::graph::Draw_2DRefresh();

	}

	void UI::update()
	{

		auto timer = ci_ext::weak_to_shared<game::Timer>(timer_);

		switch (type_)
		{
		case UITYPE::CUTIN:
			if (flag){
				switch (state_)
				{
				case MOVESTATE::RIGHTCENTER:
					if (initF == true)
					{
						easing::Start("cutin1");
						initF = false;
					}
					easing::GetPos("cutin1", x);
					if (x <= 640)
					{
						state_ = MOVESTATE::CENTER;
						initF = true;
					}
					break;
				case MOVESTATE::CENTER:
					/*auto timer = ci_ext::weak_to_shared<game::Timer>(timer_);*/
					if (timer->get() > 3.0f)
					{
						state_ = MOVESTATE::CENTERLEFT;
					}
					break;
				case MOVESTATE::CENTERLEFT:
					if (initF == true)
					{
						easing::Start("cutin2");
						initF = false;
					}
					easing::GetPos("cutin2", x);
					if (x <= -300)
					{
						kill();
					}
					break;
				}
			}
		case UITYPE::POPUP:
			if (gplib::input::CheckPush(gplib::input::KEY_UP))
			{
				flagset();
			}
			if (flag){
				if (gplib::input::CheckPush(gplib::input::KEY_LEFT)){
					sizeY = 1.2f;
					sizeX = 1.0f;
					Yes = true;
					No = false;
				}
				else if (gplib::input::CheckPush(gplib::input::KEY_RIGHT)){
					sizeX = 1.2f;
					sizeY = 1.0f;
					Yes = false;
					No = true;
				}
				else if (gplib::input::CheckPush(gplib::input::KEY_DOWN) && (Yes == true || No == true)){
					//決定みたいなやつ
					kill();
				}
			}
			break;

		case UITYPE::CHARA:
			if (gplib::input::CheckPush(gplib::input::KEY_LEFT))		//左プレイヤーターンの時
			{
				player1scale = 1.2f;
				player2scale = 1.0f;

			}
			if (gplib::input::CheckPush(gplib::input::KEY_RIGHT))	//右プレイヤーターンの時
			{
				player2scale = 1.2f;
				player1scale = 1.0f;

			}
			break;
		case UITYPE::PHASE:
			if (gplib::input::CheckPush(gplib::input::KEY_BTN1)){
			/*if (timer->get() > 2.0f)
				{
					scaleX = 1.5f;
					scaleY = 1.5f;
				}*/
			
				if (i < 4)
				{
					i++;
				}
				if (i == 3)
				{
					i = 0;
				}

			}
				break;
		}


		easing::Step();

	}



}