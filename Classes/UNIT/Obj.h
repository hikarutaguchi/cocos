#pragma once
#include "cocos2d.h"
#include <vector>
#include "_DebugConOut.h"
#include "INPUT/_state.h"
#include "INPUT/InputKey.h"
#include "INPUT/InputPad.h"
#include "ACT/ActionMng.h"

class Obj : public cocos2d::Sprite
{
public:
	virtual void update(float delta) = 0;


private:

protected:

	bool CheckHit(Node * sp, DIR dir);		// ìñÇΩÇËîªíË
	void changeanim(Obj* sp, std::string st, DIR dir);


	cocos2d::AnimationCache *animcache;			// ±∆“∞ºÆ›ìoò^∑¨Øº≠

	cocos2d::Animation *animation;				// åªç›ÇÃ±∆“∞ºÆ›

	cocos2d::Vec2 offset = { 20,35 };			// îªíËÇÃµÃæØƒ
	cocos2d::Vec2 Point1;						// îªíËÇÃç€ÇÃì_
	cocos2d::Vec2 Point2;						// îªíËÇÃç€ÇÃì_
};

