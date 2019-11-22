#include "jump.h"
#include "UNIT/Player.h"

bool jump::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	sp.setPosition(sp.getPosition() + module.move);
	return true;
}

bool jumping::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	sp.setPosition(sp.getPosition() + module.move);
	return false;
}
