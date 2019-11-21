#include "cocos2d.h"
#include "CheckHitObj.h"
#include <UNIT/Player.h>

//“–‚½‚è”»’è
bool CheckHitObj::operator()(cocos2d::Sprite & sp, ActModule & module)
{
	auto dirctor = Director::getInstance();
	auto mapdata = (TMXTiledMap*)dirctor->getRunningScene()->getChildByName("LAYER")
		->getChildByName("BG_LAYER")->getChildByName("MAP");

	TMXLayer *collisionLayer = mapdata->getLayer("Layer1");

	auto chipsize = mapdata->getTileSize();

	auto pPos = ((Obj&)sp).getPosition();

	cocos2d::Vec2 colitionPos1;
	cocos2d::Vec2 colitionPos2;

	colitionPos1 = pPos + module.colPos[0];
	colitionPos2 = pPos + module.colPos[1];

	auto dis = dirctor->getWinSize().height;
	int selPosX;
	int selPosY;
	selPosX = colitionPos1.x / chipsize.width;
	selPosY = (dis - colitionPos1.y) / chipsize.height;

	int selPosX2;
	int selPosY2;
	selPosX2 = colitionPos2.x / chipsize.width;
	selPosY2 = (dis - colitionPos2.y) / chipsize.height;

	auto hp = collisionLayer->getTileGIDAt(Vec2(selPosX, selPosY));

	auto hp2 = collisionLayer->getTileGIDAt(Vec2(selPosX2, selPosY2));


	if (hp != 0 || hp2 != 0)
	{
		return false;
	}

	return true;
}
