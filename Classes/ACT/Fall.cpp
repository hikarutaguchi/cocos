#include "Fall.h"
#include "UNIT/Player.h"

bool fall::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	sp.setPosition(sp.getPosition() + module.move);
	return true;
}

bool falling::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	sp.setPosition(sp.getPosition() + module.move);
	return true;
}
