#pragma once
#include "../../lib/ci_ext/object.hpp"

namespace game
{

	class CSceneTitle : public ci_ext::Object
	{
		//*************************************************//
		//　定数
		//*************************************************//
	private:

		enum STATE {

			FADEIN,
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

		void Wait();

	public:

		CSceneTitle(const std::string& objectName);

		void init() override;
		void render() override;
		void update() override;

	};

}