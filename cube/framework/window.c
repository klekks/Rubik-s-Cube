#include "glut.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "../cube/cube.h"

void WndResize(int x, int y) {
    glViewport(0, 0, x, y);
    float k = x / (float) y;
    float sz = 0.1;
    glLoadIdentity();
    glFrustum(-k*sz, k*sz, -sz, sz, 2*sz, 100);
}

PWSTR LoadFile(HWND hWnd) {
    OPENFILENAME ofn;

    wchar_t formats[] = L"Rubik's Cube(*.RUBIKSCUBE)\0*.RUBIKSCUBE\0\0";

    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = formats;
    ofn.lpstrCustomFilter = formats;
    ofn.nMaxCustFilter = 256;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
    ofn.lpstrFile  = calloc(512, sizeof(char));
    ofn.nMaxFile  = 512;
    ofn.nFilterIndex = 1;
	if (!GetOpenFileName(&ofn)) printf("\nERROR %d\n", CommDlgExtendedError());
	return ofn.lpstrFile;
}

PWSTR UploadFile(HWND hWnd) {
    OPENFILENAME ofn;

    wchar_t formats[] = L"Rubik's Cube(*.RUBIKSCUBE)\0*.RUBIKSCUBE\0\0";
    wchar_t *file = calloc(512, sizeof(wchar_t));
    if (!file) return;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = formats;
    //ofn.lpstrCustomFilter = formats;
    ofn.nMaxCustFilter = 256;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
    ofn.lpstrFile = file;
    ofn.nMaxFile  = 512;
    ofn.nFilterIndex = 1;
	if (!GetSaveFileName(&ofn)) printf("\nERROR %d\n", CommDlgExtendedError());

    if (!strstr(file, L".rubikscube")) {
        wcscat(file, L".rubikscube");
    }
    for (int i = 0; i < 512; i++)
        printf("%wc", file[i]);
	return ofn.lpstrFile;
}

unsigned QuickCheckSum(char* buff, unsigned size) {
    unsigned res = 0;
    for (int i = 0; i < size; i++) res += buff[i];
    return res;
}

RCube* LoadCube(wchar_t * path, HWND hwnd){
    RCube *cube = calloc(1, sizeof(RCube));
    FILE* file = NULL;

    _wfopen_s(&file, path, L"rb");

    if (!cube) ExitProcess(-1);
    if (!file) {
            free(cube);
            MessageBox(hwnd, L"File not found.", L"Import Error", MB_OK);
            return NULL;
    }
    unsigned key, cs;

    fread(&key, sizeof(unsigned), 1, file);

    if (key != 4831001) {
            free(cube);
        MessageBox(hwnd, L"Invalid backup format!", L"Import Error", MB_OK);
        return NULL;
    }
    //fread_s(cube, sizeof(RCube), sizeof(RCube), 1, file);
    fread(cube, sizeof(RCube), 1, file);
    fread(&cs, sizeof(unsigned), 1, file);

    if (cs != QuickCheckSum(cube, sizeof(RCube))) {
        free(cube);
        MessageBox(hwnd, L"Invalid backup format!", L"Import Error", MB_OK);
        return NULL;
    }

    fclose(file);
    if (!cube) {
        free(cube);
        MessageBox(hwnd, L"Invalid backup format!", L"Import Error", MB_OK);
        return NULL;
    }
    return cube;
}


void SaveCube(wchar_t *path, RCube cube) {
    FILE* file = NULL;
    _wfopen_s(&file, path, L"wb");
    if (!file) {
            MessageBox(NULL, L"File not found.", L"Export Error", MB_OK);
            return NULL;
    }
    unsigned key = 4831001;
    unsigned check_sum = QuickCheckSum(&cube, sizeof(RCube));

    fwrite(&key, sizeof(unsigned), 1, file);
    fwrite(&cube, sizeof(RCube), 1, file);
    fwrite(&check_sum, sizeof(unsigned), 1, file);

    fclose(file);
}
