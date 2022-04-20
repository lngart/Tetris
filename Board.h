#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"
#include "Fl_Widget.H"
#include "Fl_Box.H"
#include "Figure.h"
#include "fl_draw.H"
#include "Fl.H"
#include "Fl_Button.H"
#include <sstream>
#include <string>

class Board : public Fl_Widget
{
    bool form[linemax][colmax]; //есть ли кубик (1 - да, 0 - нет)
    int fillcolor[linemax][colmax];
    int nextFigure[5][5];
    std::string scorelabel;
    Fl_Box* scorebox;
    int score;

    Figure nowfigure, nextfigure;

public:

    Board();

    static void timeractions(void *p);
    void set_score(Fl_Box **s);

private:
    bool can_down();
    void draw();
    void transfer_cubes();
    void delete_line();
    void draw_cube();
    bool create_figure();
    void delete_cube();
    void period();
    int handle(int h);
};

#endif // BOARD_H
