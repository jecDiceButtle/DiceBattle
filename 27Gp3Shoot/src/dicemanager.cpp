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

	const ci_ext::Vec3i DiceManager::STARTMASU[2][2] =
	{
		{ ci_ext::Vec3i(1, 0, 0), ci_ext::Vec3i(3, 0, 0) },
		{ ci_ext::Vec3i(1, 4, 0), ci_ext::Vec3i(3, 4, 0) }
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
			(selectDice_ += 1) %= 2;
		}

	}

	void DiceManager::MovingPos(const int no, const ci_ext::Vec3i& dir)
	{
		//=============================
		// ダイスへ移動できるか確認
		//=============================
		auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, no));
		//待機中以外は移動不可
		if (!dice->isIdoling()) 
			return;

		//=============================
		// 隣り合ったダイスを確認
		//=============================

		for (int i = 0; i < dicemasu.size(); i++)	//プレイヤー
		{
			for (int j = 0; j < dicemasu[i].size(); j++)	//ダイス
			{
				if (i == turnPlayer_ && j == no)
					continue;

				if ((dicemasu[turnPlayer_][no] + dir).x() == dicemasu[i][j].x() 
					&& (dicemasu[turnPlayer_][no] + dir).y() == dicemasu[i][j].y())
				{
					return;
				}
			}
			
		}

		//=============================
		// コストの確認とダイスの移動
		//=============================

		auto stage = ci_ext::weak_to_shared<CSceneStage>(p_parent);
		if (stage->checkMovableDice((dicemasu[turnPlayer_][no] + dir)))
		{
			dicemasu[turnPlayer_][no].offset(dir.x(),dir.y());

			auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, selectDice_));
			
			dice->Move(dir, dicemasu[turnPlayer_][no]);
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
			for (int j = 0; j < 2; j++)	//ダイスの数
			{
				std::string str = "dice_p" + std::to_string(i) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice(str,STARTMASU[i][j]));
			}
		}

		// ダイスのマス座標の初期化
		for (int i = 0; i < 2; i++)
		{
			std::vector<ci_ext::Vec3i> temp;
			for (int j = 0; j < 2; j++)
			{
				temp.push_back(STARTMASU[i][j]);
			}
			dicemasu.push_back(temp);
		}
	}
	

	void DiceManager::render()
	{
#ifdef _DEBUG
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "現在プレイヤー :" + std::to_string(turnPlayer_) +
			",選択ダイス :" + std::to_string(selectDice_) + "  X:" +
			std::to_string(dicemasu[turnPlayer_][selectDice_].x()) +
			", Y:" + std::to_string(dicemasu[turnPlayer_][selectDice_].y());

		gplib::font::Draw_FontTextNC(100, 100, 0.f, str, ARGB(255, 0, 0, 0), 0);


		for (int i = 0; i < dicemasu.size(); i++)
		{
			for (int j = 0; j < dicemasu[i].size(); j++)
			{
				std::string str = "プレイヤー" + std::to_string(i) +
					",  ダイス" + std::to_string(j) + "  X:" +
					std::to_string(dicemasu[i][j].x()) +
					", Y:" + std::to_string(dicemasu[i][j].y());

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