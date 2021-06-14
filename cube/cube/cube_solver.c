#include <windows.h>
#include "cube_solver.h"
#include <malloc.h>
#include <stdio.h>
#include "../params.h"

extern unsigned ROTATION_DELAY;


#define MAX_SOLUTION_LENGTH 10000

char* mstrcat(char* str1, char* str2)
{
	char* begin = str1;
	while (*str1)
		str1++;

	while (*str1++ = *str2++);

	*str1 = '\0';
	return begin;
}

unsigned long long EvaluateTable(char* matrix, int size) {
	unsigned long long value = 0;
	unsigned long long base = 1;
	for (int i = 0; i < size; i++) {
		value += (matrix[i]) ? base : 0;
		base *= 2;
	}
	return value;
}

unsigned long long MakeSnapshot5(RCube* cube) {
	char snapshot[25];
	for (int i = 0; i < 25; i++) snapshot[i] = 0;

	for (int i = 18; i < 21; i++) {
		if (cube->segment[i].color[Up] == RCYellow) snapshot[i - 2] = '1';
		if (cube->segment[i].color[Front] == RCYellow) snapshot[i + 3] = '1';
	}
	for (int i = 21; i < 24; i++)
		if (cube->segment[i].color[Up] == RCYellow) snapshot[i - 10] = '1';
	for (int i = 24; i < 27; i++) {
		if (cube->segment[i].color[Up] == RCYellow) snapshot[i - 18] = '1';
		if (cube->segment[i].color[Back] == RCYellow) snapshot[i - 23] = '1';
	}

	if (cube->segment[18].color[Left] == RCYellow) snapshot[15] = '1';
	if (cube->segment[21].color[Left] == RCYellow) snapshot[10] = '1';
	if (cube->segment[24].color[Left] == RCYellow) snapshot[5] = '1';
	if (cube->segment[20].color[Right] == RCYellow) snapshot[19] = '1';
	if (cube->segment[23].color[Right] == RCYellow) snapshot[14] = '1';
	if (cube->segment[26].color[Right] == RCYellow) snapshot[9] = '1';

	return EvaluateTable(snapshot, 25);
}

