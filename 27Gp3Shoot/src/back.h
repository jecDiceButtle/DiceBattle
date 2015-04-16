#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"


namespace game
{

	class Back : public ci_ext::Object
{
	//*************************************************//
	//　定数
	//*************************************************//
private:
	

	//*************************************************//
	//　変数
	//*************************************************//
private:

	int back_num;

	//*************************************************//
	//　関数
	//*************************************************//
private:


public:

	/*
		@brief							コンストラクタ
		@param[in]	objectName			オブジェクト名
		@return							なし
	*/
	//backnum=0(STAGEBACK)
	Back(const std::string& objectName, const int backnum);


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
		@brief							座標の移動確認
		@param[in]	pos					移動先の座標
		@return							移動可能かどうか
		@true							可
		@false							不可
	*/




};

}