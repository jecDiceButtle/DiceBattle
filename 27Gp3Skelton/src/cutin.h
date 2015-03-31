#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Cutin : public ci_ext::Object
{
	//*************************************************//
	//　定数
	//*************************************************//
private:

//	static const int HOGE;				// 定数の例。削除すること。


	//*************************************************//
	//　変数
	//*************************************************//
private:

	float cutinX;
//	int piyo;							// 変数の例。削除すること。


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
	Cutin(const std::string& objectName,int y);
	~Cutin();
	int cutinY;
	int draw();

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