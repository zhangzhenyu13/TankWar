#include"StatusWnd.h"

void StatusWnd::draw(){
	HDC hmem = CreateCompatibleDC(*pDC);//current dc
	HBITMAP hbmp=CreateCompatibleBitmap(*pDC,200,800);
	HBITMAP hbmpbk=LoadBitmap(*pInst,MAKEINTRESOURCE(ZONE_STATUS));
	HGDIOBJ hOldSel=SelectObject(hmem,hbmp);
	HBRUSH bg=CreateSolidBrush(RGB(10,50,30));
	HFONT font=CreateFont(
					20, // nHeight
					0, // nWidth
					0, // nEscapement
					0, // nOrientation
					FW_NORMAL, // nWeight
					FALSE, // bItalic
					FALSE, // bUnderline
					0, // cStrikeOut
					GB2312_CHARSET, // nCharSet
					OUT_DEFAULT_PRECIS, // nOutPrecision
					CLIP_DEFAULT_PRECIS, // nClipPrecision
					DEFAULT_QUALITY, // nQuality
					DEFAULT_PITCH | FF_SWISS,
					L"¿¬Ìå_GB2312" // nPitchAndFamily Arial
					);
	SelectObject(hmem,bg);
	Rectangle(hmem,0,0,200,800);
	SelectObject(hmem,hbmpbk);
	SelectObject(hmem,font);
	SetTextColor(hmem,RGB(255,0,0));
	SetBkMode(hmem,TRANSPARENT);
	
	//Team A
	TextOut(hmem,0,100,L"WE ARE TEAM A",strlen("WE ARE TEAM A"));
	for(int i=0;i<5;i++){
		int x=10,y=150+i*40;
		std::string s="LEVEL ";
		char n='0'+5-i;
		s.push_back(n);
		s+=" : ";
		n='0'+level_R1[4-i];
		s.push_back(n);
	    int len=MultiByteToWideChar(CP_ACP,0,s.c_str(),s.length(),NULL,0);
		LPWSTR info=new WCHAR[len];
		MultiByteToWideChar(CP_ACP,0,s.c_str(),s.length(),info,len);
		TextOut(hmem,x,y,info,len);
	}
	Rectangle(hmem,0,370,200,340);
	//Team B
	SetTextColor(hmem,RGB(0,0,255));
	TextOut(hmem,0,400,L"WE ARE TEAM B",strlen("WE ARE TEAM B"));
	for(int i=0;i<5;i++){
		int x=10,y=450+i*40;
		std::string s="LEVEL ";
		char n='0'+5-i;
		s.push_back(n);
		s+=" : ";
		n='0'+level_R2[4-i];
		s.push_back(n);
	    int len=MultiByteToWideChar(CP_ACP,0,s.c_str(),s.length(),NULL,0);
		LPWSTR info=new WCHAR[len];
		MultiByteToWideChar(CP_ACP,0,s.c_str(),s.length(),info,len);
		TextOut(hmem,x,y,info,len);
	}

	BitBlt(*pDCObj, 1200,0,200,750,//copy data between dc
				hmem, 0, 0,SRCCOPY);
	//release Mem
	DeleteObject(font);
	DeleteObject(bg);
	DeleteObject(hbmp);
	DeleteObject(hbmpbk);
	DeleteObject(hOldSel);
	DeleteDC(hmem);
}