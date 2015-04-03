#pragma once
#include "../../lib/ci_ext/object.hpp"

namespace game
{

	class CSceneTitle : public ci_ext::Object
	{
		//*************************************************//
		//�@�萔
		//*************************************************//
	private:

		enum STATE {

			FADEIN,
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

		void Wait();

	public:

		CSceneTitle(const std::string& objectName);

		void init() override;
		void render() override;
		void update() override;

	};

}