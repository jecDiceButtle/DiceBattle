#include "cutin.h"
#include "../../lib/gplib.h"
#include "easing.h"

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//

//	const int Cutin::HOGE = 100;

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	Cutin::Cutin(const std::string& objectName,int y)
		:
		Object(objectName),
		cutinY(y)
	{
		easing::Create("cutinX", easing::EASINGTYPE::LINEAR, 500, 0, 60);
		gplib::graph::Draw_LoadObject("Cutin", "res/gra/cutin.png");
		
	}
	Cutin::~Cutin()
	{

	}
	int Cutin::draw()
	{
		
		gplib::graph::Draw_Graphics(
			(int)easing::GetPos("cutinX"), cutinY, 0.f,
			"Cutin",
			0, 0,
			gplib::graph::Draw_GetImageWidth("Cutin"), gplib::graph::Draw_GetImageHeight("Cutin"),
			0, 1.f, 1.f, 0);
		
		//easing::GetPos("cutin", cutinX);
		/*gplib::graph::Draw_GraphicsLeftTop(
			(int)cutinX, gplib::system::WINH / 2, 0.f,
			"cutin",
			0, 0,600 , 103, 0);*/
		return 0;
	}

	void Cutin::render()
	{
		gplib::graph::Draw_Clear();
		Cutin::draw();
		
	}

	void Cutin::update()
	{

		easing::Start("cutinX");
		
		easing::Step();	
	}

}