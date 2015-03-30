#include "Collider.h"
#include "../../lib/gplib.h"
#include "movableObject.h"

#include "effect.h"

namespace game
{

	Collider::Collider(const std::string& objectName, const std::string& srcName, const std::string& destName)
  :
	Object(objectName),
  srcname_(srcName),
	destname_(destName)
{
}

void Collider::render()
{
}

void Collider::update()
{
  //指定した名前のオブジェクトを取得
  auto src = getObjectsFromRoot({ srcname_ });
  auto dest = getObjectsFromRoot({ destname_ });
  //判定チェック
  for (auto s : src)
  {
    for (auto d : dest)
    {
      s.lock()->collision(d);
      d.lock()->collision(s);
    }
  }
}

}