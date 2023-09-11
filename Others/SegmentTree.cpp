#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{

private:
    vector<int> arr;
    vector<int> segmentTree;
    int n;
    int leftChild(int node)
    {
        return 2 * node + 1;
    }
    int rightChild(int node)
    {
        return 2 * node + 2;
    }
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            segmentTree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(leftChild(node), start, mid);
        build(rightChild(node), mid + 1, end);

        segmentTree[node] = segmentTree[leftChild(node)] + segmentTree[rightChild(node)];
    }

public:
    SegmentTree(vector<int> arr)
    {
        this->arr = arr;
        n = arr.size();
        segmentTree.resize(4 * n);
        build(0, 0, n - 1);
    }

    int query(int left, int right)
    {
        return query(0, 0, n - 1, left, right);
    }

    int query(int node, int start, int end, int left, int right)
    {
        if (right < start || end < left) // out of range
            return 0;

        if (left <= start && end <= right)
            return segmentTree[node];

        int mid = (start + end) / 2;
        int leftSum = query(leftChild(node), start, mid, left, right);
        int rightSum = query(rightChild(node), mid + 1, end, left, right);
        return leftSum + rightSum;
    }

    void update(int updateNode, int value)
    {
        int diff = value - arr[updateNode];
        arr[updateNode] = value;

        update(0, 0, n - 1, updateNode, diff);
    }

    void update(int node, int start, int end, int updateNode, int diff)
    {
        if (updateNode < start || end < updateNode)
            return;

        segmentTree[node] += diff;

        if (start == end)
            return;

        int mid = (start + end) / 2;
        update(leftChild(node), start, mid, updateNode, diff);
        update(rightChild(node), mid + 1, end, updateNode, diff);
    }

    void print()
    {
        for (int i = 0; i < segmentTree.size(); i++)
        {
            cout << segmentTree[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    vector<int> arr{1, 2, 3};
    int n = arr.size();

    SegmentTree segmentTree(arr);
    segmentTree.print();

    auto sum = segmentTree.query(1, 2);
    cout << "sum: " << sum << endl;

    segmentTree.update(1, 10);
    segmentTree.print();
}