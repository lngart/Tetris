#ifndef MENU_H
#define MENU_H

#include "Fl_Window.H"
#include "Fl_Box.H"
#include "Board.h"
#include "Fl.H"
#include "Fl_Button.H"
#include "Fl_Double_Window.H"


class Menu
{
public:

    static Fl_Double_Window *menu_win;
    static Fl_Double_Window *help_win;
    static Fl_Double_Window *game_win;

    static void start_cb(Fl_Widget*, void*);
    static void close_cb(Fl_Widget*, void*);
    static void help_cb(Fl_Widget*, void*);

    static void menu();
};

#endif // MENU_H
