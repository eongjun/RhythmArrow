#pragma once
class Note_s
{
public:
	Note_s();
	Note_s(int p, int a, int d);
	~Note_s();
	int m_pos;
	int m_arrow;
	int m_delay;
	Note_s& operator=(const Note_s& n);
};

