#include "stdafx.h"
#include "Note.h"


Note::Note()
{
}

Note::Note(int t,int value,int x)
	:m_time(t), m_value(value), m_x(x),m_y(0), m_success(0)
{
	
}

Note::~Note()
{
}
