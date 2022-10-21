#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// classic tic tac toe game with AI

char boardmatrix[][3] = {
	32, 32, 32,
	32, 32, 32,
	32, 32, 32
};

// global board
bool playerwon = false, aiwon = false;
// win flags

bool displayBoard();
void getPlayerMove();
void checkWinner();
void getAIMove();
// game over when no cell is free
// invalid move ends game
// 8 possible checks
// careful AI

int main(int argc, char *argv[])
{
	do
	{
		getPlayerMove(); 
		checkWinner();
		if (playerwon)
		{
			displayBoard();
			puts("You won!");
			return 0;
		}
			if (!displayBoard())
			break;

		getAIMove();
		checkWinner();
		if (aiwon)
		{
			displayBoard();
			puts("You lose!");
			return 0;
		}
		if (!displayBoard())
			break;
	}
	while (true);
	// in each move board is checked then
	// winner
	return 0;
}

bool displayBoard() // TODO: require improvement
{
	for (int line = 0, i = 0; line < 6; line++)
	{
		if (line % 2 == 0)
		{
			for (int dash = 1, j = 0; dash < 12; dash++)
				if (dash % 4 == 0)
					putchar('|');
				else
				{
					if (dash == 2 || dash == 6 || dash == 10)
					{
						putchar(boardmatrix[i][j]);
						j++;
						putchar(32);
						putchar(32);
						continue;
					}
					putchar(32);
					putchar(32);
				}
			i++;
		}
		else
		{
			if (line == 5)
			{
				for (int dash = 0; dash < 12; dash++)
					if (dash == 4 || dash == 8)
						putchar('|');
					else
					{
						putchar(32);
						putchar(32);
					}
				continue;
			}
			for (int dash = 1; dash < 12; dash++)
				if (dash % 4 == 0)
					putchar('|');
				else
					printf("%s", "_ ");
		}
		putchar('\n');
	}
	putchar('\n');
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (boardmatrix[i][j] == 32)
				return true;
	puts("Game Over\nNo one wins.");
	return false;
}

void getPlayerMove()
{
	int x, y;
	x = y = 0;
	printf("%s: ", "Your turn: in x y format");
	scanf("%d %d", &x, &y);
	x--, y--;
	if (boardmatrix[x][y] == 32 && x<3 && y<3)
		boardmatrix[x][y] = 'X';
	else
	{
		puts("invalid move.");
		exit(1);
	}
}

void checkWinner()
{
	for (int i = 0; i < 3; i++)
	{
		if ((boardmatrix[i][0] == 'X') || (boardmatrix[i][0] == 'O'))
			if ((boardmatrix[i][0] == boardmatrix[i][1])
				&& (boardmatrix[i][1] == boardmatrix[i][2]))
				if (boardmatrix[i][0] == 'X')
					playerwon = true;
				else
					aiwon = true;
	}

	for (int i = 0; i < 3; i++)
	{
		if ((boardmatrix[0][i] == 'X') || (boardmatrix[0][i] == 'O'))
			if ((boardmatrix[0][i] == boardmatrix[1][i])
				&& (boardmatrix[1][i] == boardmatrix[2][i]))
				if (boardmatrix[0][i] == 'X')
					playerwon = true;
				else
					aiwon = true;
	}

	if ((boardmatrix[0][0] == 'X') || (boardmatrix[0][0] == 'O'))
		if ((boardmatrix[0][0] == boardmatrix[1][1]) && (boardmatrix[1][1] == boardmatrix[2][2]))
			if (boardmatrix[0][0] == 'X')
				playerwon = true;
			else
				aiwon = true;

	if ((boardmatrix[0][2] == 'X') || (boardmatrix[0][2] == 'O'))
		if ((boardmatrix[0][2] == boardmatrix[1][1]) && (boardmatrix[1][1] == boardmatrix[2][0]))
			if (boardmatrix[0][2] == 'X')
				playerwon = true;
			else
				aiwon = true;
}

