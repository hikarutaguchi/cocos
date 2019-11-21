#pragma once
#include <ACT/ActionMng.h>

struct moveLR
{
	bool operator()(cocos2d::Sprite & sp, ActModule & module);
};
