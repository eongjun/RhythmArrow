#pragma once
#include "Direction.h"
#include <vector>

class MG_3
{
public:
	MG_3();
	~MG_3();

	void SetVector(int a);
	void SetBase(int w, int h);
	void Timer(int time);
	void Paint(CDC* main_dc, CBitmap* img);
	void CheckKey(int n);

	std::vector<Direction> m_note;
	CRect m_box; //충돌을 확인할 상자
	int head;
	int tail;
	int width;
	int height;
	int m_score;
};

