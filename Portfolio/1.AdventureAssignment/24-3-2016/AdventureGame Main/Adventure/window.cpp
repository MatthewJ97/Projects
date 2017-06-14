////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		Window																			////
////																									////
////		Purpose:	controls all window events														////
////																									////
////		Authors:	Roger Keating with assistance from Mitchell Croft								////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "window.h"
#include "string.h"
#include <tchar.h>

// These are the static class variables 
int Window::mScreenWidth;
int Window::mScreenHeight;
eColor Window::mCurrentColor;
HANDLE Window::mhSTDOut;



// Initialise the console window 
bool Window::Initialise(int a_width, int a_height, wchar_t *name)
{
	// set the width and height of the project
	mScreenWidth  = a_width;
	mScreenHeight = a_height;

	// setting up the actual window
	mhSTDOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (mhSTDOut == INVALID_HANDLE_VALUE) {
		cout << "ERROR: COULD NOT GET INPUT HANDLE!" << endl;
		return EXIT_FAILURE;
	}

	SMALL_RECT window;
	window.Top		= 0;
	window.Left		= 0;
	window.Bottom	= mScreenHeight - 1;
	window.Right	= mScreenWidth  - 1;
	HANDLE mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer	= { (short)mScreenWidth, (short)mScreenHeight };
	SetConsoleScreenBufferSize(mHandle, buffer);
	SetConsoleWindowInfo(mHandle, TRUE, &window);

	SetCursorVisibility(false);

	// put a name on the console window
	SetConsoleTitle(name);

	// Get the console handle
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, WS_MAXIMIZE);

	return EXIT_SUCCESS;
}

// show/hide the cursor 
void Window::SetCursorVisibility(bool a_show)
{
	CONSOLE_CURSOR_INFO lCursor;
	GetConsoleCursorInfo(mhSTDOut, &lCursor);
	lCursor.bVisible = a_show;
	SetConsoleCursorInfo(mhSTDOut, &lCursor);
}

// changes the color of the drawn text
void Window::SetTextColor(eColor a_color)
{
	SetConsoleTextAttribute(mhSTDOut, a_color);
}

// sets the position where the next character will be drawn
BOOL Window::SetXY(int a_x, int a_y)
{
	COORD c = { (short)a_x, (short)a_y };
	return SetConsoleCursorPosition(mhSTDOut, c);
}

// draw a character at position (x, y)
void Window::DrawChar(int a_x, int a_y, unsigned char pChar)
{
	// if the character is out of bounds then return
	if (a_x < 0 || a_x > mScreenWidth || a_y < 0 || a_y > mScreenHeight) {
		return;
	}

	BOOL result = SetXY(a_x, a_y);

	cout << pChar;
}
void Window::DrawEncryptChar(int a_x, int a_y, unsigned char pChar)
{
	// if the character is out of bounds then return
	if (a_x < 0 || a_x > mScreenWidth || a_y < 0 || a_y > mScreenHeight) {
		return;
	}

	int randCol = rand() % 3;
	for (int i = 0; i < 5; i++) {
		if (randCol == 1) {
			SetTextColor(RED);
		}
		else if(randCol == 0) {
			SetTextColor(EVIL);
		}
		else {
			SetTextColor(EVIL2);
		}
		BOOL result = SetXY(a_x, a_y);
		char Rand = rand() % 90 + 160;
		cout << Rand;
		Sleep(2);

	}
	SetTextColor(WHITE);
	SetXY(a_x, a_y);
	cout << pChar;
}
void Window::DrawEncryptLine(int a_x, int a_y, eColor a_color, const char *a_line, int a_max)
{
	// if the character is out of bounds then return
	if (a_x < 0 || a_x > mScreenWidth || a_y < 0 || a_y > mScreenHeight)
		return;

	// must increment line after reaching the p_max character
	SetTextColor(a_color);
	int charCount = 0, textCount = 0;
	int x = a_x;
	int y = a_y;
	// lets print this out in line form
	int lastBreak = 0;

	while (true) {
		// find the number of characters to print out
		int doBreak = 1000;
		int k;
		for (k = charCount; a_line[k] != '\0'; ++k) {
			if (k - lastBreak == a_max) break;
			if (a_line[k] == ' ') doBreak = k;
			if (a_line[k] == '\n') {
				doBreak = k;
				break;
			}
		}
		if (a_line[k] == '\0') doBreak = k;
		lastBreak = doBreak;
		if (a_line[charCount] == ' ' || a_line[charCount] == '\n') charCount++;

		if (a_line[charCount] == 'D') {
			short cc = 10;
		}
		for (int k = charCount; a_line[k] != '\0'; ++k) {
			if (k >= doBreak) break;
			DrawEncryptChar(++x, y, a_line[charCount++]);
			SetTextColor(a_color);
		}
		y++;
		x = a_x;
		if (a_line[charCount] == '\0') break;
	}
}

