#pragma once
#include "_state.h"


struct InputKey : public _state
{
public:
	InputKey(cocos2d::Sprite * sp);
	~InputKey();
	void Update(cocos2d::Node *sp);
	INPUT_TYPE getType() { return INPUT_TYPE::KEY; };	// 入力ﾀｲﾌﾟ
	DIR GetDirData() { return data; };					// 方向を取得
	cocos2d::Vec2 GetMove() { return move; };			// 移動量
	bool GetHoldFlag() { return HoldF; };
	
private:
};
