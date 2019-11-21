#pragma once
#include <ACT/ActionMng.h>
#include "UNIT/Obj.h"

struct jump
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};

struct jumping
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};