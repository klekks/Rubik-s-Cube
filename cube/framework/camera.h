#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

typedef struct SCamera {
    float x,y,z;
    float XRot, YRot, ZRot;
} SCamera;

void CameraApply();
void CameraRotation(float, float);
void CameraAutoMoveByMouse(int centerX, int centerY, float speed);
void CameraMoveByDirection(int forwardMove, int rightMove, float speed);
void CameraMoveByMouse(int, int, float);
void CheckingCursor(int x, int y);
void StartCursorMoving(float speed);
void EndCursorMoving(int x, int y);
void InitCamera(SCamera c);

#endif // CAMERA_H_INCLUDED
