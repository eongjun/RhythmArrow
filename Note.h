#pragma once
class Note
{
public:
	Note();
	Note(int t, int value, int x);
	~Note();

	int m_time;
	int m_x;
	int m_y;
	int m_value;
	int m_success; //노트타자 성공 여부
};

