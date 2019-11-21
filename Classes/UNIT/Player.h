#pragma once
#include "UNIT/Obj.h"

using key = cocos2d::EventKeyboard::KeyCode;

class Player : public Obj
{
public:
	static cocos2d::Sprite* createSprite();
	static Player* create();
	Player();
	~Player();
	void update(float delta);

	key getnowkey();			// 現在の入力したｷｰを返す
	INPUT_TIMING getTiming();	// 今の入力状態を返す
	void SetAct(ACT_ID id);
	ACT_ID GetAct();
	

private:
	bool init();				// 初期化
	_state *inputstate;			// 入力媒体	
	ActionMng * _actP;			// ｱｸｼｮﾝ登録ｸﾗｽのﾎﾟｲﾝﾀ
	INPUT_TIMING _timing;		// 現在の入力ﾀｲﾐﾝｸﾞ
	ACT_ID _actid;
};

