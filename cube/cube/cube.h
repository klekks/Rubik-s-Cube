#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "glut.h"
#include "../framework/structures.h"
#include "../framework/queue.h"
#include "../params.h"
#include <Windows.h>

#define RCubeSideLength 3
#define RCubeSize 27      // pow(RCubeSideLength, 3)
#define CubeSides 6

typedef enum {RCNoColor, RCWhite, RCGreen, RCRed, RCBlue, RCOrange, RCYellow} RCubeColor;
typedef enum {           Down = 0,Left=1, Front=2,Right=3,Back=4,   Up=5 }   RCubeSide;


typedef struct {
    char sides;
    RCubeColor color[CubeSides];
    char position;
    char solved_position;
} RCubeSegment;

void swap(RCubeSegment*, RCubeSegment*);

typedef struct {
    RCubeSegment segment[RCubeSize];
}RCube;

typedef struct {
    char r, g, b;
}RColor;


RCube* CreateCube();
Queue* ParseNotation(char* str);
Queue* Optimize(char* inp);
void MixCube(RCube**, HDC);
void RCubeLeftPlus(RCube* cube);
void RCubeLeftMinus(RCube* cube);
void RCubeRightPlus(RCube* cube);
void RCubeRightMinus(RCube* cube);
void RCubeUpPlus(RCube* cube);
void RCubeUpMinus(RCube* cube);
void RCubeDownMinus(RCube* cube);
void RCubeDownPlus(RCube* cube);
void RCubeFrontPlus(RCube* cube);
void RCubeFrontMinus(RCube* cube);
void RCubeBackPlus(RCube* cube);
void RCubeBackMinus(RCube* cube);
void RCubeMiddleXPlus(RCube* cube);
void RCubeMiddleXMinus(RCube* cube);
void RCubeMiddleYPlus(RCube* cube);
void RCubeMiddleYMinus(RCube* cube);
void RCubeMiddleZPlus(RCube* cube);
void RCubeMiddleZMinus(RCube* cube);
void RCubelPlus(RCube* cube);
void RCubelMinus(RCube* cube);
void RCubedPlus(RCube* cube);
void RCubedMinus(RCube* cube);
void RCuberPlus(RCube* cube);
void RCuberMinus(RCube* cube);
void RCubeRotateXPlus(RCube* cube);
void RCubeRotateXMinus(RCube* cube);
void RCubeRotateYPlus(RCube* cube);
void RCubeRotateYMinus(RCube* cube);
void RCubeRotateZPlus(RCube* cube);
void RCubeRotateZMinus(RCube* cube);

#endif // CUBE_H_INCLUDED
