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
		if (gplib::input::CheckPush(gplib::input::KEY_LEFT))
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
			//ダイスに選択描画
			// dice->select();

			bool selectF = true;			//選択フラグ

			//ダイスのいずれかが移動中は選択変更を不可
			std::string str = "p" + std::to_string(turnPlayer_);
			auto objects = getObjectsFromChildren({ "dice", str });
			for (auto obj : objects)
			{
				auto dice = ci_ext::weak_to_shared<game::Dice>(obj);

				if (dice->isMoving())
					selectF = false;
			}


			if (selectF)
			{
				//選択可能なダイスを探す。
				for (int i = 1; i <= (int)dicemasu[turnPlayer_].size(); i++)
				{
					int no = (selectDice_ + i) % (int)dicemasu[turnPlayer_].size();

					//選択されているダイスの次が選択できるか
					auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, no));

					if (dice->isIdoling())
					{
						selectDice_ = no;
						break;
					}
				}
			}
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
	void DiceManager::ChangeTurn(const int playerID)
	{
		if (turnPlayer_ != playerID)
		{
			turnPlayer_ = playerID;
			selectDice_ = 0;
		}
	}

	//**************************************************************************************//
	void DiceManager::Check()
	{
		//=============================
		// 隣り合ったダイスを確認
		//=============================

		ci_ext::Vec3i dir[] =
		{

			ci_ext::Vec3i(-1, 0, 0),		// 左
			ci_ext::Vec3i(1, 0, 0),			// 右
			ci_ext::Vec3i(0, 1, 0),			// 上
			ci_ext::Vec3i(0, -1, 0),		// 下

		};

		int enemyPlayer = (turnPlayer_ + 1) % 2;
		battledice.clear();


		for (int i = 0; i < dicemasu[turnPlayer_].size(); i++)	//自分のダイスの数
		{
			bool inflag= false;				//挿入フラグ
			pBattleDice temp;
			temp.selectF = false;

			//検索するダイスが攻撃可能かどうか（死んでないかどうか）
			auto offdice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, i));
			if (!offdice->isIdoling()) continue;

			temp.p_offense = offdice;

			for (int j = 0; j < dicemasu[enemyPlayer].size(); j++)	//相手のダイスの数
			{
				//敵ダイスが生きているかどうか
				auto defdice = ci_ext::weak_to_shared<Dice>(getDicePtr(enemyPlayer, j));
				if (!defdice->isIdoling()) continue;

				for (int k = 0; k < 4; k++)							//方向の確認の回数
				{
					//隣り合っているか判定
					if ((dicemasu[turnPlayer_][i] + dir[k]).x() == dicemasu[enemyPlayer][i].x()
						&& (dicemasu[turnPlayer_][i] + dir[k]).y() == dicemasu[enemyPlayer][i].y())
					{
						inflag = true;
						temp.p_defense.push_back(defdice);
						break;
					}


				}

			}

			if (inflag)
				battledice.push_back(temp);

		}
	}
	
	

	//**************************************************************************************//


	void DiceManager::Summon()
	{
		//召喚フェイズはとりあえず保留
		//デス状態がない場合は次のフェーズへ

		bool nextF = true;		//フェイズ移動フラグ

		std::string str = "p" + std::to_string(turnPlayer_);
		auto objects = getObjectsFromChildren({ "dice", str });

		for (auto obj : objects)
		{
			auto dice = ci_ext::weak_to_shared<game::Dice>(obj);
			if (dice->isDying())
				nextF = false;
		}

		if (nextF)
		{
			auto parent = ci_ext::weak_to_shared<CSceneStage>(p_parent);
			parent->NextPhase();
		}

	}
	void DiceManager::Main()
	{
		key();
	}
	void DiceManager::Battle()
	{
		switch (batphase_)
		{
			//======================
			//攻撃するキャラの確認
			//======================
		case game::DiceManager::check:
			
			Check();
			//攻撃待機０ならend

			if (battledice.empty())
			{
				batphase_ = end;
			}

			//1以上ならAtkSelect
			else
			{
				batphase_ = atkSelect;
			}
			break;

			//======================
			//攻撃側のキャラ選択
			//======================
		case game::DiceManager::atkSelect:
			
			//攻撃待機が1キャラならemySelect
			if (battledice.size() == 1)
			{
				batphase_ = emySelect;
			}
			//攻撃待機2なら選択させる
			else
			{

			}


			break;

			//======================
			//防御側の選択
			//======================
		case game::DiceManager::emySelect:


			
			for (auto bdice : battledice)
			{
				if (bdice.selectF)
				{
					//攻撃待機1ならbattle
					if (bdice.p_defense.size() == 1)
					{
						batphase_ = battle;
					}
					//攻撃待機2なら選択させる
					else
					{

					}
					
				}
			}
			
			

			


			break;

			//======================
			//勝敗の判定と攻撃アニメーション
			//======================
		case game::DiceManager::battle:



			break;

			//======================
			//ダメージ処理とダイスの削除
			//======================
		case game::DiceManager::destroy:

			break;

			//======================
			//攻撃ダイスがない場合、次のフェーズへ
			//======================
		case game::DiceManager::end:
			
			auto parent = ci_ext::weak_to_shared<CSceneStage>(p_parent);
			parent->NextPhase();
			break;
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

	void DiceManager::init()
	{
		//ダイスの生成
		for (int i = 0; i < 2; i++)	//プレイヤー
		{
			for (int j = 0; j < 2; j++)	//ダイスの数
			{
				std::string str = "dice_p" + std::to_string(i) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice(str,dicemasu[i][j]));
			}
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
		switch (phase_)
		{
			//召喚フェイズ
		case 0:
			Summon();
			break;
			//メインフェイズ
		case 1:
			Main();
			break;
			//バトルフェイズ
		case 2:
			Battle();
			break;
		}

	}

	//メッセージ受信
	void DiceManager::receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg)
	{
		//メッセージ分割
		auto msgVec = gplib::text::split(msg, ",");

		for (auto ms : msgVec){
			//さらに分割
			auto mVec = gplib::text::split(ms, "=");
			
				if (mVec[0] == "player")
				{
					ChangeTurn(stoi(mVec[1]));
				}
				if (mVec[0] == "phase")
				{
					phase_ = stoi(mVec[1]);
				}
			}
	}
}