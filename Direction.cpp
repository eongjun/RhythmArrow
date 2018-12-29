#include "stdafx.h"
#include "Direction.h"


Direction::Direction()
{
}

Direction::Direction(int dir,int x,int y, int t)
{
	m_x = x;
	m_y = y;
	m_dir = dir;
	m_time = t;
	m_success = 0;
}

Direction::~Direction()
{
}
