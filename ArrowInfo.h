#pragma once
class ArrowInfo
{
public:
	ArrowInfo();
	~ArrowInfo();
	ArrowInfo(int x);
	ArrowInfo(int t, int d, int l);
	ArrowInfo(int t, int d, int l, int k);
	int arrowX; // x좌표
	int arrowY; // y좌표
	int arrowT; // 시간정보 10ms == 1
	int arrowD; // 방향키 정보 0:down, 1:left, 2:right, 3:up
	int arrowL; // 지속시간
	int arrowA; // 노트의 생존여부 0:없음, 1:있음
	int arrowLD;
};

