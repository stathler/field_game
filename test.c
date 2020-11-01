#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'
#define ROWS 20
#define COLS 20

typedef struct {
    int row;
    int col;
    char current;
} cell_t;

/* Declaration of data structure */
typedef struct {
    char current;
} cell;

/* Declaration of functions */
void init_field(const int rows, const int cols, cell field[rows][cols]);
void load_glider(const int rows, const int cols, cell field[rows][cols]);
void load_semaphore(const int rows, const int cols, cell field[rows][cols]);
/* void load_random(const int rows, const int cols, cell field[rows][cols]); */
void load_custom(const int rows, const int cols, cell field[rows][cols]);

void init_world(cell field[ROWS][COLS])
{
   for(int i = 0; i < ROWS; i++)
   {
      for(int k = 0; k < COLS; k++)
      {
         if(field[i][k].current == ALIVE)
         {
            printf("%c ", ALIVE);
         }
         else
         {
            printf("%c ", DEAD);
         }
      }
      printf("\n");
   }
}

bool print_menu()
{
   char input[4];
   printf("Select one of the following options: \n");
   printf("(enter) Step \n");
   printf("(any)   Exit \n");
   fgets(input, sizeof(input), stdin);

   if(input[0] == '\n')
   {
      return true;
   }

   else
   {
      return false;
   }
}

void init_field(int n, int m, cell field[n][m])
{
    for (int r = 0 ; r < n; r++) {
        for (int c = 0 ; c < m; c++) {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ([G]lider, [S]emaphore, ");
    printf("[R]andom or [C]ustom): ");

    int ch = getchar();

    if (ch != '\n') {
        getchar();
    }

    switch (ch) {
        case 'g':
        case 'G':
            load_glider(n, m, field);
            break;
        case 's':
        case 'S':
            load_semaphore(n, m, field);
            break;
        case 'c':
        case 'C':
        default:
            load_custom(n, m, field);
    }
}


void load_glider(const int rows, const int cols,
                 cell field[rows][cols])
{
   	field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}

void load_semaphore(const int rows, const int cols,
                    cell field[rows][cols])
{
    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}

void load_custom(const int rows, const int cols,
                 cell field[rows][cols])
{
    printf("Give custom format string: ");
    do {
        int r, c;
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}

bool is_within_boundary(int row, int col)
{
    if (row < 0 || row > ROWS)
    {
        return false;
    }

    if (col < 0 || col > COLS)
    {
        return false;
    }

    return true;
}

int get_number_of_living_cells(int n, int m, cell field[ROWS][COLS])
{
    int number_of_living_cells = 0;
    for (int row = n - 1; row <= n +1; row++)
    {
        for (int col = m - 1; col <= m + 1; col++) 
        {
            if (is_within_boundary(row, col) && field[row][col].current == ALIVE)
            {
                number_of_living_cells++;
            }
        }
    }
    return number_of_living_cells;
}

int update_world(cell field[ROWS][COLS])
{
    int max_size = 9;

    cell test[ROWS][COLS];

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            test[row][col].current = field[row][col].current;
        }
    }

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            int number_of_living_neighbours = get_number_of_living_cells(row, col, test);

            if (field[row][col].current == ALIVE) {
                number_of_living_neighbours--;

                if (number_of_living_neighbours < 2) {
                    field[row][col].current =  DEAD;
                }
                else if (number_of_living_neighbours == 2) {
                    field[row][col].current = ALIVE;
                }
                else if (number_of_living_neighbours == 3) {
                    field[row][col].current = ALIVE;
                }
                else if (number_of_living_neighbours == 4) {
                    field[row][col].current = DEAD;
                }
                else if (number_of_living_neighbours > 4) {
                    field[row][col].current = DEAD;
                }
            }
            else {
                if (number_of_living_neighbours == 3) {
                    field[row][col].current = ALIVE;
                }
            }
        }
    }
    return 0;
}

int main()
{
	const int rows = ROWS;
    const int cols = COLS;
    int exit =  0;
    bool choice;

    cell field[ROWS][COLS];
    init_field(ROWS, COLS, field);

    while (exit != 1)
    {
	    init_world(field);
        
        choice = print_menu();

        if (choice == true)
        {
            update_world(field);
        }
        else if (choice == false)
        {
            exit = 1;
        }
    }
    return 0;
}



