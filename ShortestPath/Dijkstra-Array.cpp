#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define NODE 6
const int INF = 10000000;

// 노드 그래프
int graph[NODE + 1][NODE + 1] = {
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 2, 5, 1, 0, 0},// 1번 노드
    { 0, 2, 0, 3, 2, 0, 0},// 2번 노드
    { 0, 5, 3, 0, 3, 1, 5},// 3번 노드
    { 0, 1, 2, 3, 0, 1, 0},// 4번 노드
    { 0, 0, 0, 1, 1, 0, 2},// 5번 노드
    { 0, 0, 0, 5, 0, 2, 0},// 6번 노드
};

// int graph[NODE + 1][NODE + 1] = {
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
//     {0, 0, 4, 0, 0, 0, 0, 0, 8, 0}, // 1
//     {0, 4, 0, 8, 0, 0, 0, 0, 11, 0}, // 2
//     {0, 0, 8, 0, 7, 0, 4, 0, 0, 2}, //3
//     {0, 0, 0, 7, 0, 9, 14, 0, 0, 0},//4
//     {0, 0, 0, 0, 9, 0, 10, 0, 0, 0},//5
//     {0, 0, 0, 4, 14, 10, 0, 2, 0, 0},//6
//     {0, 0, 0, 0, 0, 0, 2, 0, 1, 6},//7
//     {0, 8, 11, 0, 0, 0, 0, 1, 0, 7},//8
//     {0, 0, 0, 2, 0, 0, 0, 6, 7, 0}//9
// };

// 노드까지의 거리. ex) distance[4]: source에서 4번노드까지의 거리
int distances[NODE + 1];

// 노드 방문 여부
bool visited[NODE + 1];


void dijkstra(int startNode);

int main()
{
    dijkstra(1);

    for (int i = 1; i <= NODE; i++)
    {
        cout << distances[i] << endl;
    }
}

/// @brief 방문하지 않은 노드중에서 거리가 가장 짧은 노드를 선택한다
/// @return 거리가 짧은 노드
int getShortPathNode()
{
    int shortestNode = 0;
    int minDistance = INF;

    for (int node = 1; node <= NODE; node++)
    {
        // 방문하지 않은 노드에 대해서만 진행한다.
        if (visited[node])
            continue;

        if (distances[node] < minDistance)
        {
            minDistance = distances[node];
            shortestNode = node;
        }
    }
    return shortestNode;
}

void updateDistance(int node)
{
    for (int otherNode = 1; otherNode <= NODE; otherNode++)
    {
        // 이전에 방문한 노드의 거리는 갱신할 필요가 없다.
        if (visited[otherNode])
            continue;

        // node -> other node 의 길이 없다
        if(graph[node][otherNode] == 0)
            continue;;

        // 최단 거리가 발견되는 경우 갱신한다.
        int newDistance = distances[node] + graph[node][otherNode];
        if (newDistance < distances[otherNode])
        {
            distances[otherNode] = newDistance;
            cout << "update distance: " << otherNode << " value: " << newDistance << endl;
        }
    }
}

/// @brief
/// @param source 시작 정점 번호
void dijkstra(int startNode)
{
    // 거리 및 방문여부 초기화
    for (int node = 1; node <= NODE; node++)
    {
        distances[node] = INF;
        visited[node] = false;
    }

    // 시작노드 방문
    distances[startNode] = 0;
    visited[startNode] = true;
    updateDistance(startNode);

    // 시작노드를 제외한 나머 노드에 대해 방문을 진행한다
    for (int i = 0; i < NODE - 1; i++)
    {
        int nodeToVisit = getShortPathNode();
        cout << "node to visit: " << nodeToVisit << endl;
        visited[nodeToVisit] = true;

        updateDistance(nodeToVisit);
    }
}
