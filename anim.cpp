/* lexxaedr 02.05.2020 */
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "anim.h"
#include "GL/glut.h"

using namespace std;

kagl::anim kagl::anim::Instance;
kagl::anim::anim() : NumOfObjects(0), IsPause(0), StartTime(clock()), DeltaTime(0), SyncTime(0), PauseTime(0), Objects{}
{
    int arg = 1;
    const char* arr[] = { "test" };
    glutInit(&arg, const_cast<char**>(arr));
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Linux - the best OS in the world!");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    Timer();
}
kagl::anim& kagl::anim::operator<<(object* Object)
{
    if (NumOfObjects < MaxNumOfObjects)
        Objects[NumOfObjects++] = Object;
    return *this;
}

void kagl::anim::Display()
{
    glClearColor(0, 0.4, 0.9, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(1, 5, 9, 0, 0, 0, 0, 1, 0);
    Instance.Timer();
    for (int i = 0; i < Instance.NumOfObjects; i++)
    {
        glPushMatrix();
        Instance.Objects[i]->Draw(&Instance);
        glPopMatrix();
    }
    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

void kagl::anim::Reshape(int w, int h)
{
    double size = 0.1, rx = size, ry = size;
    if (w > h)
        rx *= (double)w / h;
    else
        ry *= (double)h / w;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, size, 100);
//	gluPerspective(60, (double)w  / h, 1, 500 );
    glMatrixMode(GL_MODELVIEW);
}

void kagl::anim::Keyboard( unsigned char key, int x, int y )
{
    for (int i = 0; i < Instance.NumOfObjects; i++)
        Instance.Objects[i]->Keyboard(&Instance, key);

    if (key == 27)
    {
        Instance.Clear();
        exit(0);
    }
}

kagl::anim::~anim()
{
    Clear();
}

void kagl::anim::Clear()
{
    for (int i = 0; i < NumOfObjects; i++)
    {
        delete Objects[i];
        Objects[i] = nullptr;
    }
    NumOfObjects = 0;
}

kagl::anim& kagl::anim::Get()
{
    return Instance;
}

kagl::cube::cube(double s) : size(s), angle(0), speed(200)
{}

void kagl::cube::Draw( kagl::anim* animation )
{
    angle += animation->DeltaTime * speed;
    glRotated(angle, 0, 1, 0);
    glTranslated(2, 0, 0);
    glutSolidTeapot(size);
}

void kagl::anim::Run()
{
    glutMainLoop();
}

void kagl::cube::Keyboard(anim* ani, int key)
{}

void kagl::anim::Timer()
{
    long t = clock();

    if (IsPause)
    {
        PauseTime += t - OldTime;
        DeltaTime = 0;
    }
    else
    {
        SyncTime = (t - StartTime - PauseTime) / (double)CLOCKS_PER_SEC;
        DeltaTime = (t - OldTime) / (double)CLOCKS_PER_SEC;;
    }
    OldTime = t;
}