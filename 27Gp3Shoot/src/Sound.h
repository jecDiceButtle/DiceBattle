#pragma once
#include "../../lib/gplib.h"
#include "../../lib/ci_ext/object.hpp"

namespace game
{
	//////////////////////////////////////
	//BGMに関する記述
	//////////////////////////////////////
	class Sound : public ci_ext::Object
	{

		
	public:
		/*
		@brief							コンストラクタ
		@param[in]	objectName			オブジェクト名
		@return							なし
		*/
		Sound(const std::string& objectName);

		/*
		@brief							BGM再生
		@return							なし
		*/
		static void SoundPlayer(const std::string& resname);
		
				/*
		@brief							SE停止
		１つ１つの消す処理はない
		@return							なし
		*/
		static void SoundStop(const std::string& resname);
	};
}