#pragma once

// �̱��� - �ν��Ͻ��� �� �ϳ��� �����ǵ��� �����ϴ� ����Ʈ���� ����

// �ھ�(������ ��ũ) Ŭ���� - ���α׷� �������� �ٽ� ����� ��� ����.
// ������ �ϳ����� �Ǵ� �ֵ��� �̱������� ����.
// Ex) �ھ�, ������(�Ŵ���)

class CCore {
	SINGLE(CCore);
private:
	HWND	handle;
	POINT	ptResolution;
	HDC		hDC;
	HDC		mDC;
	HBITMAP hBit;


	HBRUSH arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN arrPen[(UINT)PEN_TYPE::END];

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

	void CreateBrushPen();

	HWND GetMainHandle() { return handle; }
	POINT GetResolution() { return ptResolution; }
	HDC GetMainDC() { return hDC; }

	HBRUSH GetBrush(BRUSH_TYPE _type) { return arrBrush[(UINT)_type]; }
	HPEN GetPen(PEN_TYPE _type) { return arrPen[(UINT)_type]; }
};

// ��ü�� �ϳ��� ����� ���ؼ���?
// -> �����ڿ� �Ҹ��ڸ� private �� ����.
// -> ��� �Լ��θ� ����� ���� �� �ִ�.
// -> �����߻�!! ��ü�� ���� ���� ����.
// -> ��ü�� ���µ� ��� �Լ��� ��� ������ ������ �����Ѱ�?
// -> �Ұ�. ���� �Լ��� ȣ���ߴ��� �� �� ����.
// -> ��� ���� ȣ���� �� �ִ� �� > static
// -> ���� ��� �Լ��� ������ ���� ���� ����θ� ���� ����.

// ���� ����
// 1. �Լ� �ȿ� ���� -> .data / �ش� �Լ������� ���� ����
// 2. ���� �ȿ� ���� -> .data / ���� �ȿ����� ���� ����.
// 3. Ŭ���� �ȿ��� ���� -> .data / ������ Ŭ���� �ܺο��� �ʱ�ȭ �ؾ� ��. (��ũ���� �߻�)