char* SolutionOLLPart(RCube cube) {
	char* res = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
	if (!res) return NULL;
	for (int zz = 0; zz < 4; zz++) {
		if (zz > 0) {
			RCubeUpPlus(&cube);
			switch (zz) {
			    case 1: res[0] = 'U'; break;
			    case 2: res[0] = 'U'; res[1] = 'U';break;
			    case 3: res[0] = 'U'; res[1] = '\'';break;
			}
		}
		unsigned long long solution = MakeSnapshot5(&cube);
		switch (solution) {
		case 10631616:
			return mstrcat(res, "(R2' D) (R' U2) (R D') (R' U2 R')"); // 1
		case 8599752:
			return mstrcat(res, "(l' U') (L U) (R U') (r' F)"); // 2
		case 440520:
			return mstrcat(res, "(l' U') (L' U) (R U') (L U) x'"); // 3
		case 8600194:
			return mstrcat(res, "(R U R' U) (R U2' R')"); // 4
		case 2504872:
			return mstrcat(res, "(L' U' L U') (L' U2 L)"); // 5
		case 8566952:
			return mstrcat(res, "(R U2) (R2' U') (R2 U') (R2' U2' R)"); // 6
		case 10631306:
			return mstrcat(res, "F (R U R' U') (R U R' U') (R U R' U') F'"); // 7
		case 4544960:
			return mstrcat(res, "x (L U' L) U2 (R' U R U2) (L' r')"); // 8
		case 4536644:
			return mstrcat(res, "(R U R' U') (r R' U) (R U' r')"); // 9
		case 4543812:
			return mstrcat(res, "S (R' U' R U) (R U) (R U' R' S')"); // 10
		case 4773412:
			return mstrcat(res, "(R U) B' (l U l' R' U') (R' F R F')"); // 11
		case 12637228:
			return mstrcat(res, "F (R U R' U') S (R U R' U') f'"); // 12
		case 4511238:
			return mstrcat(res, "f (R U R' U') f' U' F (R U R' U') F'"); // 13
		case 6837540:
			return mstrcat(res, "f (R U R' U') f' U F (R U R' U') F'"); // 14
		case 4773188:
			return mstrcat(res, "r' R U R U R' U' r R2' F R F'"); // 15
		case 14701892:
			return mstrcat(res, "B L U L' U B' U2 B' R B R'"); // 16
		case 4510796:
			return mstrcat(res, "(R U R' U) (R' F R F') U2 (R' F R F')"); // 17
		case 6568198:
			return mstrcat(res, "(R U R' U') (R' F R F')"); // 18
		case 4503844:
			return mstrcat(res, "F (R U R' U') F'"); // 19
		case 12663076:
			return mstrcat(res, "(R B') (R' U' R U) y (R U') F'"); // 20
		case 6568516:
			return mstrcat(res, "(L' B) (L U L' U') y' (L' U) F"); // 21
		case 4536868:
			return mstrcat(res, "(R U R2' U') (R' F) (R U) (R U') F'"); // 22
		case 4536334:
			return mstrcat(res, "B' (R' U' R) y (R U') (R' U2 R)"); // 23
		case 12630060:
			return mstrcat(res, "f (R U R' U') (R U R' U') f'"); // 24
		case 2774658:
			return mstrcat(res, "(R U R' U R d') (R U' R' F')"); // 25
		case 4766244:
			return mstrcat(res, "F (R U R' U') x R U' L U R' U' r'"); // 26
		case 710304:
			return mstrcat(res, "(R' U2) (R2 U) (R' U) (R U2) y (l' U' l)"); // 27
		case 12630278:
			return mstrcat(res, "x' (R U' R' F') (R U R') x y (R' U R)"); // 28
		case 6830156:
			return mstrcat(res, "x' (L' U L F) (L' U' L) x y' (L U' L')"); // 29
		case 6830372:
			return mstrcat(res, "(r U r') (R U R' U') (r U' r')"); // 30
		case 12630596:
			return mstrcat(res, "(l' U' l) (L' U' L U) (l' U l)"); // 31
		case 439588:
			return mstrcat(res, "f (R U R' U') f'"); // 32
		case 744004:
			return mstrcat(res, "f' (L' U' L U) f"); // 33
		case 2503942:
			return mstrcat(res, "(R d) (L' d') (R' U) (l U l')"); // 34
		case 8607820:
			return mstrcat(res, "(L' d') (R d) (L U') (r' U' r)"); // 35
		case 4807042:
			return mstrcat(res, "(R U R' U) (R U' R' U') (R' F R F')"); // 36
		case 4502728:
			return mstrcat(res, "(L' U' L U') (L' U L U) (L F' L' F)"); // 37
		case 4765344:
			return mstrcat(res, "(r U) (R' U) (R U') (R' U) (R U2' r')"); // 38
		case 4774560:
			return mstrcat(res, "(l' U') (L U') (L' U) (L U') (L' U2 l)"); // 39
		case 8565804:
			return mstrcat(res, "r' U r2 U' r2' U' r2 U r'"); // 40
		case 2775558:
			return mstrcat(res, "l U' l2' U l2 U l2' U' l"); // 41
		case 12638376:
			return mstrcat(res, "F (R U R' U') (R U R' U') F'"); // 42
		case 6829698:
			return mstrcat(res, "F' (L' U' L U) (L' U' L U) F"); // 43
		case 6829472:
			return mstrcat(res, "r U2 R' U' R U' r'"); // 44
		case 12638912:
			return mstrcat(res, "l' U2' L U L' U l"); // 45
		case 8566022:
			return mstrcat(res, "(l U L' U) (L U2' l')"); // 46
		case 2775116:
			return mstrcat(res, "(r' U' R U') (R' U2 r)"); // 47
		case 2766116:
			return mstrcat(res, "F (R U R' U') F' U F (R U R' U') F'"); // 48
		case 8575556:
			return mstrcat(res, "F' (L' U' L U) F U' F' (L' U' L U) F"); // 49
		case 6576832:
			return mstrcat(res, "F (R U') (R' U' R U) (R' F')"); // 50
		case 4511944:
			return mstrcat(res, "(L U2) (L2 B) (L B' L U2 L')"); // 51
		case 12662402:
			return mstrcat(res, "(L U L') y x' (L' U) (L F') (L' U' L) x"); // 52
		case 6576296:
			return mstrcat(res, "(R' U' R) y' x' (R U') (R' F) (R U R') x"); // 53
		case 10630468:
			return mstrcat(res, "(R U') (R' U2) (R U) y (R U') (R' U' F')"); // 54
		case 10639684:
			return mstrcat(res, "(L' U) (L U2') (L' U') y' (L' U) (L U F)"); // 55
		case 701764:
			return mstrcat(res, "(R2' U R' B') (R U') (R2' U) (l U l')"); // 56
		case 710980:
			return mstrcat(res, "(L2 U' L B) (L' U) (L2 U') (r' U' r)"); // 57
		}
	}
	free(res);
	return NULL;
}


unsigned PLLHASH(char M[3][3]) {
    unsigned base = 1, res = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (M[i][j])
                res += base;
            base *= 2;
        }
    return res;
}

