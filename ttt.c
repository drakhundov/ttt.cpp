// TicTacToe v1.0

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

#define getrand(min, max) (min + (rand() % (max - min + 1)))

// Coordinates are 0..2 within the program.
// User input is transferred into array indices. (1 -> 0, 2 -> 1, 3 -> 2).
// Coordinates must be in "uint8_t*" format.
// The board is in "char[3][3]" format.

char board[3][3];
char sym[3] = {'x', 'o', '#'};

void init_board(char[3][3]);
void print_board(char[3][3]);
void getrandcoords(char[3][3], uint8_t *);
char gettile(char[3][3], uint8_t *);
void settile(char[3][3], uint8_t *, char);
bool coords_are_valid(uint8_t *);
bool tile_is_empty(char[3][3], uint8_t *);

int main()
{
    uint8_t *coords = (uint8_t *)malloc(2 * sizeof(uint8_t));
    char turn = 0; // 0 -- computer, 1 -- player
    srand(time(NULL));
    init_board(board);
    char player = sym[getrand(0, 1)];
    char comp = (player == sym[0]) ? sym[1] : sym[0];
    while (1) // TODO: Write a function to check if game is over.
    {
        system("clear");
        printf("Player: %c\nComputer: %c\n\n", player, comp);
        print_board(board);
        if (turn == 0)
        {
            getrandcoords(board, coords);
            settile(board, coords, comp);
            turn = 1;
        }
        else
        {
            do
            {
                printf("\nPick coordinates (row, col): ");
                scanf("%" SCNu8 " %" SCNu8, &coords[0], &coords[1]);
                coords[0] -= 1;
                coords[1] -= 1;
                if (!coords_are_valid(coords))
                {
                    puts("Selected coordinates go beyond the game board.");
                }
                else if (!tile_is_empty(board, coords))
                {
                    puts("Selected tile is not empty.");
                }
                else
                {
                    break;
                }
            } while (true);
            settile(board, coords, player);
            turn = 0;
        }
    }

    return 0;
}

void init_board(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            settile(board, (uint8_t[]){i, j}, '\0');
        }
    }
}

void print_board(char board[3][3])
{
    char tile;
    for (int i = 0; i < 3; i++)
    {
        printf("[ ");
        for (int j = 0; j < 3; j++)
        {
            tile = gettile(board, (uint8_t[]){i, j});
            if (tile == '\0')
            {
                tile = sym[2];
            }
            printf("%c ", tile);
        }
        printf("]\n");
    }
}

void getrandcoords(char board[3][3], uint8_t *coords)
{
    do
    {
        coords[0] = (uint8_t)getrand(0, 2);
        coords[1] = (uint8_t)getrand(0, 2);
    } while (!tile_is_empty(board, coords));
}

char gettile(char board[3][3], uint8_t *coords)
{
    if (coords_are_valid(coords))
    {
        return board[coords[0]][coords[1]];
    }
    return EOF;
}

void settile(char board[3][3], uint8_t *coords, char c)
{
    if (!coords_are_valid(coords))
    {
        fprintf(stderr, "Selected row and column must be between 1 and 3.");
        exit(1);
    }
    board[coords[0]][coords[1]] = c;
}

bool tile_is_empty(char board[3][3], uint8_t *coords)
{
    return coords_are_valid(coords) && board[coords[0]][coords[1]] == '\0';
}

bool coords_are_valid(uint8_t *coords)
{
    return coords[0] >= 0 && coords[0] <= 2 && coords[1] >= 0 && coords[1] <= 2;
}
