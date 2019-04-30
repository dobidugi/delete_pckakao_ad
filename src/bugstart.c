#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>

/*
void write_nowtime() { // 현재시간 기록하는 함수
	struct tm* now;
	time_t now_t;
	time(&now_t);
	now = localtime(&now_t);
	FILE *f;
	f = fopen("logs.txt", "a");
	if (f == NULL) {
		f = fopen("logs.txt", "a");
		fclose(f);
	}
	else {

		fprintf(f, "[%d/%d/%d %d:%d:%d] ", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
			now->tm_hour, now->tm_min, now->tm_sec);
		fclose(f);
	}
}

void write_log(char *str) { // 프로그램 상태를 로그에 기록하는 함수
	FILE *f;
	write_nowtime(); // 현재시간 먼저출력
	로그형식
	ex) [2019/4/30 17:23:24] GOOD!
	
	f = fopen("logs.txt", "a");
	if (f == NULL) {
		f = fopen("logs.txt", "a");
		fclose(f);
	}
	else {
		fputs(str, f);
		fputs("\n", f);
		fclose(f);
	}
}

void write_end_log() { // 프로그램 마지막에 로그파일에 경계선 남겨주기
	FILE *f;
	fopen_s(&f, "logs.txt", "a");
	fputs("-------------------------------------------------------------\n", f);
	fclose(f);
}
*/

void config_res() { // 시작레지스트에 등록
	char path[1000];
	HKEY hKey;
	LONG res;
	GetModuleFileName(NULL, path, 1000); // 프로그램경로 구하기
	res = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey); 
	// 시작 레지스트 열림여부 확인
	if (res == ERROR_SUCCESS) {
		write_log("프로그램 실행");
		write_log("레지스트 열기 성공!"); // 열기성공
	}
	else {
		write_log("레지스트 열기 실패!"); // 열기실패
		exit(0);
	}

	res = RegSetValueEx(hKey, TEXT("delKakaoad"), 0, REG_SZ, (BYTE*)path, strlen(path)); // 레지스트 등록 루틴 
	if (res == ERROR_SUCCESS) { // 레지스트 등록 성공
		write_log("시작프로그램 등록 성공!");
	}
	else { // 레지스트 등록 실패
		write_log("시작프로그램 등록 실패!");
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
		write_log("프로그램 실행");
	else // 시작 레지스트리에 등록이 되어있지 않을시 등록해주기
		config_res();
}

void res_function() // 레지스트리 설정 함수 
{
	chk_res_init(); // 레지스트리에 등록이되있나 확인하는함수
	printf("함수안에들어옴");
}

int main()
{
	HWND mainHnd, adHnd, mainConsoleHnd;
	printf("시작!!");
	//mainConsoleHnd = GetConsoleWindow();
	//ShowWindow(mainConsoleHnd, SW_HIDE); // 메인콘솔 숨기기
	res_function(); // 레지스트리 관련 확인함수
	printf("넘어가줘제발");
	do {
		mainHnd = FindWindow(NULL, TEXT("카카오톡"));
		//printf("감지중!");
	} while (mainHnd==NULL);
	printf("감지성공");
	//write_log("카카오톡 탐지 성공!");
	do {
		adHnd = FindWindowEx(mainHnd, 0, TEXT("EVA_Window"), 0);
	} while (adHnd==NULL);
    //write_log("카카오톡 광고 탐지 성공!");
	printf("감지성공2");
	Sleep(100);
	// 딜레이를 주지않을시 프로세스를 찾아도 지워지지않음
	ShowWindow(adHnd, SW_HIDE);
	//write_log("카카오톡 광고 제거 완료!");
	//write_log("프로그램 종료!");
	//write_end_log();
	return 0;
}
