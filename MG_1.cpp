#include <afxwin.h>
#include "stdafx.h"
#include "MG_1.h"


MG_1::MG_1()
{
	head = tail = 0;
	m_hero = 0;
	m_plus = 0;
	m_jump = 0;	
	m_score = 0;
}



MG_1::~MG_1()
{
	m_map.~vector();
}

void MG_1::Timer(int time)
{
	m_hit = CRect(Hero_x - 20, Hero_y - m_hero - 40, Hero_x + 20, Hero_y - m_hero);

	if (m_jump == 1) //점프중이면
	{
		m_hero += m_plus;
		if (m_plus < 0.9)
		{
			m_plus = 0;
			m_jump = -1;
		}
		else
			m_plus *= 0.94;
	}
	else if (m_jump == -1) //떨어지면
	{
		m_hero += m_plus;

		if (m_plus == 0)
			m_plus -= 0.7;

		m_plus *= 1.1f;

		if (m_hero < 0) {
			m_hero = 0;
			m_plus = 0;
			m_jump = 0;
		}
	}

	for (int i = head; i<tail; i++)
	{
		m_map[i].m_pos -= 4;
		CRect save1(m_map[i].m_pos - 5, Hero_y - m_map[i].m_height, m_map[i].m_pos + 5, Hero_y);
		CRect save2 = m_hit;

		CRect check;
		if (check.IntersectRect(&save1, &save2)) //충돌확인
		{
			m_map[i].m_success = false;
		}
	}

	if (tail < m_map.size())
		if (m_map[tail].m_time < time)
			this->tail++;
	if (head < m_map.size()) {
		if (m_map[head].m_pos < 0)
		{
			if (m_map[head].m_success)
				m_score++;
			this->head++;
		}
	}
}

void MG_1::Get_Jump(int j)
{
	this->m_jump = j;
	if(j == 1)
		m_plus += 15.0f;
}

void MG_1::Paint(CDC* main_dc, CDC* memdc)
{
	CBitmap bmp;

	for (int i = head; i<tail; i++)
	{
		Huddle h = m_map[i];
		main_dc->Rectangle(h.m_pos - 5, Hero_y - h.m_height, h.m_pos + 5, Hero_y);
	}
	main_dc->Ellipse(m_hit);
}

void MG_1::SetVector(int a)
{
	this->m_map.push_back(Huddle(width, a));
}

void MG_1::Set_Base(int w,int h)
{
	this->width = w;
	this->height = h;
	this->Hero_y = this->height;
}
