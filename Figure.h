#ifndef FIGURE_H
#define FIGURE_H

#include "Constants.h"
#include "Cube.h"
#include "cstdlib"
#include "ctime"

extern int bordercolor;

class Figure
{
    cube cubes[4];      // Фигура состоит из 4 кубиков
    int color;
    int type;           //Всего в игре 7 различных фигур

public:
    Figure();

    int get(int i, int var) const;
    int get_color() const;
    int get_type() const;
    void move_down();
    bool can_move_right() const;
    bool can_move_left() const;
    void move_right(bool form[linemax][colmax]);
    void move_left(bool form[linemax][colmax]);
    bool rotate_clockwise(int afterrotate[][2], bool form[linemax][colmax], int pivr, int pivc);
    bool rotate_counterclockwise(int afterrotate[][2], bool form[linemax][colmax], int pivr, int pivc);
    void rotate_cw(bool form[linemax][colmax]);
    void rotate_ccw(bool form[linemax][colmax]);
};

#endif // FIGURE_H
