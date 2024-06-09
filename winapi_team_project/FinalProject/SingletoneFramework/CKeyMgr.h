#pragma once

enum class KEY_STATE {
	NONE,
	TAP,
	HOLD,
	AWAY,
};

enum  class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LAST,
};

struct KeyInfo {
	KEY_STATE	state;
	bool		prev;
};

class CKeyMgr {
	SINGLE(CKeyMgr);
private:
	vector<KeyInfo> vecKey;

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY key) { return vecKey[(int)key].state; }
};