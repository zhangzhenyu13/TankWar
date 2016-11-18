#pragma once
#include<windows.h>
#include<math.h>
namespace DataFunc {
	void FillArea(RECT& rect,bool flag,bool **map,int row=720,int col=1208) {
		for (int y = rect.top; y <= rect.bottom; y++)
			for (int x = rect.left; x <= rect.right; x++)
				map[y][x] = flag;
	}
	bool IsaPoint(POINT p, RECT rect) {
		if (p.x<rect.right&&p.x>rect.left)
			if (p.y<rect.bottom&&p.y>rect.top)
				return true;
			else
				return false;
	}
	bool interset(RECT& rect1,RECT& rect2) {
		int x, y;
		x = rect1.left; y = rect1.top;
		if (IsaPoint({ x,y }, rect2))
			return true;
		x = rect1.right;
		if (IsaPoint({ x,y }, rect2))
			return true;
		y = rect1.bottom;
		if (IsaPoint({ x,y }, rect2))
			return true;
		x = rect1.left;
		if (IsaPoint({ x,y }, rect2))
			return true;
		return false;
		
	}
	
};