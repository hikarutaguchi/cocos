#include <INPUT/InputPad.h>

void InputPad::Update(cocos2d::Node * sp)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(InputPad::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(InputPad::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(InputPad::onTouchMoved, this);


	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, sp);

	sp->setPosition(sp->getPositionX() + move.x, sp->getPositionY() + move.y);

}

bool InputPad::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto tPos = touch->getLocation();
	m_startPos = { tPos.x,tPos.y };
	return true;
}

void InputPad::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto tPos = touch->getLocation();

	auto angle = atan2(tPos.y - m_startPos.y, tPos.x - m_startPos.x);

	move.x = cos(angle) * 2;
	move.y = sin(angle) * 2;
	/*if (move.x > 0)
	{
		data = DIR::RIGHT;
	}
	else if(move.x < 0)
	{
		data = DIR::LEFT;
	}*/
}

void InputPad::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	move = { 0,0 };
	//data = DIR::STOP;
}
