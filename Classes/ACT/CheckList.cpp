#include "CheckList.h"
#include "UNIT/Player.h"
bool CheckList::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	auto test = ((Player&)sp).GetAct();
	TRACE("現在のアニメーション = %d\n", test);
	for (auto data : module.black)
	{
		if (test == data)
		{
			return false;
		}
		/*if (data == module.actID)
		{
			return false;
		}*/
	}

	for (auto data : module.white)
	{
		if (data == module.actID)
		{
			return true;
		}
	}

	if (module.black.size() < 1)
	{
		return true;
	}

	return true;
}
