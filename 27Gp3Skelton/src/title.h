#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "timer.h"

namespace game
{

class CSceneTitle : public ci_ext::Object
{
	//*************************************************//
	//　定数
	//*************************************************//
private:

	enum class STATE {

		FADEIN,
		IN_ANIM,
		WAIT,
		FADEOUT

	};


	//*************************************************//
	//　変数
	//*************************************************//

private:

	STATE					state_;				// シーン状態


	//*************************************************//
	//　関数
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