#include "Board.h"

Board::Board(): Fl_Widget(0, 0, colmax * cubesize + 300, linemax * cubesize, "Tetris")
{
    int i,j;

    for(i = 0; i < linemax; ++i)
        for(j = 0; j < colmax; ++j)
        {
            form[i][j] = false;
            fillcolor[i][j] = backcolor;
        }

    for(i = 0; i < 5; ++i)
        for(j = 0; j < 5; ++j)
            nextFigure[i][j] = figureboxcolor;

    score = 0;
}

void Board::timeractions(void *p)
{
    (static_cast<Board*>(p))->period();
}

void Board::set_score(Fl_Box **s)
{
    scorebox = *s;
    score = 0;
}

bool Board::can_down()
{
    for(int i = 0; i < 4; ++i)
        if( (nowfigure.get(i, 1) >= linemax)                                                      ||
            (form[nowfigure.get(i, 1) + 1][nowfigure.get(i , 2)])                                 ||
            (fillcolor[nowfigure.get(i, 1) + 1][nowfigure.get(i , 2)] != backcolor                &&
             fillcolor[nowfigure.get(i, 1) + 1][nowfigure.get(i , 2)] != nowfigure.get_color())
          )
            return false;
    return true;
}

void Board::draw() //рисуем доску
{
    int i, j;

    for(i = 0; i < linemax; ++i)
        for(j = 0; j < colmax; ++j)
            if(fillcolor[i][j] != backcolor)
                fl_draw_box(FL_BORDER_BOX, 5 + j*cubesize,
                            i*cubesize-5, cubesize, cubesize, fillcolor[i][j]); //рисуем фигуры
            else
                fl_draw_box(FL_FLAT_BOX, 5 + j*cubesize,
                            i*cubesize-5, cubesize, cubesize, fillcolor[i][j]); //фон

    for(i = 0; i < 5; ++i)    //какая следующая фигура
        for(j = 0; j < 5; ++j)
            if(nextFigure[i][j] != figureboxcolor)
                fl_draw_box(FL_BORDER_BOX, (j + colmax + 4)*cubesize, (i + linemax/2 + 2)*cubesize, cubesize, cubesize, nextFigure[i][j]);
            else
                fl_draw_box(FL_FLAT_BOX, (j + colmax + 4 )*cubesize, (i + linemax/ 2 + 2)*cubesize , cubesize, cubesize, nextFigure[i][j]);

    fl_draw_box(FL_FLAT_BOX, colmax*cubesize + 5, 0, 5, linemax*cubesize, bordercolor);  //границы игрового поля
    fl_draw_box(FL_FLAT_BOX, 0, 0, 5, linemax*cubesize, bordercolor);
    fl_draw_box(FL_FLAT_BOX, 5, 0, colmax*cubesize, 5, bordercolor);
    fl_draw_box(FL_FLAT_BOX, 5, linemax*cubesize-5, colmax*cubesize, 5, bordercolor);
}

void Board::transfer_cubes()
{
    for(int i = 0; i < 4; ++i)
    {
        fillcolor[nowfigure.get(i, 1)][nowfigure.get(i, 2)] = nowfigure.get_color();
        form[nowfigure.get(i, 1)][nowfigure.get(i , 2)] = true ;
    }

    delete_line();
    draw();
}

void Board::delete_line()
{
    bool flag;
    int i;

    for(i = 0; i < linemax; ++i)
    {
        flag = true;

        for(int j = 0; j < colmax; ++j)
            if(form[i][j] == false)
                flag = false;

        if(flag) //сдвиг строк на 1 вниз
        {
            for(int j = i; j >= 1; --j)
            {
                for(int k = 0; k < colmax; ++k)
                {
                    form[j][k] = form[j - 1][k];
                    fillcolor[j][k] = fillcolor[j - 1][k] ;
                }
            }

            for(int k = 0; k < colmax; ++k)
            {
                form[0][k] = false;
                fillcolor[0][k] = backcolor;
            }

            ++score;
        }
    }
}

void Board::draw_cube()
{
    for(int i = 0; i < 4; ++i)
        fillcolor[nowfigure.get(i , 1)][nowfigure.get(i , 2)] = nowfigure.get_color();
}


