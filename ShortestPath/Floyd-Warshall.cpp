#include <iostream>

using namespace std;

#define INF 10000000

#define NODE 4

int graph[NODE][NODE] = {
    {0,    4,    INF,  6},
    {3,    0,    7,    INF},
    {5,    INF,  0,    4},
    {INF,  INF,  2,    0},
};

int distanceMap[NODE][NODE];

void floyd_warshall();

int main()
{
    floyd_warshall();

    for (int i = 0; i < NODE; i++)
    {
        for (int j = 0; j < NODE; j++)
        {
            cout << distanceMap[i][j] << " ";
        }
        cout << endl;
    }
}

void floyd_warshall()
{
    for (int i = 0; i < NODE; i++)
    {
        for (int j = 0; j < NODE; j++)
        {
            distanceMap[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < NODE; k++)
    {
        for (int i = 0; i < NODE; i++)
        {
            for (int j = 0; j < NODE; j++)
            {
                if (distanceMap[i][k] + distanceMap[k][j] < distanceMap[i][j])
                    distanceMap[i][j] = distanceMap[i][k] + distanceMap[k][j];
            }
        }
    }
}
