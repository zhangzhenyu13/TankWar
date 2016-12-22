#pragma once
#include<windows.h>
#include<math.h>
namespace DataFunc {
	void FillArea(RECT& rect,bool flag,bool **map,int row=720,int col=1208) {
		for (int y = rect.top; y <= rect.bottom; y++)
			for (int x = rect.left; x <= rect.right; x++)
				map[y][x] = flag;
	}
	
	
};