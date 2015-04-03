#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/gplib.h"

namespace game
{
	class CSceneStage : public ci_ext::Object
	{
	private:

		//*************************************************//
		//　定数
		//*************************************************//

		//状態遷移
		enum class STAGESTATE
		{
			STANDBY,				//ゲーム前
			PLAYING,				//ゲーム中
			RESULT,					//ゲームオーバー
		};

		//プレイヤーターン
		enum class TURN
		{
			null = -1,				//ターン未設定
			PLAYER1,				//プレイヤー１
			PLAYER2,				//プレイヤー２
		};

		//ターンフェイズ
		enum class PHASE
		{
			null = -1,				//ターン未設定
			SUMMON,					//召喚(アルファ保留）
			MAIN,					//移動
			BUTTLE,					//対戦
			END,					//（とりあえず仮配置）
		};


		//*************************************************//
		//　変数
		//*************************************************//

	private:
		static const int JUDGE[3][3];

		bool		phaseinit_;			// フェイズの更新フラグ

		TURN		turn_;				// プレイヤーターン
		STAGESTATE	state_;				// 状態遷移
		PHASE		phase_;				// ターンフェイズ


		//*************************************************//
		//　関数
		//*************************************************//

	public:

		CSceneStage(const std::string& objectName);

		/*
			@brief			勝敗判定
			@param			なし
			@return			勝敗結果		-1:敗北 0:あいこ 1:勝利
		*/
		int getAttackJudge(int player, int enemy);
		

		/*
			@brief			フェイズの更新
			@return			なし
		*/
		void NextPhase();

		void init() override;
		void render() override;
		void update() override;
	};

}