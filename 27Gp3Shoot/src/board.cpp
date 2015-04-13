#include "board.h"
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

	const ci_ext::Vec3i Board::MAPSIZE = ci_ext::Vec3i(5,5,0);

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	bool Board::isMovablePosition(const ci_ext::Vec3i &pos)
	{
		return (0 <= pos.x() && pos.x() <= MAPSIZE.x()
			&& (0 <= pos.y() && pos.y() <= MAPSIZE.y()));
	}



	Board::Board(const std::string& objectName)
		:
		MovableObject(
		DrawObjf(objectName)
		)
	{

	}

	void Board::render()
	{
		meshManage->drawMesh(DxVec3(0.f, 0.f, 0.f), "board", DxVec3(0.f, 0.f, 0.f), ARGB(255, 255, 255, 255), DxVec3(10.f, 10.f, 10.f));
	}

	void Board::update()
	{

	}

}