#include "stdafx.h"
#include "Windows.h"
#include "iostream"
#include "string"

using namespace std;

string getClipboard() {
	OpenClipboard(NULL);
	HANDLE h;
	h = GetClipboardData(CF_TEXT);
	CloseClipboard();
	return (char *)h;
}

void printString(string message) {
	
	HKL currentKBL = GetKeyboardLayout(0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wScan = 0;

	for (int i = 0; i < message.size(); i++) {
		WORD key = VkKeyScanEx(message[i], currentKBL);
		ip.ki.dwFlags = 0;
		ip.ki.wVk = key;
		SendInput(1, &ip, sizeof(INPUT));
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}

}

void detectCopy() {
	while (true) {
		Sleep(100);
		if (GetAsyncKeyState(VK_CONTROL))
		{
			if (GetKeyState('A') & GetKeyState('S') &0x8000)
			{
				printString(getClipboard());
			}
		}
	}
}

int main()
{
	FreeConsole();
	detectCopy();
}

