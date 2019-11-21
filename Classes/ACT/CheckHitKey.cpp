#include "CheckHitKey.h"
#include <UNIT/Player.h>

bool CheckHitKey::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	bool flag = true;
	if (((Player&)sp).getTiming() == module.timing && ((Player&)sp).getnowkey() == module.Key)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}
