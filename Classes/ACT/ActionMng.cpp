//#pragma execution_character_set("utf-8")
#include <ACT/ActionMng.h>
#include <ACT/moveLR.h>
#include <ACT/jump.h>
#include <ACT/CheckHitObj.h>
#include <ACT/CheckHitKey.h>
#include <ACT/CheckList.h>
#include <ACT/Fall.h>
#include <UNIT/Player.h>
#include <Effekseer/Effekseer.h>

ActionMng::ActionMng(cocos2d::Sprite &sp) : _sprite(sp)
{
	
}

void ActionMng::Updata()
{
	auto checkLam = [&](std::pair<std::string, ActModule> data) {
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
			//SetAct(_module[data.first].actID);
			_module[data.first].RunAction(_sprite, data.second);
			chF = true;
			nowAct = data.second.actID;
			//TRACE("現在のアニメーション = %d\n", nowAct);
		}
	}

	if (((Player&)_sprite).getjumpf())
	{
		nowAct = ACT_ID::JUMPING;
	}
	if (nowAct == ACT_ID::JUMPING)
	{
		if (!((Player&)_sprite).getjumpf())
		{
			nowAct = ACT_ID::IDLE;
		}
	}

	if (chF == false)
	{
		nowAct = ACT_ID::IDLE;
		//TRACE("現在のアニメーション = %d\n", nowAct);
	}
	//TRACE("現在のﾀｲﾐﾝｸﾞ = %d\n", ((Player&)_sprite).getTiming());
	AnimUpdata();
}

//アニメーション追加
bool ActionMng::AddActionM(std::string actname, ActModule & act)
{
	if (actname == "右移動" || actname == "左移動")
	{
		act.ActList.emplace_back(CheckList());
		act.ActList.emplace_back(CheckHitKey());
		act.ActList.emplace_back(CheckHitObj());
		act.RunAction = moveLR();
	}

	if (actname == "ジャンプ")
	{
		act.ActList.emplace_back(CheckHitKey());
		act.ActList.emplace_back(CheckHitObj());
		//_module[actname].ActList.emplace_back(CheckList());
		act.RunAction = jump();
	}

	if (actname == "ジャンプ中")
	{
		act.ActList.emplace_back(CheckList());
		act.ActList.emplace_back(CheckHitObj());
		act.RunAction = jumping();
	}

	/*if (actname == "落下")
	{
		_module.try_emplace(actname, std::move(act));
		_module[actname].ActList.emplace_back(CheckHitObj());
		_module[actname].RunAction = fall();
	}*/

	if (actname == "落下中")
	{
		//_module[actname].ActList.emplace_back(CheckHitKey());
		act.ActList.emplace_back(CheckList());
		act.ActList.emplace_back(CheckHitObj());
		act.RunAction = falling();
	}

	if (actname == "停止")
	{
		//_module[actname].ActList.emplace_back(CheckHitKey());
		//_module[actname].ActList.emplace_back(CheckHitObj());
		act.ActList.emplace_back(CheckList());
		//_module[actname].RunAction = idle();
	}

	if (_module.find(actname) == _module.end())
	{
		_module.emplace(actname,std::move(act));
	}

	return true;
}

void ActionMng::SetAct(ACT_ID id, bool flag)
{
	//((Player&)_sprite).SetAct(id);
}

void ActionMng::AnimUpdata()
{
	for (auto data : _module)
	{
		if (((Player&)_sprite).GetAct() != ACT_ID::JUMPING)
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
						//TRACE("現在のｷｰ = %d\n", ((Player&)_sprite).getnowkey());
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
	}

	if (((Player&)_sprite).GetAct() == ACT_ID::JUMPING)
	{
		if (_animation == _animcache->getAnimation("jump"))
		{
			return;
		}
		else
		{
			((Obj&)_sprite).stopAllActions();
			_animation = _animcache->getAnimation("jump");
		}
	}
	((Player&)_sprite).runAction(RepeatForever::create(Animate::create(_animation)));
}

//初期化
void ActionMng::init()
{
	_animcache = lpImageMng.getAnim();
	_animation = _animcache->getAnimation("idle");
	nowAct = ACT_ID::IDLE;
}