#pragma once
#include "_state.h"


struct InputKey : public _state
{
public:
	InputKey(cocos2d::Sprite * sp);
	~InputKey();
	void Update(cocos2d::Node *sp);
	INPUT_TYPE getType() { return INPUT_TYPE::KEY; };	// “ü—ÍÀ²Ìß
	DIR GetDirData() { return data; };					// •ûŒü‚ðŽæ“¾
	cocos2d::Vec2 GetMove() { return move; };			// ˆÚ“®—Ê
	bool GetHoldFlag() { return HoldF; };
	
private:
};
