#include "dice.h"
#include "../../lib/gplib.h"
//tuika
#include "monster.h"


#include "movableObject.h"

//3Dカメラ
extern Dx_Camera *dxCamera;
extern LPDIRECT3DDEVICE9 pD3DDevice;
//メッシュ全体管理クラス
extern DX3DMESHMANAGER *meshManage;
extern Dx_Camera *dxCamera;




namespace game
{
	using namespace ci_ext;
	using namespace gplib;


	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//
	//float Yaw = 0.f, Pit = 0.f, Roll = 0.f;
	
	//ダイスの座標
	float masuX = 3;
	float masuY = 3;
	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	Dice::Dice(const std::string& objectName, const int playerid, const int diceid)
		:
		MovableObject(
		DrawObjf(objectName)
		),
		playerID_(playerid),
		diceID_(diceid)
	{
		yy = 5.0f;
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


	float Dice::getDicePosX()
	{
		xx = ((masuX - 3) * 10);
		return xx;
	}
	float Dice::getDicePosY()
	{
		zz = ((masuY - 3) * 10);
		return zz;
	}

	//////////////////////
	/*float Set_Yaw()
	{
		Yaw += 10.f;
		return Yaw;
	}

	float Set_Pic()
	{
		Pit += 10.f;
		return Pit;
	}

	float Set_Roll()
	{
		Roll += 10.f;
		return Roll;
	}*/
	///////////////////////
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

	void Dice::setMasu(int x, int y)
	{
		masuX = x;
		masuY = y;
	}

	/////////////////////////////////////
	//俺ゾーン
	/////////////////////////////////////

	void calc()
	{



	}

	void Dice::render()
	{
		ci_ext::Vec3f angle(0, 0, 0);
		ci_ext::Vec3f scale(10.f, 10.f, 10.f);
		ci_ext::Vec3f pos(xx, yy, zz);
		meshManage->drawMesh(pos, "dice", angle, ARGB(255, 200, 200, 200), scale);

		//insertAsChild(new Monster("monster", pos, 0));
	}

	void Dice::update()
	{
		getDicePosY();
		getDicePosX();
		//if (gplib::input::CheckPush(gplib::input::KEY_UP))
		//{
		//	masuY -= 1;
		//	getDicePosY();
		//}
		//if (gplib::input::CheckPush(gplib::input::KEY_DOWN))
		//{
		//	masuY += 1;
		//	getDicePosY();
		//}
		//if (gplib::input::CheckPush(gplib::input::KEY_LEFT))
		//{
		//	masuX -= 1;
		//	getDicePosX();
		//}
		//if (gplib::input::CheckPush(gplib::input::KEY_RIGHT))
		//{
		//	masuX += 1;
		//	getDicePosX();
		//}
	}
}