#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "timer.h"

namespace game
{

class Stage : public ci_ext::Object
{
	//ƒƒ“ƒo•Ï”
private:

	int	point_;
	std::weak_ptr<ci_ext::Object> timer_;

public:
	//ƒƒ“ƒoŠÖ”

  Stage(const std::string& objectName);

  void AddPoint(int pt);

  void init() override;
  void render() override;
  void update() override;
};

}