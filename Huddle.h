#pragma once
class Huddle
{
public:
	int m_height;
	int m_pos;
	int m_time;
	int m_success;

	Huddle();
	Huddle(int p, int t);
	~Huddle();
};