char* SolutionPLLPart(RCube cube) {
    char* res = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
    if (!res) return NULL;

    char M[3][3] = { 0,0,0,0,0,0,0,0,0 };

    int m = 0, u = 0;
    for (int j = 0; j < 4; j++) {
        int tmp = 0;
        for (int i = 18; i < 27; i++)
            if (cube.segment[i].solved_position == i && i != 22)
                tmp++;
        if (tmp > m) {
            m = tmp;
            u = j;
        }
        RCubeUpPlus(&cube);
    }

    //for (int i = 0; i < u; i++) RCubeUpPlus(&cube);
    int y;
    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < 4; i++) {
            u = k;
            y = i;
            memset(M, 0, 9);
            for (int j = 18; j < 27; j++)
                if (cube.segment[j].color[Back] == cube.segment[j - 9].color[Back] &&
                    cube.segment[j].color[Left] == cube.segment[j - 9].color[Left] &&
                    cube.segment[j].color[Right] == cube.segment[j - 9].color[Right] &&
                    cube.segment[j].color[Front] == cube.segment[j - 9].color[Front])
                    M[j % 9 / 3][j % 3] = 1;

            unsigned hash = PLLHASH(M);
            printf("\n%d\n", hash);
            if (m == 5)
                if (hash == 469)
                    if (cube.segment[21].color[Left] == cube.segment[20].color[Right]) {
                        strcat(res, "(R2 U) (R U R' U') (R' U') (R' U R')"); // 1
                        goto out;
                    }
                    else {
                        strcat(res, "(R U' R U) (R U)(R U')(R' U' R2)");  // 2
                        goto out;
                    }
                       
                else if (hash == 187) 
                    if (cube.segment[26].color[Right] == cube.segment[19].color[Front]) {
                        strcat(res, "(l' U R') D2 (R U' R') D2 R2");  // 5
                        goto out;
                    }
                    else {
                        strcat(res, "y' (r U' L) D2 (L' U L) D2 L2");  // 6
                        goto out;
                    }
            if (m == 4)
                if (hash == 341) 
                    if (cube.segment[21].color[Left] == cube.segment[20].color[Right]) {
                        strcat(res, "(R2 L2 D) (R2 L2 U2) (R2 L2 D) R2 L2"); // 4
                        goto out;
                    }
                    else if (cube.segment[23].color[Right] == cube.segment[18].color[Front]) {
                        strcat(res, "R B' R' B F R' B' F R' B R F2 U"); // 3
                        goto out;
                    }
                    else {
                        strcat(res, "U R B' R' B F R' B' F R' B R F2"); // 3
                        goto out;
                    }
                else if (hash == 186) {
                    if (cube.segment[24].color[Back] == cube.segment[21].color[Left]) {
                        strcat(res, "x' (R U') (R' D) (R U R') u2' (R' U) (R D) (R' U' R)"); // 7
                        goto out;
                    }
                    else {
                        strcat(res, "y x' (R U') (R' D) (R U R') u2' (R' U) (R D) (R' U' R)"); // 7
                        goto out;
                    }
                } //printf("\nIs 7\n");
                else if (hash == 217) {
                    strcat(res, "(R U2 R' U' R U2) (L' U R' U' L)");
                    goto out;
                } //printf("\nIs 8\n");
                else if (hash == 436) {
                    strcat(res, "(L' U2 L U L' U2) (R U' L U R')");
                    goto out;
                } //printf("\nIs 9\n");
                else if (hash == 157) {
                    strcat(res, "F L U L' F L U' F U F U' F' L' F2");
                    goto out;
                } //printf("\nIs 10\n");
                else if (hash == 181) {
                    strcat(res, "F' R' U' R F' R' U F' U' F' U F R F2");
                    goto out;
                } //printf("\nIs 11\n");
                else if (hash == 211) {
                    strcat(res, "(R U R' U') (R' F) (R2 U') (R' U' R U) (R' F')");
                    goto out;
                } //printf("\nIs 12\n");
                else if (hash == 151) {
                    strcat(res, "(R' U R U' R2) (F' U' F U) (R F R' F' R2 U')");
                    goto out;
                } //printf("\nIs 13\n");
                else if (hash == 220) {
                    strcat(res, "L' U R U' L U L' U R' U' L U2 R U2 R'");
                    goto out;
                } //printf("\nIs 14\n");
                else if (hash == 403) {
                    strcat(res, "(R' U L') U2 (R U' L) (R' U L') U2 (R U' L U)");
                    goto out;
                } //printf("\nIs 20\n");
                else if (hash == 214) {
                    strcat(res, "(L U' R) U2 (L' U R') (L U' R) U2 (L' U R' U')");
                    goto out;
                } //printf("\nIs 19\n");
                else if (hash == 307) {
                    strcat(res, "(F R U') (R' U' R U) (R' F') (R U R' U') (R' F R F')");
                    goto out;
                } //printf("\nIs 21\n");
            if (m == 2)
                if (hash == 400)
                    if (cube.segment[21].color[Left] == cube.segment[26].color[Right]) {
                        strcat(res, "(R2' u' R U') (R U R' u R2) y (R U' R')"); // 15
                        goto out;
                    }
                    else {
                        strcat(res, "U' (R U R') y' (R2' u' R U') (R' U R' u R2)"); // 18
                        goto out;
                    }
                else if (hash == 304) 
                    if (cube.segment[21].color[Left] == cube.segment[20].color[Right]) {
                        strcat(res, "y (R2 u) (R' U R' U' R u') R2' y' (R' U R)"); // 16
                        goto out;
                    }
                    else {
                        strcat(res, "(R' U' R) y (R2' u R' U) (R U' R u' R2')"); // 17
                        goto out;
                    }
                
            RCubeRotateYPlus(&cube);
        }
        RCubeUpPlus(&cube);
    }
    free(res);
    return NULL;
    out:;

    char *p = calloc(1024, sizeof(char));
    if (u == 0);
    else if (u == 1) strcat(p, "U");
    else if (u == 2) strcat(p, "U2");
    else if (u == 3) strcat(p, "U'");

    if (y == 0);
    else if (y == 1) strcat(p, "y");
    else if (y == 2) strcat(p, "yy");
    else if (y == 3) strcat(p, "y'");
    strcat(p, res);
    free(res);
	return p;
}

