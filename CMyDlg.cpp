// CMyDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_Team_Dlg01.h"
#include "CMyDlg.h"
#include "afxdialogex.h"
#include "Windows.h"
#include "fstream"
#include "string"
#include "MFC_Team_Dlg01Dlg.h"
#include "CResult.h"

// CMyDlg 대화 상자

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, p_time(0)
	, arrow_start(0)
	, arrow_end(0)
	, arrow_num(0)
	, up_effect(0)
	, down_effect(0)
	, left_effect(0)
	, right_effect(0)
	, total_time(0)
	, miss(0)
	, great(0)
	, perfect(0)
	, combo(0)
	, IsGreat(0)
	, IsMiss(0)
	, IsPerfect(0)
	, long_down(0)
	, LongNum(0)
	, game_series(-1)
	, twice(false)
	, IsAup(0)
	, IsAleft(0)
	, IsAright(0)
	, IsAdown(0)
	, IsC(0)
{
	arrow.push_back(ArrowInfo(0));
	std::string s_bgm;
	std::ifstream inputfile("Bgm1.txt");
	if (inputfile.is_open()) {
		inputfile >> s_bgm;
		inputfile >> total_time;
		int a, b, c;
		while (!inputfile.eof()) {
			inputfile >> a >> b >> c;
			arrow.push_back(ArrowInfo(a + 200, b, c));
			arrow_num++;
		}
	}
	inputfile.close();
	//arrow.push_back(ArrowInfo(0));
	bgm = s_bgm.c_str();

	std::ifstream inputfile2("mini_note.txt");
		if (inputfile2.is_open()) {
			int a;
			while (!inputfile2.eof()) {
				inputfile2 >> a;
				mini_pos.AddTail(a);
			}
		}
	inputfile2.close();
}

