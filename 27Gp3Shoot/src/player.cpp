#include "player.h"
#include "../../lib/gplib.h"
#include "stage.h"

namespace game
{

	//�ǉ��@�R�X�g�摜�ǂݍ���
	
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
		//cost�摜�̓ǂݍ���
		gplib::graph::Draw_LoadObject("cost", "res/gra/cost.png");
		gplib::graph::Draw_LoadObject("cost_back", "res/gra/cost_back.png");
		pos_1P.x(100);
		pos_1P.y(100);

		pos_2P.x(1000);
		pos_2P.y(100);
	}

	void Player::render()
	{
#if _DEBUG
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "P1_COST:" + std::to_string(cost[0]) + "  P2_COST:" + std::to_string(cost[1]);

		gplib::font::Draw_FontTextNC(100, 150, 0.f, str, ARGB(255, 0, 0, 0), 0);
		


		//�ǉ� cost�`��
		//player1
		for (int i = 0; i < DEFAULTCOST; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_1P.ix() + COST_Space * i, pos_1P.iy(), pos_1P.z(),
				"cost_back",
				0, 0, COST_W, COST_H);
		}
		for (int i = 0; i < cost[0]; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_1P.ix() + COST_Space * i, pos_1P.iy(), pos_1P.z(),
				"cost",
				0, 0, COST_W, COST_H);
		}
		/////////////////////////////////
		//player2
		for (int i = 0; i < DEFAULTCOST; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_2P.ix() + COST_Space * -i, pos_2P.iy(), pos_2P.z(),
				"cost_back",
				0, 0, COST_W, COST_H);
		}
		for (int i = 0; i < cost[1]; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_2P.ix() + COST_Space * -i, pos_2P.iy(), pos_2P.z(),
				"cost",
				0, 0, COST_W, COST_H);
		}
		///////////////////////////////////////////////

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

	void Player::receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg, const int num)
	{

		if (msg == "turn")
		{
			CostReset(num);
		}
		if (msg == "phase")
		{

		}

	}

}