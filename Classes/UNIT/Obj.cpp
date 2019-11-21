#include "Obj.h"

USING_NS_CC;

bool Obj::CheckHit(Node * sp, DIR dir)
{
	DIR nowDir = dir;
	auto dirctor = Director::getInstance();
	auto mapdata = (TMXTiledMap*)dirctor->getRunningScene()->getChildByName("LAYER")
		->getChildByName("BG_LAYER")->getChildByName("MAP");

	TMXLayer *collisionLayer = mapdata->getLayer("Layer1");

	auto chipsize = mapdata->getTileSize();

	auto pPos = sp->getPosition();

	switch (nowDir)
	{

		//offset(20,35);
		case DIR::RIGHT:
			Point1 = Vec2(pPos.x + offset.x, pPos.y + offset.y);
			Point2 = Vec2(pPos.x + offset.x, pPos.y - offset.y);
			break;
		case DIR::LEFT:
			Point1 = Vec2(pPos.x - offset.x, pPos.y + offset.y);
			Point2 = Vec2(pPos.x - offset.x, pPos.y - offset.y);
			break;
		case DIR::UP:
			Point1 = Vec2(pPos.x, pPos.y + offset.y + 5);
			Point2 = Vec2(pPos.x, pPos.y + offset.y + 5);
			break;
		case DIR::DOWN:
			Point1 = Vec2(pPos.x, pPos.y - offset.y - 30);
			Point2 = Vec2(pPos.x, pPos.y - offset.y - 30);
			break;
		case DIR::STOP:
			Point1 = Vec2(pPos.x, pPos.y - offset.y - 30);
			Point2 = Vec2(pPos.x, pPos.y - offset.y - 30);
			break;
	default:
		break;
	}

	auto dis = dirctor->getWinSize().height;
	int selPosX;
	int selPosY;
	selPosX = Point1.x / chipsize.width;
	selPosY = (dis - Point1.y) / chipsize.height;

	int selPosX2;
	int selPosY2;
	selPosX2 = Point2.x / chipsize.width;
	selPosY2 = (dis - Point2.y) / chipsize.height;

	auto hp = collisionLayer->getTileGIDAt(Vec2(selPosX, selPosY));

	auto hp2 = collisionLayer->getTileGIDAt(Vec2(selPosX2, selPosY2));

	
	if (hp != 0 || hp2 != 0)
	{
		return true;
	}
	//TRACE("pos.x = %f   pos.y = %f\n", pPos.x, pPos.y);
	//TRACE("Bpos.x = %f   Bpos.y = %f\n", Point2.x, Point2.y);
	return false;
}

void Obj::changeanim(Obj * sp, std::string st, DIR dir)
{
	if (animation == animcache->getAnimation(st))
	{
		return;
	}
	else
	{
		sp->stopAllActions();
		if (dir == DIR::LEFT)
		{
			auto flip = FlipX::create(true);
			this->runAction(flip);
		}
		if (dir == DIR::RIGHT)
		{
			auto flip = FlipX::create(false);
			this->runAction(flip);
		}
		animation = animcache->getAnimation(st);
	}

	sp->runAction(RepeatForever::create(Animate::create(animation)));
}
