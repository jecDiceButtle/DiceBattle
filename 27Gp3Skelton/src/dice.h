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