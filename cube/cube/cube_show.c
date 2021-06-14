#include <windows.h>
#include "glut.h"
#include "../params.h"
#include "../framework/camera.h"
#include "cube.h"

extern unsigned ROTATION_DELAY;

#define BaseColor BaseColor_
#define SEGMENT_RGB(A) BaseColor[A].r, BaseColor[A].g, BaseColor[A].b
RColor BaseColor_[] ={BASE_COLOR_NO_COLOR,BASE_COLOR_1, BASE_COLOR_2, BASE_COLOR_3, BASE_COLOR_4, BASE_COLOR_5, BASE_COLOR_6};



void CheckMessage(){
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT) exit(-3);
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
}

void ShowPartOfCube(RCube cube, int x1, int x2, int y1, int y2, int z1, int z2) {
    int i;
    glPushMatrix();
        glTranslatef(1.5f * EDGE_SIZE, 1.5f* EDGE_SIZE, 0);
    glPopMatrix();
    for (int z = z1; z < z2; z++)
    for (int y = y1; y < y2; y++)
    for (int x = x1; x < x2; x++) {
        i = x + 3 * y + 9 * z;
        glPushMatrix();
            glTranslatef(EDGE_SIZE * x - 1.5f* EDGE_SIZE, EDGE_SIZE * y - 1.5f * EDGE_SIZE, EDGE_SIZE * z - 1.5f * EDGE_SIZE);
            glBegin(GL_QUADS);
                // bottom
                glColor3ub(SEGMENT_RGB(cube.segment[i].color[0]));
                glVertex3f(0, 0, 0);
                glVertex3f(0, EDGE_SIZE, 0);
                glVertex3f(EDGE_SIZE, EDGE_SIZE, 0);
                glVertex3f(EDGE_SIZE, 0, 0);
                // left
                glColor3ub(SEGMENT_RGB(cube.segment[i].color[1]));
                glVertex3f(0, 0, 0);
                glVertex3f(0, EDGE_SIZE, 0);
                glVertex3f(0, EDGE_SIZE, EDGE_SIZE);
                glVertex3f(0, 0, EDGE_SIZE);
                //front
                glColor3ub(SEGMENT_RGB(cube.segment[i].color[2]));
                glVertex3f(0, 0, 0);
                glVertex3f(EDGE_SIZE, 0, 0);
                glVertex3f(EDGE_SIZE, 0, EDGE_SIZE);
                glVertex3f(0, 0, EDGE_SIZE);
                //right
                glColor3ub(SEGMENT_RGB(cube.segment[i].color[3]));
                glVertex3f(EDGE_SIZE, 0, 0);
                glVertex3f(EDGE_SIZE, EDGE_SIZE, 0);
                glVertex3f(EDGE_SIZE, EDGE_SIZE, EDGE_SIZE);
                glVertex3f(EDGE_SIZE, 0, EDGE_SIZE);
                //back
                glColor3ub(SEGMENT_RGB(cube.segment[i].color[4]));
                glVertex3f(0, EDGE_SIZE, EDGE_SIZE);
                glVertex3f(0, EDGE_SIZE, 0);
                glVertex3f(EDGE_SIZE, EDGE_SIZE, 0);
                glVertex3f(EDGE_SIZE, EDGE_SIZE, EDGE_SIZE);
                //top
                glColor3ub(SEGMENT_RGB(cube.segment[i].color[5]));
                glVertex3f(0, 0, EDGE_SIZE);
                glVertex3f(0, EDGE_SIZE, EDGE_SIZE);
                glVertex3f(EDGE_SIZE, EDGE_SIZE, EDGE_SIZE);
                glVertex3f(EDGE_SIZE, 0, EDGE_SIZE);
            glEnd();

            glEnable(GL_LINE_SMOOTH);
            //make black lines
            glLineWidth(SEPARATOR_LINE_WIDTH);
            glBegin(GL_LINE_STRIP);
                glColor3ub(SEGMENT_RGB(RCNoColor));
                glVertex3f(0,0,0);
                glVertex3f(EDGE_SIZE,0,0);
                glVertex3f(EDGE_SIZE,EDGE_SIZE,0);
                glVertex3f(0,EDGE_SIZE,0);
                glVertex3f(0,0,0);
                glVertex3f(0,0,EDGE_SIZE);
                glVertex3f(EDGE_SIZE,0,EDGE_SIZE);
                glVertex3f(EDGE_SIZE,0,0);
                glVertex3f(EDGE_SIZE,EDGE_SIZE,0);
                glVertex3f(EDGE_SIZE,EDGE_SIZE,EDGE_SIZE);
                glVertex3f(EDGE_SIZE,0,EDGE_SIZE);
                glVertex3f(EDGE_SIZE,EDGE_SIZE,EDGE_SIZE);
                glVertex3f(0,EDGE_SIZE,EDGE_SIZE);
                glVertex3f(0,0,EDGE_SIZE);
                glVertex3f(0,EDGE_SIZE,EDGE_SIZE);
                glVertex3f(0,EDGE_SIZE,0);
            glEnd();
        glPopMatrix();
    }
}


