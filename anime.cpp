/* lexxaedr 02.05.2020 */

#include <cstdlib>
#include <iostream>
#include "anim.h"
#include "GL/glut.h"
#include "checker.h"

using namespace std;

int main(int argc, char** argv)
{
    kagl::anim& animation = kagl::anim::Get();
    kagl::checker* chk = new kagl::checker();
    animation << new kagl::bounce_ball(chk) << chk;
    animation.Run();
    return 0;
}