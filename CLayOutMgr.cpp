#include "stdafx.h"
#include "CLayoutMgr.h"


CLayoutMgr::CLayoutMgr()
{
}


CLayoutMgr::~CLayoutMgr()
{
}

VOID CLayoutMgr::DrawBitmapTrans(IN OUT CDC* pDC, IN CBitmap* pcBitmap, IN int x, IN int y, IN COLORREF crMask)
{
	CBitmap     *pOldBitmapImage = NULL;
	CBitmap     *pOldBitmapTrans = NULL;
	COLORREF    clrOldBack = 0;
	COLORREF    clrOldText = 0;
	BITMAP      bm = { 0, };
	CDC         dcImage;
	CDC         dcTrans;
	CBitmap     bitmapTrans;

	if ((NULL == pcBitmap) || (NULL == pDC))
	{
		return;
	}

	pcBitmap->GetBitmap(&bm);
	dcImage.CreateCompatibleDC(pDC);
	pOldBitmapImage = dcImage.SelectObject(pcBitmap);
	clrOldBack = pDC->SetBkColor(RGB(255, 255, 255));
	clrOldText = pDC->SetTextColor(RGB(0, 0, 0));
	dcTrans.CreateCompatibleDC(pDC);
	bitmapTrans.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);
	dcImage.SetBkColor(crMask);
	dcTrans.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcTrans, 0, 0, SRCAND);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCINVERT);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(clrOldBack);
	pDC->SetTextColor(clrOldText);
	bitmapTrans.DeleteObject();
	dcTrans.DeleteDC();
	dcImage.SelectObject(pOldBitmapImage);
	dcImage.DeleteDC();
	dcTrans.Detach();
	dcImage.Detach();
}
