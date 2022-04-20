#include "Menu.h"

void Menu::menu()
{
    menu_win->begin();

    Fl_Box *menu_label = new Fl_Box(70,40,160,60,"Menu");

    Fl_Button *start_btn = new Fl_Button(70,100,160,60,"Start");
    Fl_Button *help_btn  = new Fl_Button(70,160,160,60,"Help");
    Fl_Button *quit_btn  = new Fl_Button(70,220,160,60,"Quit");

    menu_label -> labelsize(25);

    start_btn -> labelsize(20);
    help_btn  -> labelsize(20);
    quit_btn  -> labelsize(20);

    start_btn -> labelfont(FL_ITALIC);
    help_btn  -> labelfont(FL_ITALIC);
    quit_btn  -> labelfont(FL_ITALIC);

    start_btn -> callback(start_cb);
    help_btn  -> callback(help_cb);
    quit_btn  -> callback(close_cb);

    menu_win -> end();
    menu_win -> show();

}

Fl_Double_Window* Menu::menu_win = new Fl_Double_Window(500,250,300,300,"Menu");

void restart_cb(Fl_Widget*, void*);

void Menu::start_cb(Fl_Widget*, void*)
{
    menu_win->hide();

    game_win = new Fl_Double_Window(800 , linemax * cubesize , "Tetris");
    game_win -> color(backcolor);

    Fl_Box* scorebox = new Fl_Box(cubesize*colmax+40,100,320,80,"Score : 0\0") ;
    scorebox -> box(FL_FLAT_BOX) ;
    scorebox -> labelfont(FL_BOLD) ;
    scorebox -> labeltype(FL_NORMAL_LABEL) ;
    scorebox -> labelsize(30) ;
    scorebox -> color(55);

    Board* B = new Board();
    B-> set_score(&scorebox);

    game_win->end() ;
    game_win->show() ;

    Fl::add_timeout(0.1, Board::timeractions,B);
}

Fl_Double_Window* Menu::game_win = new Fl_Double_Window(800 , linemax * cubesize , "Tetris");

void back_cb(Fl_Widget*, void*)
{
    Menu::help_win -> hide();
    Menu::menu();
}

void Menu::help_cb(Fl_Widget*, void*)
{
    menu_win -> hide();

    help_win = new Fl_Double_Window(500,250,300,300,"Menu");

    const char* manual = "Tetris is a puzzle based on\n"
                         "the use of geometric shapes\n"
                         "consisting of four squares.\n"
                         "\n"
                         "Use the right(→) and left(←)\n"
                         "arrows to move.\n"
                         "Use the up(↑) and down(↓)\n"
                         "arrows to rotate the shape.\n"
                         "Use the space bar to avoid\n"
                         "waiting for the shape to drop.\n";

    Fl_Box *help_label = new Fl_Box{70,90,160,60, manual};
    help_label -> labelsize(20);

    Fl_Button *back_btn = new Fl_Button(70,250,160,30,"Back");
    back_btn -> callback(back_cb);
    back_btn -> labelsize(20);
    back_btn -> labelfont(FL_ITALIC);

    help_win->end();
    help_win->show();
}

Fl_Double_Window* Menu::help_win = new Fl_Double_Window(500,250,300,300,"Menu");

void Menu::close_cb(Fl_Widget*, void*)
{
    exit(0);
}
