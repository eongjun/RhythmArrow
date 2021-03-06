// CEditResult.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_Team_Dlg01.h"
#include "CEditResult.h"
#include "afxdialogex.h"


// CEditResult 대화 상자

IMPLEMENT_DYNAMIC(CEditResult, CDialog)

CEditResult::CEditResult(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG6, pParent)
{

}

CEditResult::~CEditResult()
{
}

void CEditResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditResult, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CEditResult 메시지 처리기


BOOL CEditResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect desk_rect;
	GetDesktopWindow()->GetWindowRect(&desk_rect);
	this->MoveWindow(desk_rect.left + (desk_rect.Width() / 2) - 175, desk_rect.bottom - (desk_rect.Height() / 2) - 200, 400, 350);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEditResult::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CDC memdc;
	CDC main_dc;
	CBitmap main_bmp;

	memdc.CreateCompatibleDC(&main_dc);
	main_dc.CreateCompatibleDC(&dc);
	main_bmp.CreateCompatibleBitmap(&dc, m_client.Width(), m_client.Height());

	main_dc.SelectObject(&main_bmp);

	main_dc.PatBlt(0, 0, m_client.Width(), m_client.Height(), WHITENESS);

	CString cstr;
	main_dc.DrawTextW(_T("<< Result >>"), CRect(100, 50, 300, 100), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	cstr.Format(_T("%d"), r_perfect);
	main_dc.DrawTextW(_T("perfect: ") + cstr, CRect(100, 150, 300, 200), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	cstr.Format(_T("%d"), r_great);
	main_dc.DrawTextW(_T("great: ") + cstr, CRect(100, 200, 300, 250), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	cstr.Format(_T("%d"), r_miss);
	main_dc.DrawTextW(_T("miss: ") + cstr, CRect(100, 250, 300, 300), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	dc.BitBlt(0, 0, m_client.Width(), m_client.Height(), &main_dc, 0, 0, SRCCOPY);
}


void CEditResult::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	GetClientRect(m_client);
}
