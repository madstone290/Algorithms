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


struct Path{
    int node;
    int distance;
    Path(int node, int distance){
        this->node = node;
        this->distance = distance;
    }
};

#define NODE 9
// 경로 그래프. 노드번호는 1번부터 시작. 
vector<Path> graph[NODE + 1] = {
    {  },
    { Path(2, 4), Path(8,8) }, // 1
    { Path(1, 4), Path(3,8), Path(8,11) }, // 2
    { Path(2, 8), Path(4,7), Path(6,4), Path(9,2) }, // 3
    { Path(3, 7), Path(5,9), Path(6, 14) }, // 4
    { Path(4, 9), Path(6,10) }, // 5
    { Path(3, 4), Path(4,14), Path(5, 10), Path(7,2) }, // 6
    { Path(6, 2), Path(8,1), Path(9,6) }, // 7
    { Path(1, 8), Path(2,11), Path(7, 1), Path(9, 7) }, // 8
    { Path(3, 2), Path(7,6), Path(8, 7) }, // 9
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
        // distance가 작은 순으로 정렬
        return left.distance > right.distance;
    }
};

// 노드까지 거리를 담을 우선순위 큐
priority_queue<NodeInfo, vector<NodeInfo>, comp> nodeInfoQ;

void dijkstra(int startNode);

void updateDistance(int node);

int main()
{
    cout <<  "Dijkstra Using Priority Queue With Adjacency List" << endl;
    dijkstra(1);

    for (int i = 1; i <= NODE; i++)
    {
        cout << distances[i] << endl;
    }
}

/// @brief 노드 A에 인접한 노드 B의 최단 거리를 갱신한다.
/// @param nodeA 출발 노드
void updateDistance(int nodeA)
{
    for(int i = 0 ; i < graph[nodeA].size(); i++)
    {
        int nodeB = graph[nodeA][i].node;
        int distance = graph[nodeA][i].distance;
        cout << "visiting node from: " << nodeA << " to: " << nodeB << " distance: " << distance << endl;

        int distanceToNodeB = distances[nodeA] + distance;
        if(distanceToNodeB < distances[nodeB])
        {
            distances[nodeB] = distanceToNodeB;
            nodeInfoQ.push(NodeInfo(distanceToNodeB, nodeB));
            
            cout << "update distance: " << nodeB << " value: " << distanceToNodeB << endl;
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

        cout << "next node is: " << nextNodeInfo.node << endl;

        // 노드를 방문해야 하는지는 확인. 
        // 이전에 등록된 노드까지의 거리가 큐에 등록된 거리보다 짧은 경우 방문할 필요가 없다.
        // 이전에 등록된 노드까지의 거리가 큐에 등록된 거리보다 짧다는 것은 이전에 방문한 노드임을 나타낸다.
        if(distances[nextNodeInfo.node] < nextNodeInfo.distance)
            continue;

        // 주변 노드의 거리 갱신
        updateDistance(nextNodeInfo.node);
    }
}
