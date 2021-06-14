#include "cube.h"
#include "cube_show.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



#define NOTATION_SYMBOLS "FRUDBLfrudblxyz'123456789S"

extern unsigned ROTATION_DELAY;

void swap(RCubeSegment* a, RCubeSegment* b) {
	RCubeSegment c = *a;
	*a = *b;
	*b = c;
}

RCube* CreateCube() {
	RCube* cube = calloc(1, sizeof(RCube));
	if (!cube) return NULL;

	for (int i = 0; i < RCubeSize; i++) {
		cube->segment[i].position = i;
		cube->segment[i].solved_position = i;

		if (i < 9) cube->segment[i].color[Down] = RCWhite;
		if (i > 17) cube->segment[i].color[Up] = RCYellow;
		if (i % 9 < 3) cube->segment[i].color[Front] = RCRed;
		if (i % 9 > 5) cube->segment[i].color[Back] = RCOrange;
		if (i % 3 == 0) cube->segment[i].color[Left] = RCGreen;
		if (i % 3 == 2) cube->segment[i].color[Right] = RCBlue;

		for (int j = 0; j < CubeSides; j++)
			cube->segment[i].sides += cube->segment[i].color[j] > 0 ? 1 : 0;
	}

	return cube;
}


void RCubeLeftPlus(RCube* cube) {
	//replace
	swap(&cube->segment[6], &cube->segment[24]);
	swap(&cube->segment[0], &cube->segment[18]);
	swap(&cube->segment[6], &cube->segment[18]);

	swap(&cube->segment[21], &cube->segment[9]);
	swap(&cube->segment[3], &cube->segment[15]);
	swap(&cube->segment[3], &cube->segment[21]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i % 3 == 0)
			cube->segment[i].position = i;

	//reorientation
	for (int i = 0; i < 27; i++)
		if (i % 3 == 0)
			if (!cube->segment[i].color[Up]) {
				cube->segment[i].color[Up] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = cube->segment[i].color[Down];
				cube->segment[i].color[Down] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = RCNoColor;
			}
			else {
				cube->segment[i].color[Down] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = cube->segment[i].color[Up];
				cube->segment[i].color[Up] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = RCNoColor;
			}
 }

void RCubeLeftMinus(RCube* cube) {
	RCubeLeftPlus(cube);
	RCubeLeftPlus(cube);
	RCubeLeftPlus(cube);
}

void RCubeRightPlus(RCube* cube) {
	//replace
	swap(&cube->segment[2], &cube->segment[20]);
	swap(&cube->segment[26], &cube->segment[8]);
	swap(&cube->segment[2], &cube->segment[26]);

	swap(&cube->segment[5], &cube->segment[11]);
	swap(&cube->segment[17], &cube->segment[23]);
	swap(&cube->segment[5], &cube->segment[23]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i % 3 == 2)
			cube->segment[i].position = i;

	//reorientation
	for (int i = 0; i < 27; i++)
		if (i % 3 == 2)
			if (!cube->segment[i].color[Up]) {
				cube->segment[i].color[Up] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = cube->segment[i].color[Down];
				cube->segment[i].color[Down] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = RCNoColor;
			}
			else {
				cube->segment[i].color[Down] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = cube->segment[i].color[Up];
				cube->segment[i].color[Up] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = RCNoColor;
			}
}

void RCubeRightMinus(RCube* cube) {
	RCubeRightPlus(cube);
	RCubeRightPlus(cube);
	RCubeRightPlus(cube);
}

void RCubeUpPlus(RCube* cube) {
	swap(&cube->segment[18], &cube->segment[24]);
	swap(&cube->segment[26], &cube->segment[20]);
	swap(&cube->segment[26], &cube->segment[18]);

	swap(&cube->segment[19], &cube->segment[21]);
	swap(&cube->segment[23], &cube->segment[25]);
	swap(&cube->segment[25], &cube->segment[19]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i > 17)
			cube->segment[i].position = i;

	for (int i = 0; i < 27; i++)
		if (i > 17)
			if (!cube->segment[i].color[Back]) {
				cube->segment[i].color[Back] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = RCNoColor;
			}
			else {
				cube->segment[i].color[Front] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = RCNoColor;
			}
}