CMyDlg::~CMyDlg()
{
	arrow.~vector();
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
//	ON_WM_CHAR()
END_MESSAGE_MAP()


// CMyDlg 메시지 처리기


BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMFCTeamDlg01Dlg* parent =
		(CMFCTeamDlg01Dlg*)AfxGetMainWnd();
	parent->ShowWindow(SW_HIDE);

	CRect desk_rect;
	GetDesktopWindow()->GetWindowRect(&desk_rect);
	this->MoveWindow(desk_rect.left + (desk_rect.Width() / 2) - 450, desk_rect.bottom - (desk_rect.Height() / 2) - 450, 900, 900);

	m_idEvent = timeSetEvent(10, 0, (LPTIMECALLBACK)RecvChecker, (DWORD)this, TIME_PERIODIC);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CALLBACK CMyDlg::RecvChecker(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->p_time += 1;
	if (pThis->p_time == 197)
		PlaySound(pThis->bgm, NULL, SND_FILENAME | SND_ASYNC);
	if (pThis->p_time == pThis->total_time + 400) {
		CResult rst;
		rst.r_perfect = pThis->perfect;
		rst.r_great = pThis->great;
		rst.r_miss = pThis->miss;
		rst.r_mini = pThis->game_1.m_score + pThis->game_2.m_score + pThis->game_3.m_score;
		rst.DoModal();
		pThis->SendMessage(WM_CLOSE);
	}

	if (pThis->arrow[pThis->arrow_start].arrowX < 5 && pThis->arrow[pThis->arrow_start].arrowA == 1) {
		pThis->arrow[pThis->arrow_start].arrowA = 0;
		pThis->combo = 0;
		pThis->miss++;
		pThis->IsMiss = 1;
		pThis->amiss = timeSetEvent(200, 0, (LPTIMECALLBACK)Miss, (DWORD)pThis, TIME_PERIODIC);
	}

	if (pThis->arrow_start < pThis->arrow_num)
		if (pThis->arrow[pThis->arrow_start].arrowX < 5 && pThis->arrow[pThis->arrow_start + 1].arrowT <= pThis->p_time + 200)
			pThis->arrow_start++;
	if (pThis->arrow_end < pThis->arrow_num)
		if (pThis->arrow[pThis->arrow_end + 1].arrowT <= pThis->p_time + 200)
			pThis->arrow_end++;

	for (int i = pThis->arrow_start; i <= pThis->arrow_end; i++) {
		pThis->arrow[i].arrowX -= 4;
	}
	for (int i = 0; i <= pThis->arrow_end; i++) {
		if (pThis->arrow[i].arrowLD > 10)
			pThis->arrow[i].arrowLD -= 4;
		if (pThis->arrow[i].arrowX <= 10 && pThis->arrow[i].arrowL != 0)
			pThis->arrow[i].arrowL--;
	}

	switch (pThis->game_series)
	{
	case 0:
		pThis->game_1.Timer(pThis->p_time);
		if (pThis->game_1.head == pThis->game_1.m_map.size() && pThis->game_2.head == 0)
			pThis->game_series += 1;
		break;
	case 1:
		pThis->game_2.Timer(pThis->p_time);
		if (pThis->game_2.head == pThis->game_2.m_note.size() && pThis->game_3.head == 0)
			pThis->game_series += 1;
		break;
	case 2:
		pThis->game_3.Timer(pThis->p_time);
		if (pThis->game_3.head == pThis->game_3.m_note.size() && pThis->game_1.head == 0)
			pThis->game_series = 0;
		break;
	default:
		break;
	}


	pThis->Invalidate(false);

}


void CMyDlg::OnPaint()
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
	main_dc.PatBlt(0, 0, m_client.Width(), m_client.Height(), BLACKNESS);
//	main_dc.PatBlt(0, 0, m_client.Width(), m_client.Height(), WHITENESS);

	switch (game_series)
	{
	case 0:
		for (int i = game_1.head; i<game_1.tail; i++)
		{
			Huddle h = game_1.m_map[i];
			main_dc.Rectangle(h.m_pos - 5, game_1.Hero_y - h.m_height, h.m_pos + 5, game_1.Hero_y);
		}
		main_dc.Ellipse(game_1.m_hit);
		break;
	case 1:
	{
		CBitmap piano_bmp;
		piano_bmp.LoadBitmapW(IDB_BITMAP65); //건반이미지
		CDC piano_dc;

		BITMAP piano_info;
		CRect m_piano = game_2.m_piano;

		piano_bmp.GetBitmap(&piano_info);

		piano_dc.CreateCompatibleDC(&main_dc);
		piano_dc.SelectObject(&piano_bmp);

		main_dc.StretchBlt(m_piano.left, m_piano.top, m_piano.Width(), m_piano.Height(),
			&piano_dc, 0, 0, piano_info.bmWidth, piano_info.bmHeight, SRCCOPY);

		CBitmap num_button[3];
		for (int i = 0; i < 3; i++)
			num_button[i].LoadBitmapW(IDB_BITMAP62 + i);

		for (int i = game_2.head; i < game_2.tail; i++)
		{
			CDC img_dc;
			BITMAP img_info; //이미지 정보

			img_dc.CreateCompatibleDC(&main_dc); //메모리dc와 연동

	
				img_dc.SelectObject(&num_button[game_2.m_note[i].m_value - 1]); //이미지를 줌
				num_button[game_2.m_note[i].m_value - 1].GetBitmap(&img_info);
				main_dc.TransparentBlt(game_2.m_note[i].m_x - 50, game_2.m_note[i].m_y - 50, 100, 100,
					&img_dc, 0, 0, img_info.bmWidth, img_info.bmHeight, RGB(255, 255, 255));
	
		}
		}
		break;
	case 2:
	{
		main_dc.Rectangle(game_3.m_box);
		CBitmap key_button[4];
		for (int i = 0; i < 4; i++)
			key_button[i].LoadBitmapW(IDB_BITMAP58 + i);
		for (int i = game_3.head; i<game_3.tail; i++) {
			CDC img_dc;
			BITMAP img_info; //이미지 정보

			img_dc.CreateCompatibleDC(&main_dc); //메모리dc와 연동

			switch (game_3.m_note[i].m_dir)
			{
			case 0:
				game_3.m_note[i].m_x += 3;
				break;
			case 1:
				game_3.m_note[i].m_x -= 3;
				break;
			case 2:
				game_3.m_note[i].m_y -= 3;
				break;
			case 3:
				game_3.m_note[i].m_y += 3;
				break;
			default: //ADSW 순으로 저장됨 58부터
				break;
			}

			key_button[game_3.m_note[i].m_dir].GetBitmap(&img_info); //이미지 정보 획득
			img_dc.SelectObject(&key_button[game_3.m_note[i].m_dir]); //이미지를 줌

			main_dc.TransparentBlt(game_3.m_note[i].m_x - 50, game_3.m_note[i].m_y - 50, 100, 100, 
				&img_dc, 0, 0, img_info.bmWidth, img_info.bmHeight, RGB(255,255,255));
			// 이미지를 그림
		}
	}
		break;
	default:
		break;
	}

	CBitmap bg;
	bg.LoadBitmapW(IDB_BITMAP43);
	BITMAP bg_info;
	bg.GetBitmap(&bg_info);
	memdc.SelectObject(&bg);
	main_dc.StretchBlt(5, 820, 610, 75, &memdc, 90, 17, bg_info.bmWidth - 90, bg_info.bmHeight - 18, SRCCOPY);
	main_dc.StretchBlt(615, 820, 280, 75, &memdc, 380, 17, bg_info.bmWidth - 420, bg_info.bmHeight - 18, SRCCOPY);

	CBitmap correct[3];
	BITMAP correct_info[3];
	correct[0].LoadBitmapW(IDB_BITMAP44);
	correct[1].LoadBitmapW(IDB_BITMAP45);
	correct[2].LoadBitmapW(IDB_BITMAP46);
	correct[0].GetBitmap(&correct_info[0]);
	correct[1].GetBitmap(&correct_info[1]);
	correct[2].GetBitmap(&correct_info[2]);
	if (IsGreat == 1) {
		memdc.SelectObject(&correct[0]);
		main_dc.StretchBlt(200, 750, 96, 34, &memdc, 0, 0, correct_info[0].bmWidth, correct_info[0].bmHeight, SRCCOPY);
	}
	if (IsMiss == 1) {
		memdc.SelectObject(&correct[1]);
		main_dc.StretchBlt(200, 750, 74, 32, &memdc, 0, 0, correct_info[1].bmWidth, correct_info[1].bmHeight, SRCCOPY);
	}
	if (IsPerfect == 1) {
		memdc.SelectObject(&correct[2]);
		main_dc.StretchBlt(200, 750, 124, 34, &memdc, 0, 0, correct_info[2].bmWidth, correct_info[2].bmHeight, SRCCOPY);
	}


	CBitmap dir_end[2];
	BITMAP dir_end_info[2];
	dir_end[0].LoadBitmapW(IDB_BITMAP41);
	dir_end[1].LoadBitmapW(IDB_BITMAP42);
	dir_end[0].GetBitmap(&dir_end_info[0]);
	dir_end[1].GetBitmap(&dir_end_info[1]);
	memdc.SelectObject(&dir_end[0]);
	main_dc.TransparentBlt(30, 823, 69, 69, &memdc, 0, 0, dir_end_info[0].bmWidth, dir_end_info[0].bmHeight, RGB(0, 255, 0));

	CBitmap arrowL[8];
	BITMAP arrowL_info[8];
	for (int j = 0; j < 8; j += 2) {
		arrowL[j].LoadBitmapW(IDB_BITMAP2 + (10 * (j / 2)));
		arrowL[j + 1].LoadBitmapW(IDB_BITMAP3 + (10 * (j / 2)));
		arrowL[j].GetBitmap(&arrowL_info[j]);
		arrowL[j + 1].GetBitmap(&arrowL_info[j + 1]);
	}

	for (int i = 0; i <= arrow_num; i++) {
		if (arrow[i].arrowX < 800 && arrow[i].arrowL != 0) {
			memdc.SelectObject(&arrowL[(arrow[i].arrowD * 2)]);
			for (int j = 0; j < arrow[i].arrowL - 7; j++)
				main_dc.TransparentBlt(arrow[i].arrowLD + 55 + (4 * j), arrow[i].arrowY + 12, 4, 44, &memdc,
					0, 0, arrowL_info[arrow[i].arrowD * 2].bmWidth, arrowL_info[arrow[i].arrowD * 2].bmHeight, RGB(0, 0, 0));

			memdc.SelectObject(&arrowL[(arrow[i].arrowD * 2 + 1)]);
			if (arrow[i].arrowL - 7 > 0)
			main_dc.TransparentBlt(arrow[i].arrowLD + 27 + (4 * arrow[i].arrowL), arrow[i].arrowY + 12, 28, 44, &memdc,
				28, 0, arrowL_info[arrow[i].arrowD * 2 + 1].bmWidth-28, arrowL_info[arrow[i].arrowD * 2 + 1].bmHeight, RGB(0, 0, 0));
		}
	}

	for (int i = arrow_start; i <= arrow_end; i++) {
		if (arrow[i].arrowX >= 5 && arrow[i].arrowA == 1) {
			if (arrow[i].arrowX < 100) {
				memdc.SelectObject(&dir_end[1]);
				main_dc.TransparentBlt(30, 823, 69, 69, &memdc, 0, 0, dir_end_info[1].bmWidth, dir_end_info[1].bmHeight, RGB(0, 255, 0));
			}

			CBitmap test;
			test.LoadBitmapW(IDB_BITMAP1 + (10 * arrow[i].arrowD));
			BITMAP test_info;
			test.GetBitmap(&test_info);
			memdc.SelectObject(&test);
			main_dc.TransparentBlt(arrow[i].arrowX, arrow[i].arrowY, 69, 69, &memdc, 0, 0, test_info.bmWidth, test_info.bmHeight, RGB(0, 0, 0));
		}
	}

	CBitmap effect[4];
	BITMAP effect_info[4];

	if (down_effect != 0) {
		effect[0].LoadBitmapW(IDB_BITMAP4 + down_effect - 1);
		effect[0].GetBitmap(&effect_info[0]);
		memdc.SelectObject(&effect[0]);
		int wid = effect_info[0].bmWidth;
		int hei = effect_info[0].bmHeight;
		main_dc.TransparentBlt(30, 823, 69, 69, &memdc, 0, 0, wid, hei, RGB(0, 0, 0));
	}

	if (left_effect != 0) {
		effect[1].LoadBitmapW(IDB_BITMAP14 + left_effect - 1);
		effect[1].GetBitmap(&effect_info[1]);
		memdc.SelectObject(&effect[1]);
		int wid = effect_info[1].bmWidth;
		int hei = effect_info[1].bmHeight;
		main_dc.TransparentBlt(30, 823, 69, 69, &memdc, 0, 0, wid, hei, RGB(0, 0, 0));
	}

	if (right_effect != 0) {
		effect[2].LoadBitmapW(IDB_BITMAP24 + right_effect - 1);
		effect[2].GetBitmap(&effect_info[2]);
		memdc.SelectObject(&effect[2]);
		int wid = effect_info[2].bmWidth;
		int hei = effect_info[2].bmHeight;
		main_dc.TransparentBlt(30, 823, 69, 69, &memdc, 0, 0, wid, hei, RGB(0, 0, 0));
	}

	if (up_effect != 0) {
		effect[3].LoadBitmapW(IDB_BITMAP34 + up_effect - 1);
		effect[3].GetBitmap(&effect_info[3]);
		memdc.SelectObject(&effect[3]);
		int wid = effect_info[3].bmWidth;
		int hei = effect_info[3].bmHeight;
		main_dc.TransparentBlt(30, 823, 69, 69, &memdc, 0, 0, wid, hei, RGB(0, 0, 0));
	}

	CBitmap comboImg[11];
	BITMAP comboImg_info[11];
	for (int i = 0; i < 11; i++) {
		comboImg[i].LoadBitmapW(IDB_BITMAP66 + i);
		comboImg[i].GetBitmap(&comboImg_info[i]);
	}
	if (combo > 999) {
		memdc.SelectObject(&comboImg[10]);
		main_dc.StretchBlt(10, 750, 34, 38, &memdc, 0, 0, comboImg_info[10].bmWidth, comboImg_info[10].bmHeight, SRCCOPY);
		main_dc.StretchBlt(45, 750, 34, 38, &memdc, 0, 0, comboImg_info[10].bmWidth, comboImg_info[10].bmHeight, SRCCOPY);
		main_dc.StretchBlt(80, 750, 34, 38, &memdc, 0, 0, comboImg_info[10].bmWidth, comboImg_info[10].bmHeight, SRCCOPY);
	}
	else {
		memdc.SelectObject(&comboImg[combo / 100 + 1]);
		main_dc.StretchBlt(10, 750, 34, 38, &memdc, 0, 0, comboImg_info[combo / 100 + 1].bmWidth, comboImg_info[combo / 100 + 1].bmHeight, SRCCOPY);
		memdc.SelectObject(&comboImg[(combo % 100) / 10 + 1]);
		main_dc.StretchBlt(45, 750, 34, 38, &memdc, 0, 0, comboImg_info[(combo % 100) / 10 + 1].bmWidth, comboImg_info[(combo % 100) / 10 + 1].bmHeight, SRCCOPY);
		memdc.SelectObject(&comboImg[combo % 10 + 1]);
		main_dc.StretchBlt(80, 750, 34, 38, &memdc, 0, 0, comboImg_info[combo % 10 + 1].bmWidth, comboImg_info[combo % 10 + 1].bmHeight, SRCCOPY);
	}
	memdc.SelectObject(&comboImg[0]);
	main_dc.StretchBlt(115, 760, 70, 25, &memdc, 0, 0, comboImg_info[0].bmWidth, comboImg_info[0].bmHeight, SRCCOPY);


	dc.BitBlt(0, 0, m_client.Width(), m_client.Height(), &main_dc, 0, 0, SRCCOPY);
}


void CMyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	GetClientRect(&m_client);
	game_1.Set_Base(m_client.Width(), m_client.Height() - 200);
	game_2.SetBase(m_client.Width(), m_client.Height() - 200);
	game_3.SetBase(m_client.Width(), m_client.Height() - 200);



		if (twice) {
			srand((unsigned)time(NULL));
			int rand_start = rand() % 3;
	
			game_series = rand_start;
			
			POSITION pos = mini_pos.GetHeadPosition();
			
			for (int i = 0; i < 3; i++)
			{
				int index = (rand_start + i) % 3;
				int set_num = 0;
				switch (index) {
				case 0:
					while (set_num != -1 && pos != NULL)
					{
						set_num = mini_pos.GetNext(pos);
						if (set_num != -1) {
							game_1.SetVector(set_num);
						}
					}
					break;
				case 1:
					while (set_num != -1 && pos != NULL)
					{
						set_num = mini_pos.GetNext(pos);
						if (set_num != -1) {
							game_2.SetVector(set_num);
						}
					}
					break;
				case 2:
					while (set_num != -1 && pos != NULL)
					{
						set_num = mini_pos.GetNext(pos);
						if (set_num != -1 ) {
							game_3.SetVector(set_num);
						}
					}
					break;
				default:
					break;
				}
			}
			mini_pos.RemoveAll();
		}
		twice = true;

}



void CMyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CDialog::OnTimer(nIDEvent);
}

void CALLBACK CMyDlg::AContinue(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->perfect++;
	pThis->IsPerfect = 1;
	pThis->combo++;
	if (pThis->arrow[pThis->LongNum].arrowL <= 0) {
		pThis->IsC = 0;
		timeKillEvent(pThis->acontinue);
		pThis->long_down = 0;
		pThis->IsPerfect = 0;
	}
}

void CALLBACK CMyDlg::ArrowDown(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->down_effect = (pThis->down_effect + 1) % 8;
	pThis->Invalidate(false);
	if (pThis->down_effect == 0) {
		pThis->IsAdown = 0;
		timeKillEvent(pThis->adown);
	}
}

void CALLBACK CMyDlg::ArrowLeft(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->left_effect = (pThis->left_effect + 1) % 8;
	pThis->Invalidate(false);
	if (pThis->left_effect == 0) {
		pThis->IsAleft = 0;
		timeKillEvent(pThis->aleft);
	}
}

void CALLBACK CMyDlg::ArrowRight(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->right_effect = (pThis->right_effect + 1) % 8;
	pThis->Invalidate(false);
	if (pThis->right_effect == 0) {
		pThis->IsAright = 0;
		timeKillEvent(pThis->aright);
	}
}

