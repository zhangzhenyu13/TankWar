#pragma once
#include<windows.h>
#include<vector>
#include"GraphicUnit.h"
#include"StatusWnd.h"
#include"StartUpWnd.h"
class GraphicLayout {
private:
	HWND pWnd;
	HINSTANCE pInst;
	std::vector<GraphicUnit*> data;
	StatusWnd* status;
	StartUpWnd* start;
protected:
	
public:
	char showStartUP=0;//0 start,1 game, 2 end
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
	StatusWnd* Status(){return status;}
	void addGraphicUnit(GraphicUnit* g) {
		data.push_back(g);
	}
	void addStartUp(StartUpWnd* startwnd) {
		start = startwnd;
	}
	void addStatusZone(StatusWnd* stwnd){
		status=stwnd;
	}
	void deleteGraphicUnit(GraphicUnit*g) {
		
		std::vector<GraphicUnit*>::iterator p = find(data.begin(), data.end(), g);
		GraphicUnit* gtmp = *p;
		delete gtmp;
		data.erase(p);
	}
	~GraphicLayout(){
		for(int i=data.size()-1;i>=0;i--)
			delete data[i];
	}

};