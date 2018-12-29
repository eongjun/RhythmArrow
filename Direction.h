#pragma once
class Direction
{
public:
	Direction();
	Direction(int dir, int x, int y, int t);
	~Direction();
	int m_dir;
	int m_x;
	int m_y;
	int m_success;
	int m_time;
};

