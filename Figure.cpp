#include "Figure.h"

int bordercolor = 0;

Figure::Figure()
{
    srand(time(0));
    color = rand() % 6 + 1; //генерируем числа в диапазоне от 1 до 7

    int middle = colmax/2;
    int choice = rand() % 7; //генерируем числа в диапазоне от 0 до 6

    switch(choice) //создаём фигуры
    {
    case 0: cubes[0].set_line(0); cubes[0].set_col(middle - 2);
            cubes[1].set_line(0); cubes[1].set_col(middle - 1);
            cubes[2].set_line(0); cubes[2].set_col(middle);
            cubes[3].set_line(0); cubes[3].set_col(middle + 1);
            type = 0;
            break;
    case 1: cubes[0].set_line(0); cubes[0].set_col(middle - 1);
            cubes[1].set_line(0); cubes[1].set_col(middle);
            cubes[2].set_line(0); cubes[2].set_col(middle + 1);
            cubes[3].set_line(1); cubes[3].set_col(middle + 1);
            type = 1;
            break;
    case 2: cubes[0].set_line(0); cubes[0].set_col(middle);
            cubes[1].set_line(0); cubes[1].set_col(middle-1);
            cubes[2].set_line(0); cubes[2].set_col(middle-2);
            cubes[3].set_line(1); cubes[3].set_col(middle-2);
            type = 2;
            break;
    case 3: cubes[0].set_line(0); cubes[0].set_col(middle);
            cubes[1].set_line(0); cubes[1].set_col(middle-1);
            cubes[2].set_line(1); cubes[2].set_col(middle);
            cubes[3].set_line(1); cubes[3].set_col(middle-1);
            type = 3;
            break;
    case 4: cubes[0].set_line(0); cubes[0].set_col(middle);
            cubes[1].set_line(0); cubes[1].set_col(middle+1);
            cubes[2].set_line(1); cubes[2].set_col(middle);
            cubes[3].set_line(1); cubes[3].set_col(middle-1 );
            type = 4;
            break;
    case 5: cubes[0].set_line(0); cubes[0].set_col(middle);
            cubes[1].set_line(0); cubes[1].set_col(middle+2);
            cubes[2].set_line(0); cubes[2].set_col(middle+1);
            cubes[3].set_line(1); cubes[3].set_col(middle+1);
            type = 5;
            break;
    case 6: cubes[0].set_line(0); cubes[0].set_col(middle);
            cubes[1].set_line(0); cubes[1].set_col(middle+1);
            cubes[2].set_line(1); cubes[2].set_col(middle+1);
            cubes[3].set_line(1); cubes[3].set_col(middle+2);
            type = 6;
            break;
    }
}

int Figure::get(int i, int v) const //1 - строка, 2 - столбец
{

    switch(v)
    {
    case 1:
        return cubes[i].get_line();
    case 2:
        return cubes[i].get_col();
    default:
        return -1;
    }
}

int Figure::get_color() const //цвет активного кубика
{
    return color ;
}

int Figure::get_type() const//тип фигуры, кубик которой активен
{
    return type ;
}

void Figure::move_down()
{
    for(int i = 0; i < 4; ++i)
        cubes[i].change_line(1);
}

bool Figure::can_move_right () const
{
    for(int i = 0; i < 4; ++i)
        if(cubes[i].get_col() == colmax - 1)
            return false;
    return true;
}

bool Figure::can_move_left () const
{
    for(int i = 0; i < 4; ++i)
        if(cubes[i].get_col() == 0)
            return false;
    return true;
}

void Figure::move_right(bool form[linemax][colmax])
{
    try
    {
        if(!can_move_right())
            throw 1;

        for(int i = 0; i < 4; ++i)
            if(form[cubes[i].get_line()][cubes[i].get_col() + 1])
                return;

        for(int i = 0; i < 4; ++i)
            cubes[i].change_col(1);
    }

    catch(int x)
    {
        bordercolor = x;
    }
}

