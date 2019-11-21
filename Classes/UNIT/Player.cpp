#include "cocos2d.h"
#include "Player.h"
#include "IMAGE/ImageMng.h"
#include <ACT/moveLR.h>

USING_NS_CC;

Sprite * Player::createSprite()
{
	return Player::create();
}

Player * Player::create()
{
	auto player = new Player();

	if (player->init())
	{
		player->autorelease();
		return player;
	}
	else
	{
		delete player;
		return nullptr;
	}
}

Player::Player() : _actP(new ActionMng(*this))
{

}

Player::~Player()
{
	delete inputstate;
	delete _actP;
}

bool Player::init()
{
	Sprite::init();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//プロパティリストをSpriteFrameCacheを使い読み込む

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/Sprites/player/player-idle/idle.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/Sprites/player/player-run/run.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/Sprites/player/player-jump/jump.plist");

	std::vector<std::string> nogi = {
		"player-idle-1.png",
		"player-idle-2.png",
		"player-idle-3.png",
		"player-idle-4.png",
	};

	std::vector<std::string> runrun = {
			"player-run-1.png",
			"player-run-2.png",
			"player-run-3.png",
			"player-run-4.png",
			"player-run-5.png",
			"player-run-6.png",
			"player-run-7.png",
			"player-run-8.png",
			"player-run-9.png",
			"player-run-10.png",
	};

	std::vector<std::string> jump = {
			"player-jump-1.png",
			"player-jump-2.png",
			"player-jump-3.png",
			"player-jump-4.png",
			"player-jump-5.png",
			"player-jump-6.png",
	};

	//読み込んだキャッシュから画像を取り出し、Spriteクラスとして利用する。
	this->Sprite::createWithSpriteFrameName("player-idle-1.png");

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	inputstate = new InputKey(this);
#else
	inputstate = new InputPad();
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_

	lpImageMng.setAnim(0.2f, true, nogi, "idle");
	lpImageMng.setAnim(0.08f, true, runrun, "run");
	lpImageMng.setAnim(0.12f, true, jump, "jump");

	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	_actP->init();

	animcache = lpImageMng.getAnim();

	auto repeat = RepeatForever::create(Animate::create(animcache->getAnimation("idle")));

	this->runAction(repeat);

	{
		//左移動
		ActModule data;
		data.black.emplace_back(ACT_ID::JUMP);
		data.black.emplace_back(ACT_ID::IDLE);
		data.move = { -3,0 };
		data.ActName = "run";
		data.timing = INPUT_TIMING::ON;
		data.actID = ACT_ID::RUN;
		data.colPos = {Vec2(-20,35),Vec2(-20,-35)};
		data.Key = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		_actP->AddActionM("左移動", data);
	}
	
	{
		//右移動
		ActModule data;
		data.black.emplace_back(ACT_ID::JUMP);
		data.black.emplace_back(ACT_ID::IDLE);
		data.ActName = "run";
		data.move = { 3,0 };
		data.timing = INPUT_TIMING::ON;
		data.actID = ACT_ID::RUN;
		data.colPos = { Vec2(20,35),Vec2(20,-35) };
		data.Key = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		_actP->AddActionM("右移動", data);
	}

	{
		//ジャンプ
		ActModule data;
		data.black.emplace_back(ACT_ID::RUN);
		data.timing = INPUT_TIMING::ON_MOMENT;
		data.ActName = "jump";
		data.move = { 0,25 };
		data.actID = ACT_ID::JUMP;
		data.colPos = { Vec2(20,40),Vec2(-20,40) };
		data.Key = cocos2d::EventKeyboard::KeyCode::KEY_SPACE;
		_actP->AddActionM("ジャンプ", data);
	}

	{
		//停止
		ActModule data;
		data.actID = ACT_ID::IDLE;
		data.ActName = "idle";
		data.timing = INPUT_TIMING::OFF;
		data.Key = cocos2d::EventKeyboard::KeyCode::KEY_NONE;
		_actP->AddActionM("停止", data);
	}

	{
		//落下
		ActModule data;
		data.actID = ACT_ID::FALL;
		data.ActName = "idle";
		//data.move = { 0,-1 };
		data.colPos = { Vec2(0,-65),Vec2(0,-65) };
		_actP->AddActionM("落下", data);
	}

	{
		//落下中
		ActModule data;
		data.actID = ACT_ID::FALLING;
		data.black.emplace_back(ACT_ID::RUN);
		data.ActName = "idle";
		data.move = { 0,-1 };
		data.colPos = { Vec2(0,-65),Vec2(0,-65) };
		data.Key = cocos2d::EventKeyboard::KeyCode::KEY_NONE;
		_actP->AddActionM("落下中", data);
	}

	this->scheduleUpdate();

	return true;
}

void Player::update(float delta)
{
	inputstate->updata();
	_actP->Updata();
}

key Player::getnowkey()
{
	return inputstate->retnowkey();
}

INPUT_TIMING Player::getTiming()
{
	return inputstate->retTiming();
}

void Player::SetAct(ACT_ID id)
{
	_actid = id;
}

ACT_ID Player::GetAct()
{
	return _actid;
}

/*std::string name;
	auto changename = [&name](int id) {
		if (id == static_cast<int>(DIR::UP))
		{
			name = "jump";
		}
		if (id == static_cast<int>(DIR::DOWN) || id == static_cast<int>(DIR::STOP))
		{
			name = "idle";
		}
		if (id == static_cast<int>(DIR::LEFT) || id == static_cast<int>(DIR::RIGHT))
		{
			name = "run";
		}
	};*/
	//TRACE("INPUT = %d\n", inputstate->GetHoldFlag());

	/*for (int i = 0; i < static_cast<int>(DIR::MAX); i++)
	{
		if (inputstate->GetDirData() == table[i])
		{
			changename(i);
			changeanim(this, name, inputstate->GetDirData());
		}
	}*/

