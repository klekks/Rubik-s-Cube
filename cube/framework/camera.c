#include <windows.h>
#include "glut.h"

#define _USE_MATH_DEFINES
#include <math.h>


#include "camera.h"

#include <stdio.h>

struct SCamera camera = {0, 0, 1.7, 63, 0, 315.5};

char  CheckingCursorMoving = 0;
static int posX = 0, posY = 0, startX = 0, startY = 0;
float movingSpeed;

void InitCamera(SCamera c) {
    camera.x = c.x;
    camera.y = c.y;
}

void CameraApply() {
    glRotatef(-camera.XRot, 1, 0, 0);
    glRotatef(-camera.YRot, 0, 1, 0);
    glRotatef(-camera.ZRot, 0, 0, 1);

    glTranslatef(-camera.x, -camera.y, -camera.z);
}


void CameraRotation(float xAngle, float zAngle){

    camera.ZRot += zAngle;
    if (camera.ZRot > 360) camera.ZRot -= 360;
    if (camera.ZRot < 0) camera.ZRot += 360;

    camera.XRot += xAngle;
    if (camera.XRot < 0) camera.XRot = 0;
    if (camera.XRot > 180) camera.XRot = 180;
}

void CameraAutoMoveByMouse(int centerX, int centerY, float speed) {
    POINT cur;
    POINT base = {centerX, centerY};
    GetCursorPos(&cur);
    CameraRotation((base.y - cur.y) * speed, (base.x - cur.x) * speed);
    SetCursorPos(base.x, base.y);
}


void CameraMoveByDirection(int forwardMove, int rightMove, float speed){
    float angle = -camera.ZRot / 180 * M_PI;

    if (forwardMove > 0)
        angle += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);
    else if (forwardMove < 0)
        angle += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));
    else {
        angle += rightMove > 0 ? M_PI_2 : -M_PI_2;
        if (rightMove == 0) speed = 0;
    }

    if (speed != 0) {
        camera.x += speed * sin(angle);
        camera.y += speed * cos(angle);
    }
}

void StartCursorMoving(float speed) {
    CheckingCursorMoving = 1;
    POINT pt;
    GetCursorPos(&pt);
    startX = pt.x;
    startY = pt.y;
    movingSpeed = speed;
}

void EndCursorMoving(int x, int y) {
    CheckingCursorMoving = 0;
}

void CheckingCursor(int x, int y) {
    if (!CheckingCursorMoving) {
        glRotatef(posX, 0, 0, 1);
        glRotatef(posY, 1, 0, 0);
        return;
    };
    POINT pt;
    GetCursorPos(&pt);
    int dx = (startX - pt.x) * movingSpeed;
    int dy = (startY - pt.y) * movingSpeed;
    //printf("%d %d\n", dx, dy);
    glRotatef(posX + dx, 0, 0, 1);
    glRotatef(posY + dy, 1, 0, 0);
    startX = pt.x;
    startY = pt.y;
    posX += dx;
    posY += dy;
}
