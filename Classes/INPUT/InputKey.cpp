#include <INPUT/InputKey.h>
USING_NS_CC;

InputKey::InputKey(cocos2d::Node * sp)
{
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		keymapstate[KEY_STATE::INPUT] = keyCode;
		return true;
	};

	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		keymapstate[KEY_STATE::INPUT] = key::KEY_NONE;
		return true;
	};
	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}

InputKey::~InputKey()
{
}

void InputKey::Update(cocos2d::Node * sp)
{
	
}
