#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"
#include "../../lib/ci_ext/DrawObj.hpp"
#include "movableObject.h"




namespace game
{

class UI : public MovableObject
{
	//*************************************************//
	//　定数
	//*************************************************//
private:


	//*************************************************//
	//　変数
	//*************************************************//
public:

enum UITYPE{ CUTIN, POPUP, CHARA, PHASE};


private:
	UITYPE type_;
	float x;	
	float y;


	//cutin
	bool	initF;
	std::weak_ptr<ci_ext::Object> timer_;
	enum MOVESTATE{ RIGHTCENTER, CENTER, CENTERLEFT };
	MOVESTATE state_;

	//popup
	
	float sizeX;
	float sizeY;
	bool flag;
	bool Yes;
	bool No;


	//chara
	float player1scale;
	float player2scale;

	//phase
	float scaleX;
	float scaleY;
	int i;

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
	UI(const std::string& objectName,UITYPE type,float x,float y);
	void flagset();
	void Cutin();
	/*
		@brief							描画
		@return							なし
	*/
	
	void init() override;


	void render() override;

	void update() override;

	/*
		@brief							フレーム更新
		@return							なし
	*/
	
};

}