//
//  main.cpp
//  TreasureHunt2
//
//  Created by Le Hoang An on 26/3/24.
//

#include <iostream>
#include <fstream>

using namespace std;
void findGold(int x, int y, const int &m, const int &n, int **map, int *moveX, int *moveY, const int &xGold, const int &yGold, int effort, int steps, int &leastEffort, bool &firstTime);
void displayMap(int **map, int m, int n);
int main(int argc, const char * argv[]) {
    ifstream fin;
    fin.open("map.txt");
    int m, n; fin >> m >> n;
    int **map = new int *[m];
    for (int i = 0; i < m; ++i)
    {
        map[i] = new int [n];
        for (int j = 0; j < n; ++j)
            map[i][j] = 0;
    }
    int numberOfRocks; fin >> numberOfRocks;
    for (int i = 0; i < numberOfRocks; ++i)
    {
        int rockMass; fin >> rockMass;
        int xRock, yRock;
        fin >> xRock >> yRock;
        map[xRock][yRock] = rockMass;
    }
    int xGold, yGold;
    fin >> xGold >> yGold;
    fin.close();
    int moveX[4] = {1, 0, -1, 0};
    int moveY[4] = {0, 1, 0, -1};
    displayMap(map, n, n);
    int x, y; printf("where do you want to start: "); cin >> x >> y;
    int leastEffort; bool firstTime = false;
    findGold(x, y, m, n, map, moveX, moveY, xGold, yGold, 0, 0, leastEffort, firstTime);
    cout << leastEffort << endl;
    for (int i = 0; i < m; ++i)
        delete [] map[i];
    delete [] map;
    return 0;
}
void findGold(int x, int y, const int &m, const int &n, int **map, int *moveX, int *moveY, const int &xGold, const int &yGold, int effort, int steps, int &leastEffort, bool &firstTime)
{
    if (x == xGold && y == yGold)
    {
        displayMap(map, m, n);
        cout << effort << endl;
        if (firstTime)
            leastEffort = effort;
        firstTime = false;
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (x + moveX[i] >= 0 && x + moveX[i] < m && y + moveY[i] >= 0 && y + moveY[i] < n && map[x + moveX[i]][y + moveY[i]] < 200)
        {
            effort += 1 + map[x + moveX[i]][y + moveY[i]];
            int temp = map[x + moveX[i]][y + moveY[i]];
            map[x + moveX[i]][y + moveY[i]] = steps + 200;
            findGold(x + moveX[i], y + moveY[i], m, n, map, moveX, moveY, xGold, yGold, effort, steps + 1, leastEffort, firstTime);
            map[x + moveX[i]][y + moveY[i]] = temp;
        }
    }
}
void displayMap(int **map, int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}
