#include "dicemanager.h"
#include "../../lib/gplib.h"
#include "dice.h"
#include "stage.h"
#include "../../lib/ci_ext/object.hpp"

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//
	const int DiceManager::JUDGE[3][3]
	{
	//		  G  C  P
	/*G*/	{ 0, 1,-1},
	/*C*/	{-1, 0, 1},
	/*P*/	{ 1,-1, 0}
	};

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//
	
	int DiceManager::getAttackJudge(int player, int enemy){
		return JUDGE[player][enemy];
	}
	
	std::weak_ptr<ci_ext::Object> DiceManager::getDicePtr(const int player, const int id)
	{
		std::string str = "dice_p" + std::to_string(player) + "_no" + std::to_string(id);

		return getObjectFromChildren(str);
	}

	
	void DiceManager::key()
	{
		if(gplib::input::CheckPush(gplib::input::KEY_LEFT))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(-1, 0, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_RIGHT))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(1, 0, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_UP))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(0, 1, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_DOWN))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(0, -1, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
		{
			//ダイスオブジェクトに生死を聞くこと。
			(selectDice_ += 1) %= 3;
		}

	}

	void DiceManager::MovingPos(const int no, const ci_ext::Vec3i& pos)
	{
		auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, no));
		//待機中以外は移動不可
		if (!dice->isIdoling()) 
			return;

		for (int i = 0; i < dicepos.size(); i++)	//プレイヤー
		{
			for (int j = 0; j < dicepos[i].size(); j++)	//ダイス
			{
				if (i == turnPlayer_ && j == no)
					continue;

				if ((dicepos[turnPlayer_][no] + pos).x() == dicepos[i][j].x() 
					&& (dicepos[turnPlayer_][no] + pos).y() == dicepos[i][j].y())
				{
					return;
				}
			}
			
		}

		auto stage = ci_ext::weak_to_shared<CSceneStage>(p_parent);
		if (stage->checkMovableDice((dicepos[turnPlayer_][no] + pos)))
		{
			dicepos[turnPlayer_][no].offset(pos.x(),pos.y());

			auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, selectDice_));
			
			dice->Move(pos, dicepos[turnPlayer_][no]);
		}


	}
	/*
		@brief							ターンの変更
		@param[in]	playerID			プレイヤー識別番号
		@return							なし
	*/
	void DiceManager::ChangeTurn(const int playerID)
	{
		turnPlayer_ = playerID;
		selectDice_ = 0;
	}

	//**************************************************************************************//
	//デフォルト関数
	//**************************************************************************************//


	DiceManager::DiceManager(const std::string& objectName,const std::weak_ptr<Object> ptr)
		:
		Object(objectName),
		p_parent(ptr),
		turnPlayer_(0),
		selectDice_(0)
	{

	}

	void DiceManager::init()
	{
		//ダイスの生成
		for (int i = 0; i < 2; i++)	//プレイヤー
		{
			for (int j = 0; j < 3; j++)	//ダイスの数
			{
				std::string str = "dice_p" + std::to_string(i) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice(str, ci_ext::Vec3i(i, j, 0)));
			}
		}

		// ダイスのボード座標の初期化
		for (int i = 0; i < 2; i++)
		{
			std::vector<ci_ext::Vec3i> temp;
			for (int j = 0; j < 3; j++)
			{
				temp.push_back(ci_ext::Vec3i(i, j, 0));
			}
			dicepos.push_back(temp);
		}
	}
	

	void DiceManager::render()
	{
#if _DEBUG
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "現在プレイヤー :" + std::to_string(turnPlayer_) +
			",選択ダイス :" + std::to_string(selectDice_) + "  X:" +
			std::to_string(dicepos[turnPlayer_][selectDice_].x()) +
			", Y:" + std::to_string(dicepos[turnPlayer_][selectDice_].y());

		gplib::font::Draw_FontTextNC(100, 100, 0.f, str, ARGB(255, 0, 0, 0), 0);


		for (int i = 0; i < dicepos.size(); i++)
		{
			for (int j = 0; j < dicepos[i].size(); j++)
			{
				std::string str = "プレイヤー" + std::to_string(i) +
					",  ダイス" + std::to_string(j) + "  X:" +
					std::to_string(dicepos[i][j].x()) +
					", Y:" + std::to_string(dicepos[i][j].y());

				if (i == turnPlayer_ && j == selectDice_)
				{
					gplib::font::Draw_FontTextNC(500 + (i * 300), 100 + 30 * j, 0.f, str, ARGB(255, 255, 0, 0), 0);
				}
				else
				{
					gplib::font::Draw_FontTextNC(500 + (i * 300), 100 + 30 * j, 0.f, str, ARGB(255, 0, 0, 0), 0);
				}	
			}
		}
		gplib::graph::Draw_2DRefresh();//tuika



#endif
	}

	void DiceManager::update()
	{
		key();

	}

	void DiceManager::receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg, const int num)
	{

		if (msg == "turn")
		{
			ChangeTurn(num);
		}
		if (msg == "phase")
		{

		}
	}
}