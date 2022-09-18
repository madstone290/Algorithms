#include <iostream>
#include <queue>

using namespace std;

#define INF 1000000000;

// #define NODE 6
// // 노드 그래프
// int graph[NODE + 1][NODE + 1] = {
//     { 0, 0, 0, 0, 0, 0, 0},
//     { 0, 0, 2, 5, 1, 0, 0},// 1번 노드
//     { 0, 2, 0, 3, 2, 0, 0},// 2번 노드
//     { 0, 5, 3, 0, 3, 1, 5},// 3번 노드
//     { 0, 1, 2, 3, 0, 1, 0},// 4번 노드
//     { 0, 0, 0, 1, 1, 0, 2},// 5번 노드
//     { 0, 0, 0, 5, 0, 2, 0},// 6번 노드
// };

#define NODE 9
int graph[NODE + 1][NODE + 1] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
    {0, 0, 4, 0, 0, 0, 0, 0, 8, 0}, // 1
    {0, 4, 0, 8, 0, 0, 0, 0, 11, 0}, // 2
    {0, 0, 8, 0, 7, 0, 4, 0, 0, 2}, //3
    {0, 0, 0, 7, 0, 9, 14, 0, 0, 0},//4
    {0, 0, 0, 0, 9, 0, 10, 0, 0, 0},//5
    {0, 0, 0, 4, 14, 10, 0, 2, 0, 0},//6
    {0, 0, 0, 0, 0, 0, 2, 0, 1, 6},//7
    {0, 8, 11, 0, 0, 0, 0, 1, 0, 7},//8
    {0, 0, 0, 2, 0, 0, 0, 6, 7, 0}//9
};

// 노드까지의 거리. ex) distance[4]: source에서 4번노드까지의 거리
int distances[NODE + 1];

// 노드까지의 거리정보
struct NodeInfo{
    int distance;
    int node;
    NodeInfo(int d, int n) 
    {
        distance = d;
        node = n;
    }
};
struct comp {
    bool operator()(NodeInfo left, NodeInfo right)
    {
        // distance 오름차순으로 정렬
        return left.distance > right.distance;
    }
};

// 노드까지 거리를 담을 우선순위 큐
priority_queue<NodeInfo, vector<NodeInfo>, comp> nodeInfoQ;

void dijkstra(int startNode);

void updateDistance(int node);

int main()
{
    cout <<  "Dijkstra Using Priority Queue With Adjacency Array" << endl;
    dijkstra(1);

    for (int i = 1; i <= NODE; i++)
    {
        cout << distances[i] << endl;
    }
}

/// @brief 주어진 노드(출발)에 인접한 노드(도착)의 최단 거리를 갱신한다.
/// @param nodeFrom 출발 노드
void updateDistance(int nodeFrom)
{
    for (int nodeTo = 1; nodeTo <= NODE; nodeTo++)
    {
        // nodeFrom-> nodeTo 의 길이 없다
        if(graph[nodeFrom][nodeTo] == 0)
            continue;;

        // 최단 거리가 발견되는 경우 갱신한다.
        int newDistance = distances[nodeFrom] + graph[nodeFrom][nodeTo];
        if (newDistance < distances[nodeTo])
        {
            distances[nodeTo] = newDistance;
            nodeInfoQ.push(NodeInfo(newDistance, nodeTo));

            cout << "update distance: " << nodeTo << " value: " << newDistance << endl;
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
    }

    // 시작노드 방문
    // 1. 거리 갱신
    distances[startNode] = 0;

    // 2. 인큐
    NodeInfo distanceInfo(0, startNode);
    nodeInfoQ.push(distanceInfo);

    // 큐 아이템이 존재하는 동안 -> 방문할 노드가 존재한다
    while(!nodeInfoQ.empty()){
        
        // 우선순위 큐의 다음 노드 확인
        NodeInfo nextNodeInfo = nodeInfoQ.top();
        nodeInfoQ.pop();

        // 노드를 방문해야 하는지는 확인. 
        // 이전에 등록된 노드까지의 거리가 큐에 등록된 거리보다 짧은 경우 방문할 필요가 없다.
        // 이전에 등록된 노드까지의 거리가 큐에 등록된 거리보다 짧다는 것은 이전에 방문한 노드임을 나타낸다.
        if(distances[nextNodeInfo.node] < nextNodeInfo.distance)
            continue;

        // 주변 노드의 거리 갱신
        updateDistance(nextNodeInfo.node);
    }
}
