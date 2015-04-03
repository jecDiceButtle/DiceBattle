#include "player.h"
#include "../../lib/gplib.h"
#include "stage.h"

namespace game
{
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//

	const int Player::HOGE = 100;

	//**************************************************************************************//
	//�֐��L�q
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