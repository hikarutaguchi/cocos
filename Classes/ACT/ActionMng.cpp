//#pragma execution_character_set("utf-8")
#include <ACT/ActionMng.h>
#include <ACT/moveLR.h>
#include <ACT/jump.h>
#include <ACT/CheckHitObj.h>
#include <ACT/CheckHitKey.h>
#include <ACT/CheckList.h>
#include <ACT/Fall.h>
#include <UNIT/Player.h>

ActionMng::ActionMng(cocos2d::Sprite &sp) : _sprite(sp)
{
	
}

void ActionMng::Updata()
{
	auto checkLam = [&](auto data) {
		for (auto check : data.second.ActList)
		{
			if (!check(_sprite, data.second))
			{
				return false;
			}
		}
		return true;
	};

	bool chF = false;
	for (auto data : _module)
	{
		if (checkLam(data))
		{
			SetAct(_module[data.first].actID);
			_module[data.first].RunAction(_sprite, data.second);
			chF = true;
			//nowAct = data.second.actID;
			TRACE("現在のアニメーション = %d\n", nowAct);
		}
	}

	if (chF == false)
	{
		nowAct = ACT_ID::IDLE;
		TRACE("現在のアニメーション = %d\n", nowAct);
	}
	AnimUpdata();
}

//アニメーション追加
bool ActionMng::AddActionM(std::string actname, ActModule & act)
{
	if (actname == "右移動" || actname == "左移動")
	{
		_module.try_emplace(actname, std::move(act));
		_module[actname].ActList.emplace_back(CheckList());
		_module[actname].ActList.emplace_back(CheckHitKey());
		_module[actname].ActList.emplace_back(CheckHitObj());
		_module[actname].RunAction = moveLR();
	}

	if (actname == "ジャンプ")
	{
		_module.try_emplace(actname, std::move(act));
		_module[actname].ActList.emplace_back(CheckHitKey());
		_module[actname].ActList.emplace_back(CheckHitObj());
		//_module[actname].ActList.emplace_back(CheckList());
		_module[actname].RunAction = jumping();
	}

	//if (actname == "停止")
	//{
	//	_module.try_emplace(actname, std::move(act));
	//	//_module[actname].ActList.emplace_back(CheckHitKey());
	//	//_module[actname].ActList.emplace_back(CheckHitObj());
	//	//_module[actname].ActList.emplace_back(CheckList());
	//	_module[actname].RunAction = idle();
	//}

	/*if (actname == "落下")
	{
		_module.try_emplace(actname, std::move(act));
		_module[actname].ActList.emplace_back(CheckHitObj());
		_module[actname].RunAction = fall();
	}*/

	if (actname == "落下中")
	{
		_module.try_emplace(actname, std::move(act));
		//_module[actname].ActList.emplace_back(CheckHitKey());
		_module[actname].ActList.emplace_back(CheckHitObj());
		_module[actname].RunAction = falling();
	}

	return true;
}

void ActionMng::SetAct(ACT_ID id, bool flag)
{
	((Player&)_sprite).SetAct(id);
}

void ActionMng::AnimUpdata()
{
	for (auto data : _module)
	{
		if (((Player&)_sprite).getnowkey() == data.second.Key)
		{
			if (_animation == _animcache->getAnimation(data.second.ActName))
			{
				return;
			}
			else
			{
				((Obj&)_sprite).stopAllActions();
				if (((Player&)_sprite).getnowkey() == key::KEY_LEFT_ARROW)
				{
					auto flip = FlipX::create(true);
					((Player&)_sprite).runAction(flip);
				}
				if (((Player&)_sprite).getnowkey() == key::KEY_RIGHT_ARROW)
				{
					auto flip = FlipX::create(false);
					((Player&)_sprite).runAction(flip);
				}
				_animation = _animcache->getAnimation(data.second.ActName);
			}
		}
	}
	
	((Player&)_sprite).runAction(RepeatForever::create(Animate::create(_animation)));
}

//初期化
void ActionMng::init()
{
	_animcache = lpImageMng.getAnim();
	_animation = _animcache->getAnimation("idle");
}

/*int count = 0;
for (auto check : data.second.ActList)
{
if (check(_sprite, data.second))
{
count++;
}
}*/
/*if (data.second.ActList.size() == count)
{
	_module[data.first].RunAction(_sprite, data.second);
}*/
//count = 0;