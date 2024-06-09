#pragma once

// 싱글톤 - 인스턴스가 단 하나만 생성되도록 보장하는 소프트웨어 패턴

// 코어(프레임 워크) 클래스 - 프로그램 구조이자 핵심 기능을 담고 있음.
// 무조건 하나여야 되는 애들을 싱글톤으로 만듦.
// Ex) 코어, 관리자(매니저)

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

// 객체를 하나만 만들기 위해서는?
// -> 생성자와 소멸자를 private 로 지정.
// -> 멤버 함수로만 만들고 지울 수 있다.
// -> 문제발생!! 객체를 만들 수가 없음.
// -> 객체가 없는데 멤버 함수와 멤버 변수에 접근이 가능한가?
// -> 불가. 누가 함수를 호출했는지 알 수 없음.
// -> 멤버 없이 호출할 수 있는 것 > static
// -> 정적 멤버 함수는 무조건 내부 정적 멤버로만 접근 가능.

// 정적 변수
// 1. 함수 안에 선언 -> .data / 해당 함수에서만 접근 가능
// 2. 파일 안에 선언 -> .data / 파일 안에서만 접근 가능.
// 3. 클래스 안에서 선언 -> .data / 무조건 클래스 외부에서 초기화 해야 함. (링크오류 발생)