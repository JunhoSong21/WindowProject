#pragma once

#include "CObject.h"

class CText :
	public CObject
{
private:
	Vec2 CenterPos; // �߾� ������
	Vec2 ScalePos; // ���ڿ��� �ʺ�� ����

public:
	CText();
	~CText();

	virtual void Update();
	virtual void Render(HDC hDC);

	CLONE(CText);
};

