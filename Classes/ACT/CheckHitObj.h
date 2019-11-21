#pragma once
#include <ACT/ActionMng.h>
#include "UNIT/Obj.h"

USING_NS_CC;

struct CheckHitObj
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};