char* SolutionCrossPart(RCube cube) {
	char* res = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
	if (!res) return NULL;

	int position = 0;
    char *p = "";
	if (cube.segment[1].solved_position != 1) {
        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == 1)
                position = i;
        if (position == 3) p = "D";
        if (position == 5) p = "D'";
        if (position == 7) p = "D2";
        if (position == 9) p = "F'";
        if (position == 11) p = "F";
        if (position == 15) p = "LU'L'FF";
        if (position == 17) p = "R'URFF";
        if (position == 19) p = "FF";
        if (position == 21) p = "U'FF";
        if (position == 23) p = "UFF";
        if (position == 25) p = "UUFF";
	}
    strcat(res, p);
    MakeTransformation(&cube, p, NULL, 0);
    p = "";
	if (cube.segment[3].solved_position != 3) {
        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == 3)
                position= i;
        if (position == 5) p = "R2U2L2";
        if (position == 7) p = "B2U'L2";
        if (position == 9) p = "L";
        if (position == 11) p = "F'UFLL";
        if (position == 15) p = "L'";
        if (position == 17) p = "R'U2L2";
        if (position == 19) p = "UL2";
        if (position == 21) p = "L2";
        if (position == 23) p = "U2L2";
        if (position == 25) p = "U'L2";
	}
	strcat(res, p);
	MakeTransformation(&cube, p, NULL, 0);
	p = "";
	if (cube.segment[7].solved_position != 7) {
        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == 7)
                position= i;
        if (position == 5) p = "R'B'";
        if (position == 9) p = "L'ULB2";
        if (position == 11) p = "RU'R'B2";
        if (position == 15) p = "B";
        if (position == 17) p = "B'";
        if (position == 19) p = "U2B2";
        if (position == 21) p = "UB2";
        if (position == 23) p = "U'B2";
        if (position == 25) p = "B2";
	}
	strcat(res, p);
	MakeTransformation(&cube, p, NULL, 0);
	p = "";
	if (cube.segment[5].solved_position != 5) {
        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == 5)
                position= i;
        if (position == 9) p = "FU'F'R2";
        if (position == 11) p = "R'";
        if (position == 15) p = "B'UBR2";
        if (position == 17) p = "R";

        if (position == 19) p = "U'R2";
        if (position == 21) p = "U2R2";
        if (position == 23) p = "R2";
        if (position == 25) p = "UR2";
	}
	strcat(res, p);
	MakeTransformation(&cube, p, NULL, 0);


	if (cube.segment[1].color[Down] != RCWhite) strcat(res, "F'RUR'F2");;
	if (cube.segment[3].color[Down] != RCWhite) strcat(res, "L'FUF'L2");;
	if (cube.segment[5].color[Down] != RCWhite) strcat(res, "RF'U'FR2");;
	if (cube.segment[7].color[Down] != RCWhite) strcat(res, "BR'U'RB2");;

	return res;
}

char* SolutionFL(RCube cube) {
    char* res = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
	if (!res) return NULL;
	int position = 0;
	char* p = "";
	if (!(cube.segment[0].solved_position == 0
                        &&
          cube.segment[0].color[Down] == RCWhite)) {
        p = "";
        for (int i = 0; i < 27; i++)
                if (cube.segment[i].solved_position == 0)
                    position = i;
            if (position == 2) {
                strcat(res, "F'BUB'F");
                MakeTransformation(&cube, "F'BUB'F", NULL, 0);
            }
            if (position == 6) {
                strcat(res, "FB'U'BF'");
                MakeTransformation(&cube, "FB'U'BF'", NULL, 0);
            }
            if (position == 8){
                strcat(res, "FBU2B'F'");
                MakeTransformation(&cube, "FBU2B'F'", NULL, 0);
            }
            if (position == 18){
                strcat(res, "UFU'F'");
                MakeTransformation(&cube, "UFU'F'", NULL, 0);
            }
            if (position == 20){
                strcat(res, "L'UL");
                MakeTransformation(&cube, "L'UL", NULL, 0);
            }
            if (position == 24){
                strcat(res, "FU'F'");
                MakeTransformation(&cube, "FU'F'", NULL, 0);
            }
            if (position == 26){
                strcat(res, "FU2F'");
                MakeTransformation(&cube, "FU2F'", NULL, 0);
            }

            if (cube.segment[0].color[Front] == RCWhite)
                p = "FUF'U2'L'UL";
            else if (cube.segment[0].color[Left] == RCWhite)
                p = "L'U'LU2FU'F'";
        strcat(res, p);
        if (p[0]) MakeTransformation(&cube, p, NULL, 0);
	}
    printf("|%s|", p);
	p = "";
	if (!(cube.segment[2].solved_position == 2
                        &&
          cube.segment[2].color[Down] == RCWhite)) {
        p = "";
        for (int i = 0; i < 27; i++)
                if (cube.segment[i].solved_position == 2)
                    position= i;
            if (position == 6) { //+
                strcat(res, "F'B'U2FB");
                MakeTransformation(&cube, "F'B'U2FB", NULL, 0);
            }
            if (position == 8){
                strcat(res, "BF'UFB'");
                MakeTransformation(&cube, "BF'UFB'", NULL, 0);
            }
            if (position == 18){
                strcat(res, "RU'R'");
                MakeTransformation(&cube, "RU'R'", NULL, 0);
            }
            if (position == 20){
                strcat(res, "URU'R'");
                MakeTransformation(&cube, "URU'R'", NULL, 0);
            }
            if (position == 24){
                strcat(res, "RU2R'");
                MakeTransformation(&cube, "RU2R'", NULL, 0);
            }
            if (position == 26){
                strcat(res, "F'UF");
                MakeTransformation(&cube, "F'UF", NULL, 0);
            }

            if (cube.segment[2].color[Front] == RCWhite)
                p = "F'U'FU2RU'R'";
            else if (cube.segment[2].color[Right] == RCWhite)
                p = "RUR'U2F'UF";
        strcat(res, p);
        if (p[0])MakeTransformation(&cube, p, NULL, 0);
	}
    printf("|%s|", p);
	p = "";

	if (!(cube.segment[6].solved_position == 6
                        &&
          cube.segment[6].color[Down] == RCWhite)) {
        p = "";
        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == 6)
                position = i;
        if (position == 8){
            strcat(res, "BUB2'U2B");
            MakeTransformation(&cube, "BUB2'U2B", NULL, 0);
        }
        if (position == 18){
            strcat(res, "B'UB");
            MakeTransformation(&cube, "B'UB", NULL, 0);
        }
        if (position == 20){
            strcat(res, "UB'UB");
            MakeTransformation(&cube, "UB'UB", NULL, 0);
        }
        if (position == 24){
            strcat(res, "U'B'UB");
            MakeTransformation(&cube, "U'B'UB", NULL, 0);
        }
        if (position == 26){
            strcat(res, "LU'L'");
            MakeTransformation(&cube, "LU'L'", NULL, 0);
        }

        if (cube.segment[6].color[Back] == RCWhite)
            p = "B'U'BU2LU'L'";
        else if (cube.segment[6].color[Left] == RCWhite)
            p = "LUL'U2'B'UB";
        strcat(res, p);
        MakeTransformation(&cube, p, NULL, 0);
	}
    printf("|%s|", p);
	p = "";

	if (!(cube.segment[8].solved_position == 8
                        &&
          cube.segment[8].color[Down] == RCWhite)) {

        for (int i = 0; i < 27; i++)
                if (cube.segment[i].solved_position == 8)
                    position= i;
            if (position == 18){
                strcat(res, "BU2B'");
                MakeTransformation(&cube, "BU2B'", NULL, 0);
            }
            if (position == 20){
                strcat(res, "BU'B'");
                MakeTransformation(&cube, "BU'B'", NULL, 0);
            }
            if (position == 24){
                strcat(res, "R'UR");
                MakeTransformation(&cube, "R'UR", NULL, 0);
            }
            if (position == 26){
                strcat(res, "U'R'UR");
                MakeTransformation(&cube, "U'R'UR", NULL, 0);
            }

            if (cube.segment[8].color[Back] == RCWhite)
                p = "BUB'U2'R'UR";
            else if (cube.segment[8].color[Right] == RCWhite)
                p = "R'U'RU2BU'B'";
	}
    printf("|%s|\n", p);
    strcat(res, p);
	return res;
}

