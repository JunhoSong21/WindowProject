#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int arrVK[(int)KEY::LAST] = {
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	VK_MENU, //ALT,
	VK_CONTROL, //CTRL,
	VK_LSHIFT, //LSHIFT,
	VK_SPACE,
	VK_RETURN, //ENTER,
	VK_ESCAPE, //ESC
	VK_LBUTTON,
	VK_RBUTTON,
	// LAST,
};

CKeyMgr::CKeyMgr() 
{
}

CKeyMgr::~CKeyMgr() 
{
}

void CKeyMgr::Init() {
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		vecKey.push_back(KeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update() {
	HWND hWnd = GetFocus();

	if (nullptr != hWnd) {
		// 모든 키에 대해서
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			// 키가 눌렸다면
			if (GetAsyncKeyState(arrVK[i]) & 0x8000) {
				if (vecKey[i].prev) {
					vecKey[i].state = KEY_STATE::HOLD;
				}
				else {
					vecKey[i].state = KEY_STATE::TAP;
				}
				vecKey[i].prev = true;
			}
			else {
				if (vecKey[i].prev) {
					vecKey[i].state = KEY_STATE::AWAY;
				}
				else {
					vecKey[i].state = KEY_STATE::NONE;
				}
				vecKey[i].prev = false;
			}
		}
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(CCore::Instance()->GetMainHandle(), &ptPos);

		CurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	else {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			vecKey[i].prev = false;
			if (KEY_STATE::TAP == vecKey[i].state || KEY_STATE::HOLD == vecKey[i].state)
				vecKey[i].state = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == vecKey[i].state)
				vecKey[i].state = KEY_STATE::NONE;
		}
	}
}
