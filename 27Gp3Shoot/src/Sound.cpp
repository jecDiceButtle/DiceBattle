#include "Sound.h"

namespace game
{
	
	//**************************************************************************************//
	//作成するプログラムで必要となる変数、定数定義
	//**************************************************************************************//


	//soundのポインタ　BGM,SEを流したい.hに追加
	//std::weak_ptr<ci_ext::Object> p_sound;
	
	//p_sound = (insertAsChild(new Sound("sound")));　init()に記述
	//ci_ext::weak_to_shared<Sound>(p_sound)->SoundPlayer("resname");　再生を行いたい箇所に記述

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
	/*BGMおよびSE再生関数*/
	void Sound::SoundPlayer(const std::string& resname)
	{
		//Aパターン
		//if (resname == "dq")gplib::bgm::DShow_Play("dq");
		//if (resname == "kb")gplib::bgm::DShow_Play("kb");

		//Bパターン　これだけでも複数再生可
		//bgmの再生
		gplib::bgm::DShow_Play(resname);
		//SEの再生
		gplib::se::DSound_Play(resname);
	}


	/*BGMおよびSE停止関数*/
	void Sound::SoundStop(const std::string& resname)
	{
		//Aパターン
		//if (resname == "dq")gplib::bgm::DShow_Stop("dq");
		//if (resname == "kb")gplib::bgm::DShow_Stop("kb");
		//Bパターン
		//BGMの停止
		gplib::bgm::DShow_Stop(resname);
		//SEの停止
		gplib::se::DSound_Stop(resname);
	}

}