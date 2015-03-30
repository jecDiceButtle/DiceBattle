#include "background.h"
#include "../../lib/gplib.h"
#include "../../lib/ci_ext/math.hpp"
#include "movableObject.h"

#include "../../lib/ci_ext/color.hpp"

#include "effect.h"
#include "root.hpp"

namespace game
{

	IBackGround::IBackGround(const std::string& objectName,
		const std::string& resname)
		:
		Object(objectName),
		resname_(resname),
		color_(0, 255, 255, 255)
	{
		std::string filename;

		gplib::file::Sys_GetIniFileDataStr("BACKGROUND", resname_, filename, "res/data/data.ini");
		gplib::graph::Draw_LoadObject(resname_, filename);


		std::string keyname = resname_ + "_w";
		size_.x(gplib::file::Sys_GetIniFileDataInt("BACKGROUND", keyname, "res/data/data.ini"));

		keyname = resname_ + "_h";
		size_.y(gplib::file::Sys_GetIniFileDataInt("BACKGROUND", keyname, "res/data/data.ini"));
		
	}

	void IBackGround::init()
	{
		auto root = getRootObject();
		auto object = ci_ext::weak_to_shared<Root>(root);

		auto wndsize = object->getWindowSize();

		scale_.x(wndsize.right / (float)size_.x());
		scale_.y(wndsize.bottom / (float)size_.y());
	}

	void IBackGround::render()
	{
		gplib::graph::Draw_GraphicsLeftTopNC(
			0, 0, 1.f,
			resname_,
			0, 0, size_.x(), size_.y(),
			0, nullptr,
			scale_.x(),scale_.y(),
			color_.a(), color_.r(), color_.g(), color_.b());
	}

	void IBackGround::update()
	{
		color_.offseta(8);
	}

}