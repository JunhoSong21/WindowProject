#include "pch.h"
#include "SelectGDI.h"

#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _type)
	: hDC(_dc)
	, defaultBrush(nullptr)
	, defaultPen(nullptr)
{
	HPEN greenPen = CCore::Instance()->GetPen(_type);
	defaultPen = (HPEN)SelectObject(_dc, greenPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _type)
	: hDC(_dc)
	, defaultBrush(nullptr)
	, defaultPen(nullptr)
{
	HBRUSH hollowBrush = CCore::Instance()->GetBrush(_type);
	defaultBrush = (HBRUSH)SelectObject(_dc, hollowBrush);
}

SelectGDI::~SelectGDI() {
	SelectObject(hDC, defaultPen);
	SelectObject(hDC, defaultBrush);
}
