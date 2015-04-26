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
		//cost画像の読み込み
		gplib::graph::Draw_LoadObject("cost", "res/gra/cost.png");
		gplib::graph::Draw_LoadObject("cost_back", "res/gra/cost_back.png");
		//costの位置を初期化
		pos_1P.x(50);
		pos_1P.y(100);

		pos_2P.x(1000);
		pos_2P.y(100);
	}

	void Player::render()
	{
#if _DEBUG
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "P1_COST:" + std::to_string(cost[0]) + "  P2_COST:" + std::to_string(cost[1]);

		//追加 cost描画//////////////////////////////////////////////////////////
		//player1
			for (int i = 0; i < DEFAULTCOST; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_1P.ix() + COST_Space * i, pos_1P.iy(), pos_1P.z(),
				"cost_back",
				0, 0, COST_W, COST_H, 0, 2.f, 2.f);
		}
			for (int i = 0; i < cost[0]; i++)
			{
				gplib::graph::Draw_Graphics(
					pos_1P.ix() + COST_Space * i, pos_1P.iy(), pos_1P.z(),
					"cost",
					0, 0, COST_W, COST_H, 0, 2.f, 2.f);
			}
		//////////////////////////////////////////////////////////////////////////
		//player2
		for (int i = 0; i < DEFAULTCOST; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_2P.ix() + COST_Space * -i, pos_2P.iy(), pos_2P.z(),
				"cost_back",
				0, 0, COST_W, COST_H,0,2.f,2.f);
		}
		for (int i = 0; i < cost[1]; i++)
		{
			gplib::graph::Draw_Graphics(
				pos_2P.ix() + COST_Space * -i, pos_2P.iy(), pos_2P.z(),
				"cost",
				0, 0, COST_W, COST_H, 0, 2.f, 2.f);
		}
		///////////////////////////////////////////////////////////////////////////

		gplib::font::Draw_FontTextNC(100, 150, 0.f, str, ARGB(255, 0, 0, 0), 0);
		gplib::graph::Draw_2DRefresh();//tuika
#endif
	}

	void Player::update()
	{
		
	}

	void Player::receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg)
	{

		//メッセージ分割
		auto msgVec = gplib::text::split(msg, ",");

		for (auto ms : msgVec){
			//さらに分割
			auto mVec = gplib::text::split(ms, "=");

			if (mVec[0] == "player")
			{
				if(turn_ != std::stoi(mVec[1]))
				{
					turn_ = std::stoi(mVec[1]);
					CostReset(turn_);
					
				}
				
			}
		}

	}

}