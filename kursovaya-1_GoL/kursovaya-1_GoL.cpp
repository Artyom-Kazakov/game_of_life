#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

bool World_stagnated(short** arr_start, short** arr_next, short rows, short cols) {
    for (short i = 0; i < rows; i++) {
        for (short j = 0; j < cols; j++) {
            if (arr_start[i][j] != arr_next[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Field_empty(short** arr_next, short rows, short cols) {
    for (short i = 0; i < rows; i++) {
        for (short j = 0; j < cols; j++) {
            if (arr_next[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

int isAlive(short** arr_start, short i, short j, short rows, short cols) {
    
    short alive = 0;
    
    // top left
    if (i == 0 && j == 0) {
        if (arr_start[i + 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j + 1] == 1) {
            alive += 1;
        }
    }

    // top right
    if (i == 0 && j == cols - 1) {
        if (arr_start[i + 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j - 1] == 1) {
            alive += 1;
        }
    }

    // bottom left
    if (i == rows - 1 && j == 0) {
        if (arr_start[i - 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j + 1] == 1) {
            alive += 1;
        }
    }

    // bottom right
    if (i == rows - 1 && j == cols - 1) {
        if (arr_start[i - 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j - 1] == 1) {
            alive += 1;
        }
    }

    // left
    if ((i > 0 && i < rows - 1) && j == 0) {
        if (arr_start[i - 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j] == 1) {
            alive += 1;
        }
    }

    // right
    if ((i > 0 && i < rows - 1) && j == cols - 1) {
        if (arr_start[i - 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j] == 1) {
            alive += 1;
        }
    }

    // top
    if (i == 0 && (j > 0 && j < cols - 1)) {
        if (arr_start[i][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j + 1] == 1) {
            alive += 1;
        }
    }

    // bottom
    if (i == rows - 1 && (j > 0 && j < cols - 1)) {
        if (arr_start[i][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j + 1] == 1) {
            alive += 1;
        }
    }

    // center
    if ((i > 0 && i < rows - 1) && (j > 0 && j < cols - 1)) {
        if (arr_start[i - 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i - 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j + 1] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j] == 1) {
            alive += 1;
        }
        if (arr_start[i + 1][j - 1] == 1) {
            alive += 1;
        }
        if (arr_start[i][j - 1] == 1) {
            alive += 1;
        }
    }

    // logic 
    if (arr_start[i][j] == 1 && (alive == 2 || alive == 3)) {
        return 1;
    }
    if (arr_start[i][j] == 0 && alive == 3) {
        return 1;
    }
    else return 0;
}

int main() {
    // reading the initital
    std::ifstream initial("initial.txt");
    short rows = 0;
    short cols = 0;
    initial >> rows >> cols;

    // arr_start creation + initialization
    short** arr_start = new short* [rows];
    for (short i = 0; i < rows; i++) {
        arr_start[i] = new short[cols]();
    }

    while (!initial.eof()) {
        short i_tmp = 0;
        short j_tmp = 0;
        initial >> i_tmp >> j_tmp;
        for (short i = 0; i < rows; i++) {
            for (short j = 0; j < cols; j++) {
                if (i == i_tmp && j == j_tmp) {
                    arr_start[i][j] = 1;
				}
			}
		}
	}
    short generation_count = 1;
    short alive_cells_count = 0;

	// print arr
	for (short i = 0; i < rows; i++) {
		for (short j = 0; j < cols; j++) {
            if (arr_start[i][j] == 0) {
                std::cout << " - ";
            }
            else {
                std::cout << " # ";
                alive_cells_count++;
            }
        }
        std::cout << std::endl;
    }

    // arr_next creation
    short** arr_next = new short* [rows];
    for (short i = 0; i < rows; i++) {
        arr_next[i] = new short[cols]();
    }
   
    std::cout << "Generation: " << generation_count << ". Alive cells: " << alive_cells_count;

    std::cout << "\n\n";
    Sleep(2000);
    std::system("cls");
    
    while(true) {
        for (short i = 0; i < rows; i++) {
            for (short j = 0; j < cols; j++) {
                arr_next[i][j] = isAlive(arr_start, i, j, rows, cols);
            }
        }
        alive_cells_count = 0;
        // arr_next print
        for (short i = 0; i < rows; i++) {
            for (short j = 0; j < cols; j++) {
                if (arr_next[i][j] == 0) {
                    std::cout << " - ";
                }
                else {
                    std::cout << " # ";
                    alive_cells_count++;
                }
            }
            std::cout << std::endl;
        }
        generation_count++;
        std::cout << "\nGeneration: " << generation_count << ". Alive cells: " << alive_cells_count;;

        if (Field_empty(arr_next, rows, cols) == true) {
            std::cout << "\n\nWorld is dead.\n";
            break;
        }
        if (World_stagnated(arr_start, arr_next, rows, cols) == true) {
            std::cout << "\n\nWorld stagnated.\n";
            break;
        }

        // arr_next -> arr_start
        for (short i = 0; i < rows; i++) {
            for (short j = 0; j < cols; j++) {
                arr_start[i][j] = arr_next[i][j];
            }
            std::cout << std::endl;
        }
        //Sleep(100);
        std::system("cls");
        
    } 
    // close + delete
	initial.close();
	for (short i = 0; i < rows; i++) {
		delete[] arr_start[i];
	}
	delete[] arr_start;
	for (short i = 0; i < rows; i++) {
		delete[] arr_next[i];
	}
	delete[] arr_next;
}