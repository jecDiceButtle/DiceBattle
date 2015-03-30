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
  //�w�肵�����O�̃I�u�W�F�N�g���擾
  auto src = getObjectsFromRoot({ srcname_ });
  auto dest = getObjectsFromRoot({ destname_ });
  //����`�F�b�N
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