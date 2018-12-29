#include "stdafx.h"
#include "MG_3.h"


MG_3::MG_3()
{
	head = tail = 0;
	m_score = 0;
}


MG_3::~MG_3()
{
	m_note.~vector();
}

void MG_3::SetVector(int a)
{
	int dir = rand() % 4;
	int n_width;
	int n_height;

	switch (dir)
	{
	case 0:
		n_width = 0;
		n_height = this->height / 2;
		break;
	case 1:
		n_width = this->width;
		n_height = this->height / 2;
		break;
	case 2:
		n_width = this->width / 2;
		n_height = this->height;
		break;
	case 3:
		n_width = this->width / 2;
		n_height = 0;
		break;
	default:
		break;
	}
	m_note.push_back(Direction(dir, n_width, n_height, a)); //노드생성
}

void MG_3::SetBase(int w, int h)
{
	this->width = w;
	this->height = h;
	m_box = CRect(width / 2 - 30, height / 2 - 30,width / 2 + 30, height / 2 + 30);
}

void MG_3::Timer(int time)
{
	if (head < m_note.size())
	{
		bool fail = false;
		switch (m_note[head].m_dir) {
		case 0:
			if (m_note[head].m_x - 50 > m_box.right)
				fail = true;
			break;
		case 1:
			if (m_note[head].m_x + 50 < m_box.left)
				fail = true;
			break;
		case 2:
			if (m_note[head].m_y + 50 < m_box.top)
				fail = true;
			break;
		case 3:
			if (m_note[head].m_y - 50 > m_box.bottom)
				fail = true;
			break;
		default:
			break;
		}
		if (m_note[head].m_success != 0 || fail)		{
			if (m_note[head].m_success == 1)
				m_score++;
			head++;
		}
	}
	if (tail < m_note.size())
		if (m_note[tail].m_time <time)
			tail++;
}

void MG_3::Paint(CDC * main_dc, CBitmap* img)
{
	for (int i = head; i<tail; i++) {
		CDC img_dc;
		BITMAP img_info; //이미지 정보

		img_dc.CreateCompatibleDC(main_dc); //메모리dc와 연동

		switch (m_note[i].m_dir)
		{
		case 0:
			m_note[i].m_x += 3;
			break;
		case 1:
			m_note[i].m_x -= 3;
			break;
		case 2:
			m_note[i].m_y -= 3;
			break;
		case 3:
			m_note[i].m_y += 3;
			break;
		default: //ADSW 순으로 저장됨 58부터
			break;
		}

		img->GetBitmap(&img_info); //이미지 정보 획득
		img_dc.SelectObject(&img[m_note[i].m_dir]); //이미지를 줌

		main_dc->StretchBlt(m_note[i].m_x - 20, m_note[i].m_y - 20, 40, 40, &img_dc, 0, 0, img_info.bmWidth, img_info.bmHeight, SRCCOPY);
		// 이미지를 그림

	}
}

void MG_3::CheckKey(int n)
{
	for (int i = head; i<tail; i++) {
		CRect dr_box(m_note[i].m_x - 50, m_note[i].m_y - 50, m_note[i].m_x + 50, m_note[i].m_y + 50);
		CRect hitcheck;
		if (hitcheck.IntersectRect(&m_box, &dr_box)) {

			if (m_note[i].m_dir == n)
			{
				m_note[i].m_success = 1; //맞다면 표시
				return;
			}
			else
				m_note[i].m_success = -1; //실패로 표시
		}
	}
}
