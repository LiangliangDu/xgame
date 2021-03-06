#include "stdafx.h"

#include "WayPointFinding.h"


WayPointFinding::WayPointFinding()
{
	x = 0;
	y = 0;
	g = 0;
	h = 0;
	f = 0;
	parent = 0;
}

bool WayPointFinding::operator < (const WayPointFinding& other) const
{
	return f < other.f;
}


bool WayPointFinding::operator == (const WayPointFinding& other) const
{
	if ((x == other.x) && (y == other.y))
	{
		return true;
	}
	return false;
}



void WayPointFinding::Setpos(int nx, int ny)
{
	x = nx;
	y = ny;
}

void WayPointFinding::Setpos(const xs::Point &pt)
{
	Setpos(pt.x, pt.y);
}


xs::Point WayPointFinding::getPos(void) const 
{
	xs::Point pt(x, y);
	return pt;
}
