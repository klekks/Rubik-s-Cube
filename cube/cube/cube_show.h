#include <windows.h>
#include "glut.h"

#pragma once
#ifndef CUBE_SHOW_H_INCLUDED
#define CUBE_SHOW_H_INCLUDED

void ShowPartOfCube(RCube cube, int x1, int x2, int y1, int y2, int z1, int z2);

void A_RCubeLeftPlus(RCube* cube, HDC hDC, char show);

void A_RCubeLeftMinus(RCube* cube, HDC hDC, char show);

void A_RCubeRightPlus(RCube* cube, HDC hDC, char show);

void A_RCubeRightMinus(RCube* cube, HDC hDC, char show);

void A_RCubeUpPlus(RCube* cube, HDC hDC, char show);

void A_RCubeUpMinus(RCube* cube, HDC hDC, char show);

void A_RCubeDownMinus(RCube* cube, HDC hDC, char show);

void A_RCubeDownPlus(RCube* cube, HDC hDC, char show);

void A_RCubeFrontPlus(RCube* cube, HDC hDC, char show);

void A_RCubeFrontMinus(RCube* cube, HDC hDC, char show);

void A_RCubeBackPlus(RCube* cube, HDC hDC, char show);

void A_RCubeBackMinus(RCube* cube, HDC hDC, char show);

void A_RCubeMiddleXPlus(RCube* cube, HDC hDC, char show);
void A_RCubeMiddleXMinus(RCube* cube, HDC hDC, char show);
void A_RCubelPlus(RCube* cube, HDC hDC, char show);
void A_RCubelMinus(RCube* cube, HDC hDC, char show);
void A_RCuberPlus(RCube* cube, HDC hDC, char show);
void A_RCuberMinus(RCube* cube, HDC hDC, char show);
void A_RCubefPlus(RCube* cube, HDC hDC, char show);
void A_RCubefMinus(RCube* cube, HDC hDC, char show);
void A_RCubedPlus(RCube* cube, HDC hDC, char show);
void A_RCubedMinus(RCube* cube, HDC hDC, char show);
void A_RCubeuPlus(RCube* cube, HDC hDC, char show);
void A_RCubeuMinus(RCube* cube, HDC hDC, char show);
void A_RCubeRotateXPlus(RCube* cube, HDC hDC, char show);
void A_RCubeRotateXMinus(RCube* cube, HDC hDC, char show);
void A_RCubeRotateYPlus(RCube* cube, HDC hDC, char show);
void A_RCubeRotateYMinus(RCube* cube, HDC hDC, char show);
void A_RCubeRotateZPlus(RCube* cube, HDC hDC, char show);
void A_RCubeRotateZMinus(RCube* cube, HDC hDC, char show);

#endif // CUBE_SHOW_H_INCLUDED
