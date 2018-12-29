#pragma once
#include "Note.h"
#include <vector>

class MG_2
{
public:
	MG_2();
	~MG_2();
	CRect m_piano; //¹Ù´Ú °Ç¹Ý

	std::vector<Note> m_note;

	void SetVector(int a);
	void SetBase(int w, int h);
	void Timer(int time);
	void Paint(CDC* main_dc, CBitmap& piano_bmp, CBitmap* num_button);
	void CheckKey(int ch);

	int width;
	int height;
	int head;
	int tail;
	int Hero_y;

	int m_score;
};

