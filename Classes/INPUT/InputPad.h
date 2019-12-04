#pragma once
#include "_state.h"


struct InputPad : public _state
{
public:
	//InputPad(cocos2d::Sprite * sp);
	void updata(cocos2d::Node *sp);
	//INPUT_TYPE getType() { return INPUT_TYPE::TOUCH; };		// 入力ﾀｲﾌﾟ
	//DIR GetDirData() { return data; };						// 方向を取得
	//cocos2d::Vec2 GetMove() { return move; };				// 移動量
	//bool GetHoldFlag() { return HoldF; };
private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);	// ﾀｯﾁ開始
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);	// ﾀｯﾁ終了
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);	// 長押し

	cocos2d::Vec2 m_startPos;
};
