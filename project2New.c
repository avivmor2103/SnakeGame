#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define COLS 75 
#define ROWS 25 

//this a struct for the loction in cordinat so it will appear as a pair ,
//in one name int the node's definition .
typedef struct cordinate
{
	int x;
	int y;
}cordinate;

//creation of the node in a struct type .
typedef struct SnakeBody
{
	cordinate point;
	struct SnakeBody* next;
}SnakeBody;

// terminal escape codes/ANSI escape codes (or ANSI escape sequences)
// "\x1B" is the escape character that tells your terminal that what comes next is not meant to be printed on the screen, 
// but rather a command to the terminal (or most likely terminal emulatoion).

// Turn escape codes ON.
void init(void);

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y);

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs);

//This function prints the borders of the game ,
//which the snake can not cross. 
//In case he touches them he is disqualified .
void printBoard();

//This function creat a new node in the memory.
SnakeBody* createNewNode(cordinate point , SnakeBody* next);

//This function prints on the board the the value of each node with the simbol '@' .
void printSnake(SnakeBody*head);

//This function get from the main the last snake's cordinate of the head .
//And also he gets a direction order so the fanction knows to change the next cordinate of the snake .
cordinate snakeMovment(char direction , cordinate point);

//This fanction put spaces after every cordinate that the snake was located in ,
//insted of '@' that was in those locations , in accordance to the snake's length .
void deleteNodeFromSnake(SnakeBody* head);

//This funtion premote the head of the snake by calling to func "creatNewNode" ,
//and put another node , so the snake will have a new head infront of him for everywhere he goes .
SnakeBody* insertNodeToHead(cordinate point , SnakeBody* head);

//This function get every directions from the user , 
//and diagnoses each one , if it is compatible to the game's keys .
bool correctWrongKB(char direction );

//This function release the nodes that was part of the snake in the board .
//By this function those nods does not takes a lot of spaces in the memory .
void freeSnake(SnakeBody * head);

//This function decide when the game is over :
//1.When the snake collide the borders .
//2.When the snake collide himself .
//3.When the snake collide himself by going in the opposite direction than he did before .
bool gameOver(cordinate point , char direction , char prevDirection , SnakeBody * head);

//This fancion comper the cordinate of the head every moment of the game ,
//with cordinates of the body .
//If he findes two parts of the snake's body in the same cordinate ,
//he send it to the "GameOver" function .
bool isCordinateIsSame(cordinate point, SnakeBody* head);

//this funcion initialize the the board , and peint it again.
// Than it print a sign than te game is over .
void printGameOver(bool res);


int main()
{
	cordinate point;
	point.x = ROWS / 2;
	point.y = COLS / 2;
	bool res = true;
	float sec = 1;
	char direction ='d';
	char prevDirection = 'd';
	int counter = 1 , interaction = 1;
	init();
	printBoard();
	SnakeBody * head = createNewNode(point, NULL);
	printSnake(head);
	while (res)/*gameOver*/
	{
		sleep(sec);
		prevDirection = direction;
		if (_kbhit())//This fanction decide if there was a push on a key so it tells the direction that the user wants .
		{
			direction = _getch(); //This fanction insert the same keys that wans push to the "direction" , so it check if the insert was compatible with the same's keys .
			if (!correctWrongKB(direction))
				direction = prevDirection;
		}
		point = snakeMovment(direction, point);
		SnakeBody * newHead = createNewNode(point, head);
		head = newHead;
		if (counter < 5)
			deleteNodeFromSnake(head);
		if (counter == 5 && sec >= (0.01))
		{
			sec = sec - 0.03;
			counter = 0;
		}
		counter++;
		interaction++;
		if (interaction >= 5)
			res = gameOver(point, direction, prevDirection, head);
		gotoxy(ROWS + 1, 1);
	}
	freeSnake(head);
	printGameOver(res);
	system("pause");
}

// Turn escape codes ON.
void init(void) {
	system("cls");
}

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y) {
	printf("\x1b[%d;%df", x, y);
}

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs) {
	clock_t clocks_start = clock();

	while (clock() - clocks_start < secs*CLOCKS_PER_SEC)
		;
}

void printBoard()
{
	int i = 0;
	int j = 0;

	while (i <= 25)
	{
		gotoxy(i, 0);
		printf("#");
		gotoxy(i, 75);
		printf("#");
		i++;
	}
	while (j <= 75)
	{
		gotoxy(0, j);
		printf("#");
		gotoxy(25, j);
		printf("#");
		j++;
	}
}

SnakeBody* createNewNode(cordinate point , SnakeBody* next)
{
	SnakeBody* node = (SnakeBody*)malloc(sizeof(SnakeBody));

	node->point = point;
	node->next = next;
	gotoxy(point.x, point.y);
	printf("@");
	return node;
}

void printSnake(SnakeBody*head)
{
	gotoxy(head->point.x, head->point.y);
	printf("@");
	head = head->next;
	gotoxy(ROWS + 1, 1);
}
	SnakeBody* insertNodeToHead(cordinate point, SnakeBody * head)
{
	SnakeBody* newHead = createNewNode( point , head);
	return newHead;
}
cordinate snakeMovment(char direction , cordinate point)
{
	switch (direction)
	{
	case 's' :
		point.x++;
		return point;
		break;
	case 'w':
		point.x--;
		return point;
		break;
	case 'd':
		point.y++;
		return point;
		break;
	case'a':
		point.y--;
		return point;
		break;
	}
}

bool correctWrongKB(char direction)
{
	if (direction == 's' || direction == 'w' || direction == 'd' || direction == 'a')
	{
		return true;
	}
	else
	{
		return false;
	}
}
void deleteNodeFromSnake(SnakeBody* head)
{
	SnakeBody* tempHead = (SnakeBody*)malloc(sizeof(SnakeBody));
	tempHead = head;
	while ( tempHead->next!= NULL &&tempHead->next->next!=NULL)
	{
		tempHead = tempHead->next;
	}
	gotoxy(tempHead->next->point.x, tempHead->next->point.y);
	printf(" "); 
	free(tempHead->next);
	tempHead->next = NULL;
}
bool gameOver(cordinate point, char direction, char prevDirection , SnakeBody * head)
{

	if (point.x == 0 || point.x == 25 || point.y == 0 || point.y == 75)
		return false;
	else if (direction == 'w'&& prevDirection == 's')
		return false;
	else if (direction == 's'&& prevDirection == 'w')
		return false;
	else if (direction == 'a'&& prevDirection == 'd')
		return false;
	else if (direction == 'd'&& prevDirection == 'a')
		return false;
	else if (isCordinateIsSame(point, head))
		return false;
	else
		return true;
}
void printGameOver(bool res)
{
	if (res == false)
	{
		init();
		printBoard();
		gotoxy(ROWS / 2, (COLS / 2)-4);
		printf("Game Over");
		gotoxy(ROWS + 1, 1);
	}
}
bool isCordinateIsSame(cordinate point , SnakeBody * head)
{
	SnakeBody* current;
	current = head ->next;
	while (current != NULL)
	{
		if ((head->point.x) == (current->point.x) && (head->point.y) == (current->point.y))
		{
			return true;
		}
		current = current->next;
	}
	return false ;
}
void freeSnake(SnakeBody * head)
{
	SnakeBody * current;
	while (head != NULL)
	{
		current = head->next;
		free(head);
		head = current;
	}
}