void RCubeUpMinus(RCube* cube) {
	RCubeUpPlus(cube);
	RCubeUpPlus(cube);
	RCubeUpPlus(cube);
}

void RCubeDownMinus(RCube* cube) {
	swap(&cube->segment[0], &cube->segment[6]);
	swap(&cube->segment[8], &cube->segment[2]);
	swap(&cube->segment[8], &cube->segment[0]);

	swap(&cube->segment[1], &cube->segment[3]);
	swap(&cube->segment[5], &cube->segment[7]);
	swap(&cube->segment[7], &cube->segment[1]);

	//repos
	for (int i = 0; i < 9; i++)
			cube->segment[i].position = i;

	for (int i = 0; i < 9; i++)
			if (!cube->segment[i].color[Back]) {
				cube->segment[i].color[Back] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = RCNoColor;
			}
			else {
				cube->segment[i].color[Front] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = RCNoColor;
			}
}

void RCubeDownPlus(RCube* cube) {
	RCubeDownMinus(cube);
	RCubeDownMinus(cube);
	RCubeDownMinus(cube);
}

void RCubeFrontPlus(RCube* cube) {
	swap(&cube->segment[0], &cube->segment[18]);
	swap(&cube->segment[20], &cube->segment[2]);
	swap(&cube->segment[20], &cube->segment[0]);

	swap(&cube->segment[1], &cube->segment[9]);
	swap(&cube->segment[11], &cube->segment[19]);
	swap(&cube->segment[1], &cube->segment[19]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i % 9 < 3)
			cube->segment[i].position = i;

	for (int i = 0; i < 27; i++)
		if (i % 9 < 3)
		if (!cube->segment[i].color[Up]) {
			cube->segment[i].color[Up] = cube->segment[i].color[Left];
			cube->segment[i].color[Left] = cube->segment[i].color[Down];
			cube->segment[i].color[Down] = cube->segment[i].color[Right];
			cube->segment[i].color[Right] = RCNoColor;
		}
		else {
			cube->segment[i].color[Down] = cube->segment[i].color[Right];
			cube->segment[i].color[Right] = cube->segment[i].color[Up];
			cube->segment[i].color[Up] = cube->segment[i].color[Left];
			cube->segment[i].color[Left] = RCNoColor;
		}
}

void RCubeFrontMinus(RCube* cube) {
	RCubeFrontPlus(cube);
	RCubeFrontPlus(cube);
	RCubeFrontPlus(cube);
}

void RCubeBackPlus(RCube* cube) {
	swap(&cube->segment[8], &cube->segment[26]);
	swap(&cube->segment[6], &cube->segment[24]);
	swap(&cube->segment[8], &cube->segment[24]);

	swap(&cube->segment[7], &cube->segment[17]);
	swap(&cube->segment[25], &cube->segment[15]);
	swap(&cube->segment[25], &cube->segment[7]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i % 9 > 5)
			cube->segment[i].position = i;

	for (int i = 0; i < 27; i++)
		if (i % 9 > 5)
			if (!cube->segment[i].color[Up]) {
				cube->segment[i].color[Up] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = cube->segment[i].color[Down];
				cube->segment[i].color[Down] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = RCNoColor;
			}
			else {
				cube->segment[i].color[Down] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = cube->segment[i].color[Up];
				cube->segment[i].color[Up] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = RCNoColor;
			}
}

void RCubeBackMinus(RCube* cube) {
	RCubeBackPlus(cube);
	RCubeBackPlus(cube);
	RCubeBackPlus(cube);
}

