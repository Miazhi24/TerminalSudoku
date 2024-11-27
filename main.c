#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Board[9][9];
int count=0;;
typedef struct {
    int x;
    int y;
}availableCoOrds;

availableCoOrds co_ords[100];

void createBoard() {
    //2D array

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Board[i][j] = 0;
        }
    }
}

void displayBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d" , Board[i][j] );
        }
        printf("\n");

    }
    //Display board
}

int checkRows() {
    for (int y = 0; y < 9; y++) {
        int sum = 0;
        for (int x = 0; x < 9; x++) {
            sum += Board[y][x];
        }
        if (sum != 45) return 0;
    }
    return 1;
}


int checkCols() {

    int solvedCols = 0;
    for (int x = 0; x < 9; x++) {
        int sum = 0;
        for (int y = 0; y < 9; y++) {
            sum = sum + Board[y][x];
        }
        if (sum == 45) {
            solvedCols++;
        }
    }
    if (solvedCols == 9) {
        return 1;
    } else {
        return 0;
    }

}

int check9th() {
    for (int sectionRow = 0; sectionRow < 3; sectionRow++) {
        for (int sectionCol = 0; sectionCol < 3; sectionCol++) {
            int sum = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    sum += Board[sectionRow * 3 + i][sectionCol * 3 + j];
                }
            }
            if (sum != 45) return 0;
        }
    }
    return 1;
}


int inArray(int arr[], int size, int num) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            return 1;
        }
    }
    return 0;
}

int isValid(int board[9][9], int row, int col, int val) {
    //check the row
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == val) {
            return 0;
        }
    }



    //check the collum
    for (int y = 0; y < 9; y++) {
        if (board[y][col] == val) {
            return 0;
        }
    }

    //check the 3x3 subgroup
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int y = startRow; y < startRow + 3; y++) {
        for (int x = startCol; x < startCol + 3; x++) {
            if (board[y][x] == val) {
                return 0;
            }
        }
    }
    return 1;
}

void populateBoard() {
    srand(time(NULL));

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            int val;
            int tries = 0;

            do {
                val = rand() % 9 + 1;
                tries++;

            } while (!isValid(Board, y, x, val) && tries < 50);

            if (tries < 50) {
                Board[y][x] = val;
            }
            else {
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        Board[i][j] = 0;
                    }
                }
                y = -1;
                break;
            }
        }

    }
}

int depopulateBoard() {

    srand(time(NULL));
    int remNum = rand() % 20 + 26;;


    while (remNum > 0) {
        int y = rand() % 9; // Random row index
        int x = rand() % 9; // Random column index

        if (Board[y][x] != 0) { // Only remove a number if the cell isn't already empty
            Board[y][x] = 0;
            co_ords[count++] = (availableCoOrds){x, y};
            remNum--; // Decrement remaining numbers to remove
        }
    }
    return count;


}

void playerTurn() {
    int x = 0;
    int y = 0;
    int num;

    printf("Enter the X\n");
    scanf("%d" , &x);
    x--;

    printf("Enter the Y\n");
    scanf("%d" , &y);
    y--;

    int temp = 0;
    for (int i = 0; i < count ; i++) {
        if (co_ords[i].x == x && co_ords[i].y == y) {
            temp++;
        }
    }
    if(temp != 0) {
        printf("Enter the a new number\n");
        scanf("%d" , &num);
        Board[y][x] = num;
    }
    else {
        printf("invalid selection\n");
        playerTurn();
    }



}


int main(void) {
    createBoard();
    populateBoard();
    int count = depopulateBoard();

    while (!(checkRows()&& checkCols() && check9th())) {
        displayBoard();
        playerTurn();
    }


    printf("solved\n");
    system("pause");
    return 0;
}
