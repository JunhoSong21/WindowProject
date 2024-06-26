#pragma once
#include "pch.h"

#define SINGLE(type) public:\
		static type* Instance()\
		{\
		static type mgr;\
		return &mgr;\
		}\
		private:\
			type();\
			~type();
#define fDT CTimeMgr::Instance()->getfDT()
#define DT CTimeMgr::Instance()->getDT()

#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key, state)CKeyMgr::Instance()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY) 
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP) 
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::Instance()->GetMousePos()

#define PI 3.1415926535f

enum class GROUP_TYPE {
	MAP,
	FURNITURE,
	PLAYER,
	MONSTER,
	ITEM,
	SCORE,
	PROJ_PLAYER,
	PROJ_MONSTER, // PROJECTILE

	END = 10,
};

enum class SCENE_TYPE {
	START,
	STAGE_010,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	SCORE,

	END,
};

enum class BRUSH_TYPE {
	HOLLOW,
	BLACK,
	WHITE,

	END,
};

enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	WHITE,

	END,
};

enum class EVENT_TYPE {
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};