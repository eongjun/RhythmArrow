#pragma once


// EditPlay 대화 상자
#include "vector"
#include "ArrowInfo.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

class EditPlay : public CDialog
{
	DECLARE_DYNAMIC(EditPlay)

public:
	EditPlay(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~EditPlay();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	bool close_check;
	CRect m_client;
	int up_effect;
	int down_effect;
	int left_effect;
	int right_effect;
	int p_time;
	int arrow_start;
	int arrow_end;
	int arrow_num;
	std::vector<ArrowInfo> arrow;
	CString bgm;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	int IsAup;
	int IsAleft;
	int IsAright;
	int IsAdown;
	int IsC;
};
