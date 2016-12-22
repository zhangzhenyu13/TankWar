#include"SelectMode.h"
#include"resource.h"
//select mode

extern SelectData myMode;
BOOL CALLBACK SelectModeProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HWND difText = GetDlgItem(hWnd, IDC_EDITD), 
		playerText = GetDlgItem(hWnd, IDC_EDITP),
		stageText=GetDlgItem(hWnd,IDC_EDITL);
	static int playerNum = 1, difLevel = 1,Stage=1;
	LPWSTR num[] = { L"0",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10",
	L"11",L"12",L"13",L"14",L"15",L"16",L"17",L"18",L"19",L"20",L"21",L"22",
	L"23",L"24",L"25",L"26",L"27",L"28",L"29",L"30"};
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			myMode.gameStage = Stage;
			myMode.gameLevel = difLevel;
			myMode.gamePlayer = playerNum;
			EndDialog(hWnd, TRUE);
			break;
		case IDRESET:
			playerNum = 1;
			difLevel = 1;
			Stage = 1;
			break;
		case IDC_ADDP:
			if (playerNum<SelectData::MAXPlayer)
				playerNum++;
			SetWindowText(playerText,num[playerNum]);
			break;
		case IDC_MINUSP:
			if (playerNum > 0)
				playerNum--;
			SetWindowText(playerText, num[playerNum]);
			break;
		case IDC_ADDD:
			if (difLevel < SelectData::MAXDif)
				difLevel++;
			SetWindowText(difText,num[difLevel]);
			break;
		case IDC_MINUSD:
			if (difLevel > 0)
				difLevel--;
			SetWindowText(difText, num[difLevel]);
			break;
		case IDC_ADDL:
			if (Stage < SelectData::MAXLevel)
				Stage++;
			SetWindowText(stageText,num[Stage]);
			break;
		case IDC_MINUSL:
			if (Stage > 0)
				Stage--;
			SetWindowText(stageText, num[Stage]);
			break;
		}
		break;
	case WM_INITDIALOG:
		playerNum = 1;
		Stage = 1;
		difLevel = 1;
		SetWindowText(hWnd, L"SELECT GAME MODE");
		SetWindowText(difText, num[difLevel]);
		SetWindowText(playerText, num[playerNum]);
		SetWindowText(stageText,num[Stage]);
		break;
	case WM_CLOSE:
		EndDialog(hWnd, FALSE);
		break;
	default:
		DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	
	return TRUE;
}