char* SolutionSL(RCube cube) {
    char* res = calloc(MAX_SOLUTION_LENGTH, sizeof(char));

	if (!res) return NULL;
	int position = 0;
	if (!(cube.segment[9].solved_position == 9
                        &&
          cube.segment[9].color[Front] == RCRed)) {
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 9)
                    position = i;
            if (position == 9) {
                strcat(res, "UFUF'U'L'U'L ");
                MakeTransformation(&cube, "UFUF'U'L'U'L ", NULL, 0);
            }
            if (position == 11) {
                strcat(res, "RU'R'U'F'UF ");
                MakeTransformation(&cube, "RU'R'U'F'UF ", NULL, 0);
            }
            if (position == 15) {
                strcat(res, "LU'L'U'B'UB ");
                MakeTransformation(&cube, "LU'L'U'B'UB ", NULL, 0);
            }
            if (position == 17) {
                strcat(res, "BU'B'U'R'UR ");
                MakeTransformation(&cube, "BU'B'U'R'UR ", NULL, 0);
            }
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 9)
                    position = i;
            if (cube.segment[position].color[Up] == RCRed) {
                if (position == 19) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                if (position == 23) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                if (position == 25) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                strcat(res, "UFU'F'U'L'UL ");
                MakeTransformation(&cube, "UFU'F'U'L'UL ", NULL, 0);
            }
            else {
                if (position == 21) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                if (position == 23) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                if (position == 25) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                strcat(res, "U'L'ULUFU'F' ");
                MakeTransformation(&cube, "U'L'ULUFU'F' ", NULL, 0);
            }
          }


    if (!(cube.segment[11].solved_position == 11
                        &&
          cube.segment[11].color[Front] == RCRed)) {
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 11)
                    position = i;
                    printf("pos: %d\n", position);
            if (position == 11) {
                strcat(res, "RU'R'U'F'UF ");
                MakeTransformation(&cube, "RU'R'U'F'UF ", NULL, 0);
            }
            if (position == 15) {
                strcat(res, "LU'L'U'B'UB ");
                MakeTransformation(&cube, "LU'L'U'B'UB ", NULL, 0);
            }
            if (position == 17) {
                strcat(res, "BU'B'U'R'UR ");
                MakeTransformation(&cube, "BU'B'U'R'UR ", NULL, 0);
            }
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 11)
                    position = i;
            printf("pos: %d\n", position);
            if (cube.segment[position].color[Up] == RCRed) {
                    printf("red top\n");
                if (position == 19) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                if (position == 21) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                if (position == 25) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                strcat(res, "U'F'UFURU'R' ");
                MakeTransformation(&cube, "U'F'UFURU'R' ", NULL, 0);
            }
            else {
                if (position == 21) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                if (position == 23) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                if (position == 25) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                strcat(res, "URU'R'U'F'UF ");
                MakeTransformation(&cube, "URU'R'U'F'UF ", NULL, 0);
            }
    }


    if (!(cube.segment[15].solved_position == 15
                        &&
          cube.segment[15].color[Left] == RCGreen)) {
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 15)
                    position = i;
            if (position == 15) {
                strcat(res, "LU'L'U'B'UB ");
                MakeTransformation(&cube, "LU'L'U'B'UB ", NULL, 0);
            }
            if (position == 17) {
                strcat(res, "BU'B'U'R'UR ");
                MakeTransformation(&cube, "BU'B'U'R'UR ", NULL, 0);
            }
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 15)
                    position = i;
            if (cube.segment[position].color[Up] == RCGreen) {
                if (position == 19) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                if (position == 21) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                if (position == 23) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                strcat(res, "ULU'L'U'B'UB ");
                MakeTransformation(&cube, "ULU'L'U'B'UB ", NULL, 0);
            }
            else {
                if (position == 19) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                if (position == 23) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                if (position == 25) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                strcat(res, "U'B'UBULU'L' ");
                MakeTransformation(&cube, "U'B'UBULU'L' ", NULL, 0);
            }
          }

    if (!(cube.segment[17].solved_position == 17
                        &&
          cube.segment[17].color[Right] == RCBlue)) {
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 17)
                    position = i;
            if (position == 17) {
                strcat(res, "BU'B'U'R'UR ");
                MakeTransformation(&cube, "BU'B'U'R'UR ", NULL, 0);
            }
            for (int i = 0 ; i< 27; i++)
                if (cube.segment[i].solved_position == 17)
                    position = i;
            if (cube.segment[position].color[Up] == RCOrange) {
                if (position == 19) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                if (position == 21) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                if (position == 25) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U", NULL, 0);
                }
                strcat(res, "UBU'B'U'R'UR ");
                MakeTransformation(&cube, "UBU'B'U'R'UR ", NULL, 0);
            }
            else {
                if (position == 19) {
                    strcat(res, "U2 ");
                    MakeTransformation(&cube, "U2 ", NULL, 0);
                }
                if (position == 21) {
                    strcat(res, "U ");
                    MakeTransformation(&cube, "U ", NULL, 0);
                }
                if (position == 23) {
                    strcat(res, "U' ");
                    MakeTransformation(&cube, "U' ", NULL, 0);
                }
                strcat(res, "U'R'URUBU'B' ");
                MakeTransformation(&cube, "U'R'URUBU'B' ", NULL, 0);
            }
          }
	return res;
}

