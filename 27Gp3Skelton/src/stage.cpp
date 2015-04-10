#include "stage.h"
#include <memory>
#include <string>
#include <iostream>

#include "logo.hpp"
#include "player.h"
#include "dicemanager.h"
#include "board.h"
#include "root.hpp"

#include <stdio.h>

extern std::shared_ptr<DX3DMESHMANAGER> meshManage;
extern std::shared_ptr<Dx_Camera> dxCamera;


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

		p_player = insertAsChild(new Player("player", this->selfPtr()));
		p_dm = insertAsChild(new DiceManager("dicemanager",this->selfPtr()));
		p_board = insertAsChild(new Board("board"));

		gplib::graph::Draw_LoadObject("logo", "res/gra/logo.png");
		
	}
	void CSceneStage::render()
	{
		dxCamera->SetEyePos(DxVec3(0.f, 0.f, -250.f));
		dxCamera->SetLookPos(0.f, 0.f, 0.f);

		meshManage->getG()->Setup3DEnv(dxCamera);

		meshManage->drawMesh(DxVec3(0, 0, 0), "dice", DxVec3(0.f, 0.f, 0.f), ARGB(255, 255, 255, 255), DxVec3(1, 1, 1));

#if _DEBUG

		gplib::graph::Draw_2DClear();
		gplib::font::Draw_FontText(50, 50, 0.f, "ゲーム画面", ARGB(255, 255, 255, 255), 0);
		gplib::graph::Draw_Graphics(
			0,0, 0.5f,
			"logo",
			0, 0,
			700, 700,
			0,
			0.1f, 0.1f
			);
		gplib::graph::Draw_2DRefresh();

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
				auto player = ci_ext::weak_to_shared<Player>(p_player);
				auto dm = ci_ext::weak_to_shared<DiceManager>(p_dm);

				if (turn_ == TURN::PLAYER1)
				{
					turn_ = TURN::PLAYER2;
					player->CostReset(1);
					dm->ChangeTurn(1);
					NextPhase();
				}

				else if (turn_ == TURN::PLAYER2)
				{
					turn_ = TURN::PLAYER1;
					player->CostReset(0);
					dm->ChangeTurn(0);
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

			if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
			{
				kill();
				//シーン遷移
				insertToParent(new Logo("scene_logo"));
			}
			break;
		}

	}
}