void getAIMove()
{
	for (int i = 0; i < 3; i++)
	{
		if ((boardmatrix[i][0] == 'O' & boardmatrix[i][1] == 'O')
			|| (boardmatrix[i][1] == 'O' & boardmatrix[i][2] == 'O')
			|| (boardmatrix[i][0] == 'O' & boardmatrix[i][2] == 'O'))
			for (int j = 0; j < 3; j++)
				for (int j = 0; j < 3; j++)
					if (boardmatrix[i][j] == 32)
					{
						boardmatrix[i][j] = 'O';
						return;
					}
		if ((boardmatrix[i][0] == 'X' & boardmatrix[i][1] == 'X')
			|| (boardmatrix[i][1] == 'X' & boardmatrix[i][2] == 'X')
			|| (boardmatrix[i][0] == 'X' & boardmatrix[i][2] == 'X'))
			for (int j = 0; j < 3; j++)
				if (boardmatrix[i][j] == 32)
				{
					boardmatrix[i][j] = 'O';
					return;
				}
	}

	for (int i = 0; i < 3; i++)
	{
		if ((boardmatrix[0][i] == 'O' & boardmatrix[1][i] == 'O')
			|| (boardmatrix[1][i] == 'O' & boardmatrix[2][i] == 'O')
			|| (boardmatrix[0][i] == 'O' & boardmatrix[2][i] == 'O'))
			for (int j = 0; j < 3; j++)
				if (boardmatrix[j][i] == 32)
				{
					boardmatrix[j][i] = 'O';
					return;
				}
		if ((boardmatrix[0][i] == 'X' & boardmatrix[1][i] == 'X')
			|| (boardmatrix[1][i] == 'X' & boardmatrix[2][i] == 'X')
			|| (boardmatrix[0][i] == 'X' & boardmatrix[2][i] == 'X'))
			for (int j = 0; j < 3; j++)
				if (boardmatrix[j][i] == 32)
				{
					boardmatrix[j][i] = 'O';
					return;
				}
	}

	if ((boardmatrix[0][0] == 'O' & boardmatrix[1][1] == 'O')
		|| (boardmatrix[1][1] == 'O' & boardmatrix[2][2] == 'O') || (boardmatrix[0][0] == 'O'
																	 && boardmatrix[2][2] == 'O'))
		for (int j = 0; j < 3; j++)
			if (boardmatrix[j][j] == 32)
			{
				boardmatrix[j][j] = 'O';
				return;
			}
	if ((boardmatrix[0][0] == 'X' & boardmatrix[1][1] == 'X')
		|| (boardmatrix[1][1] == 'X' & boardmatrix[2][2] == 'X') || (boardmatrix[0][0] == 'X'
																	 && boardmatrix[2][2] == 'X'))
		for (int j = 0; j < 3; j++)
			if (boardmatrix[j][j] == 32)
			{
				boardmatrix[j][j] = 'O';
				return;
			}

	if ((boardmatrix[0][2] == 'O' & boardmatrix[1][1] == 'O')
		|| (boardmatrix[1][1] == 'O' & boardmatrix[2][0] == 'O') || (boardmatrix[0][2] == 'O'
																	 && boardmatrix[2][0] == 'O'))
		for (int j = 0, i = 2; j < 3, i >= 0; j++, i--)
			if (boardmatrix[j][i] == 32)
			{
				boardmatrix[j][i] = 'O';
				return;
			}
	if ((boardmatrix[0][2] == 'X' & boardmatrix[1][1] == 'X')
		|| (boardmatrix[1][1] == 'X' & boardmatrix[2][0] == 'X') || (boardmatrix[0][2] == 'X'
																	 && boardmatrix[2][0] == 'X'))
		for (int j = 0, i = 2; j < 3, i >= 0; j++, i--)
			if (boardmatrix[j][i] == 32)
			{
				boardmatrix[j][i] = 'O';
				return;
			}

	if (boardmatrix[1][1] == 32)
	{
		boardmatrix[1][1] = 'O';
		return;
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (boardmatrix[i][j] == 32)
			{
				boardmatrix[i][j] = 'O';
				return;
			}
}