void Figure::move_left(bool form[linemax][colmax])
{
    try
    {
        if(!can_move_left())
            throw 1;
        for(int i = 0; i < 4; ++i)
            if(form[cubes[i].get_line()][cubes[i].get_col() - 1])
                return;

        for(int i = 0; i < 4; ++i)
            cubes[i].change_col(-1);
    }
    catch(int x)
    {
        bordercolor = x;
    }
}

bool Figure::rotate_clockwise(int afterrotate[][2],      //возможен ли повотрот по часовой стрелке
                              bool form[linemax][colmax],
                              int ax_line, int ax_col)
{
    int colshift[4];
    int lineshift[4];
    for(int i = 0; i < 4; ++i)
    {
        lineshift[i] = ax_line - cubes[i].get_line();
        colshift[i] = cubes[i].get_col() - ax_col;
    }

    for(int i = 0; i < 4; ++i)
    {
        afterrotate[i][0] = ax_line + colshift[i]; // новая строка
        afterrotate[i][1] = ax_col + lineshift[i]; //новый столбец
    }

    for(int i = 0; i < 4; ++i)
    {
        if( (afterrotate[i][0] >= linemax                          ||
             afterrotate[i][0] <= 0                                ||
             afterrotate[i][1] >= colmax                           ||
             afterrotate[i][1] <= 0                                ||
             form[afterrotate[i][0]][afterrotate[i][1]])
           )
            return false ;
    }
    return true ;
}

bool Figure::rotate_counterclockwise(int afterrotate[][2],
                                     bool form[linemax][colmax],
                                     int ax_line, int ax_col) //повороот против часовой стрелки
{
    int colshift[4];
    int lineshift[4];
    for(int i = 0; i < 4; ++i)
    {
        lineshift[i] = ax_line - cubes[i].get_line();
        colshift[i] = cubes[i].get_col() - ax_col;
    }
    for(int i = 0; i < 4; ++i)
    {
        afterrotate[i][0] = ax_line - colshift[i]; //новая строка
        afterrotate[i][1] = ax_col - lineshift[i]; //новый столбец
    }

    for(int i = 0; i < 4; ++i)
    {
        if( (afterrotate[i][0] >= linemax                            ||
             afterrotate[i][0] <= 0                                  ||
             afterrotate[i][1] >= colmax                             ||
             afterrotate[i][1] <= 0                                  ||
             form[afterrotate[i][0]][afterrotate[i][1]])
           )
            return false ;
    }
    return true ;
}

void Figure::rotate_cw(bool form[linemax][colmax])
{
    int afterrotate[4][2];
    int ax_line,ax_col;
    ax_line = cubes[2].get_line(); //оси проходят через кубики с индексом 2
    ax_col = cubes[2].get_col();

    if(type!=3) //квадрат можно не поворачивать
    {
        try
        {
            if(!rotate_clockwise(afterrotate, form, ax_line, ax_col))
                throw 1;
            cubes[0].set_line(afterrotate[0][0]) ; cubes[0].set_col(afterrotate[0][1]) ;
            cubes[1].set_line(afterrotate[1][0]) ; cubes[1].set_col(afterrotate[1][1]) ;
            cubes[3].set_line(afterrotate[3][0]) ; cubes[3].set_col(afterrotate[3][1]) ;
        }
        catch(int x)
        {
            bordercolor = x;
        }
    }
}

void Figure::rotate_ccw(bool form[linemax][colmax])
{
    int afterrotate[4][2];
    int ax_line,ax_col;
    ax_line = cubes[2].get_line(); //оси проходят через кубики с индексом 2
    ax_col = cubes[2].get_col();

    if(type!=3) //квадрат можно не поворачивать
    {
        try
        {
            if(!rotate_counterclockwise(afterrotate, form, ax_line, ax_col))
                throw 1;
            cubes[0].set_line(afterrotate[0][0]) ; cubes[0].set_col(afterrotate[0][1]) ;
            cubes[1].set_line(afterrotate[1][0]) ; cubes[1].set_col(afterrotate[1][1]) ;
            cubes[3].set_line(afterrotate[3][0]) ; cubes[3].set_col(afterrotate[3][1]) ;
        }
        catch(int x)
        {
            bordercolor = x;
        }
    }
}
