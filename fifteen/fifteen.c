/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("\nYou win!\n\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nillegal move\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(300000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("\033[1;33m");
    printf("WELCOME TO THE GAME OF FIFTEEN!\n");
    usleep(3000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int counter_for_tiles = d * d - 1;
    
    if (d % 2 != 0)
    {
        for (int i = 0; i < d; i++) 
        {
            for (int j = 0; j < d; j++)
            {
                if (i == d - 1 && j == d - 1)
                {
                    board[i][j] = d * d;
                }
                else 
                {
                    board[i][j] = counter_for_tiles--;
                }
                
            }
        }
    }
    else 
    {
        for (int i = 0; i < d; i++) 
        {
            for (int j = 0; j < d; j++)
            {
                if (i == d - 1 && j == d - 1)
                {
                    board[i][j] = d * d;
                }
                else if (counter_for_tiles == 2)
                {
                    board[i][j] = 1;
                    counter_for_tiles--;
                }
                else if (counter_for_tiles == 1)
                {
                    board[i][j] = 2;
                }
                else
                {
                    board[i][j] = counter_for_tiles--;
                }
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // DONE
    
    printf("\n");
    
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == d * d)
            {
                printf("    ");
            }
            else 
            {
                printf("\033[1;33m");
                printf("%2i  ", board[i][j]);
            }
            if (j == d - 1) 
            {
                printf("\n\n");
            }
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // DONE

    int blank_position_x;
    int blank_position_y;
    
    int chosen_tile_x;
    int chosen_tile_y;
    
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                chosen_tile_x = i;
                chosen_tile_y = j;
            }
            if (board[i][j] == d * d)
            {
                blank_position_x = i;
                blank_position_y = j;
            }
        }
    }
    
    if ((chosen_tile_y == blank_position_y - 1 && chosen_tile_x == blank_position_x) 
        || (chosen_tile_y == blank_position_y + 1 && chosen_tile_x == blank_position_x)
        || (chosen_tile_y == blank_position_y && chosen_tile_x == blank_position_x + 1)
        || (chosen_tile_y == blank_position_y && chosen_tile_x == blank_position_x - 1))
    {
        board[blank_position_x][blank_position_y] = board[chosen_tile_x][chosen_tile_y];
        board[chosen_tile_x][chosen_tile_y] = d * d;
        return true;
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // DONE
    int counter = 0;
    
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == board[i][j + 1] - 1)
            {
                counter++;
            }
        }
    }
    
    if (counter == d * (d - 1))
    {
        return true;
    }
    
    return false;
}
