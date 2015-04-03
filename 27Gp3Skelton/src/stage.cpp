#include "stage.h"
#include <memory>
#include <string>
#include <iostream>

#include "logo.hpp"
#include "dice.h"
#include "player.h"

#include <stdio.h>

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//
	const int CSceneStage::JUDGE[3][3]
	{
	//		  G  C  P
	/*G*/	{ 0, 1,-1},
	/*C*/	{-1, 0, 1},
	/*P*/	{ 1,-1, 0}
	};


	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//
	
	int CSceneStage::getAttackJudge(int player, int enemy){
		return JUDGE[player][enemy];
	}

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
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//std::string str = "dice_player" + std::to_string(i+1) + "_no" + std::to_string(j);
				insertAsChild(new Dice("dice", i, j));
			}
		}

		insertAsChild(new Player("player"));
		
	}
	void CSceneStage::render()
	{

#if _DEBUG
		gplib::font::Draw_FontTextNC(0, 0, 0.f, "ゲーム画面", ARGB(255, 255, 255, 255), 0);
		
		switch (turn_)
		{
		case game::CSceneStage::TURN::PLAYER1:
			std::cout << "プレイヤー１" ;
			break;
		case game::CSceneStage::TURN::PLAYER2:
			std::cout << "プレイヤー２" ;
			break;
		}


		switch (phase_)
		{
		case game::CSceneStage::PHASE::SUMMON:
			std::cout << ":召喚フェーズ" << std::endl;
			break;
		case game::CSceneStage::PHASE::MAIN:
			std::cout << ":メインフェーズ" << std::endl;
			break;
		case game::CSceneStage::PHASE::BUTTLE:
			std::cout << ":バトルフェーズ" << std::endl;
			break;
		case game::CSceneStage::PHASE::END:
			std::cout << ":エンドフェーズ" << std::endl;
			break;
		}

#endif

	}
	void CSceneStage::update()
	{
		switch (state_)
		{
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
		case game::CSceneStage::STAGESTATE::PLAYING:

			//フェーズ送信処理
			if (phaseinit_)
			{
				//作成予定
				//フェイズの状態を各オブジェクトへ送信する処理を書くこと
				//プレイヤーターンも送っちゃう

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
			}

			//ステート切り替え//
			if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
			{
				state_ = CSceneStage::STAGESTATE::RESULT;
			}
			break;

			//=============================================================================
			
		case game::CSceneStage::STAGESTATE::RESULT:

			if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
			{
				kill();
				//シーン遷移
				insertToParent(new Logo("scene_logo"));
			}
			break;
		}

	}
}


