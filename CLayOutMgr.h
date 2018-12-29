#pragma once
class CLayoutMgr
{
public:
	CLayoutMgr();
	~CLayoutMgr();
	static VOID DrawBitmapTrans(IN OUT CDC* pDC, IN CBitmap* pcBitmap, IN int x, IN int y, IN COLORREF crMask);

};

