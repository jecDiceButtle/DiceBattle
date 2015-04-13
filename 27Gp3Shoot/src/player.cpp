#include "player.h"
#include "../../lib/gplib.h"
#include "stage.h"

namespace game
{
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//

	const int Player::DEFAULTCOST = 3;

	//**************************************************************************************//
	//�֐��L�q
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
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "P1_COST:" + std::to_string(cost[0]) + "  P2_COST:" + std::to_string(cost[1]);

		gplib::font::Draw_FontTextNC(100, 150, 0.f, str, ARGB(255, 0, 0, 0), 0);
		gplib::graph::Draw_2DRefresh();//tuika
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