void RCubeMiddleXPlus(RCube* cube) {
	swap(&cube->segment[3], &cube->segment[21]);
	swap(&cube->segment[5], &cube->segment[23]);
	swap(&cube->segment[3], &cube->segment[23]);

	swap(&cube->segment[4], &cube->segment[12]);
	swap(&cube->segment[22], &cube->segment[14]);
	swap(&cube->segment[22], &cube->segment[4]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i % 9 > 2 && i % 9 < 6)
			cube->segment[i].position = i;

	for (int i = 0; i < 27; i++)
		if (i % 9 > 2 && i % 9 < 6)
			if (!cube->segment[i].color[Up]) {
				cube->segment[i].color[Up] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = cube->segment[i].color[Down];
				cube->segment[i].color[Down] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = RCNoColor;
			}
			else {
				cube->segment[i].color[Down] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = cube->segment[i].color[Up];
				cube->segment[i].color[Up] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = RCNoColor;
			}
}

void RCubeMiddleXMinus(RCube* cube) {
	RCubeMiddleXPlus(cube);
	RCubeMiddleXPlus(cube);
	RCubeMiddleXPlus(cube);
}

void RCubeMiddleYPlus(RCube* cube) {
	swap(&cube->segment[9], &cube->segment[15]);
	swap(&cube->segment[17], &cube->segment[11]);
	swap(&cube->segment[17], &cube->segment[9]);

	swap(&cube->segment[10], &cube->segment[12]);
	swap(&cube->segment[14], &cube->segment[16]);
	swap(&cube->segment[16], &cube->segment[10]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i > 8 && i < 18)
			cube->segment[i].position = i;

	for (int i = 0; i < 27; i++)
		if (i > 8 && i < 18)
			if (!cube->segment[i].color[Back]) {
				cube->segment[i].color[Back] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = RCNoColor;
			}
			else {
				cube->segment[i].color[Front] = cube->segment[i].color[Right];
				cube->segment[i].color[Right] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = cube->segment[i].color[Left];
				cube->segment[i].color[Left] = RCNoColor;
			}
}

void RCubeMiddleYMinus(RCube* cube) {
	RCubeMiddleYPlus(cube);
	RCubeMiddleYPlus(cube);
	RCubeMiddleYPlus(cube);
}

void RCubeMiddleZPlus(RCube* cube) {
	swap(&cube->segment[1], &cube->segment[19]);
	swap(&cube->segment[25], &cube->segment[7]);
	swap(&cube->segment[1], &cube->segment[25]);

	swap(&cube->segment[4], &cube->segment[10]);
	swap(&cube->segment[16], &cube->segment[22]);
	swap(&cube->segment[4], &cube->segment[22]);

	//repos
	for (int i = 0; i < 27; i++)
		if (i % 3 == 1)
			cube->segment[i].position = i;

	//reorientation
	for (int i = 0; i < 27; i++)
		if (i % 3 == 1)
			if (!cube->segment[i].color[Up]) {
				cube->segment[i].color[Up] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = cube->segment[i].color[Down];
				cube->segment[i].color[Down] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = RCNoColor;
			}
			else {
				cube->segment[i].color[Down] = cube->segment[i].color[Back];
				cube->segment[i].color[Back] = cube->segment[i].color[Up];
				cube->segment[i].color[Up] = cube->segment[i].color[Front];
				cube->segment[i].color[Front] = RCNoColor;
			}
}

void RCubeMiddleZMinus(RCube* cube) {
	RCubeMiddleZPlus(cube);
	RCubeMiddleZPlus(cube);
	RCubeMiddleZPlus(cube);
}

void RCubelPlus(RCube* cube) {
	RCubeLeftPlus(cube);
	RCubeMiddleZMinus(cube);
}

void RCubelMinus(RCube* cube) {
	RCubeLeftMinus(cube);
	RCubeMiddleZPlus(cube);
}

