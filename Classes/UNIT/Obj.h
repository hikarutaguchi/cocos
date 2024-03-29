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

	bool CheckHit(Node * sp, DIR dir);		// 当たり判定
	void changeanim(Obj* sp, std::string st, DIR dir);


	cocos2d::AnimationCache *animcache;			// ｱﾆﾒｰｼｮﾝ登録ｷｬｯｼｭ

	cocos2d::Animation *animation;				// 現在のｱﾆﾒｰｼｮﾝ

	cocos2d::Vec2 offset = { 20,35 };			// 判定のｵﾌｾｯﾄ
	cocos2d::Vec2 Point1;						// 判定の際の点
	cocos2d::Vec2 Point2;						// 判定の際の点
};

