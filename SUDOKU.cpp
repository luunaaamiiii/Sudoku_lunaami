#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

long long iterasi = 0;

bool is_valid(const vector<vector<int>>& grid, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }
    
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solve_sudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    iterasi++;
                    
                    if (is_valid(grid, row, col, num)) {
                        grid[row][col] = num;
                        
                        if (solve_sudoku(grid)) {
                            return true;
                        }
                        
                        grid[row][col] = 0; 
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void print_grid(const vector<vector<int>>& grid) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "---------------------" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> contoh1 = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    vector<vector<int>> contoh2 = {
        {0, 0, 4, 3, 0, 0, 2, 0, 9},
        {0, 0, 5, 0, 0, 9, 0, 0, 1},
        {0, 7, 0, 0, 6, 0, 0, 4, 3},
        {0, 0, 6, 0, 0, 2, 0, 8, 7},
        {1, 9, 0, 0, 0, 7, 4, 0, 0},
        {0, 5, 0, 0, 8, 3, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 1, 0, 5},
        {0, 0, 3, 5, 0, 8, 6, 9, 0},
        {0, 4, 2, 9, 1, 0, 3, 0, 0}
    };

    vector<vector<int>> contoh3 = {
        {0, 0, 4, 6, 0, 8, 9, 1, 2},
        {0, 7, 2, 0, 0, 0, 3, 4, 8},
        {1, 0, 0, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    };

    int pilihan;
    cout << "Pilih matriks Sudoku yang ingin diselesaikan (1, 2, atau 3): ";
    cin >> pilihan;

    vector<vector<int>> grid_pilihan;

    if (pilihan == 1) {
        grid_pilihan = contoh1;
    } else if (pilihan == 2) {
        grid_pilihan = contoh2;
    } else if (pilihan == 3) {
        grid_pilihan = contoh3;
    } else {
        cout << "Pilihan tidak valid. Silakan jalankan ulang program dan pilih 1, 2, atau 3." << endl;
        return 1;
    }

    iterasi = 0;
    
    auto start_time = high_resolution_clock::now();
    
    if (solve_sudoku(grid_pilihan)) {
        auto end_time = high_resolution_clock::now();
        duration<double> execution_time = end_time - start_time;
        
        cout << "\nOutput:\n" << endl;
        print_grid(grid_pilihan);
        
        cout << "\nJumlah iterasi = " << iterasi << endl;
        cout << fixed << setprecision(5);
        cout << "Waktu eksekusi = " << execution_time.count() << " detik\n";
    } else {
        cout << "\nTidak ada solusi untuk Sudoku ini.\n";
    }

    return 0;
}