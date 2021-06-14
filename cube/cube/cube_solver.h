#pragma once
#include "cube.h"


void Solve(RCube *cube, HDC hDC);
char* SolutionOLLPart(RCube cube);
char* SolutionPLLPart(RCube cube);
char* SolutionCrossPart(RCube cube);
char* SolutionF2L(RCube cube);
char* SolutionFL(RCube cube);
char* SolutionSL(RCube cube);
void MakeTransformation(RCube* cube, char* transf, HDC hdc, char show);