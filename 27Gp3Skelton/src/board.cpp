#include "board.h"
#include "../../lib/gplib.h"

namespace game
{
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
		Object(objectName)
	{

	}

	void Board::render()
	{
		
	}

	void Board::update()
	{

	}

}