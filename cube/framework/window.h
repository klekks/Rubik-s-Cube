#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "../cube/cube.h"

void WndResize(int x, int y);
PWSTR LoadFile(HWND hWnd);
PWSTR UploadFile(HWND hWnd);
RCube* LoadCube(wchar_t* path, HWND hwnd);
void SaveCube(wchar_t* path, RCube cube);
#endif // WINDOW_H_INCLUDED
