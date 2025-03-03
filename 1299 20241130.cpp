#include <iostream>
#include <vector>
#include <algorithm>
const long long int MAX = 0x7FFFFFFFFFFFFFFF;
using namespace std;
struct Node{
    long long int x;
    long long int y;
};
bool cmp(Node &a, Node &b) {
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
}
long long int distance2 (Node &a, Node &b) {
    long long int distance_x2 = (a.x - b.x) * (a.x - b.x);
    //cout << "横坐标之差" << a.x - b.x << endl;
    long long int distance_y2 = (a.y - b.y) * (a.y - b.y);
    //cout << "纵坐标之差" << a.y - b.y << endl;
    return distance_x2 + distance_y2;
}
long long int minimum_distance(int l, int r, vector<Node> &node) {
    long long int distance = MAX;
    if(l >= r)
        return distance;
    if(l == r - 1)
        return distance2(node[l], node[r]);
    int mid = l + (r - l) / 2;
    long long int left_distance = minimum_distance(l, mid, node);
    long long int right_distance = minimum_distance(mid, r, node);
    distance = min(left_distance, right_distance);
    vector<Node> mid_point;
    for (int i = l; i <= r; i++) {
        long long int x_distance = std::abs(node[i].x - node[mid].x);
        if((x_distance * x_distance) <= distance) {
            mid_point.push_back(node[i]);
        }
    }
    sort(mid_point.begin(), mid_point.end(), [](const Node &a, const Node &b) {
        return a.y < b.y;
    });
    for (int i = 0; i < mid_point.size(); i++) {
        for (int j = i + 1; j < mid_point.size(); j++) {
            long long int y_distance = std::abs(mid_point[i].y - mid_point[j].y);
            if((y_distance * y_distance) <= distance) {
                long long int temp_distance = distance2(mid_point[i], mid_point[j]);
                distance = min(distance, temp_distance);
            }else
                break;
        }
    }
    return distance;
}
int main() {
    int n;
    scanf("%d", &n);
    vector<Node> node(n);
    for (int i = 0; i < n; i++)
        scanf("%lld%lld", &node[i].x, &node[i].y);
    sort(node.begin(), node.end(), cmp);
    printf("%lld\n", minimum_distance(0, n - 1, node));
    return 0;
}