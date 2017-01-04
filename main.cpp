#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include <chrono>
#include <thread>
#include "snake.h"


void create_border(int maxY, int maxX)
{

	for(int i = 0; i <= maxX; i++)
	{
		mvaddch(0,i, '+');
		mvaddch(maxY-1, i, '+');
	}

	for(int i = 0; i <= maxY; i++)
	{
		mvaddch(i, 0, '+');
		mvaddch(i, maxX-1, '+');
	}
}


int main()
{
 
	char input;

	int maxY, maxX;
	initscr();	

	getmaxyx(stdscr,maxY,maxX);
	snake s(maxY, maxX);

	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	while(input != 'q')
	{
		create_border(maxY, maxX);
		timeout(250);
		input = getch();

		if((int)input == 'l')
		{
			addch('!');
			s.right();
		}
		else if((int)input == 'h')
		{
			addch('!');
			s.left();
		}
		else if((int)input == 'j')
		{
			addch('!');
			s.up();
		}
		else if((int)input == 'k')
		{
			addch('!');
			s.down();
		}

		if(s.move())
		{
			clear();
			create_border(maxY, maxX);
			s.render();
		}
		else
		{
			break;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}


	refresh();
	getch();
	endwin();

	return 0;
}