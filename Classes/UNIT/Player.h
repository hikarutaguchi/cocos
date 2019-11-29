#pragma once
#include "UNIT/Obj.h"
#include <Effekseer/Effekseer.h>

using key = cocos2d::EventKeyboard::KeyCode;

class Player : public Obj
{
public:
	static cocos2d::Sprite* createSprite();
	static Player* create();
	Player();
	~Player();
	void update(float delta);

	key getnowkey();			// ���݂̓��͂�������Ԃ�
	INPUT_TIMING getTiming();	// ���̓��͏�Ԃ�Ԃ�
	void SetAct();
	ACT_ID GetAct();
	

private:
	bool init();				// ������
	_state *inputstate;			// ���͔}��	
	ActionMng * _actP;			// ����ݓo�^�׽���߲��
	INPUT_TIMING _timing;		// ���݂̓������ݸ�
	ACT_ID _actid;
	efk::EffectEmitter* emitter;
	efk::Effect* effect;
	std::unique_ptr<efk::EffectManager> manager = nullptr;
	bool test = false;
};

