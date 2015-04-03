#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/gplib.h"

namespace game
{

class CSceneStage : public ci_ext::Object
{
	//ƒƒ“ƒo•Ï”
private:


public:
	//ƒƒ“ƒoŠÖ”

  CSceneStage(const std::string& objectName);

  void init() override;
  void render() override;
  void update() override;
};

}