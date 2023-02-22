#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "teapot.h"

// GLUT CALLBACK functions
void displayCB();
void reshapeCB(int w, int h);
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);

void initGL();
int  initGLUT(int argc, char **argv);
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);

// global variables
GLuint listId = 0; // id of display list
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX = 0;
float cameraAngleY = 0;
float cameraDistance;

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    mouseLeftDown = mouseRightDown = false;

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();

    // compile a display list of teapot mesh
    // see detail in createTeapotDL()
    listId = createTeapotDL();

    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}

int initGLUT(int argc, char **argv)
{
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(400, 300);               // window size

    glutInitWindowPosition(100, 100);           // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);
    glutReshapeFunc(reshapeCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    return handle;
}

void initGL()
{
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    setCamera(0, 0, 10, 0, 0, 0);
}

void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

void displayCB()
{
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    // tramsform camera
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading

    drawTeapot();           // render with vertex array, glDrawElements()
    glPopMatrix();
    glutSwapBuffers();
}

void reshapeCB(int w, int h)
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // set perspective viewing frustum
    float aspectRatio = (float)w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-aspectRatio, aspectRatio, -1, 1, 1, 100);
    gluPerspective(60.0f, aspectRatio, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
}

void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
            mouseLeftDown = true;
        else if(state == GLUT_UP)
            mouseLeftDown = false;

        break;
    case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN)
            mouseRightDown = true;
        else if(state == GLUT_UP)
            mouseRightDown = false;
        break;
    default:
        break;
    }
}

void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}
