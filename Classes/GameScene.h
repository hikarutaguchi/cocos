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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "INPUT/_state.h"
#include "INPUT/InputKey.h"
#include "INPUT/InputPad.h"
#include "IMAGE/ImageMng.h"
#include "UNIT/Obj.h"
#include "UNIT/Player.h"
#include "Effekseer/Effekseer.h"
#include <ck/ck.h>
#include <ck/bank.h>
#include <ck/sound.h>
#include <ck/effect.h>
#include <ck/config.h>
//#include <ck/effectparam.h>
//#include <ck/effectbus.h>


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void update(float delta);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//efk::EffectManager*		manager = nullptr;

	//int count = 0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:

	CkBank* _bank = nullptr;
	CkSound* _soundEffect = nullptr;
	CkSound* _music = nullptr;

	std::unique_ptr<efk::EffectManager> manager = nullptr;

	//cocos2d::Sprite *face;
	cocos2d::Vec2 move;
	_state *inputstate;
	ImageMng *imagemng;

	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

};

#endif // __HELLOWORLD_SCENE_H__
