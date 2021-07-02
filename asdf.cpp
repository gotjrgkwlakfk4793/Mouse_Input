#include <Windows.h> // 필요한 헤더 파일
#include <stdio.h>


// 여기부터 그대로 넣을 것 (main 함수 위에)
HWND wnd;
TEXTMETRIC tmetrix;

void InitSystem()
{
	DWORD prev_mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	wnd = GetConsoleWindow();
	HDC dc = GetDC(wnd);
	GetTextMetrics(dc, &tmetrix);
	ReleaseDC(wnd, dc);

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void GetXY(POINT* pt)
{
	GetCursorPos(pt);
	ScreenToClient(wnd, pt);
	pt->x /= tmetrix.tmAveCharWidth;
	pt->y /= tmetrix.tmHeight;
}

inline bool CheckClick()
{
	return GetForegroundWindow() == wnd && GetAsyncKeyState(VK_LBUTTON);
}
// 여기까지 그대로 넣을 것

int main()  // 예제
{
	POINT pt;

	InitSystem(); // 초기화 (GetXY 사용 전에 실행해야 함)

	while (true)
	{
		if (CheckClick()) // 클릭했는지 확인
		{
			GetXY(&pt); // 화면 상의 X, Y 값 얻기
			printf(" (%d , %d) \n", pt.x, pt.y); // X 값 : pt.x  Y 값 : pt.y
		}
	}
}
