#ifndef CUBE_H
#define CUBE_H

class cube
{
    int line, col;       // строка(x) и столбец(y)

public:

    void set_line(int x) { line = x; }
    void set_col(int y) { col = y; }

    void change_line(int x) { line += x; }
    void change_col(int y) { col += y; }

    int get_line() const { return line; }
    int get_col() const { return col; }
};

#endif // CUBE_H
