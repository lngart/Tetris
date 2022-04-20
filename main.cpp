#include "Menu.h"
#include <iostream>

int main()
try
{
    Menu  T;
    T.menu();

    return(Fl::run()) ;
}
catch (std::exception& e)
{
    std::cerr << "exception: " << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Oops, unknown exception" << std::endl;
    return 2;
}