// draw a text line block at position (x, y) in color at block width (a_max)
void Window::DrawLine(int a_x, int a_y, eColor a_color,const char *a_line, int a_max)
{
	// if the character is out of bounds then return
	if (a_x < 0 || a_x > mScreenWidth || a_y < 0 || a_y > mScreenHeight)
		return;

	// must increment line after reaching the p_max character
	SetTextColor(a_color);
	int charCount = 0, textCount = 0;
	int x = a_x;
	int y = a_y;
	// lets print this out in line form
	int lastBreak = 0;

	while (true) {
		// find the number of characters to print out
		int doBreak = 1000;
		int k;
		for (k = charCount; a_line[k] != '\0'; ++k) {
			if (k - lastBreak == a_max) break;
			if (a_line[k] == ' ') doBreak = k;
			if (a_line[k] == '\n') {
				doBreak = k;
				break;
			}
		}
		if (a_line[k] == '\0') doBreak = k;
		lastBreak = doBreak;
		if (a_line[charCount] == ' ' || a_line[charCount] == '\n') charCount++;

		if (a_line[charCount] == 'D') {
			short cc = 10;
		}
		for (int k = charCount; a_line[k] != '\0'; ++k) {
			if (k >= doBreak) break;
			DrawChar(++x, y, a_line[charCount++]);
		}
		y++;
		x = a_x;
		if (a_line[charCount] == '\0') break;
	}
}

// clear the screen
void Window::ClearScreen()
{
	system("CLS");
}

// clear a specific rectangle of the screen
void Window::ClearSection(Rect a_location)
{
	SetTextColor(WHITE);

	for (int X = a_location.x; X <= a_location.x + a_location.width; X++) {
		for (int Y = a_location.y; Y <= a_location.y + a_location.height; Y++) {
			SetXY(X, Y);
			cout << " ";
		}
	}
}


// draws a rectangle in a specified color
void Window::DrawBorder(Rect a_location, eColor a_color)
{
	SetTextColor(a_color);

	// top corner
	DrawChar(a_location.x, a_location.y, char(201));													//TOP LEFT CORNER

	for (int X = a_location.x + 1; X < a_location.x + a_location.width - 1; X++) 						//TOP BORDER
		DrawChar(X, a_location.y, char(205));

	// top right corner
	DrawChar(a_location.x + a_location.width - 1, a_location.y, char(187));								//TOP RIGHT CORNER

	DrawChar(a_location.x, a_location.y + a_location.height - 2, char(200));							//BOTTOM LEFT CORNER

	for (int X = a_location.x + 1; X < a_location.x + a_location.width - 1; X++) 						//BOTTOM BORDER
		DrawChar(X, a_location.y + a_location.height - 2, char(205));


	DrawChar(a_location.x + a_location.width - 1, a_location.y + a_location.height - 2, char(188));		//BOTTOM RIGHT CORNER

	for (int Y = a_location.y + 1; Y < a_location.y + a_location.height - 2; Y++) {
		DrawChar(a_location.x, Y, char(186));															//LEFT BORDER
		DrawChar(a_location.x + a_location.width - 1, Y, char(186));									//RIGHT BORDER
	}
}

void Window::DrawBentCorridor(Rect a_location, eColor a_color)
{
	SetTextColor(a_color);

	// top corner
	DrawChar(a_location.x, a_location.y, char(201));													//TOP LEFT CORNER

	for (int X = a_location.x + 1; X < a_location.x + a_location.width - 1; X++) 						//TOP BORDER
		DrawChar(X, a_location.y, char(205));


	for (int X = a_location.x + a_location.height; X < a_location.x + a_location.width - 1; X++) 						//BOTTOM BORDER
		DrawChar(X, a_location.y + a_location.height-2 , char(205));

//down corridor


	for (int Y = a_location.y + 1; Y < a_location.y + a_location.width + 5 - 1; Y++) 						//TOP BORDER
		DrawChar( a_location.x, Y, char(186));


	for (int Y = a_location.y + a_location.height - 1; Y < a_location.y + a_location.width +5 - 1; Y++) 						//BOTTOM BORDER
		DrawChar( a_location.x + a_location.height, Y, char(186));

	DrawChar(a_location.x + a_location.height, a_location.y + a_location.height-2, char(201));
}


// get the mouse position
COORD Window::getMousePos()
{
	COORD pt = { -1, -1 };
	HWND hWnd = GetConsoleWindow();

	POINT pos = { 0, 0 };

	if (GetCursorPos(&pos)) {
		if (ScreenToClient(hWnd, &pos)) {
			RECT getRekt = { 0, 0 };
			GetClientRect(hWnd, &getRekt);

			int consoleWidth = mScreenWidth;
			int consoleHeight = mScreenHeight;

			int clientWidth = getRekt.right - getRekt.left;
			int clientHeight = getRekt.bottom - getRekt.top;

			pt.X = (short)((pos.x *consoleWidth) / clientWidth);
			pt.Y = (short)((pos.y *consoleHeight) / clientHeight);

			return pt;
		}
	}
	return pt;
}
