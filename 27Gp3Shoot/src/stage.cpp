#include "stage.h"
#include <memory>
#include <string>
#include <iostream>

#include "logo.hpp"
#include "player.h"
#include "dicemanager.h"
#include "board.h"

//tuika
#include "camera.h"
#include "back.h"

#include <stdio.h>


namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//


	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//
	
	

	void CSceneStage::NextPhase()
	{
		phaseinit_ = true;

		switch (phase_)
		{
		case game::CSceneStage::PHASE::SUMMON:
			phase_ = PHASE::MAIN;
			break;

		case game::CSceneStage::PHASE::MAIN:
			phase_ = PHASE::BUTTLE;
			break;

		case game::CSceneStage::PHASE::BUTTLE:
			phase_ = PHASE::END;
			break;

		case game::CSceneStage::PHASE::END:
			phase_ = PHASE::SUMMON;
			break;
		}
	}

	bool CSceneStage::checkMovableDice(const ci_ext::Vec3i &pos)
	{

		auto board = ci_ext::weak_to_shared<Board>(p_board);
		//ボードがOKしてくれたら
		if (board->isMovablePosition(pos))
		{
			auto player = ci_ext::weak_to_shared<Player>(p_player);
			//プレイヤーのコストがあるのならば
			if (player->isCostRemain((int)turn_))
			{
				//プレイヤーのコストを減らす
				player->CostDecrease((int)turn_);
				return true;
			}
		}
		return false;
	}

	//**************************************************************************************//
	//デフォルト関数
	//**************************************************************************************//

	CSceneStage::CSceneStage(const std::string& objectName)
		:
		Object(objectName),
		state_(STAGESTATE::STANDBY),
		turn_(TURN::null),
		phase_(PHASE::null)
	{

	}
	void CSceneStage::init()
	{

		p_board = insertAsChild(new Board("board"));
		p_player = insertAsChild(new Player("player", this->selfPtr()));
		p_dm = insertAsChild(new DiceManager("dicemanager",this->selfPtr()));
		p_camera = insertAsChild(new Camera("camera"));

		insertAsChild(new Back("stageback",0));

	}
	void CSceneStage::render()
	{
		//デバッグ用
#ifdef _DEBUG
		gplib::graph::Draw_2DClear();

		//gplib::font::Draw_FontTextNC(0, 0, 0.f, "ゲーム画面", ARGB(255, 0, 0, 0), 0); //今はなし
		std::string str = " ";

		switch (turn_)
		{
		case game::CSceneStage::TURN::PLAYER1:
			//std::cout << "プレイヤー１" ;
			str = "プレイヤー１";
			
			break;
		case game::CSceneStage::TURN::PLAYER2:
			//std::cout << "プレイヤー２" ;
			str = "プレイヤー２";
			break;
		}
		gplib::font::Draw_FontTextNC(0, 20, 0.f, str, ARGB(255, 0, 0, 0), 0);


		switch (phase_)
		{
		case game::CSceneStage::PHASE::SUMMON:
			//std::cout << ":召喚フェーズ" << std::endl;
			str = ":召喚フェーズ";
			
			break;
		case game::CSceneStage::PHASE::MAIN:
			//std::cout << ":メインフェーズ" << std::endl;
			str = ":メインフェーズ";
			
			break;
		case game::CSceneStage::PHASE::BUTTLE:
			//std::cout << ":バトルフェーズ" << std::endl;
			str = ":バトルフェーズ";
			break;
		case game::CSceneStage::PHASE::END:
			//std::cout << ":エンドフェーズ" << std::endl;
			str = ":エンドフェーズ";
			break;
		}
		gplib::font::Draw_FontTextNC(120, 20, 0.f, str, ARGB(255, 0, 0, 0), 0);

		gplib::graph::Draw_2DRefresh();
#endif

	}
	void CSceneStage::update()
	{
		switch (state_)
		{
			//=============================================================================
			//  先攻後攻決めるフェイズ（未実装）
			//=============================================================================
		case game::CSceneStage::STAGESTATE::STANDBY:

			//ステート切り替え//
			if (true)
			{
				state_ = CSceneStage::STAGESTATE::PLAYING;
				phase_ = PHASE::SUMMON;
				turn_ = TURN::PLAYER1;
			}
			break;

			//=============================================================================
			//  ゲーム中のフェイズ
			//=============================================================================
		case game::CSceneStage::STAGESTATE::PLAYING:

			//フェーズ送信処理
			if (phaseinit_)
			{
				postMsgAllChildren("phase", (int)phase_);
				phaseinit_ = false;
			}

			//プレイヤーターン交換処理
			if (phase_ == PHASE::END)
			{
				if (turn_ == TURN::PLAYER1)
				{
					turn_ = TURN::PLAYER2;
					NextPhase();
				}
				else if (turn_ == TURN::PLAYER2)
				{
					turn_ = TURN::PLAYER1;
					NextPhase();
				}
				postMsgAllChildren("turn", (int)turn_);
			}



			//ステート切り替え//
			if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
			{
				//state_ = CSceneStage::STAGESTATE::RESULT; //今はなし
			}
			break;


			//=============================================================================
			//  リザルト
			//=============================================================================
			
		case game::CSceneStage::STAGESTATE::RESULT:

			if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
			{
				/*kill();*/
				//シーン遷移
				//insertToParent(new Logo("scene_logo")); //今はなし
			}
			break;
		}

	}
}


