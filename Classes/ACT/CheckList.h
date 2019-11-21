#pragma once
#include <ACT/ActionMng.h>
#include "UNIT/Obj.h"

struct CheckList
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};