/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "EFFECT/EffectMng.h"


USING_NS_CC;

enum class LAYER {
	BG = 0,
	CH = 10,
	FR = 20
};

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool {
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::getInstance()->end();
		}
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // add a label shows "Hello World"
    // create and initialize a label

	TMXTiledMap *map = TMXTiledMap::create("unti.tmx");

	//auto rsize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	//manager = efk::EffectManager::create(rsize);

	//manager.reset(efk::EffectManager::create(Director::getInstance()->getOpenGLView()->getDesignResolutionSize()));

	//auto effect = efk::Effect::create("Laser01.efk",5.0f);
	//auto emitter = efk::EffectEmitter::create(manager.get());
	//emitter->setEffect(effect);
	//emitter->setPlayOnEnter(true);

	//emitter->setRotation3D(cocos2d::Vec3(0, 90, 0));
	//emitter->setPosition(Vec2(320, 150));

	//emitter->setScale(10);



	map->setName("MAP");

	map->setPosition(0, 0);

	auto Layer	 = Layer::create();
	Layer->setName("LAYER");
	auto bgLayer = Layer::create();
	bgLayer->setName("BG_LAYER");
	auto ChLayer = Layer::create();
	ChLayer->setName("CH_LAYER");
	auto FrLayer = Layer::create();
	FrLayer->setName("FR_LAYER");

	this->addChild(Layer,0);

	Layer->addChild(bgLayer, static_cast<int>(LAYER::BG));
	Layer->addChild(ChLayer, static_cast<int>(LAYER::CH));
	Layer->addChild(FrLayer, static_cast<int>(LAYER::FR));

	auto bgImage  = Sprite::create("image/Environment/background.png");
	auto bgImage2 = Sprite::create("image/Environment/background.png");
	auto MdImage  = Sprite::create("image/Environment/middleground.png");
	auto MdImage2 = Sprite::create("image/Environment/middleground.png");
	auto FrImage  = Sprite::create("image/Environment/middleground-no-fungus.png");

	bgImage->setPosition(Point(visibleSize.width / 2 - 150, visibleSize.height / 2 - 25));
	bgImage2->setPosition(Point((visibleSize.width + 55), visibleSize.height / 2 - 25));
	MdImage->setPosition(Point(visibleSize.width / 2 - 150, visibleSize.height / 2 - 25));
	MdImage2->setPosition(Point((visibleSize.width + 100), visibleSize.height / 2 - 25));
	

	bgLayer->addChild(bgImage, 0);
	bgLayer->addChild(bgImage2, 0);
	bgLayer->addChild(MdImage, 0);
	bgLayer->addChild(MdImage2, 0);
	
	bgLayer->addChild(map,1);

	lpEffectMng.SetEffect("test", "Laser01.efk");

	ChLayer->addChild(lpEffectMng.PlayEffect("test"),10);

	//ChLayer->addChild(emitter, 10);

	auto player = Player::createSprite();
	player->setName("player");
	ChLayer->addChild(player);

	/* 再生 */
//#if CK_PLATFORM_ANDROID
//	// Androidでの初期化はAppActivity.javaにて行っている
//#else
//	CkConfig config;
//#endif
//	CkInit(&config);
//	//Bank sounds ファイルの再生
//	//CkBank* bank = CkBank::newBank("dsptouch.ckb", kCkPathType_FileSystem);
//	_bank = CkBank::newBank("dsptouch.ckb", kCkPathType_FileSystem);
////	
//	_soundEffect = CkSound::newBankSound(_bank,1);
//	_soundEffect = CkSound::newBankSound(_bank, "hiphoppiano");    // 別関数にてckbxで設定したindex番号でも呼び出し可能
//	_soundEffect->play();



	//Stream sounds ファイルの再生
	//_music = CkSound::newStreamSound("bgm_stage1.cks");
	//_music->setLoopCount(-1);
	//_music->play();

	this->scheduleUpdate();

    return true;
}

void GameScene::update(float delta)
{
	lpEffectMng.Updata();
	//(*manager).update();
	//CkUpdate();    // Stream sounds再生を行うのに必須関数
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void GameScene::visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags)
{
	//manager->begin(renderer, _globalZOrder);
	cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
	//manager->end(renderer, _globalZOrder);
}
