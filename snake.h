#include <ncurses.h>
#include <string>
#include <vector>
#include <utility>

class snake
{
	
	public:

		snake(int maxY, int maxX);
		//changes direction variable to respective value
		void left();
		void right();
		void up();
		void down();

		//moves the snake in the direction specified by the direction variable
		bool move();

		//adds another segment to the snake when the last segement passes the food
		void grow();

		//displays snake body
		void render();


	private:

		std::vector< std::pair<int, int> > snakeBody;
		std::pair<int, int> fruit;

		//positions at which the snake will add a segement
		std::vector< std::pair<int, int> > growAt;

		//direction snake is currently traveling in
		std::string direction;

		bool growNext = FALSE;

		//max x value
		int rightSide;
		//max y value
		int bottom;

		//sets the y and x variables of each segment of the snakes body to the one behind it in terms of the layout in the vector
		//the first element of the vector being the head of the snake
		// except the snakes head which will change depending on the value of the direction variable
		void updateBody();

		//returns true if snake hits the side (game over)
		bool hitSide();
		bool hitSnake();
		bool hitFruit();
};