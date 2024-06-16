#pragma once

class SelectGDI {
private:
	HDC		hDC;
	HPEN	defaultPen;
	HBRUSH	defaultBrush;

public:
	SelectGDI(HDC _dc, PEN_TYPE _type);
	SelectGDI(HDC _dc, BRUSH_TYPE _type);
	~SelectGDI();
};