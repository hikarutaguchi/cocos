#pragma once
#include "_state.h"


struct InputKey : public _state
{
public:
	InputKey(cocos2d::Sprite * sp);
	~InputKey();
	void Update(cocos2d::Node *sp);
	INPUT_TYPE getType() { return INPUT_TYPE::KEY; };	// ��������
	DIR GetDirData() { return data; };					// �������擾
	cocos2d::Vec2 GetMove() { return move; };			// �ړ���
	bool GetHoldFlag() { return HoldF; };
	
private:
};
