#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <time.h>

void config_res() { // 시작레지스트에 등록
	char path[1000];
	HKEY hKey;
	LONG res;
	GetModuleFileName(NULL, path, 1000); // 프로그램경로 구하기
	res = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey);
	// 시작 레지스트 열림여부 확인
	if (res == ERROR_SUCCESS) {
		// 열기성공
	}
	else {
		// 열기실패
		exit(0);
	}

	res = RegSetValueEx(hKey, TEXT("delKakaoad"), 0, REG_SZ, (BYTE*)path, strlen(path)); // 레지스트 등록 루틴 
	if (res == ERROR_SUCCESS) { // 레지스트 등록 성공

	}
	else { // 레지스트 등록 실패
		exit(0);
	}
	RegCloseKey(hKey); // 레지스트키 닫기
}

void chk_res_init() { // 시작레지스트에 등록되있는지 확인
	char path[1000];
	DWORD buffsize = 8192;
	LONG res;
	res = RegGetValue(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), "delkakaoad", RRF_RT_ANY, NULL, (PVOID)&path, &buffsize);
	if (res == ERROR_SUCCESS) // 시작 레지스트리에 이미 등록되있을시
	{

	}
	else // 시작 레지스트리에 등록이 되어있지 않을시 등록해주기
		config_res();
}

void res_function() // 레지스트리 설정 함수 
{
	chk_res_init(); // 레지스트리에 등록이되있나 확인하는함수
}

int main()
{
	HWND mainHnd, adHnd, mainConsoleHnd;
	mainConsoleHnd = GetConsoleWindow();
	ShowWindow(mainConsoleHnd, SW_HIDE); // 메인콘솔 숨기기
	res_function(); // 레지스트리 관련 확인함수

	do {
		mainHnd = FindWindow(NULL, TEXT("카카오톡"));
	} while (mainHnd == NULL);
	do {
		adHnd = FindWindowEx(mainHnd, 0, TEXT("EVA_Window"), 0);
	} while (adHnd == NULL);
	Sleep(100);
	ShowWindow(adHnd, SW_HIDE);
	return 0;
}
