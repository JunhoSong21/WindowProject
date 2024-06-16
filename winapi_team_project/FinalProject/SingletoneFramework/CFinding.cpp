#include "pch.h"
#include "CFinding.h"

#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"
#include "CCamera.h"

UINT CFinding::nextID = 0;

CFinding::CFinding()
	:owner(nullptr)
	, iID(nextID++)
	, icol(0)
{
}

CFinding::CFinding(const CFinding& _origin)
	: owner(nullptr)
	, offsetPos(_origin.offsetPos)
	, finalPos(_origin.finalPos)
	, scale(_origin.scale)
	, iID(nextID++)
	, icol(0)
{
}

CFinding::~CFinding()
{
}

void CFinding::FinalUpdate() {
	Vec2 objectPos = owner->getPos();
	finalPos = objectPos + offsetPos;

	assert(0 <= icol);
}

void CFinding::Render(HDC _hDC) {
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (icol)
		ePen = PEN_TYPE::RED;

	SelectGDI p(_hDC, ePen);
	SelectGDI b(_hDC, BRUSH_TYPE::HOLLOW);

	Vec2 RenderPos = CCamera::Instance()->GetRenderPos(finalPos);

	Rectangle(_hDC
		, (int)(RenderPos.x - scale.x / 2.f)
		, (int)(RenderPos.y - scale.y / 2.f)
		, (int)(RenderPos.x + scale.x / 2.f)
		, (int)(RenderPos.y + scale.y / 2.f));
}

void CFinding::OnFinding(CFinding* _pOther) {
	owner->OnFinding(_pOther);
}

void CFinding::OnFindingEnter(CFinding* _pOther)
{
	++icol;
	owner->OnFindingEnter(_pOther);
}

void CFinding::OnFindingExit(CFinding* _pOther)
{
	--icol;
	owner->OnFindingExit(_pOther);
}