void CALLBACK CMyDlg::ArrowUp(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->up_effect = (pThis->up_effect + 1) % 8;
	pThis->Invalidate(false);
	if (pThis->up_effect == 0) {
		pThis->IsAup = 0;
		timeKillEvent(pThis->aup);
	}
}

void CALLBACK CMyDlg::Great(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->IsGreat = 0;
	timeKillEvent(pThis->agreat);
}

void CALLBACK CMyDlg::Miss(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->IsMiss = 0;
	timeKillEvent(pThis->amiss);
}

void CALLBACK CMyDlg::Perfect(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2) {
	CMyDlg* pThis = (CMyDlg*)dwUser;
	pThis->IsPerfect = 0;
	timeKillEvent(pThis->aperfect);
}


BOOL CMyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (arrow[arrow_start].arrowA == 1 && arrow[arrow_start].arrowX < 100) {
		if (pMsg->message == WM_KEYDOWN) {
			if (pMsg->wParam == VK_DOWN) {
				arrow[arrow_start].arrowA = 0;
				if (arrow[arrow_start].arrowD == 0) {
					IsAdown = 1;
					adown = timeSetEvent(20, 0, (LPTIMECALLBACK)ArrowDown, (DWORD)this, TIME_PERIODIC);
					if (arrow[arrow_start].arrowL != 0) {
						LongNum = arrow_start;
						long_down = 1;
						IsC = 1;
						acontinue = timeSetEvent(100, 0, (LPTIMECALLBACK)AContinue, (DWORD)this, TIME_PERIODIC);
					}
					combo++;
					if (arrow[arrow_start].arrowX > 65 || arrow[arrow_start].arrowX < 10) {
						great++;
						IsGreat = 1;
						agreat = timeSetEvent(200, 0, (LPTIMECALLBACK)Great, (DWORD)this, TIME_PERIODIC);
					}
					else {
						perfect++;
						IsPerfect = 1;
						aperfect = timeSetEvent(200, 0, (LPTIMECALLBACK)Perfect, (DWORD)this, TIME_PERIODIC);
					}
				}
				else {
					combo = 0;
					miss++;
					IsMiss = 1;
					amiss = timeSetEvent(200, 0, (LPTIMECALLBACK)Miss, (DWORD)this, TIME_PERIODIC);
				}

				if (arrow_start < arrow_num)
					if (arrow[arrow_start].arrowX < 5 && arrow[arrow_start + 1].arrowT <= p_time + 200)
						arrow_start++;
			}
			else if (pMsg->wParam == VK_LEFT) {
				arrow[arrow_start].arrowA = 0;
				if (arrow[arrow_start].arrowD == 1) {
					if (arrow[arrow_start].arrowL != 0) {
						LongNum = arrow_start;
						long_down = 2;
						IsC = 1;
						acontinue = timeSetEvent(100, 0, (LPTIMECALLBACK)AContinue, (DWORD)this, TIME_PERIODIC);
					}
					IsAleft = 1;
					aleft = timeSetEvent(20, 0, (LPTIMECALLBACK)ArrowLeft, (DWORD)this, TIME_PERIODIC);
					combo++;
					if (arrow[arrow_start].arrowX > 65 || arrow[arrow_start].arrowX < 10) {
						great++;
						IsGreat = 1;
						agreat = timeSetEvent(200, 0, (LPTIMECALLBACK)Great, (DWORD)this, TIME_PERIODIC);
					}
					else {
						perfect++;
						IsPerfect = 1;
						aperfect = timeSetEvent(200, 0, (LPTIMECALLBACK)Perfect, (DWORD)this, TIME_PERIODIC);
					}
				}
				else {
					combo = 0;
					miss++;
					IsMiss = 1;
					amiss = timeSetEvent(200, 0, (LPTIMECALLBACK)Miss, (DWORD)this, TIME_PERIODIC);
				}

				if (arrow_start < arrow_num)
					if (arrow[arrow_start].arrowX < 5 && arrow[arrow_start + 1].arrowT <= p_time + 200)
						arrow_start++;
				
			}
			else if (pMsg->wParam == VK_RIGHT) {
				arrow[arrow_start].arrowA = 0;
				if (arrow[arrow_start].arrowD == 2) {
					if (arrow[arrow_start].arrowL != 0) {
						LongNum = arrow_start;
						long_down = 3;
						IsC = 1;
						acontinue = timeSetEvent(100, 0, (LPTIMECALLBACK)AContinue, (DWORD)this, TIME_PERIODIC);
					}
					IsAright = 1;
					aright = timeSetEvent(20, 0, (LPTIMECALLBACK)ArrowRight, (DWORD)this, TIME_PERIODIC);
					combo++;
					if (arrow[arrow_start].arrowX > 65 || arrow[arrow_start].arrowX < 10) {
						great++;
						IsGreat = 1;
						agreat = timeSetEvent(200, 0, (LPTIMECALLBACK)Great, (DWORD)this, TIME_PERIODIC);
					}
					else {
						perfect++;
						IsPerfect = 1;
						aperfect = timeSetEvent(200, 0, (LPTIMECALLBACK)Perfect, (DWORD)this, TIME_PERIODIC);
					}
				}
				else {
					combo = 0;
					miss++;
					IsMiss = 1;
					amiss = timeSetEvent(200, 0, (LPTIMECALLBACK)Miss, (DWORD)this, TIME_PERIODIC);
				}
				
				if (arrow_start < arrow_num)
					if (arrow[arrow_start].arrowX < 5 && arrow[arrow_start + 1].arrowT <= p_time + 200)
						arrow_start++;
			}
			else if (pMsg->wParam == VK_UP) {
				arrow[arrow_start].arrowA = 0;
				if (arrow[arrow_start].arrowD == 3) {
					if (arrow[arrow_start].arrowL != 0) {
						LongNum = arrow_start;
						long_down = 4;
						IsC = 1;
						acontinue = timeSetEvent(100, 0, (LPTIMECALLBACK)AContinue, (DWORD)this, TIME_PERIODIC);
					}
					IsAup = 1;
					aup = timeSetEvent(20, 0, (LPTIMECALLBACK)ArrowUp, (DWORD)this, TIME_PERIODIC);
					combo++;
					if (arrow[arrow_start].arrowX > 65 || arrow[arrow_start].arrowX < 10) {
						great++;
						IsGreat = 1;
						agreat = timeSetEvent(200, 0, (LPTIMECALLBACK)Great, (DWORD)this, TIME_PERIODIC);
					}
					else {
						perfect++;
						IsPerfect = 1;
						aperfect = timeSetEvent(200, 0, (LPTIMECALLBACK)Perfect, (DWORD)this, TIME_PERIODIC);
					}
				}
				else {
					combo = 0;
					miss++;
					IsMiss = 1;
					amiss = timeSetEvent(200, 0, (LPTIMECALLBACK)Miss, (DWORD)this, TIME_PERIODIC);
				}
				
				if (arrow_start < arrow_num)
					if (arrow[arrow_start].arrowX < 5 && arrow[arrow_start + 1].arrowT <= p_time + 200)
						arrow_start++;
			}
		}
		Invalidate(false);
	}

	if(pMsg->message==WM_KEYDOWN)
				{
					switch (game_series) {
					case 0:
						if (pMsg->wParam == VK_SPACE && game_1.m_jump == 0)
							game_1.Get_Jump(1); //점프상태로.
						break;
					case 1:
					{
						int ch = -1;
						switch (pMsg->wParam)
						{
						case '1':
							ch = 1;
							break;
						case '2':
							ch = 2;
							break;
						case '3':
							ch = 3;
							break;
						default:
							break;
						}
						if (ch != -1)
							game_2.CheckKey(ch);
					}
					break;
					case 2:
					{
						int dir_num = -1;
						switch (pMsg->wParam)
						{
						case 'A':
							dir_num = 0;
							break;
						case 'D':
							dir_num = 1;
							break;
						case 'S':
							dir_num = 2;
							break;
						case 'W':
							dir_num = 3;
							break;
						default:
							break;
						}
						game_3.CheckKey(dir_num);
						break;
					}
					default:
						break;
					}
					Invalidate(false);
				}


	if (pMsg->message == WM_KEYUP) {
		if (pMsg->wParam == VK_DOWN) {
			if (long_down = 1) {
				timeKillEvent(acontinue);
				long_down = 0;
				IsPerfect = 0;
			}
		}
		else if (pMsg->wParam == VK_LEFT) {
			if (long_down = 2) {
				timeKillEvent(acontinue);
				long_down = 0;
				IsPerfect = 0;
			}
		}
		else if (pMsg->wParam == VK_RIGHT) {
			if (long_down = 3) {
				timeKillEvent(acontinue);
				long_down = 0;
				IsPerfect = 0;
			}
		}
		else if (pMsg->wParam == VK_UP) {
			if (long_down = 4) {
				timeKillEvent(acontinue);
				long_down = 0;
				IsPerfect = 0;
			}
		}
		long_down = 0;
		LongNum = 0;
	}


	return CDialog::PreTranslateMessage(pMsg);
}


void CMyDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	timeKillEvent(m_idEvent);
	sndPlaySound(NULL, SND_ASYNC);
	if (IsAup == 1)
		timeKillEvent(aup);
	if (IsAleft == 1)
		timeKillEvent(aleft);
	if (IsAright == 1)
		timeKillEvent(aright);
	if (IsAdown == 1)
		timeKillEvent(adown);
	if (IsPerfect == 1)
		timeKillEvent(aperfect);
	if (IsGreat == 1)
		timeKillEvent(agreat);
	if (IsMiss == 1)
		timeKillEvent(amiss);
	if (IsC == 1)
		timeKillEvent(acontinue);

	CDialog::OnCancel();
}


//void CMyDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	int ch = -1;
//	switch (nChar)
//	{
//	case '1':
//		ch = 1;
//		break;
//	case '2':
//		ch = 2;
//		break;
//	case '3':
//		ch = 3;
//		break;
//	default:
//		break;
//	}
//	if (ch != -1)
//		game_2.CheckKey(ch);
//
//	CDialog::OnChar(nChar, nRepCnt, nFlags);
//}
