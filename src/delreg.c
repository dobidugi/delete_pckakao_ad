#include <Windows.h>
#include <stdio.h>

void del_regs() { // 레지스트에 등록된값을 삭제
	LONG res;
	HKEY hKey;
	res = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS, &hKey);
	if (res == ERROR_SUCCESS) { // 레지스트에 등록이 되있을시
		res = RegDeleteValue(hKey, TEXT("delKakaoad"));
		if (res == ERROR_SUCCESS){
			printf("성공적으로 삭제가 되었습니다.\n");
		}
		else { // 레지스트에 등록이 안되있을시.
			printf("삭제실패.\n");
			system("pause");
		}
	}
	else { // 레지스트 파일을 열수 없을시
		printf("레지스트 열기 실패.\n");
		system("pause");
		exit(0);
	}
}

void chk_res_init() { // 시작레지스트에 등록되있는지 확인
	char path[1000];
	DWORD buffsize = 8192;
	LONG res;
	res = RegGetValue(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), "delkakaoad", RRF_RT_ANY, NULL, (PVOID)&path, &buffsize);
	if (res == ERROR_SUCCESS) // 시작 레지스트리에 이미 등록되있을시
	{
		del_regs();
	}
	else // 시작 레지스트리에 등록이 되어있지 않을시 등록해주기
	{
		printf("레지스트에 등록이 되있지않아 삭제할수 없습니다.\n");
		system("pause");
		exit(0);
	}
}

void res_function() // 레지스트리 설정 함수 
{
	chk_res_init(); // 레지스트리에 등록여부 확인하는함수
}

int main()
{
	res_function();
	system("pause");
	return 0;
}
