#include <iostream>
#include <map>
#include <fstream>
#define R 5
#define C 5
// Stable marriage problem
// temp and tempArray vary based on how we conduct the matching (programmer side vs department side)
using namespace std;

void readFile (int p_grid[R][C], int d_grid[R][C]) {
    ifstream inFile;
    inFile.open("matching-data.txt");

    for (int i = 0; i<R; i++) {
        for (int j = 0; j<C; j++) {
            inFile >> d_grid[i][j];
        }
    }

    for (int i = 0; i<R; i++) {
        for (int j = 0; j<C; j++) {
            inFile >> p_grid[i][j];
        }
    }
}

void printGrid (int grid[R][C]) {
    for (int i = 0; i<R; i++) {
        for (int j = 0; j<C; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void printMap (map <int, int> &mymap) {
    map <int, int> :: iterator it;
    cout << endl;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        cout << "Department #" << it->first << " will get Programmer #" << it->second << endl;
    }
}

int assignEntity (int p_grid[R][C], int tempArray[], int &temp, map <int, int> &mymap) {
    for (int row = 0; row<R; row++) {
        if (p_grid[row][temp-1] == tempArray[0] || p_grid[row][temp-1] == tempArray[1]) {
            // cout << "Department #" << p_grid[row][temp-1] << " will get Programmer #" << temp << endl;
            mymap.insert(pair <int, int> (p_grid[row][temp-1], temp));
            return (p_grid[row][temp-1]);
        }
    }
    return 0;
}

bool checkEntity (int temp, map <int, int> &mymap) {
    map <int, int> :: iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        if (it->second == temp) {
            return true;
        }
    }
    return false;
}

void cleanArray (int tempArray[]) {
    for (int i = 0; i<R; i++) {
        tempArray[i] = 0;
    }
}

void findMatch (int p_grid[R][C], int d_grid[R][C], map <int, int> &mymap) {
    bool check;
    int tempArray[R];

    for (int row = 0; row<R; row++) {
        for (int col = 0; col<C; col++) {
            int common_pref = d_grid[row][col]; // programmer value to compare
            if (common_pref != -1 && !checkEntity(common_pref, mymap)) {
                int i = col; // index to compare and while loop control variable
                int j = 0; // tempArray index
                cleanArray(tempArray);
                while (i<5)
                {
                    if (common_pref == d_grid[row][i]) {
                        tempArray[j] = i+1;
                        cout << d_grid[row][i] << " ";
                        d_grid[row][i] = -1;
                        j++;
                    }
                    i++;  
                }
                // cout << endl;
                // for (int i = 0; i<R; i++) {
                //     cout << tempArray[i] << " ";
                // }
                // cout << endl;
                int entity = assignEntity(p_grid, tempArray, common_pref, mymap);
                for (int i = 0; i<R; i++) {
                    d_grid[i][entity-1] = -1; // setting the department value to -1
                }
            }
        }
    }
}


int main () {
    map <int, int> mymap; // Department to programmer
    int p_grid[R][C]; // Programmeer grid with preference
    int d_grid[R][C]; // Department grid with preference

    readFile(p_grid, d_grid);
    findMatch(p_grid, d_grid, mymap);
    printMap(mymap);

    return 0;
}

