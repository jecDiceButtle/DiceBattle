#include "player.h"
#include "../../lib/gplib.h"
#include "stage.h"

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//

	const int Player::DEFAULTCOST = 3;

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	bool Player::isCostRemain(const int id)
	{
		return cost[id] > 0;
	}

	void Player::CostDecrease(const int id, const int point)
	{
		cost[id] -= point;
	}
	
	void Player::CostReset(const int id)
	{
		cost[id] = DEFAULTCOST;
	}


	Player::Player(const std::string& objectName, const std::weak_ptr<Object> ptr)
		:
		Object(objectName),
		p_parent(ptr)
	{
		for (int i = 0; i < 2; i++)
		{
			cost.push_back(DEFAULTCOST);
		}
	}

	void Player::render()
	{
#if _DEBUG

		std::string str = "P1_COST:" + std::to_string(cost[0]) + "  P2_COST:" + std::to_string(cost[1]);

		gplib::font::Draw_FontTextNC(100, 150, 0.f, str, ARGB(255, 255, 255, 255), 0);

#endif
	}

	void Player::update()
	{
		if (gplib::input::CheckPush(gplib::input::KEY_BTN1))
		{
			auto stage = getObjectFromRoot("scene_stage");
			auto object = ci_ext::weak_to_shared<CSceneStage>(stage);

			object->NextPhase();
		}
	}

}