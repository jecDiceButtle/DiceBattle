#include "dice.h"
#include "../../lib/gplib.h"

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//
	

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	Dice::Dice(const std::string& objectName,const int playerid,const int diceid)
		:
		Object(objectName),
		playerID_(playerid),
		diceID_(diceid)
	{

	}

	int Dice::getTopType(){
		return num[0];
	}

	int Dice::getId_Player(){
		return playerID_;
	}
	int Dice::getId_Dice(){
		return diceID_;
	}

	void Dice::swap(DIRECT dir){

		TYPE Numkeep = num[0];

		if (dir == LEFT){
			num[0] = num[2];
			num[2] = num[5];
			num[5] = num[3];
			num[3] = Numkeep;
		}
		if (dir == RIGHT){
			num[0] = num[3];
			num[3] = num[5];
			num[5] = num[2];
			num[2] = Numkeep;
		}
		if (dir == FOWARD){
			num[0] = num[1];
			num[1] = num[5];
			num[5] = num[4];
			num[4] = Numkeep;
		}
		if (dir == BACK){
			num[0] = num[4];
			num[4] = num[5];
			num[5] = num[1];
			num[1] = Numkeep;
		}
	}

	

	void Dice::render()
	{
		
	}

	void Dice::update()
	{

	}

}