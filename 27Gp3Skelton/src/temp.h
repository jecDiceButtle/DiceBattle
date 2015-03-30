#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Temp : public ci_ext::Object
{
	//*************************************************//
	//　定数
	//*************************************************//
private:

	static const int HOGE;				// 定数の例。削除すること。


	//*************************************************//
	//　変数
	//*************************************************//
private:

	int piyo;							// 変数の例。削除すること。


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
	Temp(const std::string& objectName);


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