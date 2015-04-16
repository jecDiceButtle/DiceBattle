#include "back.h"
#include "../../lib/gplib.h"



namespace game
{



	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//
	

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//


	
	Back::Back(const std::string& objectName, const int backnum)
		:
		Object(objectName),
		back_num(backnum)
	{
		gplib::graph::Draw_LoadObject("StageBack", "res/gra/StageBack.png");
	}

	void Back::render()
	{
		gplib::graph::Draw_2DClear();

		switch (back_num){
			case 0:
				gplib::graph::Draw_GraphicsLeftTop(0.f, 0.f, 1.f, "StageBack", 0, 0, gplib::system::WINW, gplib::system::WINH);
				break;
	}
		
		gplib::graph::Draw_2DRefresh();
	}

	void Back::update()
	{

	}

}