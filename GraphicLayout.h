#pragma once
#include<windows.h>
#include<vector>
#include"GraphicUnit.h"
class GraphicLayout {
private:
	HWND pWnd;
	HINSTANCE pInst;
	std::vector<GraphicUnit*> data;
protected:
	
public:
	void RefreshWnd(HWND wnd) {
		pWnd = wnd;
	}
	GraphicLayout(HWND wnd, HINSTANCE inst) :pWnd(wnd), pInst(inst) {}
	void draw();
	
	void Init() {
		for (int i = 0; i < data.size(); i++) {
			data[i]->setHandle(&pWnd, &pInst);
		}
	}

	void addGraphicUnit(GraphicUnit* g) {
		data.push_back(g);
	}
	void deleteGraphicUnit(GraphicUnit*g) {
		std::vector<GraphicUnit*>::iterator p = find(data.begin(), data.end(), g);
		GraphicUnit* gtmp = *p;
		delete gtmp;
		data.erase(p);
	}
};