#pragma once


// CTitle 대화 상자

class CTitle : public CDialog
{
	DECLARE_DYNAMIC(CTitle)

public:
	CTitle(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTitle();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString t_title;
};
