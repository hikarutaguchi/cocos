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

	key getnowkey();			// Œ»İ‚Ì“ü—Í‚µ‚½·°‚ğ•Ô‚·
	INPUT_TIMING getTiming();	// ¡‚Ì“ü—Íó‘Ô‚ğ•Ô‚·
	void SetAct();
	ACT_ID GetAct();
	

private:
	bool init();				// ‰Šú‰»
	_state *inputstate;			// “ü—Í”}‘Ì	
	ActionMng * _actP;			// ±¸¼®İ“o˜^¸×½‚ÌÎß²İÀ
	INPUT_TIMING _timing;		// Œ»İ‚Ì“ü—ÍÀ²Ğİ¸Ş
	ACT_ID _actid;
	efk::EffectEmitter* emitter;
	efk::Effect* effect;
	std::unique_ptr<efk::EffectManager> manager = nullptr;
	bool test = false;
};