int Board::handle(int h)
{
    if(h == FL_KEYDOWN)
    {
        switch(Fl::event_key())
        {
            case FL_Escape: exit(0);
            case FL_Left:
            {
                delete_cube();
                nowfigure.move_left(form);
                draw_cube();
                break;
            }
            case FL_Right:
            {
                delete_cube();
                nowfigure.move_right(form);
                draw_cube();
                break;
            }
            case FL_Up:
            {
                delete_cube();
                nowfigure.rotate_cw(form);
                draw_cube();
                break;
            }
            case FL_Down:
            {
                delete_cube();
                nowfigure.rotate_ccw(form);
                draw_cube();
                break;
            }
            case spacebar:
            {
                while(can_down())
                {
                    delete_cube();
                    nowfigure.move_down();
                    draw_cube();
                }
            }
        }
    }
    redraw();
}

bool Board::create_figure()
{
    nowfigure = nextfigure;
    for(int i = 0; i < 4; ++i)
        if(fillcolor[nowfigure.get(i, 1)][nowfigure.get(i, 2)] != backcolor)
            return false;
    return true;
}

void Board::delete_cube()
{
    for(int i = 0; i < 4; ++i)
        fillcolor[nowfigure.get(i , 1)][nowfigure.get(i , 2)] = backcolor;
}

void Board::period()
{
    bordercolor = 0;
    if(can_down())
    {
        delete_cube();
        nowfigure.move_down();
        draw_cube();
    }
    else
    {
        transfer_cubes();
        if(!create_figure())
        {
            std::stringstream game_over_label;
            game_over_label << score;
            std::string temp_str = game_over_label.str();
            scorelabel ="Gameover\n Score: ";
            scorelabel += temp_str;

            scorebox->label(scorelabel.c_str());
            redraw();

            Fl_Window *game_over_win = new Fl_Window(500,250,300,300,"Game Over");
            game_over_win -> set_modal();
            game_over_win -> callback([](Fl_Widget*, void*)
                                    {if (Fl::event()==FL_SHORTCUT && Fl::event_key()==FL_Escape)
                                     return;
                                     exit(0);});

            Fl_Box *game_over_box = new Fl_Box(70,40,160,60,scorelabel.c_str());
            game_over_box -> labelsize(30);

            Fl_Button *exit_btn  = new Fl_Button(70,220,160,60,"Quit");
            exit_btn -> labelsize(20);
            exit_btn -> labelfont(FL_ITALIC);
            exit_btn -> callback([](Fl_Widget*, void*){ exit(0); });

            game_over_win -> end();
            game_over_win -> show();

            Fl::run();
        }

        Figure newfigure;
        nextfigure = newfigure;

        for(int i = 0; i < 5; ++i)
            for(int j = 0 ; j < 5; ++j)
                nextFigure[i][j] = figureboxcolor;

        switch(nextfigure.get_type())
        {
        case 0:
            nextFigure[2][0] = nextFigure[2][1] = nextFigure[2][2] = nextFigure[2][3] = nextfigure.get_color();
            break;
        case 1:
            nextFigure[1][1] = nextFigure[1][2] = nextFigure[1][3] = nextFigure[2][3] = nextfigure.get_color();
            break ;
        case 2:
            nextFigure[1][1] = nextFigure[1][2] = nextFigure[1][3] = nextFigure[2][1] = nextfigure.get_color();
            break;
        case 3:
            nextFigure[2][1] = nextFigure[2][2] = nextFigure[3][1] = nextFigure[3][2] = nextfigure.get_color();
            break;
        case 4:
            nextFigure[1][2] = nextFigure[1][3] = nextFigure[2][1] = nextFigure[2][2] = nextfigure.get_color();
            break;
        case 5:
            nextFigure[1][1] = nextFigure[1][2] = nextFigure[1][3] = nextFigure[2][2] = nextfigure.get_color();
            break;
        case 6:
            nextFigure[1][1] = nextFigure[1][2] = nextFigure[2][2] = nextFigure[2][3] = nextfigure.get_color();
            break;
        }
    }
    std::stringstream game_score_label;
    game_score_label << score;
    std::string temp_str = game_score_label.str();
    scorelabel = "Score : ";
    scorelabel += temp_str.c_str();

    scorebox->label(scorelabel.c_str());
    redraw() ;
    Fl::repeat_timeout(speedtime,timeractions,this);
}
