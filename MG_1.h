#pragma once
#include "Huddle.h"
#include <vector>

#define Hero_x 100

class MG_1
{
public:
	MG_1();
	~MG_1();

	void SetVector(int a);
	void Set_Base(int w, int h);
	void Timer(int time);
	void Get_Jump(int j);
	void Paint(CDC* main_dc,CDC* memdc);

	int width;
	int height;
	int Hero_y;
	int m_hero;
	CRect m_hit; //타격판정 확인
	float m_plus; //점프시 속도 증감값
	int m_jump; //점프 상태

	std::vector<Huddle> m_map;
	int head;
	int tail;
	int m_score;
};

