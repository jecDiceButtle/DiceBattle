#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "timer.h"

namespace game
{

class CSceneTitle : public ci_ext::Object
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:

	enum class STATE {

		FADEIN,
		IN_ANIM,
		WAIT,
		FADEOUT

	};


	//*************************************************//
	//�@�ϐ�
	//*************************************************//

private:

	STATE					state_;				// �V�[�����


	//*************************************************//
	//�@�֐�
	//*************************************************//

private:

	void InAnim();
	void Wait();

public:

	CSceneTitle(const std::string& objectName);

	void init() override;
	void render() override;
	void update() override;
};

}