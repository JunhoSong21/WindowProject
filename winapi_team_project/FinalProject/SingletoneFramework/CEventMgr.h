#pragma once

struct tEvent {
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CEventMgr {
	SINGLE(CEventMgr)
private:
	vector<tEvent> vecEvent;

	vector<CObject*> vecDead;

	void Excute(const tEvent& _eve);

public:
	void Update();

	void AddEvent(const tEvent& _eve) { vecEvent.push_back(_eve); }
};