char* SolutionF2L(RCube cube) {
    char* res = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
    char* ans = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
    char angle[] = { 0, 6, 8, 2 };
    char edge[] = { 9,15,17,11 };
    RCube cpy = cube;


    for (int step = 0; step < 4; step++) {
        int p_edge = 0, p_angle = 0;
        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == angle[step])
                p_angle = i;

        if (p_angle == 2) strcat(res, "RUR'");
        if (p_angle == 6) strcat(res, "B'U'B");
        if (p_angle == 8) strcat(res, "R'U2R");
        if (p_angle == 20) strcat(res, "U");
        if (p_angle == 24) strcat(res, "U'");
        if (p_angle == 26) strcat(res, "U2");

        MakeTransformation(&cube, res, NULL, 0);

        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == edge[step])
                p_edge = i;
        if (p_edge == 11) {
            strcat(res, "RUR'U'");
            MakeTransformation(&cube, "RUR'U'", NULL, 1);
        }
        if (p_edge == 15) {
            strcat(res, "B'U'BU");
            MakeTransformation(&cube, "B'U'BU", NULL, 0);
        }
        if (p_edge == 17) {
            strcat(res, "R'URU'");
            MakeTransformation(&cube, "R'URU'", NULL, 0);
        }

        for (int i = 0; i < 27; i++)
            if (cube.segment[i].solved_position == edge[step])
                p_edge = i;
            else if (cube.segment[i].solved_position == angle[step])
                p_angle = i;

        strcat(res, "y'");
        if (p_edge >= 18 && p_angle >= 18) {// оба сегмента в верхней части
            if (p_edge == 19 && p_angle == 18) {
                if (cube.segment[p_edge].color[Front] == cube.segment[p_angle].color[Front]
                    && cube.segment[p_angle].color[Left] == RCWhite)
                    strcat(res, "U (R U' R')");
                else if (cube.segment[p_angle].color[Left] == RCWhite
                    && cube.segment[p_angle].color[Front] != cube.segment[p_edge].color[Front])
                    strcat(res, "U' (R U2' R') U (F' U' F)");
                else if (cube.segment[p_angle].color[Front] == RCWhite
                    && cube.segment[p_edge].color[Front] != cube.segment[p_angle].color[Left])
                    strcat(res, "U' (R U' R' U) (R U R')"); // 14
                else if (cube.segment[p_angle].color[Front] == RCWhite
                    && cube.segment[p_angle].color[Left] == cube.segment[p_edge].color[Front])
                    strcat(res, "(R U' R') U2 (F' U' F)"); // 16
                else if (cube.segment[p_angle].color[Up] == RCWhite
                    && cube.segment[p_angle].color[Front] == cube.segment[p_edge].color[Up])
                    strcat(res, "(R U2 R') U' (R U R')");  // 17
                else if (cube.segment[p_angle].color[Up] == RCWhite
                    && cube.segment[p_angle].color[Left] != cube.segment[p_edge].color[Front])
                    strcat(res, "U' (R' F R F') U' (F' U' F)"); // 24
            }
            else if (p_edge == 21 && p_angle == 18) {
                if (cube.segment[p_edge].color[Left] == cube.segment[p_angle].color[Left]
                    && cube.segment[p_angle].color[Front] == RCWhite)
                    strcat(res, "U' (F' U F)");
                else if (cube.segment[p_angle].color[Front] == RCWhite
                    && cube.segment[p_edge].color[Left] != cube.segment[p_angle].color[Left])
                    strcat(res, "U (F' U2 F) U' (R U R')");
                else if (cube.segment[p_angle].color[Left] == RCWhite
                    && cube.segment[p_edge].color[Left] != cube.segment[p_angle].color[Front])
                    strcat(res, "U (F' U F U') (F' U' F)"); // 13
                else if (cube.segment[p_angle].color[Left] == RCWhite
                    && cube.segment[p_edge].color[Left] == cube.segment[p_angle].color[Front])
                    strcat(res, "(F' U F) U2 (R U R')"); // 15
                else if (cube.segment[p_angle].color[Up] == RCWhite
                    && cube.segment[p_angle].color[Front] == cube.segment[p_edge].color[Left])
                    strcat(res, "(F' U2 F) U (F' U' F)"); // 16
                else if (cube.segment[p_angle].color[Up] == RCWhite
                    && cube.segment[p_edge].color[Left] == cube.segment[p_angle].color[Left])
                    strcat(res, "U (F R' F' R) U (R U R')");
            }
            else if (p_angle == 18 && p_edge == 23) {
                if (cube.segment[p_angle].color[Front] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Left])
                    strcat(res, "(R U R')");
                else if (cube.segment[p_angle].color[Left] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Up])
                    strcat(res, "(U' R U R') U2 (R U' R')"); // 5
                else if (cube.segment[p_angle].color[Front] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Up])
                    strcat(res, "U (F' U2 F) U2 (F' U F)"); // 8
                else if (cube.segment[p_angle].color[Left] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Front])
                    strcat(res, "U' R U' R' U (F' U' F)"); // 9
                else if (cube.segment[p_angle].color[Up] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Front])
                    strcat(res, "U R U2 R2 (F R F')");
                else if (cube.segment[p_angle].color[Up] == RCWhite &&
                    cube.segment[p_edge].color[Up] != cube.segment[p_angle].color[Front])
                    strcat(res, "F' L' U2 L F");
            }
            else if (p_angle == 18 && p_edge == 25) {
                if (cube.segment[p_angle].color[Left] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Front])
                    strcat(res, "(F' U' F)"); // 3
                else if (cube.segment[p_angle].color[Front] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Up])
                    strcat(res, "(U F' U' F) U2 (F' U F)"); // 6
                else if (cube.segment[p_angle].color[Left] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Up])
                    strcat(res, "U' (R U2' R') U2 (R U' R')"); // 7
                else if (cube.segment[p_angle].color[Front] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Left])
                    strcat(res, "U F' U F U' (R U R')"); // 10
                else if (cube.segment[p_angle].color[Up] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Left])
                    strcat(res, "U' F' U2 F2 (R' F' R)"); // 20
                else if (cube.segment[p_angle].color[Up] == RCWhite &&
                    cube.segment[p_edge].color[Up] == cube.segment[p_angle].color[Front])
                    strcat(res, "R B U2 B' R'"); // 21
            }
        }
        else if (p_angle < 9 && p_edge >= 18) {// угол на месте, ребро в верхнем слое
            if (p_edge == 25) {
                strcat(res, "U'");
                p_edge = 21;
                RCubeUpMinus(&cube);
            }
            else if (p_edge == 23) {
                strcat(res, "U");
                p_edge = 19;
                RCubeUpPlus(&cube);
            }
            if (p_edge == 19 && cube.segment[p_edge].color[Front] == cube.segment[p_edge - 9].color[Front]
                && cube.segment[p_edge].color[Front] != RCNoColor);
            else if (p_edge == 19) {
                strcat(res, "U");
                RCubeUpPlus(&cube);
            }
            else if (p_edge == 21 && cube.segment[p_edge].color[Left] == cube.segment[p_edge - 9].color[Left]);
            else {
                strcat(res, "U'");
                RCubeUpMinus(&cube);
            }
            for (int i = 0; i < 27; i++)
                if (cube.segment[i].solved_position == edge[step])
                    p_edge = i;
            if (cube.segment[p_angle].color[Front] == cube.segment[1].color[Front]
                && cube.segment[p_edge].color[Front] != RCNoColor)
                strcat(res, "U' (F' U' F U) (R U R')"); // 25
            else if (cube.segment[p_angle].color[Front] == cube.segment[1].color[Front]
                && cube.segment[p_edge].color[Left] != RCNoColor)
                strcat(res, "U (R U R' U') (F' U' F)"); // 26
            else if (cube.segment[p_angle].color[Left] == RCWhite
                && cube.segment[p_edge].color[Front] != RCNoColor)
                strcat(res, "(R U' R2) (F R F')"); // 27
            else if (cube.segment[p_angle].color[Left] == RCWhite
                && cube.segment[p_edge].color[Left] != RCNoColor)
                strcat(res, "(F' U' F U) (F' U' F)"); // 29
            else if (cube.segment[p_angle].color[Front] == RCWhite
                && cube.segment[p_edge].color[Front] != RCNoColor)
                strcat(res, "(R U R' U')(R U R')"); // 30
            else if (cube.segment[p_angle].color[Front] == RCWhite
                && cube.segment[p_edge].color[Left] != RCNoColor)
                strcat(res, "(F' U F2) (R' F' R)"); // 28
        }
        else if (p_edge < 18 && p_angle == 18) { // боковушка на месте, угол над ней
            if (cube.segment[p_edge].color[Left] == cube.segment[p_angle].color[Left]
                && cube.segment[p_angle].color[Up] == RCWhite)
                strcat(res, "(R U' R' U)(F' U F)"); // 31
            else if (cube.segment[p_edge].color[Left] != cube.segment[p_angle].color[Left]
                && cube.segment[p_angle].color[Up] == RCWhite)
                strcat(res, "(R U R' U')(R U R' U')(R U R')"); // 32
            else if (cube.segment[p_edge].color[Front] == cube.segment[p_angle].color[Front]
                && cube.segment[p_angle].color[Left] == RCWhite)
                strcat(res, "(U' R U' R') U2 (R U' R')"); // 33
            else if (cube.segment[p_edge].color[Front] != cube.segment[p_angle].color[Front]
                && cube.segment[p_angle].color[Left] == RCWhite)
                strcat(res, "U' R U R' U (F' U' F)"); // 35
            else if (cube.segment[p_edge].color[Left] == cube.segment[p_angle].color[Left]
                && cube.segment[p_angle].color[Front] == RCWhite)
                strcat(res, "(U F' U F) U2 (F' U F)"); // 34
            else if (cube.segment[p_edge].color[Left] != cube.segment[p_angle].color[Left]
                && cube.segment[p_angle].color[Front] == RCWhite)
                strcat(res, "U F' U' F U' (R U R')"); // 36
        }
        else if (p_edge < 18 && p_angle < 9) { // на местах
            if (cube.segment[p_edge].color[Front] == cube.segment[p_angle].color[Front]);
            else if (cube.segment[p_edge].color[Front] != cube.segment[p_angle].color[Front]
                && cube.segment[p_angle].color[Down] == RCWhite)
                strcat(res, "(R U R') U2 (R U2 R') d (R' U' R)"); // 38
            else if (cube.segment[p_angle].color[Front] == RCWhite
                && cube.segment[p_angle].color[Left] == cube.segment[p_edge].color[Left])
                strcat(res, "(R U' R')(F' L' U2 L F)"); // 42
            else if (cube.segment[p_angle].color[Front] == RCWhite
                && cube.segment[p_angle].color[Left] != cube.segment[p_edge].color[Left])
                strcat(res, "(R U' R' U)(R U2' R') U (R U' R')"); // 40

            else if (cube.segment[p_angle].color[Left] == RCWhite
                && cube.segment[p_angle].color[Front] == cube.segment[p_edge].color[Front])
                strcat(res, "y(L' U L)(F R U2 R' F')"); // 41
            else if (cube.segment[p_angle].color[Left] == RCWhite
                && cube.segment[p_angle].color[Front] != cube.segment[p_edge].color[Front])
                strcat(res, "(R U R' U') (R U2 R') U' (R U R')"); // 39
        }



        //////////////////////
        cube = cpy;
        strcat(ans, res);
        printf("\nStep: %d\nSolution: %s\n", step, res);
        MakeTransformation(&cube, ans, NULL, 0);
        memset(res, 0, MAX_SOLUTION_LENGTH);
        //Sleep(1500);
    }

    return ans;
}

