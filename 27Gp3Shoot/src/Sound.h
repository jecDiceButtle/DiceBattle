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
		@brief							BGM�Đ�
		@return							�Ȃ�
		*/
		static void BgmPayer(const std::string& resname);
		/*
		@brief							SE�Đ�
		@return							�Ȃ�
		*/
		static void SePayer(const std::string& resname);

		/*
		@brief							BGM��~
										�P�P�̏��������͂Ȃ�
		@return							�Ȃ�
		*/
		static void BgmStop(const std::string& resname);
		/*
		@brief							SE��~
		�P�P�̏��������͂Ȃ�
		@return							�Ȃ�
		*/
		static void SeStop(const std::string& resname);

		public:
		/*
		@brief							�R���X�g���N�^
		@param[in]	objectName			�I�u�W�F�N�g��
		@return							�Ȃ�
		*/
		Sound(const std::string& objectName);

		void updata();
	};
}