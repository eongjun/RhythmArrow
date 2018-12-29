#include "stdafx.h"
#include "Note_s.h"

Note_s::Note_s(){}

Note_s::Note_s(int p, int a, int d)
{
	this->m_pos = p;
	this->m_arrow = a;
	this->m_delay = d;
}


Note_s::~Note_s()
{
}

Note_s& Note_s::operator=(const Note_s& n) {
	this->m_arrow = n.m_arrow;
	this->m_delay = n.m_delay;
	this->m_pos = n.m_pos;
	return *this;
}