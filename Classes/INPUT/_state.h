#pragma once
#include "cocos2d.h"

enum class DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP,
	MAX
};

enum class KEY_STATE {
	NOW,
	OLD,
	INPUT,
	MAX
};

enum class INPUT_TYPE {
	KEY,
	TOUCH,
	MAX
};

enum class INPUT_TIMING {
	ON,
	ON_MOMENT,
	OFF,
	OFF_TIMING
};

using key = cocos2d::EventKeyboard::KeyCode;

using keymap = std::map<KEY_STATE, cocos2d::EventKeyboard::KeyCode>;

struct _state
{
public:
	//virtual void Update(cocos2d::Node *sp) = 0;
	// ·°ŠÖŒW‚Ìî•ñXV
	virtual void updata(cocos2d::Node *sp)
	{
		keymapstate[KEY_STATE::OLD] = keymapstate[KEY_STATE::NOW];
		keymapstate[KEY_STATE::NOW] = keymapstate[KEY_STATE::INPUT];

		if(keymapstate[KEY_STATE::OLD] == keymapstate[KEY_STATE::NOW])
		{
			timing = INPUT_TIMING::ON;
		}

		if (keymapstate[KEY_STATE::NOW] == key::KEY_NONE  && keymapstate[KEY_STATE::OLD] == key::KEY_NONE)
		{
			timing = INPUT_TIMING::OFF;
		}

		if (keymapstate[KEY_STATE::NOW] != key::KEY_NONE  && keymapstate[KEY_STATE::OLD] == key::KEY_NONE)
		{
			timing = INPUT_TIMING::ON_MOMENT;
			CCLOG("timing = %d", timing);
		}
		if (keymapstate[KEY_STATE::NOW] == key::KEY_NONE  && keymapstate[KEY_STATE::OLD] != key::KEY_NONE)
		{
			timing = INPUT_TIMING::OFF_TIMING;
			CCLOG("timing = %d", timing);
		}

		if (!jumpf)
		{
			if (keymapstate[KEY_STATE::NOW] == key::KEY_SPACE && timing == INPUT_TIMING::ON_MOMENT)
			{
				jumpf = true;
			}
		}

		if (jumpf)
		{
			jumpCnt++;
		}

		if (jumpCnt > 40)
		{
			jumpCnt = 0;
			jumpf = false;
		}

		nowkey = keymapstate[KEY_STATE::INPUT];
	};
	//virtual INPUT_TYPE getType() = 0;				// “ü—ÍÀ²Ìßæ“¾
	//virtual DIR GetDirData() = 0;					// Œ»İŒü‚¢‚Ä‚¢‚é•ûŒü‚ğæ“¾
	//virtual cocos2d::Vec2 GetMove() = 0;			// ˆÚ“®—Ê‚ğæ“¾
	bool GetJmpF() { return jumpf; };
	INPUT_TIMING retTiming() { return timing; };	// “ü—ÍÀ²Ğİ¸Ş
	key retnowkey() { return nowkey; };				// Œ»İ‰Ÿ‚µ‚Ä‚¢‚é·°
protected:
	bool HoldF = false;
	DIR data = DIR::STOP;
	cocos2d::Vec2 move;

	keymap keymapstate;
	INPUT_TIMING timing;
	key nowkey;

	bool jumpf = false;
	int jumpCnt = 0;
	//std::pair<KEY_STATE, int> teststate;

	//keystate p_keystate;
};