void RCubedPlus(RCube* cube) {
	RCubeDownPlus(cube);
	RCubeMiddleYPlus(cube);
}

void RCubedMinus(RCube* cube) {
	RCubeDownMinus(cube);
	RCubeMiddleYMinus(cube);
}

void RCuberPlus(RCube* cube) {
	RCubeRightPlus(cube);
	RCubeMiddleZPlus(cube);
}

void RCuberMinus(RCube* cube) {
	RCubeRightMinus(cube);
	RCubeMiddleZMinus(cube);
}

void RCubefPlus(RCube* cube) {
	RCubeFrontPlus(cube);
	RCubeMiddleXPlus(cube);
}

void RCubefMinus(RCube* cube) {
	RCubeFrontMinus(cube);
	RCubeMiddleXMinus(cube);
}

void RCubeuPlus(RCube* cube) {
	RCubeUpPlus(cube);
	RCubeMiddleYPlus(cube);
}

void RCubeuMinus(RCube* cube) {
	RCubeUpMinus(cube);
	RCubeMiddleYMinus(cube);
}

void RCubeRotateXPlus(RCube* cube) {
	RCubeRightPlus(cube);
	RCubeMiddleZPlus(cube);
	RCubeLeftMinus(cube);
}

void RCubeRotateXMinus(RCube* cube) {
	RCubeRotateXPlus(cube);
	RCubeRotateXPlus(cube);
	RCubeRotateXPlus(cube);
}

void RCubeRotateYPlus(RCube* cube) {
	RCubeUpPlus(cube);
	RCubeMiddleYPlus(cube);
	RCubeDownMinus(cube);

}

void RCubeRotateYMinus(RCube* cube) {
	RCubeRotateYPlus(cube);
	RCubeRotateYPlus(cube);
	RCubeRotateYPlus(cube);
}

void RCubeRotateZPlus(RCube* cube) {
	RCubeFrontPlus(cube);
	RCubeMiddleXPlus(cube);
	RCubeBackMinus(cube);
}

void RCubeRotateZMinus(RCube* cube) {
	RCubeRotateZPlus(cube);
	RCubeRotateZPlus(cube);
	RCubeRotateZPlus(cube);
}


