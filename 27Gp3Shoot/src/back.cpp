#include "back.h"
#include "../../lib/gplib.h"



namespace game
{



	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//

	

	//**************************************************************************************//
	//�֐��L�q
	//**************************************************************************************//


	Back::Back(const std::string& objectName)
		:
		Object(objectName)
	{
		gplib::graph::Draw_LoadObject("StageBack", "res/gra/StageBack.png");
	}

	void Back::render()
	{
		gplib::graph::Draw_2DClear();
		gplib::graph::Draw_GraphicsLeftTop(0.f, 0.f, 1.f, "StageBack", 0, 0, gplib::system::WINW, gplib::system::WINH);
		gplib::graph::Draw_2DRefresh();
	}

	void Back::update()
	{

	}

}