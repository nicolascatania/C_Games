#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 3
#define COLS 3


void initializeBoard(char board[ROWS][COLS]);
void showBoard(char board[ROWS][COLS]);
void getMove(char board[ROWS][COLS], int* x, int* y);
int checkBoard(char board[ROWS][COLS]);


int main()
{
    char board[ROWS][COLS];
    int turn=0,x,y, win =0;

    int p1_wins=0, p2_wins=0;
    char c[]= {'x','o'};


    initializeBoard(board);
    while(1)
    {

        puts("Select x as -1 to exit game.");

        if(!turn)
        {
            puts("Player one plays (x).");
        }
        else
        {
            puts("Player two plays(o).");
        }
        getMove(board, &x,&y);

        if(x==-1)
        {
            system("cls");
            puts("GAME ENDED.");
            printf("\nVictories:\nP1:%d P2:%d\n", p1_wins, p2_wins);
            break;
        }

        board[x][y] = c[turn];

        turn = !turn;
        system("cls");

        showBoard(board);
        win = checkBoard(board);

        switch(win)
        {
        case 1:
            p1_wins++;
            printf("Player 1 wins!\n");
            printf("\nVictories:\nP1:%d P2:%d\n", p1_wins, p2_wins);
            initializeBoard(board);
            break;
        case 2:
            p2_wins++;
            printf("Player 2 wins!\n");
            printf("\nVictories:\nP1:%d P2:%d\n", p1_wins, p2_wins);
            initializeBoard(board);
            break;
        case 3:
            printf("It's a draw!\n");
            initializeBoard(board);
            break;
        case 0:
            continue;
        default:
            initializeBoard(board);
            break;
        }
    }



    return 0;
}

void initializeBoard(char board[ROWS][COLS])
{
    int i,j;
    for(i=0; i<ROWS; i++)
    {
        for(j=0; j<COLS; j++)
        {
            board[i][j]= ' ';
        }
    }

}

void showBoard(char board[ROWS][COLS])
{
    int i, j;
    puts("TIC TAC TOE GAME");
    puts("  0   1   2");
    for(i=0; i<ROWS; i++)
    {
        printf("%d ", i);
        for(j=0; j<COLS; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < COLS - 1) printf("|");
        }
        puts("");
        if (i < ROWS - 1)
        {
            puts("  ---+---+---");
        }
    }
    puts("");
}


void getMove(char board[ROWS][COLS], int* x, int* y)
{
    char input[100];
    int err = 0;

    puts("Select x & y position...");
    do {
        err = 0;
        fgets(input, sizeof(input), stdin);
        if(sscanf(input,"%d %d",x, y)==2 && *x==-1){
            puts("Game finished");
        }
        else if (sscanf(input, "%d %d", x, y) != 2 || *x < -1 || *x >= ROWS || *y < 0 || *y >= COLS) {
            puts("INVALID OPERATION");
            err = 1;

        }
        else if(board[*x][*y]!= ' '){
            puts("ALREADY OCCUPIED");
            err=1;
        }
    } while (err);
}

int checkBoard(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]))
        {
            if(board[i][0]=='x')
            {
                return 1;
            }
            else if(board[i][0]=='o')
            {
                return 2;
            }
        }
        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            if(board[0][i]=='x')
            {
                return 1;
            }
            else if(board[0][i]=='o')
            {
                return 2;
            }
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0]== 'x')
        {
            return 1;
        }
        else if (board[0][0]=='o')
        {
            return 2;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {

        if(board[0][2]=='x')
        {
            return 1;
        }
        else if (board[0][2]=='o')
        {
            return 2;
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // Game is still ongoing
            }
        }
    }
    return 3; // Draw
}

