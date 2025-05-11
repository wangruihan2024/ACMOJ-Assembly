#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<bool>> adj;
vector<bool> visited;
int n;
bool found = false;

void move_to(int current, int target) {
    cout << target << endl;
    cout.flush();
    
    string response;
    cin >> response;
    if (response == "FAIL") {
        exit(0);
    }
    for (int i = 1; i <= n; ++i) {
        adj[target][i] = (response[i-1] == '1');
        adj[i][target] = adj[target][i];
    }
}
void dfs(int current) {
    if (current == n) {
        cout << "yes" << endl;
        found = true;
        exit(0);
    }
    visited[current] = true;
    for (int neighbor = 1; neighbor <= n; ++neighbor) {
        if (adj[current][neighbor] && !visited[neighbor]) {
            // Move to the neighbor
            move_to(current, neighbor);   
            dfs(neighbor);
            if (found) return;
            move_to(neighbor, current);     
        }
    }
    // visited[current] = false;
}
int main() {
    cin >> n;
    string s1;
    cin >> s1;
    adj.resize(n+1, vector<bool>(n+1, false));
    visited.resize(n+1, false);
    for (int j = 1; j <= n; ++j) {
        adj[1][j] = (s1[j-1] == '1');
        adj[j][1] = adj[1][j]; 
    }
    dfs(1);
    if (!found) {
        cout << "no" << endl;
    }
    return 0;
}