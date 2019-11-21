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

	void setAnim(float delay, bool restore, std::vector<std::string> name , std::string animName);	// ��Ұ��݂�o�^

	cocos2d::AnimationCache* getAnim();			// ��Ұ��݂��擾
	cocos2d::Animation * nowAnim();				// ���݂̱�Ұ��݂��擾

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