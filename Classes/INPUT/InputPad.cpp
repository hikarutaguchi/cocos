#include <INPUT/InputPad.h>

//InputPad::InputPad(cocos2d::Sprite * sp)
//{
//}

void InputPad::updata(cocos2d::Node * sp)
{
	keymapstate[KEY_STATE::OLD] = keymapstate[KEY_STATE::NOW];
	keymapstate[KEY_STATE::NOW] = keymapstate[KEY_STATE::INPUT];

	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(InputPad::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(InputPad::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(InputPad::onTouchMoved, this);

	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, sp);

	//sp->setPosition(sp->getPositionX() + move.x, sp->getPositionY() + move.y);
	if (keymapstate[KEY_STATE::OLD] == key::KEY_NONE)
	{
		timing = INPUT_TIMING::OFF;
	}

	if (!jumpf)
	{
		if (keymapstate[KEY_STATE::NOW] == key::KEY_SPACE && timing == INPUT_TIMING::ON)
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
	//CCLOG("timing = %d", timing);
}

bool InputPad::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	timing = INPUT_TIMING::ON_MOMENT;
	auto tPos = touch->getLocation();
	m_startPos = { tPos.x,tPos.y };
	//CCLOG("timing = %d", timing);
	return true;
}

void InputPad::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	timing = INPUT_TIMING::ON;
	auto tPos = touch->getLocation();
	auto angle = atan2(tPos.y - m_startPos.y, tPos.x - m_startPos.x);
	move.x = cos(angle) * 2;
	move.y = sin(angle) * 2;
	if (move.x > 0)
	{
		keymapstate[KEY_STATE::INPUT] = key::KEY_RIGHT_ARROW;
	}
	else if(move.x < 0)
	{
		//timing = INPUT_TIMING::ON;
		keymapstate[KEY_STATE::INPUT] = key::KEY_LEFT_ARROW;
	}

	if (move.y > 0)
	{
		keymapstate[KEY_STATE::INPUT] = key::KEY_SPACE;
	}
}

void InputPad::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	keymapstate[KEY_STATE::INPUT] = key::KEY_NONE;
	timing = INPUT_TIMING::OFF_TIMING;
	move = { 0,0 };
	//CCLOG("timing = %d", timing);
	//data = DIR::STOP;
}
