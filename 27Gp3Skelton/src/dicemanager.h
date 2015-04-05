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

	//*************************************************//
	//　変数
	//*************************************************//
private:
	std::weak_ptr<ci_ext::Object> p_parent;				// 親のポインタ

	std::vector<std::weak_ptr<ci_ext::Object>> p_dice;	// ダイスオブジェクトのポインタ

	std::vector<ci_ext::Vec3i> dicepos;					// ダイスオブジェクトの座標

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


public:

	/*
		@brief							コンストラクタ
		@param[in]	objectName			オブジェクト名
		@param[in]	ptr					親のポインタ
		@return							なし
	*/
	DiceManager(const std::string& objectName, const std::weak_ptr<Object> ptr);


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

};

}