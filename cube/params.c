#include "params.h"
#include "glut.h"
#include "cube/cube.h"
#include <Windows.h>
#include "framework/queue.h"


Queue transformation_queue = {0,0,0};
unsigned ROTATION_DELAY = 1; // temp of rotation D_ALPHA*max(ROTATION_DELAY, 20) = DURATION 