void A_RCubeLeftPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("L\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 1, 3, 0, 3, 0, 3);
            glRotated(alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 0, 1, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeLeftPlus(cube);
 }

void A_RCubeLeftMinus(RCube* cube, HDC hDC, char show) {
    if (show) printf("L'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 1, 3, 0, 3, 0, 3);
            glRotated(-alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 0, 1, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeLeftMinus(cube);
}

void A_RCubeRightPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("R\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 2, 0, 3, 0, 3);
            glRotated(-alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 2, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
    RCubeRightPlus(cube);
}

void A_RCubeRightMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("R'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 2, 0, 3, 0, 3);
            glRotated(alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 2, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeRightMinus(cube);
}

void A_RCubeUpPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("U\n");
	int alpha = 0;
	if (show) 
        while (alpha < 90) {
            alpha += D_ALPHA;
            glClearColor(BACKGROUND_COLOR);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 2);
            glRotated(-alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 2, 3);
            glPopMatrix();
            SwapBuffers(hDC);
            Sleep(ROTATION_DELAY);
	    }
    RCubeUpPlus(cube);
}

void A_RCubeUpMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("U'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 2);
            glRotated(alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 2, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeUpMinus(cube);
}

void A_RCubeuPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("u\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 1);
            glRotated(-alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 1, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
    RCubeuPlus(cube);
}

void A_RCubeuMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("u'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 1);
            glRotated(alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 1, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeuMinus(cube);
}

void A_RCubeDownMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("D'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 1, 3);
            glRotated(-alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 1);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
    RCubeDownMinus(cube);
}

void A_RCubeDownPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("D\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 1, 3);
            glRotated(alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 1);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeDownPlus(cube);
}


void A_RCubedMinus(RCube* cube, HDC hDC, char show) {
    if (show) printf("d'\n");
    int alpha = 0;
    if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        CameraApply();
        CheckingCursor(0, 0);
        ShowPartOfCube(*cube, 0, 3, 0, 3, 2, 3);
        glRotated(-alpha, 0, 0, 1);
        ShowPartOfCube(*cube, 0, 3, 0, 3, 1, 2);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
    }
    RCubedMinus(cube);
}

void A_RCubedPlus(RCube* cube, HDC hDC, char show) {
    if (show) printf("d\n");
    int alpha = 0;
    if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        CameraApply();
        CheckingCursor(0, 0);
        ShowPartOfCube(*cube, 0, 3, 0, 3, 2, 3);
        glRotated(alpha, 0, 0, 1);
        ShowPartOfCube(*cube, 0, 3, 0, 3, 1, 2);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
    }
    RCubedPlus(cube);
}


void A_RCubeFrontPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("F\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 1, 3, 0, 3);
            glRotated(alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 1, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
    RCubeFrontPlus(cube);
}

void A_RCubeFrontMinus(RCube* cube, HDC hDC, char show) {
    if (show) printf("F'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 1, 3, 0, 3);
            glRotated(-alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 1, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeFrontMinus(cube);
}

void A_RCubeBackPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("B\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 2, 0, 3);
            glRotated(-alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 2, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeBackPlus(cube);
}

void A_RCubeBackMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("B'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 2, 0, 3);
            glRotated(alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 2, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeBackMinus(cube);
}

void A_RCubeMiddleXPlus(RCube* cube, HDC hDC, char show) {
    if (show) printf("S\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 1, 0, 3);
            ShowPartOfCube(*cube, 0, 3, 2, 3, 0, 3);
            glRotated(alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 1, 2, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeMiddleXPlus(cube);
}

void A_RCubeMiddleXMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("S'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 1, 0, 3);
            ShowPartOfCube(*cube, 0, 3, 2, 3, 0, 3);
            glRotated(-alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 1, 2, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeMiddleXMinus(cube);
}


void A_RCubelPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("l\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 2, 3, 0, 3, 0, 3);
            glRotated(alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 0, 2, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubelPlus(cube);
}

void A_RCubelMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("l'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 2, 3, 0, 3, 0, 3);
            glRotated(-alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 0, 2, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubelMinus(cube);
}

void A_RCuberPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("r\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 1, 0, 3, 0, 3);
            glRotated(-alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 1, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCuberPlus(cube);
}

void A_RCuberMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("r'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 1, 0, 3, 0, 3);
            glRotated(alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 1, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCuberMinus(cube);
}

void A_RCubefPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("f\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 2, 3, 0, 3);
            glRotated(alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 2, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubefPlus(cube);
}

void A_RCubefMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("f'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            ShowPartOfCube(*cube, 0, 3, 2, 3, 0, 3);
            glRotated(-alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 2, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubefMinus(cube);
}

void A_RCubeRotateXPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("x\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            glRotated(-alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeRotateXPlus(cube);
}

void A_RCubeRotateXMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("x'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            glRotated(alpha, 1, 0, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeRotateXMinus(cube);
}

void A_RCubeRotateYPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("y\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            glRotated(-alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeRotateYPlus(cube);
}

void A_RCubeRotateYMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("y'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            glRotated(alpha, 0, 0, 1);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeRotateYMinus(cube);
}

void A_RCubeRotateZPlus(RCube* cube, HDC hDC, char show) {
	if (show) printf("z\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            glRotated(alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
    RCubeRotateZPlus(cube);
}

void A_RCubeRotateZMinus(RCube* cube, HDC hDC, char show) {
	if (show) printf("z'\n");
	int alpha = 0;
	if (show) while (alpha < 90) {
        alpha += D_ALPHA; //CheckMessage();
        glClearColor(BACKGROUND_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
            CameraApply();
            CheckingCursor(0, 0);
            glRotated(-alpha, 0, 1, 0);
            ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);
        glPopMatrix();
        SwapBuffers(hDC);
        Sleep(ROTATION_DELAY);
	}
	RCubeRotateZMinus(cube);
}