Queue* ParseNotation(char* str) {
	if (!str) return NULL;
	Queue *q = calloc(1, sizeof(Queue));
	if (!q) return NULL;
	int str_len = strnlen(str, 10000);
	int sum = 0, count = 1;
	for (int i = 0; i < str_len; i++) {
		if (!(strchr(NOTATION_SYMBOLS, str[i]))) continue;

		switch (str[i]) { // decollision addition
		case 'z':
			sum += 3;
			break;
		case 'y':
			sum += 2;
			break;
		}

		sum += str[i];
		int not = strchr("23456789", str[i + 1]);
		if (i + 1 < str_len && strchr("23456789", str[i + 1]) && ++i) count = (str[i] - 48) % 10;
		if (i + 1 < str_len && str[i + 1] == '\'' && ++i) sum += str[i];

		for (int h = 0; h < count; h++) {
			switch (sum) {
			case 'U':
				QueuePush(q, A_RCubeUpPlus);
				break;
			case 'D':
				QueuePush(q, A_RCubeDownPlus);
				break;
			case 'F':
				QueuePush(q, A_RCubeFrontPlus);
				break;
			case 'B':
				QueuePush(q, A_RCubeBackPlus);
				break;
			case 'R':
				QueuePush(q, A_RCubeRightPlus);
				break;
			case 'L':
				QueuePush(q, A_RCubeLeftPlus);
				break;
			case 'U' + '\'':
				QueuePush(q, A_RCubeUpMinus);
				break;
			case 'D' + '\'':
				QueuePush(q, A_RCubeDownMinus);
				break;
			case 'F' + '\'':
				QueuePush(q, A_RCubeFrontMinus);
				break;
			case 'B' + '\'':
				QueuePush(q, A_RCubeBackMinus);
				break;
			case 'R' + '\'':
				QueuePush(q, A_RCubeRightMinus);
				break;
			case 'L' + '\'':
				QueuePush(q, A_RCubeLeftMinus);
				break;
			case 'l':
				QueuePush(q, A_RCubelPlus);
				break;
			case 'r':
				QueuePush(q, A_RCuberPlus);
				break;
			case 'l' + '\'':
				QueuePush(q, A_RCubelMinus);
				break;
			case 'r' + '\'':
				QueuePush(q, A_RCuberMinus);
				break;
            case 'f':
				QueuePush(q, A_RCubefPlus);
				break;
			case 'f' + '\'':
				QueuePush(q, A_RCubefMinus);
				break;
            case 'u':
				QueuePush(q, A_RCubeuPlus);
				break;
			case 'u' + '\'':
				QueuePush(q, A_RCubeuMinus);
				break;
			case 'd':
				QueuePush(q, A_RCubedPlus);
				break;
			case 'd' + '\'':
				QueuePush(q, A_RCubedMinus);
				break;
			case 'S':
				QueuePush(q, A_RCubeMiddleXPlus);
				break;
			case 'S' + '\'':
				QueuePush(q, A_RCubeMiddleXMinus);
				break;
			case 'x':
				QueuePush(q, A_RCubeRotateXPlus);
				break;
			case 'y' + 2:
				QueuePush(q, A_RCubeRotateYPlus);
				break;
			case 'z' + 3:
			    QueuePush(q, A_RCubeRotateZPlus);
				break;
			case 'x' + '\'':
				QueuePush(q, A_RCubeRotateXMinus);
				break;
			case 'y' + '\'' + 2:
				QueuePush(q, A_RCubeRotateYMinus);
				break;
			case 'z' + '\'' + 3:
			    QueuePush(q, A_RCubeRotateZMinus);
				break;
			}
		}
		sum = 0;
		count = 1;
	}
	return q;
}

void MixCube(RCube **cube, HDC hDC) {
    unsigned tmp = ROTATION_DELAY;
    ROTATION_DELAY = 0;
    srand(time(NULL));
	free(*cube);
	*cube = CreateCube();

    void (*p[])(RCube*, HDC, char) = {A_RCubeBackMinus, A_RCubeBackPlus,
                                      A_RCubeDownMinus,A_RCubeDownPlus,
                                      A_RCubeFrontMinus, A_RCubeFrontPlus,
                                      A_RCubeLeftMinus, A_RCubeLeftPlus,
                                      A_RCubeRightMinus, A_RCubeRightPlus,
                                      A_RCubeUpMinus, A_RCubeUpPlus,
                                      };

    for (int i = 0; i < 31; i++)
        p[rand() % (sizeof(p) / sizeof(p[0]))](*cube, hDC, 1);

    ROTATION_DELAY = tmp;
}

Queue* Optimize(char* inp) {
	Stack* stack = NewStack();
	Stack* stack2 = NewStack();
	return ParseNotation(inp);
	Queue* queue = ParseNotation(inp);

	while (queue->size > 0) {
		void* obj = QueuePop(queue);
	
		if (!StackEmpty) {
			void* obj2 = StackPop(stack);
			if (((STRUCT_OBJ*)obj2)->val) obj2 = ((STRUCT_OBJ*)obj2)->val;
			if (obj == obj2) continue;
			else {
				StackPush(stack, obj2);
				StackPush(stack, obj);
			}
		} else StackPush(stack, obj);
	}

	while (!StackEmpty(stack)) {
		STRUCT_OBJ* obj = StackPop(stack);
		if (obj) StackPush(stack2, obj->val);
	}
	while (!StackEmpty(stack2)) {
		STRUCT_OBJ* obj = StackPop(stack2);
		if (obj) QueuePush(queue, obj->val);
	}
	return queue;
}
