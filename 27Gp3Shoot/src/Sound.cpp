#include "Sound.h"

namespace game
{
	
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//


	//**************************************************************************************//
	//関数記述
	//**************************************************************************************//
	
	Sound::Sound(const std::string& objectName)
		:
		Object(objectName)		
	{
		gplib::bgm::DShow_LoadFile("dq", "msc/bgm/Title_bgm1.wma");
		gplib::bgm::DShow_LoadFile("kb", "msc/bgm/Title_bgm2.mp3");
	}

	void Sound::BgmPayer(const std::string& resname)
	{
		//Aパターン
		if (resname == "dq")gplib::bgm::DShow_Play("dq");
		if (resname == "kb")gplib::bgm::DShow_Play("kb");
		//Bパターン
		//gplib::bgm::DShow_Play(resname);//dq
		//gplib::bgm::DShow_Play(resname);//kb
	}

	void Sound::BgmStop(const std::string& resname)
	{
		//gplib::bgm::DShow_Stop("");
		if (resname == "dq")gplib::bgm::DShow_Stop("dq");
		if (resname == "kb")gplib::bgm::DShow_Stop("kb");
	}
	///////////////////////////////////////////////
	void Sound::SePayer(const std::string& resname)
	{
		//gplib::Se::DShow_Player("");
	}

	void Sound::SeStop(const std::string& resname)
	{
		//gplib::Se::DShow_Stop("");
	}

}