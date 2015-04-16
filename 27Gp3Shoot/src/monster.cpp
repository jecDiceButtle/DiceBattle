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




	Monster::Monster(const std::string& objectName, const Vec3f pos, const int monsternum)
		:
		MovableObject(
		DrawObjf(objectName)
		),
		m_pos(pos),
		monster_num(monsternum)
	{

	}

	void Monster::render()
	{
		Vec3f angle(0, 0, 0);
		Vec3f scale(10.f, 10.f, 10.f);

		switch (monster_num){
		case 0:
			meshManage->drawMesh(m_pos, "kuzira", angle, ARGB(255, 200, 200, 200), scale);
			break;
		case 1:
			meshManage->drawMesh(m_pos, "kinoko", angle, ARGB(255, 200, 200, 200), scale);
			break;
		case 2:
			meshManage->drawMesh(m_pos, "tori", angle, ARGB(255, 200, 200, 200), scale);
			break;
		}
	}

	void Monster::update()
	{

	}

}