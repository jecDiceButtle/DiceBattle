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

	

	//*************************************************//
	//　変数
	//*************************************************//
private:
	int diceID_;
	int playerID_;
	TYPE num[6];
	DIRECT dir_;
	
	//dice座標
	float xx;											//ダイスのX座標
	float yy;											//ダイスのY座標
	float zz;											//ダイスのZ座標〔今は0〕
	
	float masuX = 0;
	float masuY = 0;
	
	//*************************************************//
	//　関数
	//*************************************************//
private:
	
public:
	Dice(const std::string& objectName,const int playerID,const int diceID);

	void render() override;
	void update() override;

	float getDicePosX();
	float getDicePosY(); 

	void swap(DIRECT dir);
	int getTopType();
	int getId_Player();
	int getId_Dice();


	void setMasu(int x, int y);
};

}