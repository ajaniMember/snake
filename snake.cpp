#include <ncurses.h>
#include <string>
#include <vector>
#include "snake.h"

snake::snake(int maxY, int maxX) : direction("R"), bottom(maxY), rightSide(maxX)
{

	snakeBody.push_back( std::make_pair(maxY/2, maxX/2) );
	snakeBody.push_back( std::make_pair(maxY/2, maxX/2-1) );
	snakeBody.push_back( std::make_pair(maxY/2, maxX/2-2) );
	snakeBody.push_back( std::make_pair(maxY/2, maxX/2-3) );
	snakeBody.push_back( std::make_pair(maxY/2, maxX/2-4) );
}

//changes direction variable to respective value
void snake::right()
{	
	//make sure we can't go backwards
	//forwards or sideways only!
	if(direction != "L")
	{
		direction = "R";
	}
}

void snake::left()
{
	//make sure we can't go backwards
	//forwards or sideways only!
	if(direction != "R")
	{
		direction = "L";
	}
}

void snake::up()
{
	//make sure we can't go backwards
	//forwards or sideways only!
	if(direction != "D")
	{
		direction = "U";
	}
}

void snake::down()
{
	//make sure we can't go backwards
	//forwards or sideways only!
	if(direction != "U")
	{
		direction = "D";
	}
}

//returns true if snake hits the side (game over)
bool snake::hitSide()
{
	int y = std::get<0>(snakeBody[0]);
	int x = std::get<1>(snakeBody[0]);

	if(direction == "R")
	{
		//if snake if just infront of right wall
		if(x == rightSide-2)
		{
			return TRUE;
		}

		return FALSE;
	}

	else if(direction == "L")
	{
		//if x is just in front of left wall
		if(x == 1)
		{
			return TRUE;
		}

		return FALSE;

	}

	else if(direction == "U")
	{
		//if y is just in front of the top wall
		if(y == 1)
		{
			return TRUE;
		}

		return FALSE;
	}

	else if(direction == "D")
	{
		if(y == bottom-2)
		{
			return TRUE;
		}

		return FALSE;
	}

}

bool snake::hitSnake()
{
	return FALSE;
}

bool snake::hitFruit()
{
	if(snakeBody[0] == fruit)
	{
		growAt.push_back(fruit);

		//generateFruit();

		return TRUE;
	}

	return FALSE;
}

//sets the y and x variables of each segment of the snakes body to the one behind it interms of the layout in te vector
//the first element of the vector being the head of the snake
// except the snakes head which will change depending on the value of the direction variable
void snake::updateBody()
{
	int snakeSize = snakeBody.size() - 1;
	int x = 0;
	int y = 0;
	int i = snakeSize;

	for(auto e = snakeBody.rbegin(); e != snakeBody.rend(); e++, i--)
	{
		//reached the head
		if(i == 0) break;

		if(i == snakeSize){

		}

		y = std::get<0>(snakeBody[i-1]);
		x = std::get<1>(snakeBody[i-1]);
		*e = std::make_pair(y, x);

	}
}

//moves the snake in the direction specified by the direction variable
bool snake::move()
{
	int y,x;
	if(growAt.size() > 0)
	{
		if(snakeBody.back() == growAt[0])
		{
			growNext = TRUE;
		}
	}
	
	if(growNext)
	{
		snakeBody.push_back(std::make_pair(0,0));
	}

	if(direction == "R")
	{
		//game is over?
		if(hitSide() || hitSnake())
		{
			
			return FALSE;
		}
		else{

			updateBody();
			y = std::get<0>(snakeBody[0]);
			x = std::get<1>(snakeBody[0]);
			snakeBody[0] = std::make_pair(y, x + 1);

		}

	}
	else if(direction == "L")
	{

		//game is over?
		if(hitSide() || hitSnake())
		{
			
			return FALSE;
		}
		else{

			updateBody();
			y = std::get<0>(snakeBody[0]);
			x = std::get<1>(snakeBody[0]);
			snakeBody[0] = std::make_pair(y, x - 1);

		}

	}
	else if(direction == "U")
	{
		//game is over?
		if(hitSide() || hitSnake())
		{
			
			return FALSE;
		}
		else{

			updateBody();
			y = std::get<0>(snakeBody[0]);
			x = std::get<1>(snakeBody[0]);
			snakeBody[0] = std::make_pair(y - 1, x);

		}

	}
	else if(direction == "D")
	{
		//game is over?
		if(hitSide() || hitSnake())
		{
			
			return FALSE;
		}
		else{

			updateBody();
			y = std::get<0>(snakeBody[0]);
			x = std::get<1>(snakeBody[0]);
			snakeBody[0] = std::make_pair(y + 1, x);

		}
	}

	render();
	return TRUE;
}

//adds another segment to the snake when the last segement passes the food
void snake::grow()
{
	snakeBody.push_back( growAt[0] );
	growAt.erase(growAt.begin());
}

//displays snake body
void snake::render()
{
	int y,x;

	for(auto e = snakeBody.begin(); e != snakeBody.end(); e++){

		y = std::get<0>(*e);
		x = std::get<1>(*e);

		mvaddch(y, x, '#');
	}
}