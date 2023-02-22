#include <GL/freeglut.h>

void display(void)
{
    static GLint vertices[] = {
        25, 25,
        100, 325,
        175, 25,
        175, 325,
        250, 25,
        325, 325
    };

    static GLfloat colors[] = {
        1.0, 0.2, 0.2,
        0.2, 0.2, 1.0,
        0.8, 1.0, 0.2,
        0.75, 0.75, 0.75,
        0.35, 0.35, 0.35,
        0.5, 0.5, 0.5
    };

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(2, GL_INT, 0, vertices);


    static GLubyte allIndices[] = {
        4, 5, 6, 7, 1, 2, 6, 5,
        0, 1, 5, 4, 0, 3, 2, 1,
        0, 4, 7, 3, 2, 3, 7, 6
    };

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, allIndices);
    
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}