void MakeTransformation(RCube* cube, char* transf, HDC hDC, char show) {
	Queue* q = Optimize(transf);
	void(*f)(RCube*, HDC, char) = NULL;
	while (q->size > 0) {
		f = QueuePop(q);
		f(cube, hDC, show);
	}
	free(q);
}


void Solve(RCube *cube, HDC hDC) {
    RCube cpy = *cube;
    char* pll;
    char* solution = calloc(MAX_SOLUTION_LENGTH, sizeof(char));
    if (!solution) return;
    pll = SolutionCrossPart(cpy);
    if (pll) {
        MakeTransformation(&cpy, pll, NULL, 0);
        strcat(solution, pll);
        free(pll);
    }
    /*pll = SolutionFL(cpy);
    if (pll) {
        MakeTransformation(&cpy, pll, NULL, 0);
        strcat(solution, pll);
        free(pll);
    }
    pll = SolutionSL(cpy);
    if (pll) {
        MakeTransformation(&cpy, pll, NULL, 0);
        strcat(solution, pll);
        free(pll);
    }*/

    pll = SolutionF2L(cpy);
    if (pll) {
        MakeTransformation(&cpy, pll, NULL, 0);
        strcat(solution, pll);
        free(pll);
    }

    pll = SolutionOLLPart(cpy);
    if (pll) {
        MakeTransformation(&cpy, pll, NULL, 0);
        strcat(solution, pll);
        free(pll);
    }
    pll = SolutionPLLPart(cpy);
    if (pll) {
        MakeTransformation(&cpy, pll, NULL, 0);
        strcat(solution, pll);
        free(pll);
    }
    //Sleep(3000);
    printf("\nSolution: %s\n", solution);
    MakeTransformation(cube, solution, hDC, 1);
    free(solution);
}

#undef MAX_SOLUTION_LENGTH
