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

	bool CheckHit(Node * sp, DIR dir);		// �����蔻��
	void changeanim(Obj* sp, std::string st, DIR dir);


	cocos2d::AnimationCache *animcache;			// ��Ұ��ݓo�^�����

	cocos2d::Animation *animation;				// ���݂̱�Ұ���

	cocos2d::Vec2 offset = { 20,35 };			// ����̵̾��
	cocos2d::Vec2 Point1;						// ����̍ۂ̓_
	cocos2d::Vec2 Point2;						// ����̍ۂ̓_
};

