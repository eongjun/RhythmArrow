#include "stdafx.h"
#include "MG_2.h"


MG_2::MG_2()
{
	head = tail = 0;
	m_score = 0;
}


MG_2::~MG_2()
{
	m_note.~vector();
}

void MG_2::SetVector(int a)
{
	int div = rand() % 3 + 1;
	int start = width / 4 * div;
	m_note.push_back(Note(a, rand() % 3 + 1, start));
}

void MG_2::SetBase(int w, int h)
{
	this->width = w;
	this->height = h;
	this->Hero_y = height - 150;

	m_piano = CRect(0, Hero_y - 20, width, Hero_y + 20);
}

void MG_2::Timer(int time)
{
	//여분 값이 남아있는지 확인할것..
	if (tail < m_note.size())
		if (m_note[tail].m_time <= time)
			tail++;
	if (head < m_note.size())
		if (m_note[head].m_y >= height || m_note[head].m_success != 0)
		{
			if (m_note[head].m_success == 1)
				m_score++;
			head++;
		}
	for (int i = head; i < tail; i++) {
		m_note[i].m_y += 5;
	}
}

void MG_2::Paint(CDC * main_dc, CBitmap& piano_bmp,CBitmap* num_button)
{

	for (int i = head; i < tail; i++)
	{
		Note n = m_note[i];

		CDC img_dc;
		CBitmap img;
		BITMAP img_info; //이미지 정보

		img_dc.CreateCompatibleDC(main_dc); //메모리dc와 연동

		if (n.m_success) {
			img_dc.SelectObject(&img[n.m_value-1]); //이미지를 줌
			img.GetBitmap(&img_info);
			main_dc->StretchBlt(n.m_x - 20, n.m_y - 20, 40, 40, &img_dc, 0, 0, img_info.bmWidth, img_info.bmHeight, SRCCOPY);
		}
	}
}

void MG_2::CheckKey(int ch)
{
	for (int i = head; i < tail; i++)
	{
		Note n = m_note[i];

		if (!n.m_success) {
			CRect circle(n.m_x - 50, n.m_y - 50, n.m_x + 50, n.m_y + 50);

			CRect checkIntersect;

			if (checkIntersect.IntersectRect(&m_piano, &circle))
			{

				if (n.m_value == ch)
					m_note[i].m_success = 1; //수정
				else
					m_note[i].m_success = -1;
				break;
			}
		}
	}
}
