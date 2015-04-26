#include "dice.h"
#include "../../lib/gplib.h"
//tuika
#include "monster.h"


#include "movableObject.h"

//3Dカメラ
extern LPDIRECT3DDEVICE9 pD3DDevice;
//メッシュ全体管理クラス
extern std::shared_ptr<Dx_Camera> dxCamera;
extern std::shared_ptr<DX3DMESHMANAGER> meshManage;




namespace game
{
	using namespace ci_ext;
	using namespace gplib;


	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//

	const Dice::TYPE Dice::ATKTYPE[6] =
	{
		TYPE::GU, TYPE::CH, TYPE::PA, TYPE::PA, TYPE::CH, TYPE::GU,
	};


	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	//===================================
	//	アクセサ
	//===================================
	bool Dice::isIdoling()
	{
		return state_ == IDOL;
	}

	bool Dice::isDying()
	{
		return state_ == DEAD;
	}
	
	bool Dice::isMoving()
	{
		return state_ == MOVE;
	}

	void Dice::destroy()
	{
		state_ = DEAD;
	}
	int Dice::getAtkSpecies()
	{
		return atkType[0];
	}
	int Dice::getDefSpecies()
	{
		return defType_;
	}

	//===================================

	void Dice::Move(const Vec3i& dir,const Vec3i& pos)
	{
		state_ = MOVE;

		if (dir.x() < 0) dir_ = LEFT;
		if (dir.x() > 0) dir_ = RIGHT;
		if (dir.y() < 0) dir_ = FOWARD;
		if (dir.y() > 0) dir_ = BACK;


		setMasu(masuX + dir.x(), masuY + dir.y());

		//とりあえず45フレームで移動しきる
		count_ = 45;
		add_.set((((pos.x() - 2) * 10) - pos_.x()) / 45.f, 0.f, (((pos.y() - 2) * 10) -pos_.z()) / 45.f);
		
	}
	

	float Dice::getDicePosX()
	{
		pos_.x(((masuX - 2) * 10));
		return pos_.x();
	}
	float Dice::getDicePosY()
	{
		pos_.z(((masuY - 2) * 10));
		return pos_.z();
	}
	void Dice::swap(DIRECT dir){

		TYPE Numkeep = atkType[0];

		if (dir == LEFT){
			atkType[0] = atkType[2];
			atkType[2] = atkType[5];
			atkType[5] = atkType[3];
			atkType[3] = Numkeep;
		}
		if (dir == RIGHT){
			atkType[0] = atkType[3];
			atkType[3] = atkType[5];
			atkType[5] = atkType[2];
			atkType[2] = Numkeep;
		}
		if (dir == FOWARD){
			atkType[0] = atkType[1];
			atkType[1] = atkType[5];
			atkType[5] = atkType[4];
			atkType[4] = Numkeep;
		}
		if (dir == BACK){
			atkType[0] = atkType[4];
			atkType[4] = atkType[5];
			atkType[5] = atkType[1];
			atkType[1] = Numkeep;
		}
	}

	void Dice::setMasu(int x, int y)
	{
		masuX = x;
		masuY = y;
	}


	void Dice::Moving()
	{
		pos_.offset(add_);

		if (--count_ < 0)
		{
			getDicePosX();
			getDicePosY();

			state_ = IDOL;
		}

	}
	void Dice::Idol()
	{

	}
	void Dice::Attack()
	{

	}

	//**************************************************************************************//
	//デフォルト関数
	//**************************************************************************************//

	Dice::Dice(const std::string& objectName,const int type,const ci_ext::Vec3i &pos)
		:
		MovableObject(
		DrawObjf(objectName)
		),
		masuX(pos.x()),
		masuY(pos.y()),
		state_(IDOL),
		dispstate_(DICE),
		defType_((TYPE)type)
	{
		getDicePosX();
		getDicePosY();
		pos_.y(5.f);
		
		for (int i = 0; i < 6;i++)
		{
			atkType[i] = ATKTYPE[i];
		}

	}

	void Dice::init(){
		p_mons=insertAsChild(new Monster("monster", pos_, (int)defType_,Vec3f(0.f,0.f,0.f)));
	}

	void Dice::render()
	{
		if (state_ != STATE::DEAD)
		{
			ci_ext::Vec3f angle(0, 0, 0);
			ci_ext::Vec3f scale(10.f, 10.f, 10.f);
			meshManage->drawMesh(pos_, "dice", angle, ARGB(255, 200, 200, 200), scale);

			//追加
			auto monsobj = ci_ext::weak_to_shared<Monster>(p_mons);
			monsobj->monster_move(pos_, angle);

		}

		
	}

	void Dice::update()
	{
		/*getDicePosY();
		getDicePosX();*/

		switch (state_)
		{
		case game::Dice::DEAD:
			
			break;
		case game::Dice::IDOL:
			Idol();
			break;

		case game::Dice::MOVE:
			Moving();
			break;

		case game::Dice::ATTACK:
			Attack();
			break;
		}

	}
}