//
//  main.cpp
//  TreasureHunt2
//
//  Created by Le Hoang An on 26/3/24.
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
void findGold(int x, int y, const int &m, const int &n, int **map, int *moveX, int *moveY, const int &xGold, const int &yGold, int effort, int steps, int &leastEffort, bool &firstTime, bool **visited);
void displayMap(int **map, int m, int n);
void heuristic(int *newX, int *newY, int **map, int validMoves);
int main() {
    ifstream fin;
    fin.open("map.txt");
    if (!fin.is_open())
    {
        cout << "cannot open file" << endl;
        return 0;
    }
    int m, n; fin >> m >> n;
    int **map = new int *[m];
    for (int i = 0; i < m; ++i)
    {
        map[i] = new int [n];
        for (int j = 0; j < n; ++j)
            map[i][j] = 0;
    } cout << "m: " << m << " n: " << n << endl;
    bool **visited = new bool *[m];
    for (int i = 0; i < m; ++i)
    {
        visited[i] = new bool [n];
        for (int j = 0; j < n; ++j)
            map[i][j] = false;
    }
    int numberOfRocks; fin >> numberOfRocks; cout << "number of rocks: " << numberOfRocks << endl;
    for (int i = 0; i < numberOfRocks; ++i)
    {
        int rockMass; fin >> rockMass; cout << "rockmass: " << rockMass << ": ";
        int xRock, yRock;
        fin >> xRock >> yRock; cout << xRock << " " << yRock << endl;
        map[xRock][yRock] = rockMass;
    }
    int xGold, yGold;
    fin >> xGold >> yGold;
    fin.close();
    int moveX[4] = {1, 0, -1, 0};
    int moveY[4] = {0, 1, 0, -1};
    displayMap(map, m, n);
    int x, y; printf("where do you want to start: "); cin >> x >> y;
    int leastEffort; bool firstTime = true;
    map[x][y] = 200;
    findGold(x, y, m, n, map, moveX, moveY, xGold, yGold, 0, 1, leastEffort, firstTime, visited);
    cout << leastEffort << endl;
    for (int i = 0; i < m; ++i)
        delete [] map[i];
    delete [] map;
    for (int i = 0; i < m; ++i)
        delete [] visited[i];
    delete [] visited;
    return 0;
}
void findGold(int x, int y, const int &m, const int &n, int **map, int *moveX, int *moveY, const int &xGold, const int &yGold, int effort, int steps, int &leastEffort, bool &firstTime, bool **visited)
{
    displayMap(map, m, n);
    if (x == xGold && y == yGold) {//cout << effort << endl;
        if (firstTime) {
            leastEffort = effort;
            displayMap(map, m, n);
            cout << "effort: " << effort << endl;
            return;
        } else
        {
            if (effort < leastEffort)
            {
                leastEffort = effort;
                displayMap(map, m, n);
                cout << "effort: " << effort << endl;
                return;
            }
        }
        firstTime = false;
        return;
    }
    int newX[4], newY[4]; int validMoves = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (x + moveX[i] >= 0 && x + moveX[i] < m && y + moveY[i] >= 0 && y + moveY[i] < n && map[x + moveX[i]][y + moveY[i]] < 200 &&
            !visited[x + moveX[i]][y + moveY[i]]) {
            newX[i] = x + moveX[i];
            newY[i] = y + moveY[i];
            ++validMoves;
        }
    }
    heuristic(newX, newY, map, validMoves);
    for (int i = 0; i < validMoves; ++i)
    {
        cout << "moving to " << newX[i] << " " << newY[i] << endl;
        int newEffort = effort + 1 + map[newX[i]][newY[i]];
        int temp = map[newX[i]][newY[i]];
        map[newX[i]][newY[i]] = steps + 200;
        visited[newX[i]][newY[i]] = true;
        findGold(newX[i], newY[i], m, n, map, moveX, moveY, xGold, yGold, newEffort, steps + 1, leastEffort, firstTime, visited);
        map[newX[i]][newY[i]] = temp;
        visited[newX[i]][newY[i]] = false;
    }

}
void displayMap(int **map, int m, int n)
{
    cout << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << setw(3) << map[j][i] << " ";
        }
        cout << endl;
    }
}
void heuristic(int *newX, int *newY, int **map, int validMoves)
{
    //int value[4] = {map[newX[0]][newY[0]], map[newX[1]][newY[1]], map[newX[2]][newY[2]], map[newX[3]][newY[3]]};
    for (int j = 0; j < validMoves; ++j)
    {
        for (int i = 0; i < validMoves - 1; ++i) {
            if (map[newX[i]][newY[i]] > map[newX[i + 1]][newY[i + 1]]) {
                int temp = newX[i + 1];
                newX[i + 1] = newX[i];
                newX[i] = temp;
                temp = newY[i + 1];
                newY[i + 1] = newY[i];
                newY[i] = temp;
            }
        }
    }
}