#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Dice : public ci_ext::Object
{
	//*************************************************//
	//Å@íËêî
	//*************************************************//
private:
	enum DIRECT{LEFT,RIGHT,FOWARD,BACK};
	enum TYPE{GU,CH,PA,DEF};

	

	//*************************************************//
	//Å@ïœêî
	//*************************************************//
private:
	int diceID_;
	int playerID_;
	TYPE num[6];
	DIRECT dir_;

	//*************************************************//
	//Å@ä÷êî
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