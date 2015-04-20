#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"



#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"
#include "../../lib/ci_ext/DrawObj.hpp"
#include "movableObject.h"
	


namespace game
{

	class Dice : public MovableObject
{
	//*************************************************//
	//　定数
	//*************************************************//
private:
	enum DIRECT{LEFT,RIGHT,FOWARD,BACK};
	enum TYPE{GU,CH,PA,DEF};

	//行動ステータス
	enum STATE
	{
		DEAD,			// 死に状態（描画なし動作なし）
		IDOL,			// 待機状態
		MOVE,			// 移動中
		ATTACK,			// 攻撃中
	};

	//描画ステータス
	enum DISPSTATE		
	{
		DICE,			// サイコロのみ
		DICE_CHARA,		// サイコロとキャラクター
		CHARA,			// キャラのみ
	};


	//*************************************************//
	//　変数
	//*************************************************//
private:
	int diceID_;
	int playerID_;
	TYPE num[6];
	DIRECT dir_;

	int count_;											// 移動カウンタ

	STATE state_;										// 行動状態
	DISPSTATE dispstate_;								// 描画状態
	
	//dice座標
	//float xx;											//ダイスのX座標
	//float yy;											//ダイスのY座標
	//float zz;											//ダイスのZ座標〔今は0〕
	
	ci_ext::Vec3f pos_;									//座標

	ci_ext::Vec3f add_;									//移動量

	float masuX;
	float masuY;
	
	//*************************************************//
	//　関数
	//*************************************************//
private:

	/*
		@brief							待機中の処理
		@return							なし
	*/
	void Idol();

	/*
		@brief							移動中の処理
		@return							なし
	*/
	void Moving();

	/*
		@brief							移動中の処理
		@return							なし
	*/
	void Attack();


public:
	Dice(const std::string& objectName, const ci_ext::Vec3i& pos = ci_ext::Vec3i::zero());
	void init()	override;
	void render() override;
	void update() override;


	float getDicePosX();
	float getDicePosY(); 

	void swap(DIRECT dir);
	int getTopType();

	/*
		@brief							アクセサ、待機中かどうか
		@return							待機中かどうか
		@true							待機中
	*/
	bool isIdoling();

	/*
		@brief							移動命令
		@return							なし
	*/
	void Move(const ci_ext::Vec3i& dir,const ci_ext::Vec3i& pos);



	void setMasu(int x, int y);
};

}