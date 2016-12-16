#pragma once
#include"GraphicUnit.h"

class StatusWnd:public GraphicUnit{
	int level_R1[5],level_R2[5];
	std::string name_R1,name_R2;
	HDC* pDCObj,*pDC;
	HWND* pWnd;
	HINSTANCE* pInst;
public:
	StatusWnd(){
		clear();
	}
	void add(int team,int level){
	    if(team==1)
			level_R1[level-1]++;
		if(team==2)
			level_R2[level-1]++;
	}
	int Sum(int team){
		int sum=0;
		if(team==1)
			for(int i=0;i<5;i++)
				sum+=level_R1[i];
		if(team==2)
			for(int i=0;i<5;i++)
				sum+=level_R2[i];
		return sum;
	}
	void clear(){
		for(int i=0;i<5;i++)
			level_R1[i]=level_R2[i]=0;
	}
	int getLevel(int l,int team){
		int re;
		team==1?re= level_R1[l-1]:re=level_R2[l-1];
		return re;
	}
	void readData(GameData*){}
	std::string getName(){return " ";}
	std::string getName(int team){
		std::string name;
		team==1?name= name_R1:name= name_R2;
		return name;
	}
	void setDC(HDC* pDC1,HDC*pDCObj1){
		pDC=pDC1;
		pDCObj=pDCObj1;
	}
	void setHandle(HWND* pWnd1,HINSTANCE* pInst1){
		pWnd=pWnd1;
		pInst=pInst1;
	}
	void draw();
};