#pragma once

#include "LibMP3DLL.h"
#include "Mp3.h"
#include "Note_s.h"

#pragma comment(lib, "Strmiids.lib")

// CEditMode 대화 상자

class CEditMode : public CDialog
{
	DECLARE_DYNAMIC(CEditMode)

public:
	CEditMode(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CEditMode();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl m_slide; //스크롤 슬라이더
	CStatic m_control; //컨트롤러 화면
	CStatic m_screen; //스크롤 화면
	CSliderCtrl m_cur_pos; //커서 위치
	int pos_all; //아래 스크롤
	int pos_cur; //윗쪽 커서
	bool m_check;

	CLibMP3DLL m_mp3; //받아오려는 음악정보
	CString m_title; //음악경로
	CString m_all_time; //음악 시간
	int bmp_size; //비트맵 사이즈

	CRect size_1, size_2;
	CBitmap img_1, img_2;
	CDC memdc[2]; //그림 그리는데 쓰는 것들.

	CArray<Note_s, Note_s&> arrow; //화살표 정보 저장용 배열
	bool playing; //음악이 틀어져있는가?
	CButton b_select;
	CButton b_play;
	CButton b_pause;
	CButton b_save;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnStnClickedStatic1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int duration;
};
