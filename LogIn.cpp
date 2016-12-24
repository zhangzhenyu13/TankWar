#include"LogIn.h"
#include"resource.h"
#include<tchar.h>
#include<fstream>
#include<iostream>
using namespace std;
extern wstring username;
extern wstring password;
BOOL CALLBACK LogInProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HWND usernameText = GetDlgItem(hWnd, IDC_EDIT_USERNAME),
		passwordText = GetDlgItem(hWnd, IDC_EDIT_PASSWORD);
	wstring path;
	WCHAR newname[20], newpassword[20];
	wfstream file;
	bool pass = true;
	long i = 0;
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_REG:
			GetWindowText(usernameText, newname, 20);
			GetWindowText(passwordText, newpassword, 20);
			if (newname[0] == '\0') {
				//MessageBox(hWnd, L"Please input your username", L"Register", MB_OK);
				break;
			}
			if (newpassword[0] == '\0') {
				//MessageBox(hWnd, L"Please input your password", L"Register", MB_OK);
				break;
			}
			path = TEXT("userfile\\");
			path += newname;
			path += L".tankUser";
			file.open(path.c_str(), ios::in);
			if (file) {
				//MessageBox(hWnd, L"This username has been used", L"Register", MB_OK);
				SetWindowText(usernameText, NULL);
				SetWindowText(passwordText, NULL);
				break;
			}
			file.open(path.c_str(), ios::out|ios::app);
			file << newpassword << endl;
			username = newname;
			//MessageBox(hWnd, L"Succed", L"Register", MB_OK);
			EndDialog(hWnd, TRUE);
			break;
		case IDOK:
			GetWindowText(usernameText, newname, 20);
			GetWindowText(passwordText, newpassword, 20);
			if (newname[0] == '\0') {
				//MessageBox(hWnd, L"Please input your username", L"Log In", MB_OK);
				break;
			}
			if (newpassword[0] == '\0') {
				//MessageBox(hWnd, L"Please input your password", L"Log In", MB_OK);
				break;
			}
			path = TEXT("userfile\\");
			path += newname;
			path+=L".tankUser";
			file.open(path.c_str(), ios::in);
			if (!file) {
				//MessageBox(hWnd, L"Wrong username", L"Log In", MB_OK);
				break;
			}
			WCHAR rightPassword[20];
			file.getline(rightPassword, 20);
			for (int i = 0; rightPassword[i] != '\0' || newpassword[i] != '\0'; i++) {
				if (rightPassword[i] != newpassword[i]) {
					pass = false;
					break;
				}
			}
			if (pass) {
				username = newname;
				//MessageBox(hWnd, L"Succeed", L"Log In", MB_OK);
				EndDialog(hWnd, TRUE);
			}
			else {
				//MessageBox(hWnd, L"Wrong password", L"Log In", MB_OK);
			}

			break;
		case IDCANCEL:
			EndDialog(hWnd, FALSE);
			break;
		//case ID_REGISTER:
			break;
		default:
			break;
		}
		break;
	case WM_INITDIALOG:
		SetWindowText(hWnd, L"LOG IN");
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