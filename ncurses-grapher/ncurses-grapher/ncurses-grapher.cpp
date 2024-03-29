// ncurses-grapher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <curses.h>
#include <vector>
#include "ncurses-grapher.h"
#include <math.h>

std::pair<int, int> getScreenMiddle() 
{
    return std::make_pair(getmaxy(stdscr)/2, getmaxx(stdscr)/2);
}

void mapEquation(const std::pair<int, int>& screenMiddle)
{
    for (int x = screenMiddle.second - getmaxx(stdscr); x < getmaxx(stdscr); x++)
    {
        int intersectionCounter = 0;


        // Note: Since sin() and cos() functions return numbers close to 0 it is best to multiply the result by some arbitrary value
        const int equationResult = 5*sin(x);

        // The -0.5 transforms the graph in 2 ways:
        // 
        // The 0.5 makes the tilts the graph so it has a ~45 degree angle
        //  since the height of characters in the console != width of characters
        //  so drawing a diagonal looks weird it this isnt accounted for
        // 
        // The - rotates the graph since pdcurses' (0, 0) is the top left angle

        mvprintw(equationResult * -0.5 + screenMiddle.first, x + screenMiddle.second, "*");

    }

    mvprintw(1, 1, "Equation: sin(x)");
}

int main()
{
    initscr();

    const std::pair<int, int> screenMiddle = getScreenMiddle();

    drawAxies(screenMiddle);

    mapEquation(screenMiddle);

    getch();


    endwin();
}

void drawAxies(const std::pair<int, int>& screenMiddle)
{
    for (int xAxis = 0; xAxis < getmaxx(stdscr); xAxis++)
    {
        mvprintw(screenMiddle.first, xAxis, "-");
    }
    for (int yAxis = 0; yAxis < getmaxx(stdscr); yAxis++)
    {
        mvprintw(yAxis, screenMiddle.second, "|");
    }

    mvprintw(screenMiddle.first, 0, "<");
    mvprintw(screenMiddle.first, getmaxx(stdscr), ">");

    mvprintw(screenMiddle.first, screenMiddle.second, "+");
    mvprintw(screenMiddle.first + 1, screenMiddle.second + 1, "0");
}
