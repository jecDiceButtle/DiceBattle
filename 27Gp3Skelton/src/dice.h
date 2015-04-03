#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Dice : public ci_ext::Object
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

	//*************************************************//
	//　関数
	//*************************************************//
private:


public:
	Dice(const std::string& objectName,const int playerID,const int diceID);

	void render() override;
	void update() override;


	
	void swap(DIRECT dir);

	int getTopType();
	int getId_Player();
	int getId_Dice();

};

}