#include "player.h"
#include "../../lib/gplib.h"
#include "stage.h"

namespace game
{
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//

	const int Player::HOGE = 100;

	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//

	Player::Player(const std::string& objectName)
		:
		Object(objectName)
	{

	}

	void Player::render()
	{
		
	}

	void Player::update()
	{
		if (gplib::input::CheckPush(gplib::input::KEY_BTN1))
		{
			auto stage = getObjectFromRoot("scene_stage");
			auto object = ci_ext::weak_to_shared<CSceneStage>(stage);

			object->NextPhase();
		}
	}

}