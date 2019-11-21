#pragma once
#include <ACT/ActionMng.h>
#include "UNIT/Obj.h"

struct fall
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};

struct falling
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};