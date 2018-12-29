#include "stdafx.h"
#include "ArrowInfo.h"


ArrowInfo::ArrowInfo()
{
}


ArrowInfo::ArrowInfo(int x)
	: arrowX(x)
	, arrowT(0)
	, arrowY(823)
	, arrowD(0)
	, arrowL(0)
	, arrowA(0)
	, arrowLD(0)
{
}


ArrowInfo::ArrowInfo(int t, int d, int l)
	: arrowT(t)
	, arrowD(d)
	, arrowL(l)
	, arrowX(830)
	, arrowY(823)
	, arrowA(1)
{
	arrowLD = 823;
}


ArrowInfo::ArrowInfo(int t, int d, int l, int k)
	: arrowT(t)
	, arrowD(d)
	, arrowL(l)
	, arrowX(830)
	, arrowY(k)
	, arrowA(1)
{
	arrowLD = 823;
}


ArrowInfo::~ArrowInfo()
{
}
