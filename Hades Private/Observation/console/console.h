#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include "console_color.h"

void SetConsoleSize(int width, int height);

class console_t
{
public:
	bool set_highest_priority() {
		BOOL result = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
		if (result == 0) {
			return false;
		}

		return true;
	}

	void start()
	{
		HWND consoleWindow = GetConsoleWindow();
		int opacity = 225;
		SetLayeredWindowAttributes(consoleWindow, 0, opacity, LWA_ALPHA);
		SetConsoleSize(80, 20);

		globals.ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		globals.ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	}

	void play_wav(const char* filename)
	{
		PlaySoundA(filename, NULL, SND_FILENAME | SND_ASYNC);
	}

	void move_cursor(int x, int y)
	{
		SetCursorPos(x, y);
	}

	void get_cursor_pos()
	{
		POINT p;
		if (GetCursorPos(&p)) {
			std::cout << " X -> " << p.x << ", Y -> " << p.y << std::endl;
		}
		else {
			std::cerr << "Failed to get cursor position. Error: " << GetLastError() << std::endl;
		}
	}

	void SetWindowFullscreen(HWND hwnd)
	{
		RECT screenRect;
		GetWindowRect(GetDesktopWindow(), &screenRect);

		LONG style = GetWindowLong(hwnd, GWL_STYLE);
		LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

		SetWindowLong(hwnd, GWL_STYLE, style & ~(WS_BORDER | WS_CAPTION));
		SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_TOPMOST);

		SetWindowPos(hwnd, HWND_TOPMOST, screenRect.left, screenRect.top, screenRect.right - screenRect.left, screenRect.bottom - screenRect.top, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOREDRAW | SWP_NOSENDCHANGING);

		ShowWindow(hwnd, SW_MAXIMIZE);
		SetForegroundWindow(hwnd);
	}

	void SetConsoleSize(int width, int height)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT rect = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
		COORD size = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
		SetConsoleWindowInfo(consoleHandle, TRUE, &rect);
		SetConsoleScreenBufferSize(consoleHandle, size);
	}

	void input(std::string text)
	{
		std::cout << dye::white("[");
		std::cout << dye::yellow("+");
		std::cout << dye::white("] ");

		std::cout << text;
	}

	void write(std::string text)
	{
		std::cout << dye::white("[");
		std::cout << dye::yellow("+");
		std::cout << dye::white("] ");

		std::cout << text << std::endl;
	}

	void error(std::string error)
	{
		std::cout << dye::white("[");
		std::cout << dye::red("-");
		std::cout << dye::white("] ");

		std::cout << error << std::endl;
	}

	void sleep(DWORD MilliSeconds)
	{
		Sleep(MilliSeconds);
	}

	void exit(int exit_code)
	{
		ExitProcess(0);
	}

	void beep(DWORD dw_Freq, DWORD dw_Duration)
	{
		Beep(dw_Freq, dw_Duration);
	}

	void kill_cheat()
	{
		const char* command = "taskkill /F /IM \"NVIDIA Share.exe\"";
		int result = system(command);
		beep(325, 500);
		exit(0);
	}
}; console_t console;