#pragma once

// CMyDlg 대화 상자
#include "vector"
#include "ArrowInfo.h"
#include "mmsystem.h"
#include "MG_1.h"
#include "MG_2.h"
#include "MG_3.h"

#pragma comment(lib, "winmm.lib")

class CMyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CRect m_client;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int up_effect;
	int down_effect;
	int left_effect;
	int right_effect;
	int p_time;
	int arrow_start;
	int arrow_end;
	int arrow_num;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	std::vector<ArrowInfo> arrow;
	CList<int,int&> mini_pos;

	MG_1 game_1;
	MG_2 game_2;
	MG_3 game_3;

	int game_series;


	CString bgm;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static void CALLBACK RecvChecker(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK AContinue(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK ArrowUp(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK ArrowLeft(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK ArrowRight(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK ArrowDown(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK Miss(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK Great(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK Perfect(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	MMRESULT m_idEvent;
	MMRESULT aup;
	MMRESULT aleft;
	MMRESULT aright;
	MMRESULT adown;
	MMRESULT amiss;
	MMRESULT agreat;
	MMRESULT aperfect;
	MMRESULT acontinue;
	virtual void OnCancel();
	int total_time;
	int miss;
	int perfect;
	int great;
	int combo;
	int IsMiss;
	int IsGreat;
	int IsPerfect;
	int long_down;
	int LongNum;
	bool twice;
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	int IsAup;
	int IsAleft;
	int IsAright;
	int IsAdown;
	int IsC;
};
