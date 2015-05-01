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
		m_pos(pos),
		monster_num(monsternum),
		m_angle(angle)
	{
		count = 0;
		moveflag = true;
	}

	void Monster::render()
	{
		//m_angle = Vec3f(0.f, 0.f, 0.f);
		Vec3f scale(10.f, 10.f, 10.f);

		auto pos = m_pos.offset(0.f, OFFSETY, 0.f);

		switch (monster_num){
			//グー、火
		case 0:
			meshManage->drawMesh(pos, "tori", m_angle, ARGB(255, 200, 200, 200), scale);
			break;
			//チョキ、木
		case 1:
			meshManage->drawMesh(pos, "kinoko", m_angle, ARGB(255, 200, 200, 200), scale);
			break;
			//パー、水
		case 2:
			meshManage->drawMesh(pos, "kuzira", m_angle, ARGB(255, 200, 200, 200), scale);
			break;
		}
	}

	void Monster::update()
	{
		updownmove();

	}

	void Monster::monster_move(Vec3f p, Vec3f a){

			m_pos = p;
			m_angle = a;
	}

	void Monster::monster_move(Vec3f p){

		m_pos = p;

	}
	

	void Monster::updownmove(){
		count++;
		if (count > 60){
			if (moveflag == true){
				count = 0;
				moveflag = false;
			}
			else if (moveflag == false){
				count = 0;
				moveflag = true;
			}
		}

		Vec3f f(0.f, 0.03f, 0.f);
		if (moveflag == true){
			m_pos += f;
		}
		else if (moveflag == false){
			m_pos -= f;
		}
	}
}