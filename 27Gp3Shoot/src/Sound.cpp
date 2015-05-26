#include "Sound.h"

namespace game
{
	
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//


	//sound�̃|�C���^�@BGM,SE�𗬂�����.h�ɒǉ�
	//std::weak_ptr<ci_ext::Object> p_sound;
	
	//p_sound = (insertAsChild(new Sound("sound")));�@init()�ɋL�q
	//ci_ext::weak_to_shared<Sound>(p_sound)->SoundPlayer("resname");�@�Đ����s�������ӏ��ɋL�q

	//**************************************************************************************//
	//�֐��L�q
	//**************************************************************************************//
	
	Sound::Sound(const std::string& objectName)
		:
		Object(objectName)		
	{
		gplib::bgm::DShow_LoadFile("dq", "msc/bgm/Title_bgm1.wma");
		gplib::bgm::DShow_LoadFile("kb", "msc/bgm/Title_bgm2.mp3");
	}
	/*BGM�����SE�Đ��֐�*/
	void Sound::SoundPlayer(const std::string& resname)
	{
		//A�p�^�[��
		//if (resname == "dq")gplib::bgm::DShow_Play("dq");
		//if (resname == "kb")gplib::bgm::DShow_Play("kb");

		//B�p�^�[���@���ꂾ���ł������Đ���
		//bgm�̍Đ�
		gplib::bgm::DShow_Play(resname);
		//SE�̍Đ�
		gplib::se::DSound_Play(resname);
	}


	/*BGM�����SE��~�֐�*/
	void Sound::SoundStop(const std::string& resname)
	{
		//A�p�^�[��
		//if (resname == "dq")gplib::bgm::DShow_Stop("dq");
		//if (resname == "kb")gplib::bgm::DShow_Stop("kb");
		//B�p�^�[��
		//BGM�̒�~
		gplib::bgm::DShow_Stop(resname);
		//SE�̒�~
		gplib::se::DSound_Stop(resname);
	}

}