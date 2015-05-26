#pragma once
#include "../../lib/gplib.h"
#include "../../lib/ci_ext/object.hpp"

namespace game
{
	//////////////////////////////////////
	//BGM�Ɋւ���L�q
	//////////////////////////////////////
	class Sound : public ci_ext::Object
	{

		
	public:
		/*
		@brief							�R���X�g���N�^
		@param[in]	objectName			�I�u�W�F�N�g��
		@return							�Ȃ�
		*/
		Sound(const std::string& objectName);

		/*
		@brief							BGM�Đ�
		@return							�Ȃ�
		*/
		static void SoundPlayer(const std::string& resname);
		
				/*
		@brief							SE��~
		�P�P�̏��������͂Ȃ�
		@return							�Ȃ�
		*/
		static void SoundStop(const std::string& resname);
	};
}