#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"
#include <vector>
#include <memory>

namespace game
{

class DiceManager : public ci_ext::Object
{
	//*************************************************//
	//　定数
	//*************************************************//
private:

	static const int JUDGE[3][3];						//判定
	static const ci_ext::Vec3i STARTMASU[2][2];			//ダイス初期位置


	//*************************************************//
	//　変数
	//*************************************************//
private:

	std::weak_ptr<ci_ext::Object> p_parent;				// 親のポインタ

	std::vector<std::vector<ci_ext::Vec3i>> dicemasu;	// ダイスオブジェクトの座標（前プレイヤー:後ダイス）

	int	turnPlayer_;									// 現在のターンプレイヤー
	int selectDice_;									// 指定しているダイス

	//*************************************************//
	//　関数
	//*************************************************//
private:

	/*
		@brief							キー入力処理
		@return							なし
	*/
	void key();

	/*
		@brief							他のダイスの座標かくにん
		@param[in] no					ダイスの配列
		@param[in] dir					方向ベクトル
		@return							なし
	*/
	void MovingPos(const int no, const ci_ext::Vec3i& pos);	


	/*
		@brief			勝敗判定
		@param			なし
		@return			勝敗結果		-1:敗北 0:あいこ 1:勝利
	*/
	int getAttackJudge(int player, int enemy);


	/*
		@brief							ダイスオブジェクトの取得
		@param[in] player				ダイスの配列
		@param[in] id					識別番号
		@return							オブジェクトポインタ
	*/
	std::weak_ptr<Object> getDicePtr(const int player,const int id);


public:

	/*
		@brief							ターンの変更
		@param[in]	playerID			プレイヤー識別番号
		@return							なし
	*/
	void ChangeTurn(const int playerID);


	/*
		@brief							コンストラクタ
		@param[in]	objectName			オブジェクト名
		@param[in]	ptr					親のポインタ
		@return							なし
	*/
	DiceManager(const std::string& objectName, const std::weak_ptr<Object> ptr);

	//tuika
	//void SetMasu();

	/*
		@brief							サイコロ作成
		@return							なし
	*/
	void init() override;


	/*
		@brief							描画
		@return							なし
	*/
	void render() override;

	/*
		@brief							フレーム更新
		@return							なし
	*/
	void update() override;

	/*
		@brief							メッセージ読み取り
		@param[in] sender				送り主ポインタ
		@param[in] msg					メッセージ（文字列）
		@param[in] num					メッセージ（数値）
		@return							なし
	*/
	void receiveMsg(std::weak_ptr<Object>& sender, const std::string& msg) override;


};

}