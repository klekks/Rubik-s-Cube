#include <windows.h>
#include <stdio.h>
#include <glut.h>

#include "framework/camera.h"
#include "framework/window.h"
#include "cube/cube.h"
#include "cube/cube_show.h"
#include "cube/cube_solver.h"
#include "params.h"

extern unsigned ROTATION_DELAY;
extern Queue TQ;

#ifdef HAS_MENU
    #include "framework/menu.h"
#endif // HAS_MENU



LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

RCube *cube;
HDC hDC;
char shifted = 0;
BOOL bQuit = FALSE;
HWND hwnd;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    WNDCLASSEX wcex;

    HGLRC hRC;
    MSG msg;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Rubik's Cube";
    wcex.hIconSm = (HICON)LoadImage(NULL, TEXT("newicon.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                            L"Rubik's Cube",
                            L"Rubik's Cube Simulator",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          WINDOW_DEFAULT_HEIGHT,
                          WINDOW_DEFAULT_WIDTH,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    if (HAS_MENU) InitMenu(hwnd);

#ifdef DEBUG
#if DEBUG==1
        if (AllocConsole())
        {
            FILE* fi = 0;
            freopen_s(&fi, "CONOUT$", "w", stdout);
        }
        AttachConsole(ATTACH_PARENT_PROCESS);
#endif
#endif
    ShowWindow(hwnd, nCmdShow);
    
    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    RECT rct;
    GetClientRect(hwnd, &rct);
    WndResize(rct.right, rct.bottom);

    glEnable(GL_DEPTH_TEST);          // подключение буфера глубины

    SCamera camera = {0,0,0,0,0,0};

    camera.x = -2.5;
    camera.y = -2.5;
    InitCamera(camera);               // инициализация камеры

    cube = CreateCube(); // инициализация куба


    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

           
            if (TQ.size > 0) {
                void (*f)(RCube*, HDC, char);
                f = QueuePop(&TQ);
                f(cube, hDC, 1);
            }
            else {
                glClearColor(BACKGROUND_COLOR);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glPushMatrix();

                CameraApply();
                CheckingCursor(0, 0);
                ShowPartOfCube(*cube, 0, 3, 0, 3, 0, 3);

                glPopMatrix();

                SwapBuffers(hDC);

                Sleep(1);
            }
            
            
        }
    }

    /* Exit */
    exit_backdoor:;
    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

int width;
wchar_t* path;
int height;
char* pll;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            WndResize(LOWORD(lParam), HIWORD(lParam));
        break;

        case WM_LBUTTONDOWN:
            StartCursorMoving(-0.2f);
            break;

        case WM_COMMAND:
            switch(wParam) {
            case SAVE_BTN:
                path = UploadFile(hwnd);
                SaveCube(path, *cube);
                free(path);
                break;

            case EXIT_BTN:
                QueueClear(&TQ);
                bQuit = TRUE;
                break;

            case LOAD_BTN:
                QueueClear(&TQ);
                path = LoadFile(hwnd);
                RCube* tmp_cube = LoadCube(path, hwnd);

                if (tmp_cube) {
                    free(cube);
                    cube = tmp_cube;
                }
                free(path);
                break;

            case NEW_BTN:
                QueueClear(&TQ);
                free(cube);
                cube = CreateCube();
                break;

            case MIX_BTN:
                QueueClear(&TQ);
                MixCube(&cube, hDC);
                printf("MIX\n");
                break;

            case SOLVE_BTN:
                Solve(cube, hDC);
                printf("SOLVE\n");
                break;

            case ABOUT_BTN:
                MessageBox(hwnd, L"Rubik's cube simulator by Ilya Petrov v.3.2", L"About", MB_OK);
                break;
            }
            break;

        case WM_LBUTTONUP:
            EndCursorMoving(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_SHIFT:
                    shifted = 1;
                break;

                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;

                case 0x55: //U
                    if (!shifted) A_RCubeUpPlus(cube, hDC, 1);
                    else A_RCubeUpMinus(cube, hDC, 1);
                    break;
                case 0x46: //F
                    if (!shifted) A_RCubeFrontPlus(cube, hDC, 1);
                    else A_RCubeFrontMinus(cube, hDC, 1);
                    break;
                case 0x52: //R
                    if (!shifted) A_RCubeRightPlus(cube, hDC, 1);
                    else A_RCubeRightMinus(cube, hDC, 1);
                    break;
                case 0x4C: //L
                    if (!shifted) A_RCubeLeftPlus(cube, hDC, 1);
                    else A_RCubeLeftMinus(cube, hDC, 1);
                    break;
                case 0x44: //D
                    if (!shifted) A_RCubeDownPlus(cube, hDC, 1);
                    else A_RCubeDownMinus(cube, hDC, 1);
                    break;
                case 0x42: //B
                    if (!shifted) A_RCubeBackPlus(cube, hDC, 1);
                    else A_RCubeBackMinus(cube, hDC, 1);
                    break;
                case 0x58: //X
                    if (!shifted) A_RCubeRotateXPlus(cube, hDC, 1);
                    else A_RCubeRotateXMinus(cube, hDC, 1);
                    break;
                case 0x59: //Y
                    if (!shifted) A_RCubeRotateYPlus(cube, hDC, 1);
                    else A_RCubeRotateYMinus(cube, hDC, 1);
                    break;
                case 0x60: //Z
                    if (!shifted) A_RCubeRotateZPlus(cube, hDC, 1);
                    else A_RCubeRotateZMinus(cube, hDC, 1);
                    break;
                case 0x4D: //M
                    QueueClear(&TQ);
                    MixCube(&cube, hDC);
                    break;
                case 0x4E: //N
                    QueueClear(&TQ);
                    free(cube);
                    cube = CreateCube();
                    break;
                case 0x45: //E
                    path = UploadFile(hwnd);
                    SaveCube(path, *cube);
                    free(path);
                    break;
                case 0x49: //I
                    QueueClear(&TQ);
                    path = LoadFile(hwnd);
                    RCube* tmp_cube = LoadCube(path, hwnd);

                    if (tmp_cube) {
                        free(cube);
                        cube = tmp_cube;
                    }
                    free(path);
                    break;
                case 0x53: //S
                    Solve(cube, hDC);
                    break;
#ifdef DEBUG
#if DEBUG==1
                case 0x43: // Cross
                    pll = SolutionCrossPart(*cube);
                    if (pll) {
                        MakeTransformation(cube, pll, hDC, 1);
                        free(pll);
                    }
                    break;
                case 0x4F: // oll
                    pll = SolutionOLLPart(*cube);
                    if (pll) {
                        MakeTransformation(cube, pll, hDC, 1);
                        free(pll);
                    }
                    break;
                case 0x50:
                    pll = SolutionPLLPart(*cube);
                    if (pll) {
                        MakeTransformation(cube, pll, hDC, 1);
                        free(pll);
                    }
                    break;
                case 0x54: // two layers
                    pll = SolutionF2L(*cube);
                    if (pll) {
                        MakeTransformation(cube, pll, hDC, 1);
                        free(pll);
                    }
                    /*if (pll) {
                        MakeTransformation(cube, pll, hDC, 1);
                        free(pll);
                    }
                    pll = SolutionSL(*cube);
                    if (pll) {
                        MakeTransformation(cube, pll, hDC, 1);
                        free(pll);
                        break;
                    }*/
                break;
#endif
#endif
            }
        }
        break;

        case WM_KEYUP:
        {
            switch (wParam)
            {
                case VK_SHIFT:
                    shifted = 0;
                break;

            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

