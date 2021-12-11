/* lexxaedr 02.05.2020 */

#ifndef _CHECKER_H
#define _CHECKER_H

#include <cmath>

namespace kagl
{
    class checker: public object
    {
    private:
        int w, h;
        double Color[8][8][3];
    public:
        checker() : w(8), h(8)
        {
            for (int x = 0; x < w; x++)
                for (int y = 0; y < h; y++)
                    if ((x ^ y) & 1)
                        Color[x][y][0] = Color[x][y][1] = Color[x][y][2] = 0;
                    else
                        Color[x][y][0] = Color[x][y][1] = Color[x][y][2] = 0.7;
        }
        void Keyboard(anim* Ani, int key) override
        {}
        void Draw(anim* Ani) override
        {
            const double h = 0.5;

            Translate();
            glDisable(GL_LIGHTING);
            glBegin(GL_LINES);
            glColor3d(1, 0, 0);
            glVertex3d(0, 0, 0);
            glVertex4d(1, 0, 0, 0);
            glColor3d(0, 1, 0);
            glVertex3d(0, 0, 0);
            glVertex4d(0, 1, 0, 0);
            glColor3d(0, 0, 1);
            glVertex3d(0, 0, 0);
            glVertex4d(0, 0, 1, 0);
            glEnd();
            glEnable(GL_LIGHTING);
            for (int x = 0; x < 8; x++)
                for (int y = 0; y < 8; y++)
                {
                    glPushMatrix();
                    glTranslated(x + 0.5, -h/2, y + 0.5);
                    glScaled(1, h, 1);
                    glColor3d(Color[x][y][0], Color[x][y][1], Color[x][y][2]);
                    glutSolidCube(1);
                    glPopMatrix();
                }
        }
        void Translate()
        {
            glTranslated(-w / 2, 0, -h / 2);
        }
        bool CorrectCeil(int x, int y)
        {
            return x >= 0 && x < 8 && y >= 0 && y < 8;
        }
        void FillCeil(int x, int y)
        {
            Color[x][y][0] = (double)rand() / RAND_MAX;
            Color[x][y][1] = (double)rand() / RAND_MAX;
            Color[x][y][2] = (double)rand() / RAND_MAX;
        }
    };

    class bounce_ball : public object
    {
    private:
        checker* Chk;
        int x, y;
        double dx, dy;
        bool moving;
        double time;
    public:
        explicit bounce_ball(checker* board) : Chk(board), moving(false), x(0), y(0), dx(0), dy(0)
        {}
        void Draw(anim* Ani) override
        {
            const double r = 0.5;
            const double speed = 100;

            glPushMatrix();
            Chk->Translate();
            if (moving)
            {
                double delta = (Ani->SyncTime - time) * speed;
                if (delta > 1)
                    x += dx, y += dy, Chk->FillCeil(x, y), dy = dx = 0, moving = false;
                glTranslated(x + 0.5 + dx * delta, r + (sin(delta * 3.1415) >= 0 ? sin(delta * 3.1415) : 0), y + 0.5 + dy * delta);
            }
            else
                glTranslated(x + 0.5, r, y + 0.5);
            glColor3d(1, 0, 0);
            glutSolidSphere(r, 20, 20);
            glPopMatrix();
        }
        void Keyboard(anim* Ani, int key) override
        {
            if (!moving)
            {
                if (key == 's')
                    if (Chk->CorrectCeil(x, y + 1))
                        dx = 0, dy = 1, time = Ani->SyncTime, moving = true;
                if (key == 'w')
                    if (Chk->CorrectCeil(x, y - 1))
                        dx = 0, dy = -1, time = Ani->SyncTime, moving = true;
                if (key == 'd')
                    if (Chk->CorrectCeil(x + 1, y))
                        dx = 1, dy = 0, time = Ani->SyncTime, moving = true;
                if (key == 'a')
                    if (Chk->CorrectCeil(x - 1, y))
                        dx = -1, dy = 0, time = Ani->SyncTime, moving = true;
            }
        }
    };
}

#endif