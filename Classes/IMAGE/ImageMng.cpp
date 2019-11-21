#include "IMAGE/ImageMng.h"

std::unique_ptr<ImageMng, ImageMng::ImageMngDeleter> ImageMng::s_instance(new ImageMng());

USING_NS_CC;

ImageMng::ImageMng()
{

}

ImageMng::~ImageMng()
{

}

void ImageMng::setAnim(float delay, bool restore, std::vector<std::string> name, std::string animName)
{
	animcache = AnimationCache::getInstance();
	animation = Animation::create();

	for (auto str : name)
	{
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	std::string as = "-";
	std::string _name = "player";
	std::string name2 = "idle";
	
	//auto a = _name + as + name2 + as;
	///*auto
	//	a.push_back(i);*/

	//for (int i = 0; i < 10; i++)
	//{
	//	a.push_back(i);
	//	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(a));
	//}
	//アニメーションの間隔
	animation->setDelayPerUnit(delay);

	// アニメーション終了後に最初に戻すかどうか
	animation->setRestoreOriginalFrame(restore);

	animcache->addAnimation(animation, animName);

}

cocos2d::AnimationCache * ImageMng::getAnim()
{
	return animcache;
}

cocos2d::Animation * ImageMng::nowAnim()
{
	return animation;
}

