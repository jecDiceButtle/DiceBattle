#include "board.h"
#include "../../lib/gplib.h"

namespace game
{
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//

	const ci_ext::Vec3i Board::MAPSIZE = ci_ext::Vec3i(5,5,0);

	//**************************************************************************************//
	//�֐��L�q
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