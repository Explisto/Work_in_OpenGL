#include <windows.h>
#include <string>

void MainWndAddMenus(HWND hWnd);

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Windows", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 270, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	//TerminateThread(readThread, 0);
	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) 
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 

{
	switch (msg) {
	case WM_COMMAND:

		switch (wp) 
		{

		}

	case WM_CREATE:
		MainWndAddMenus(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd) 
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();

	//AppendMenu(SubMenu, MF_STRING, OnMenuAction1, L"Clear");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	//AppendMenu(SubMenu, MF_STRING, OnMenuAction2, L"Save");
	//AppendMenu(SubMenu, MF_STRING, OnMenuAction3, L"Load");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	//AppendMenu(SubMenu, MF_STRING, OnMenuAction4, L"Exit");

	SetMenu(hWnd, RootMenu);
}
/*
void MainWndAddWidgets(HWND hWnd) {

	hStaticControl = CreateWindowA("static", "WINDOWS GRADIENTS", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 5, 220, 30, hWnd, NULL, NULL, NULL);
	//hEditControl = CreateWindowA("edit", "This is EDIT control", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 5, 40, 470, 120, hWnd, NULL, NULL, NULL);
	windowRectangle = { 5 + 470, 40, 5, 40 + 120 };

	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 5, 170, 100, 30, hWnd, (HMENU)DlgIndexColorR, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 110, 170, 100, 30, hWnd, (HMENU)DlgIndexColorG, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 215, 170, 100, 30, hWnd, (HMENU)DlgIndexColorB, NULL, NULL);

	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Set color", WS_VISIBLE | WS_CHILD | ES_CENTER, 130, 5, 65, 30, hWnd, (HMENU)OnReadColor, NULL, NULL);
}

void SaveData(LPCSTR path) {
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLenth = GetWindowTextLength(hEditControl) + 1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth);

	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[] data;
}
void LoadData(LPCSTR path) {
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hEditControl, Buffer);

	CloseHandle(FileToLoad);
}
void SetOpenFileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "D:/SavesC++/OUR Project/Release";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}
void SetWindowStatus(std::string status) {
	SetWindowTextA(hStaticControl, status.c_str());
}
*/