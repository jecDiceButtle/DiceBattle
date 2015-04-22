#include "monster.h"
#include "../../lib/gplib.h"

//tuika
#include "movableObject.h"

//3Dカメラ
extern LPDIRECT3DDEVICE9 pD3DDevice;
//メッシュ全体管理クラス
extern std::shared_ptr<Dx_Camera> dxCamera;
extern std::shared_ptr<DX3DMESHMANAGER> meshManage;


namespace game
{
	//tuika
	using namespace ci_ext;
	using namespace gplib;
	//tuika


	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//

	const float Monster::OFFSETY = 5.f;


	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//




	Monster::Monster(const std::string& objectName, const Vec3f pos, const int monsternum, const Vec3f angle)
		:
		MovableObject(
		DrawObjf(objectName)
		),
		movepos(pos),
		monster_num(monsternum),
		moveangle(angle)
	{

	}

	void Monster::render()
	{
		//m_angle = Vec3f(0.f, 0.f, 0.f);
		Vec3f scale(10.f, 10.f, 10.f);

		auto pos = m_pos.offset(0.f, OFFSETY, 0.f);

		switch (monster_num){
		case 0:
			meshManage->drawMesh(pos, "kuzira", m_angle, ARGB(255, 200, 200, 200), scale);
			break;
		case 1:
			meshManage->drawMesh(pos, "kinoko", m_angle, ARGB(255, 200, 200, 200), scale);
			break;
		case 2:
			meshManage->drawMesh(pos, "tori", m_angle, ARGB(255, 200, 200, 200), scale);
			break;
		}
	}

	void Monster::update()
	{
		monster_move(movepos,moveangle);
	}

	void Monster::monster_move(Vec3f p,Vec3f a){
		m_pos = p;
		m_angle = a;
	}
}