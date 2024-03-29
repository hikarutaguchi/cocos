#pragma once
#include "cocos2d.h"

#define lpImageMng ImageMng::GetInstance()

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		return *s_instance;
	}

	void setAnim(float delay, bool restore, std::vector<std::string> name , std::string animName);	// ｱﾆﾒｰｼｮﾝを登録

	cocos2d::AnimationCache* getAnim();			// ｱﾆﾒｰｼｮﾝを取得
	cocos2d::Animation * nowAnim();				// 現在のｱﾆﾒｰｼｮﾝを取得

private:

	ImageMng();
	~ImageMng();

	struct ImageMngDeleter
	{
		void operator()(ImageMng *img) const
		{
			delete img;
		}
	};

	cocos2d::AnimationCache *animcache;

	cocos2d::Animation *animation;

	static std::unique_ptr<ImageMng, ImageMngDeleter> s_instance;
	
};