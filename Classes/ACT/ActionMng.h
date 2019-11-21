#pragma once
#include <cocos2d.h>
#include <IMAGE/ImageMng.h>
#include <INPUT/_state.h>
#include <UNIT/Obj.h>
#include <array>

enum class ACT_ID
{
	IDLE,
	RUN,
	JUMP,
	JUMPING,
	FALL,
	FALLING,
	MAX
};

struct ActModule;
class Action;

using Actmodulestate = std::function<bool(cocos2d::Sprite &, ActModule &)>;

//Ӽޭ�ٍ\����
struct ActModule
{
	std::list<ACT_ID> white;
	std::list<ACT_ID> black;
	std::list<Actmodulestate> ActList;
	std::string ActName;
	Actmodulestate RunAction;
	ACT_ID actID;
	std::array<cocos2d::Vec2, 2> colPos;
	cocos2d::Vec2 move;
	cocos2d::EventKeyboard::KeyCode Key;
	INPUT_TIMING timing;
};

class ActionMng
{
 public:
	 ActionMng(cocos2d::Sprite &sp);
	 void Updata();
	 void init();											// �������n
	 bool AddActionM(std::string actname, ActModule & act);	// ����݂̒ǉ�
	 void SetAct(ACT_ID id, bool flag = false);
	 ACT_ID GetID() { return nowAct; };
 private:
	 void AnimUpdata();										// ��Ұ��݂̍X�V
	 std::map<std::string, ActModule> _module;				// �ް��o�^�p
	 ACT_ID nowAct;
	 cocos2d::Sprite &_sprite;								// 

	 cocos2d::AnimationCache *_animcache;					// ��Ұ��ݓo�^�����
	 cocos2d::Animation		 *_animation;					// ���݂̱�Ұ���
};