#include "ACT/moveLR.h"
#include "UNIT/Player.h"

bool moveLR::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	//TRACE("現在のアニメーション = %d\n", tesut);
	sp.setPosition(sp.getPosition() + module.move);
	return true;
}
