#include "dicemanager.h"
#include "../../lib/gplib.h"
#include "dice.h"
#include "stage.h"

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//


	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//
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

	}

	void DiceManager::MovingPos(const int no, const ci_ext::Vec3i& pos)
	{
		for (int i = 0; i < dicepos.size(); i++)	//プレイヤー
		{
			for (int j = 0; j < dicepos[i].size(); j++)	//ダイス
			{
				if (i == turnPlayer_ && j == no)
					continue;

				if ((dicepos[turnPlayer_][no] + pos) == dicepos[i][no])
				{
					return;
				}
			}
			
		}

		auto stage = ci_ext::weak_to_shared<CSceneStage>(p_parent);
		if (stage->checkMovableDice((dicepos[turnPlayer_][no] + pos)))
		{
			dicepos[turnPlayer_][no].offset(pos.x(),pos.y());
		}

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
				//std::string str = "dice_player" + std::to_string(i+1) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice("dice", i, j));
				p_dice.push_back(ptr);
			}
		}

		// ダイスのボード座標の初期化
		for (int i = 0; i < 2; i++)
		{
			std::vector<ci_ext::Vec3i> temp;
			for (int j = 0; j < 3; j++)
			{
				temp.push_back(ci_ext::Vec3i(5, 5, 0));
			}
			dicepos.push_back(temp);
		}
	}

	void DiceManager::render()
	{
#if _DEBUG

		std::string str = "現在プレイヤー :" + std::to_string(turnPlayer_) +
			",選択ダイス :" + std::to_string(selectDice_) + "  X:" +
			std::to_string(dicepos[turnPlayer_][selectDice_].x()) +
			", Y:" + std::to_string(dicepos[turnPlayer_][selectDice_].y());

		gplib::font::Draw_FontTextNC(100, 100, 0.f, str, ARGB(255, 255, 255, 255), 0);


#endif
	}

	void DiceManager::update()
	{
		key();
	}

}