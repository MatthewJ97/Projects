#ifndef WINDOW_H_
#define WINDOW_H_
// Full version

#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include <conio.h>
#include <string>
#include <vector>


using namespace std;

enum {ONE = 1, TWO = 1, THREE, FOUR};

typedef unsigned int uint;

enum eColor : char
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKMAGENTA,
	DARKYELLOW,
	LIGHTGRAY,
	GRAY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
	EVIL = 75,
	EVIL2 = 80
};

struct Rect
{
	//POSITION AND SIZE OF THE 2D SHAPE
	int x, y, width, height;
};

class Window
{
public:
	static bool Initialise(int a_width, int a_height, wchar_t *name);
	static void SetCursorVisibility(bool pShow);
	static void SetTextColor(eColor pColor);
	static BOOL SetXY(int pX, int pY);
	static void DrawChar(int pX, int pY, unsigned char pLine);
	static void DrawEncryptChar(int pX, int pY, unsigned char pLine);
	static void DrawLine(int pX, int pY, eColor pColor,const char *pChar, int p_max);
	static void DrawEncryptLine(int pX, int pY, eColor pColor, const char *pChar, int p_max);
	static void ClearScreen();
	static void ClearSection(Rect pLocation);
	static void DrawBorder(Rect pLocation, eColor pColor);
	static void DrawBentCorridor(Rect a_location, eColor a_color);
	// getters
	static COORD Window::getMousePos();
	static int getRoomHeight() { return mScreenHeight; }
	static int getRoomWidth() { return mScreenWidth; }
private:
	//static COORD mBuffer;
	static int mScreenWidth;
	static int mScreenHeight;
	static eColor mCurrentColor;
	//static COORD mBuffer;
	static HANDLE mhSTDOut;

};


#endif //WINDOW_H_