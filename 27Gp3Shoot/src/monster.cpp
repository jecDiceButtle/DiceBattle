#include "monster.h"
#include "../../lib/gplib.h"

//tuika
#include "movableObject.h"

//3Dカメラ
extern Dx_Camera *dxCamera;
extern LPDIRECT3DDEVICE9 pD3DDevice;
//メッシュ全体管理クラス
extern DX3DMESHMANAGER *meshManage;
extern Dx_Camera *dxCamera;
//tuika


namespace game
{
	//tuika
	using namespace ci_ext;
	using namespace gplib;
	//tuika


	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//



	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//




	Monster::Monster(const std::string& objectName)
		:
		MovableObject(
		DrawObjf(objectName)
		)
	{

	}

	void Monster::render()
	{
		
	}

	void Monster::update()
	{

	}

}