#pragma once


// CEditResult 대화 상자

class CEditResult : public CDialog
{
	DECLARE_DYNAMIC(CEditResult)

public:
	CEditResult(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEditResult();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CRect m_client;
	int r_perfect;
	int r_great;
	int r_miss;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
