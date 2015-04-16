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
		add_.set((((pos.x() - 3) * 10) - pos_.x()) / 45.f, 0.f, (((pos.y() - 3) * 10) -pos_.z()) / 45.f);
		


	}
	
	//===================================

	int Dice::getTopType(){
		return num[0];
	}


	float Dice::getDicePosX()
	{
		pos_.x(((masuX - 3) * 10));
		return pos_.x();
	}
	float Dice::getDicePosY()
	{
		pos_.z(((masuY - 3) * 10));
		return pos_.z();
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

	Dice::Dice(const std::string& objectName,const ci_ext::Vec3i &pos)
		:
		MovableObject(
		DrawObjf(objectName)
		),
		masuX(pos.x()),
		masuY(pos.y()),
		state_(IDOL),
		dispstate_(DICE)
	{
		getDicePosX();
		getDicePosY();
		pos_.y(5.f);

	}
	void Dice::render()
	{
		ci_ext::Vec3f angle(0, 0, 0);
		ci_ext::Vec3f scale(10.f, 10.f, 10.f);
		meshManage->drawMesh(pos_, "dice", angle, ARGB(255, 200, 200, 200), scale);

		//insertAsChild(new Monster("monster", pos, 0));
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